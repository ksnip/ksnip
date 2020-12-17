/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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

#ifndef KSNIP_CAPTUREMODES_H
#define KSNIP_CAPTUREMODES_H

#include <QMetaType>
#include <QHash>
#include <QObject>

enum class CaptureModes
{
    RectArea,
    LastRectArea,
    FullScreen,
    CurrentScreen,
    ActiveWindow,
    WindowUnderCursor,
    Portal
};

static QString captureModeString(CaptureModes captureMode)
{
	static QHash<CaptureModes, QString> modeStringMap = {
		{CaptureModes::RectArea, QObject::tr("Rectangular Area")},
		{CaptureModes::LastRectArea,  QObject::tr("Last Rectangular Area")},
		{CaptureModes::FullScreen, QObject::tr("Full Screen (All Monitors)")},
		{CaptureModes::CurrentScreen, QObject::tr("Current Screen")},
		{CaptureModes::ActiveWindow, QObject::tr("Active Window")},
		{CaptureModes::WindowUnderCursor, QObject::tr("Window Under Cursor")},
		{CaptureModes::Portal, QObject::tr("Screenshot Portal")}
	};

	Q_ASSERT(modeStringMap.contains(captureMode));
	return modeStringMap.value(captureMode);
}

inline uint qHash(const CaptureModes captureMode, uint seed) {
	return qHash(static_cast<int>(captureMode), seed);
}

Q_DECLARE_METATYPE(CaptureModes)

#endif // KSNIP_CAPTUREMODES_H
