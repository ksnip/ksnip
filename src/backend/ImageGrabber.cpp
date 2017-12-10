/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#include "ImageGrabber.h"

#include "src/gui/MainWindow.h"
#include "src/gui/SnippingArea.h"
#include "src/helper/X11GraphicsHelper.h"

ImageGrabber::ImageGrabber(MainWindow* parent) : QObject(), mParent(parent)
{
    mSnippingArea = nullptr;
}

ImageGrabber::~ImageGrabber()
{
    delete mSnippingArea;
}

//
// Public Functions
//

void ImageGrabber::grabImage(CaptureMode captureMode, bool capureCursor, int delay)
{
    mCaptureCursor = capureCursor;
    mCaptureDelay = (delay < 0) ? 0 : delay;
    mCaptureMode = captureMode;

    if (mCaptureMode == RectArea) {
        openSnippingArea();
    } else {
        QTimer::singleShot(getDelay(), this, &ImageGrabber::grabRect);
    }
}

void ImageGrabber::openSnippingArea()
{
    initSnippingAreaIfRequired();

    if (X11GraphicsHelper::isCompositorActive()) {
        mSnippingArea->showWithoutBackground();
    } else {
        auto screenRect = X11GraphicsHelper::getFullScreenRect();
        auto background = createPixmap(screenRect);
        mSnippingArea->showWithBackground(background);
    }
}

void ImageGrabber::initSnippingAreaIfRequired()
{
    if (!mSnippingArea) {
        mSnippingArea = new SnippingArea(mParent);
        connect(mSnippingArea, &SnippingArea::finished, [this]() {
            QTimer::singleShot(getDelay(), this, &ImageGrabber::grabRect);
        });
        connect(mSnippingArea, &SnippingArea::canceled, [this]() {
            emit canceled();
        });
    }
}

/*
 * Returns delay in msec. On the user chosen delay we add a default delay of 200
 * msec so the mainwindow has enough time to hide before we take screenshot.
 * When we run CLI mode we don't need this buffer as the mainwindow is not shown
 */
int ImageGrabber::getDelay() const
{
    if (mParent->getMode() == MainWindow::CLI || mCaptureDelay >= mMinCaptureDelay) {
        return mCaptureDelay;
    }
    return mCaptureDelay + 200;
}

void ImageGrabber::setRectFromCorrectSource()
{
    if (mCaptureMode == RectArea) {
        mCaptureRect = mSnippingArea->selectedRectArea();
    } else if (mCaptureMode == FullScreen) {
        mCaptureRect = X11GraphicsHelper::getFullScreenRect();
    } else if (mCaptureMode == CurrentScreen) {
        mCaptureRect = currectScreenRect();
    } else if (mCaptureMode == ActiveWindow) {
        mCaptureRect = X11GraphicsHelper::getActiveWindowRect();
        if (mCaptureRect.isNull()) {
            qWarning("ImageGrabber::getActiveWindow: Found no window with focus.");
            mCaptureRect = currectScreenRect();
        }
    }
}

/*
 * Returns the rect of the screen where the mouse cursor is currently located
 */
QRect ImageGrabber::currectScreenRect() const
{
    auto screen = QApplication::desktop()->screenNumber(QCursor::pos());
    return QApplication::desktop()->screenGeometry(screen);
}

void ImageGrabber::grabRect()
{
    setRectFromCorrectSource();
    auto screenShot = createPixmap(mCaptureRect);

    if (mCaptureCursor) {
        screenShot = X11GraphicsHelper::blendCursorImage(screenShot, mCaptureRect);
    }
    emit finished(screenShot);
}

QPixmap ImageGrabber::createPixmap(const QRect& rect) const
{
    auto screen = QGuiApplication::primaryScreen();
    auto pixmap = screen->grabWindow(QApplication::desktop()->winId(),
                                            rect.topLeft().x(),
                                            rect.topLeft().y(),
                                            rect.width(),
                                            rect.height());
    return pixmap;
}
