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

#include <QGuiApplication>
#include <QPainter>
#include <QScreen>


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
    // MacOs currently captures always mouse by itself
    return {};
}

/*
 * QScreen::grabWindow() returns every screen at its native resolution with the
 * device pixel ratio set. The parts are composed on a canvas with the highest
 * ratio, so the result keeps that resolution instead of one pixel per point.
 */
QPixmap MacImageGrabber::getScreenshotFromRect(const QRect &rect) const
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    return AbstractRectAreaImageGrabber::getScreenshotFromRect(rect);
#else
    struct Part { QRect area; QPixmap grabbed; };
    QList<Part> parts;
    auto ratio = 1.0;
    for (auto screen : QGuiApplication::screens()) {
        auto screenGeometry = screen->geometry();
        auto intersection = screenGeometry.intersected(rect);
        if (intersection.isEmpty()) {
            continue;
        }

        // grabWindow() expects coordinates relative to the screen
        auto source = intersection.translated(-screenGeometry.topLeft());
        auto grabbed = screen->grabWindow(0, source.x(), source.y(), source.width(), source.height());
        ratio = qMax(ratio, grabbed.devicePixelRatio());
        parts.append({ intersection, grabbed });
    }

    QPixmap composed(rect.size() * ratio);
    composed.setDevicePixelRatio(ratio);
    composed.fill(Qt::transparent);

    QPainter painter(&composed);
    for (const auto &part : parts) {
        auto target = QRectF(part.area.topLeft() - rect.topLeft(), QSizeF(part.area.size()));
        painter.drawPixmap(target, part.grabbed, QRectF(part.grabbed.rect()));
    }
    painter.end();

    return composed;
#endif
}

/*
 * mCaptureRect is in points, the background can have a higher resolution.
 */
QPixmap MacImageGrabber::getScreenshotFromBackground() const
{
    auto background = snippingAreaBackground();
    auto ratio = background.devicePixelRatio();
    QRect rectInPixels(qRound(mCaptureRect.x() * ratio), qRound(mCaptureRect.y() * ratio),
                       qRound(mCaptureRect.width() * ratio), qRound(mCaptureRect.height() * ratio));
    return background.copy(rectInPixels);
}

QPixmap MacImageGrabber::getScreenshot() const
{
    auto screenshot = AbstractRectAreaImageGrabber::getScreenshot();
    // The editor and the save operations expect the pixel size of the image, so it must not be scaled by the ratio
    screenshot.setDevicePixelRatio(1.0);
    return screenshot;
}
