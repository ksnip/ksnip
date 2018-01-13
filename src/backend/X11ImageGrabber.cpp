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

#include "X11ImageGrabber.h"

void X11ImageGrabber::grabImage(CaptureModes captureMode, bool capureCursor, int delay)
{
    mCaptureCursor = capureCursor;
    mCaptureDelay = delay;
    mCaptureMode = captureMode;

    if (mCaptureMode == CaptureModes::RectArea) {
        getRectArea();
    } else {
        QTimer::singleShot(mCaptureDelay, this, &X11ImageGrabber::grabRect);
    }
}

void X11ImageGrabber::getRectArea()
{
    if (X11GraphicsHelper::isCompositorActive()) {
        openSnippingArea();
    } else {
        auto screenRect = X11GraphicsHelper::getFullScreenRect();
        auto background = createPixmap(screenRect);
        openSnippingAreaWithBackground(background);
    }
}

void X11ImageGrabber::setRectFromCorrectSource()
{
    if (mCaptureMode == CaptureModes::RectArea) {
        mCaptureRect = selectedSnippingAreaRect();
    } else if (mCaptureMode == CaptureModes::FullScreen) {
        mCaptureRect = X11GraphicsHelper::getFullScreenRect();
    } else if (mCaptureMode == CaptureModes::CurrentScreen) {
        mCaptureRect = currectScreenRect();
    } else if (mCaptureMode == CaptureModes::ActiveWindow) {
        mCaptureRect = X11GraphicsHelper::getActiveWindowRect();
        if (mCaptureRect.isNull()) {
            qWarning("ImageGrabber::getActiveWindow: Found no window with focus.");
            mCaptureRect = currectScreenRect();
        }
    }
}

void X11ImageGrabber::grabRect()
{
    setRectFromCorrectSource();
    auto screenShot = createPixmap(mCaptureRect);

    if (mCaptureCursor) {
        screenShot = X11GraphicsHelper::blendCursorImage(screenShot, mCaptureRect);
    }
    emit finished(screenShot);
}

QPixmap X11ImageGrabber::createPixmap(const QRect& rect) const
{
    auto screen = QGuiApplication::primaryScreen();
    auto pixmap = screen->grabWindow(QApplication::desktop()->winId(),
                                            rect.topLeft().x(),
                                            rect.topLeft().y(),
                                            rect.width(),
                                            rect.height());
    return pixmap;
}
