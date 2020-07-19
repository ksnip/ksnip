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

#include "WidgetHiderFactory.h"

WidgetHider *WidgetHiderFactory::create(QWidget *widget)
{
#if defined(__APPLE__) || defined(_WIN32)
	return new WidgetHider(widget);
#endif

#if defined(__linux__)
	auto platformChecker = PlatformChecker::instance();
	if (platformChecker->isWayland() && platformChecker->isGnome()) {
		return new GnomeWaylandWidgetHider(widget);
	} else {
		return new WidgetHider(widget);
	}
#endif
}
