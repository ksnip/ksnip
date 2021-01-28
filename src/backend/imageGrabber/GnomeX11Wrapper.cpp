/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "GnomeX11Wrapper.h"

QRect GnomeX11Wrapper::getActiveWindowRect() const
{
	auto windowId = X11Wrapper::getActiveWindowId();
	auto windowRect = X11Wrapper::getWindowRect(windowId);

	auto frameExtents = getGtkFrameExtents(windowId);

	return windowRect.adjusted(frameExtents.left, frameExtents.top, -frameExtents.right, -frameExtents.bottom);
}

GnomeX11Wrapper::FrameExtents GnomeX11Wrapper::getGtkFrameExtents(unsigned int windowId)
{
	FrameExtents values{};
	auto connection = QX11Info::connection();
	auto atom_cookie = xcb_intern_atom(connection, 0, strlen("_GTK_FRAME_EXTENTS"), "_GTK_FRAME_EXTENTS");
	ScopedCPointer<xcb_intern_atom_reply_t> atom_reply(xcb_intern_atom_reply(connection, atom_cookie, nullptr));

	if (!atom_reply.isNull()) {
		auto cookie = xcb_get_property(connection, 0, windowId, atom_reply->atom, XCB_ATOM_CARDINAL, 0, 4);
		ScopedCPointer<xcb_get_property_reply_t> reply(xcb_get_property_reply(connection, cookie, nullptr));

		if (!reply.isNull()) {
			int length = xcb_get_property_value_length(reply.data());
			if (length != 0) {
				auto gtkFrameExtents = static_cast<uint32_t*>(xcb_get_property_value(reply.data()));
				values.left = (int)gtkFrameExtents[0];
				values.right = (int)gtkFrameExtents[1];
				values.top = (int)gtkFrameExtents[2];
				values.bottom = (int)gtkFrameExtents[3];
			}
		}
	}

	return values;
}
