/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "HdpiScaler.h"

QRect HdpiScaler::unscale(const QRect &rect) const
{
	auto factor = scaleFactor();
	return {
		static_cast<int>(rect.x() / factor),
		static_cast<int>(rect.y() / factor),
		static_cast<int>(rect.width() / factor),
		static_cast<int>(rect.height() / factor)
	};
}

QRect HdpiScaler::scale(const QRect &rect) const
{
	auto factor = scaleFactor();
	return {
		static_cast<int>(rect.x() * factor),
		static_cast<int>(rect.y() * factor),
		static_cast<int>(rect.width() * factor),
		static_cast<int>(rect.height() * factor)
	};
}

qreal HdpiScaler::scaleFactor() const
{
	auto desktopWidget = QApplication::desktop();
	
#if defined(__APPLE__)
	qDebug("DesktopWidget devicePixelRatio: %s", qPrintable(QString::number(desktopWidget->devicePixelRatio())));
	qDebug("DesktopWidget devicePixelRatioF: %s", qPrintable(QString::number(desktopWidget->devicePixelRatioF())));
	qDebug("DesktopWidget logicalDpiX: %s", qPrintable(QString::number(desktopWidget->logicalDpiX())));
	qDebug("DesktopWidget logicalDpiY: %s", qPrintable(QString::number(desktopWidget->logicalDpiY())));
	qDebug("DesktopWidget physicalDpiX: %s", qPrintable(QString::number(desktopWidget->physicalDpiX())));
	qDebug("DesktopWidget physicalDpiY: %s", qPrintable(QString::number(desktopWidget->physicalDpiY())));

    auto screen = QApplication::primaryScreen();
    qDebug("QScreen devicePixelRatio: %s", qPrintable(QString::number(screen->devicePixelRatio())));
    qDebug("QScreen logicalDotsPerInch: %s", qPrintable(QString::number(screen->logicalDotsPerInch())));
    qDebug("QScreen logicalDotsPerInchX: %s", qPrintable(QString::number(screen->logicalDotsPerInchX())));
    qDebug("QScreen logicalDotsPerInchY: %s", qPrintable(QString::number(screen->logicalDotsPerInchY())));
    qDebug("QScreen physicalDotsPerInch: %s", qPrintable(QString::number(screen->physicalDotsPerInch())));
    qDebug("QScreen physicalDotsPerInchX: %s", qPrintable(QString::number(screen->physicalDotsPerInchX())));
    qDebug("QScreen physicalDotsPerInchY: %s", qPrintable(QString::number(screen->physicalDotsPerInchY())));

    auto widget = QApplication::activeWindow();
    qDebug("Widget devicePixelRatio: %s", qPrintable(QString::number(widget->devicePixelRatio())));
    qDebug("Widget devicePixelRatioF: %s", qPrintable(QString::number(widget->devicePixelRatioF())));
    qDebug("Widget logicalDpiX: %s", qPrintable(QString::number(widget->logicalDpiX())));
    qDebug("Widget logicalDpiY: %s", qPrintable(QString::number(widget->logicalDpiY())));
    qDebug("Widget physicalDpiX: %s", qPrintable(QString::number(widget->physicalDpiX())));
    qDebug("Widget physicalDpiY: %s", qPrintable(QString::number(widget->physicalDpiY())));

	return widget->devicePixelRatio();

#endif
	
#if defined(__linux__) || defined(_WIN32)
	return desktopWidget->devicePixelRatioF();
#endif
}
