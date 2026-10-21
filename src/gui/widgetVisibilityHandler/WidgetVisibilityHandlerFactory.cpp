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

#include "WidgetVisibilityHandlerFactory.h"

#include <QGuiApplication>

WidgetVisibilityHandler *WidgetVisibilityHandlerFactory::create(QWidget *widget, const QSharedPointer<IPlatformChecker> &platformChecker)
{
#if defined(UNIX_X11)
	// The GNOME handler exists for native Wayland sessions, where a client cannot
	// activate its own window. ksnip frequently runs as an X11/XWayland client on
	// such a session (Qt defaults to the xcb platform), and there activateWindow()
	// does work, so only use the GNOME handler for a native Wayland Qt platform.
	// Otherwise an already existing editor gets raised but never takes keyboard
	// focus (see #1197).
	const bool isNativeWayland = QGuiApplication::platformName() == QLatin1String("wayland");
	if (platformChecker->isWayland() && platformChecker->isGnome() && isNativeWayland) {
		return new GnomeWaylandWidgetVisibilityHandler(widget);
	} else {
		return new WidgetVisibilityHandler(widget);
	}
#else
	return new WidgetVisibilityHandler(widget);
#endif
}
