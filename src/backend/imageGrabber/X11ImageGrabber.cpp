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

X11ImageGrabber::X11ImageGrabber() : AbstractImageGrabber(new LinuxSnippingArea),
    mX11Wrapper(new X11Wrapper)
{
    mSupportedCaptureModes.append(CaptureModes::RectArea);
    mSupportedCaptureModes.append(CaptureModes::FullScreen);
    mSupportedCaptureModes.append(CaptureModes::CurrentScreen);
    mSupportedCaptureModes.append(CaptureModes::ActiveWindow);
}

X11ImageGrabber::~X11ImageGrabber()
{
    delete mX11Wrapper;
}

void X11ImageGrabber::grabImage(CaptureModes captureMode, bool captureCursor, int delay)
{
	mCaptureCursor = captureCursor;
    mCaptureDelay = delay;

    if (isCaptureModeSupported(captureMode)) {
        mCaptureMode = captureMode;
    } else {
        qWarning("Unsupported Capture Mode selected, falling back to full screen.");
        mCaptureMode = CaptureModes::FullScreen;
    }


    if (mCaptureMode == CaptureModes::RectArea) {
        getRectArea();
    } else {
        QTimer::singleShot(mCaptureDelay, this, &X11ImageGrabber::grab);
    }
}

void X11ImageGrabber::getRectArea()
{
    if (mX11Wrapper->isCompositorActive()) {
        openSnippingArea();
    } else {
        auto screenRect = mX11Wrapper->getFullScreenRect();
        auto background = createPixmap(screenRect);
        openSnippingAreaWithBackground(background);
    }
}

void X11ImageGrabber::setRectFromCorrectSource()
{
    if (mCaptureMode == CaptureModes::RectArea) {
        mCaptureRect = selectedSnippingAreaRect();
    } else if (mCaptureMode == CaptureModes::FullScreen) {
        mCaptureRect = mX11Wrapper->getFullScreenRect();
    } else if (mCaptureMode == CaptureModes::CurrentScreen) {
	    mCaptureRect = currentScreenRect();
    } else if (mCaptureMode == CaptureModes::ActiveWindow) {
        mCaptureRect = mX11Wrapper->getActiveWindowRect();
        if (mCaptureRect.isNull()) {
            qWarning("ImageGrabber::getActiveWindow: Found no window with focus.");
	        mCaptureRect = currentScreenRect();
        }
    }
}

void X11ImageGrabber::grab()
{
    setRectFromCorrectSource();
    auto screenShot = createPixmap(mCaptureRect);

    if (mCaptureCursor) {
        screenShot = mX11Wrapper->blendCursorImage(screenShot, mCaptureRect);
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
