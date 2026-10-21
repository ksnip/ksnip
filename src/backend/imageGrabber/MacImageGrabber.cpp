/*
 * Copyright (C) 2018 Damir Porobic <https://github.com/damirporobic>
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

#include "MacImageGrabber.h"


MacImageGrabber::MacImageGrabber(const QSharedPointer<IConfig> &config) :
    AbstractRectAreaImageGrabber(new MacSnippingArea(config), config),
    mMacWrapper(new MacWrapper)
{
    addSupportedCaptureMode(CaptureModes::RectArea);
	addSupportedCaptureMode(CaptureModes::LastRectArea);
    addSupportedCaptureMode(CaptureModes::FullScreen);
    addSupportedCaptureMode(CaptureModes::CurrentScreen);
}

QRect MacImageGrabber::fullScreenRect() const
{
    return mMacWrapper->getFullScreenRect();
}

QRect MacImageGrabber::activeWindowRect() const
{
    // Not supported for MacOs
    return {};
}

CursorDto MacImageGrabber::getCursorWithPosition() const
{
    return mMacWrapper->getCursorWithPosition();
}

/*
 * The cursor position is in points, but the editor works with the pixels of the
 * screenshot, so position and image are scaled to the ratio of the screenshot.
 */
CursorDto MacImageGrabber::getCursorRelativeToScreenshot() const
{
    auto cursor = AbstractRectAreaImageGrabber::getCursorRelativeToScreenshot();
    if (!cursor.isValid()) {
        return cursor;
    }

    auto size = QSizeF(cursor.image.size()) / cursor.image.devicePixelRatio() * mScreenshotRatio;
    auto image = cursor.image.scaled(size.toSize(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    image.setDevicePixelRatio(1.0);

    return { image, (QPointF(cursor.position) * mScreenshotRatio).toPoint() };
}

QPixmap MacImageGrabber::getScreenshot() const
{
    auto screenshot = AbstractRectAreaImageGrabber::getScreenshot();
    mScreenshotRatio = screenshot.devicePixelRatio();
    return screenshot;
}
