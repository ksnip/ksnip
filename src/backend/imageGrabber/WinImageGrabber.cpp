/*
 * Copyright (C) 2018 Damir Porobic <https://github.com/damirporobic>
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
 */

#include "WinImageGrabber.h"

WinImageGrabber::WinImageGrabber() : AbstractImageGrabber(new WinSnippingArea),
    mWinWrapper(new WinWrapper)
{
    mSupportedCaptureModes.append(CaptureModes::RectArea);
    mSupportedCaptureModes.append(CaptureModes::FullScreen);
    mSupportedCaptureModes.append(CaptureModes::ActiveWindow);
    mSupportedCaptureModes.append(CaptureModes::CurrentScreen);
}

void WinImageGrabber::grabImage(CaptureModes captureMode, bool captureCursor, int delay)
{
    Q_ASSERT(isCaptureModeSupported(captureMode));

    mCaptureMode = captureMode;
    mCaptureCursor = captureCursor;
    mCaptureDelay = delay;

    if (mCaptureMode == CaptureModes::RectArea) {
        openSnippingArea();
    } else {
        QTimer::singleShot(mCaptureDelay, this, &WinImageGrabber::grab);
    }
}

void WinImageGrabber::setRectFromCorrectSource()
{
    switch (mCaptureMode) {
        case CaptureModes::RectArea:
            mCaptureRect = selectedSnippingAreaRect();
            break;
        case CaptureModes::FullScreen:
            mCaptureRect = mWinWrapper->getFullScreenRect();
            break;
        case CaptureModes::ActiveWindow:
            mCaptureRect = mWinWrapper->getActiveWindowRect();
            break;
        case CaptureModes::CurrentScreen:
            mCaptureRect = currentScreenRect();
            break;
    }
}

void WinImageGrabber::grab()
{
    setRectFromCorrectSource();
    auto pixmap = grabPixmap();

    if(mCaptureCursor) {
        pixmap = mWinWrapper->blendCursorImage(pixmap, mCaptureRect);
    }

    emit finished(pixmap);
}

QPixmap WinImageGrabber::grabPixmap() const
{
    auto screen = QGuiApplication::primaryScreen();
    auto pixmap = screen->grabWindow(QApplication::desktop()->winId(),
                                     mCaptureRect.left(),
                                     mCaptureRect.top(),
                                     mCaptureRect.width(),
                                     mCaptureRect.height());

    return pixmap;
}
