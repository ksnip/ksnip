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

#include "EnumTranslator.h"

EnumTranslator *EnumTranslator::instance()
{
	static EnumTranslator instance;
	return &instance;
}

QString EnumTranslator::toString(CaptureModes captureMode) const
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
