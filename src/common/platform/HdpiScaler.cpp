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
    auto myWindow = QGuiApplication::topLevelWindows().first();
    qDebug("QWindow devicePixelRatio: %s", qPrintable(QString::number(myWindow->devicePixelRatio())));

	return myWindow->devicePixelRatio();

#endif
	
#if defined(__linux__) || defined(_WIN32)
    return desktopWidget->devicePixelRatioF();
#endif
}
