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
    setWindowFlags(windowFlags() | Qt::WindowFullscreenButtonHint);
}

QRect MacSnippingArea::selectedRectArea() const
{
    return mHdpiScaler.scale(getCaptureArea());
}

void MacSnippingArea::setFullScreen()
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    setFixedSize(QDesktopWidget().size());
#else
    auto screen = QGuiApplication::primaryScreen();
    if (screen) {
        setFixedSize(screen->geometry().size());
    }
#endif
    QWidget::showFullScreen();
}

QSizeF MacSnippingArea::getSize() const
{
    return QSizeF(geometry().size());
}
