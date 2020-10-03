/*
 * Copyright (C) 2017 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "AbstractImageGrabber.h"

AbstractImageGrabber::AbstractImageGrabber() :
    mConfig(KsnipConfigProvider::instance()),
    mIsCaptureCursorEnabled(false),
    mCaptureDelay(0),
    mCaptureMode(CaptureModes::FullScreen)
{
}

bool AbstractImageGrabber::isCaptureModeSupported(CaptureModes captureMode) const
{
    return mSupportedCaptureModes.contains(captureMode);
}

QList<CaptureModes> AbstractImageGrabber::supportedCaptureModes() const
{
    return mSupportedCaptureModes;
}

void AbstractImageGrabber::grabImage(CaptureModes captureMode, bool captureCursor, int delay)
{
    setIsCaptureCursorEnabled(captureCursor);
    setCaptureDelay(delay);
    setCaptureMode(captureMode);

    QTimer::singleShot(captureDelay(), this, &AbstractImageGrabber::grab);
}

void AbstractImageGrabber::addSupportedCaptureMode(CaptureModes captureMode)
{
    mSupportedCaptureModes.append(captureMode);
}

void AbstractImageGrabber::setCaptureDelay(int delay)
{
    mCaptureDelay = mDelayHandler.getDelay(delay);
}

int AbstractImageGrabber::captureDelay() const
{
    return mCaptureDelay;
}

CaptureModes AbstractImageGrabber::captureMode() const
{
    return mCaptureMode;
}

void AbstractImageGrabber::setCaptureMode(CaptureModes captureMode)
{
    if (isCaptureModeSupported(captureMode)) {
        mCaptureMode = captureMode;
    } else {
        qWarning("Unsupported Capture Mode selected, falling back to full screen.");
        mCaptureMode = CaptureModes::FullScreen;
    }
}

bool AbstractImageGrabber::isCaptureDelayBelowMin() const
{
    return mCaptureDelay <= mDelayHandler.minDelayInMs();
}

bool AbstractImageGrabber::isCaptureCursorEnabled() const
{
    return mIsCaptureCursorEnabled;
}

void AbstractImageGrabber::setIsCaptureCursorEnabled(bool enabled)
{
    mIsCaptureCursorEnabled = enabled;
}
