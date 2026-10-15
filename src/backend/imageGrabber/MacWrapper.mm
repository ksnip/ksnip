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

#include "MacWrapper.h"

#import <AppKit/AppKit.h>

#include <QCursor>
#include <QGuiApplication>
#include <QImage>
#include <QScreen>

QRect MacWrapper::getFullScreenRect() const
{
    auto mainDisplayID = CGMainDisplayID();
    auto screenWidth = (int)CGDisplayPixelsWide(mainDisplayID);
    auto screenHeight = (int)CGDisplayPixelsHigh(mainDisplayID);
    return {0, 0, screenWidth, screenHeight};
}

/*
 * Returns the current system cursor with the device pixel ratio of the screen it
 * is on, and the position of its top left corner in global coordinates (in points).
 */
CursorDto MacWrapper::getCursorWithPosition() const
{
    auto cursor = [NSCursor currentSystemCursor];
    if (cursor == nil || cursor.image == nil) {
        return {};
    }

    auto position = QCursor::pos();
    auto screen = QGuiApplication::screenAt(position);
    auto ratio = screen != nullptr ? screen->devicePixelRatio() : 1.0;

    // Draw the cursor at the resolution of the screen, the image can have several representations
    auto size = cursor.image.size;
    auto width = qRound(size.width * ratio);
    auto height = qRound(size.height * ratio);
    QImage image(width, height, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);

    auto colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceSRGB);
    auto context = CGBitmapContextCreate(image.bits(), width, height, 8, image.bytesPerLine(), colorSpace,
                                         kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Host);
    CGColorSpaceRelease(colorSpace);
    if (context == nullptr) {
        return {};
    }
    CGContextScaleCTM(context, ratio, ratio);
    [NSGraphicsContext saveGraphicsState];
    NSGraphicsContext.currentContext = [NSGraphicsContext graphicsContextWithCGContext:context flipped:NO];
    [cursor.image drawInRect:NSMakeRect(0, 0, size.width, size.height)];
    [NSGraphicsContext restoreGraphicsState];
    CGContextRelease(context);
    image.setDevicePixelRatio(ratio);

    // The hot spot is in the flipped coordinate system of the image, so it is relative to the top left corner
    auto hotSpot = cursor.hotSpot;
    position -= QPoint(qRound(hotSpot.x), qRound(hotSpot.y));

    return { QPixmap::fromImage(image), position };
}
