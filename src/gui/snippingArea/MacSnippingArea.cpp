/*
 * Copyright (C) 2019 Damir Porobic <https://github.com/damirporobic>
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

#include "MacSnippingArea.h"
#include <QtGlobal>
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <QDesktopWidget>
#else
#include <QGuiApplication>
#include <QScreen>
#endif

MacSnippingArea::MacSnippingArea(const QSharedPointer<IConfig> &config) : AbstractSnippingArea(config)
{
}

QRect MacSnippingArea::selectedRectArea() const
{
    auto captureArea = getCaptureArea();
    if (!isBackgroundTransparent() && width() > 0) {
        // Scale by the real ratio between the frozen background and the window, since the
        // background is not guaranteed to be captured at the screen's devicePixelRatio.
        auto factor = static_cast<qreal>(background().width()) / width();
        return {
            static_cast<int>(captureArea.x() * factor),
            static_cast<int>(captureArea.y() * factor),
            static_cast<int>(captureArea.width() * factor),
            static_cast<int>(captureArea.height() * factor)
        };
    }
    return mHdpiScaler.scale(captureArea);
}

void MacSnippingArea::setFullScreen()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    setFixedSize(QDesktopWidget().size());
#else
    auto screen = QGuiApplication::primaryScreen();
    if (screen) {
        setFixedSize(screen->geometry().size());
        // Native full screen mode places the window below the menu bar, which offsets
        // the snipping area from the frozen background, so cover the screen manually.
        move(screen->geometry().topLeft());
    }
#endif
    QWidget::show();
}

QSizeF MacSnippingArea::getSize() const
{
    return QSizeF(geometry().size());
}
