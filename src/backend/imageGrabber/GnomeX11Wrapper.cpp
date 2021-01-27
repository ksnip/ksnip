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

	auto connection = QX11Info::connection();

	xcb_get_property_cookie_t cookie;
	xcb_get_property_reply_t *reply;

	xcb_intern_atom_cookie_t atomCookie = xcb_intern_atom(connection, 0, strlen("_GTK_FRAME_EXTENTS"), "_GTK_FRAME_EXTENTS");

	cookie = xcb_get_property(connection, 0, windowId, atomCookie.sequence, XCB_ATOM_CARDINAL, 0, 4);

	qDebug("Checking reply");
	if ((reply = xcb_get_property_reply(connection, cookie, nullptr))) {
		int len = xcb_get_property_value_length(reply);
		if (len == 0) {
			printf("Length zero\n");
		} else {
			printf("_GTK_FRAME_EXTENTS is %.*s\n", len, (char*)xcb_get_property_value(reply));
		}
	}
	free(reply);

	auto xpropOutput = getXpropOutput(windowId);

	auto gtkFrameExtentsLine = getGtkFrameExtentsLine(xpropOutput);
	if (gtkFrameExtentsLine.hasMatch()) {
		return getCroppedRect(windowRect, gtkFrameExtentsLine);
	}

	return windowRect;
}

QRect GnomeX11Wrapper::getCroppedRect(const QRect &windowRect, const QRegularExpressionMatch &gtkFrameExtentsLine)
{
	auto frameExtents = gtkFrameExtentsLine.captured(1).split(QLatin1String(","));
	auto left = frameExtents[0].toInt();
	auto right = frameExtents[1].toInt();
	auto top = frameExtents[2].toInt();
	auto bottom = frameExtents[3].toInt();

	return windowRect.adjusted(left, top, -right, -bottom);
}

QRegularExpressionMatch GnomeX11Wrapper::getGtkFrameExtentsLine(const QByteArray &xpropOutput)
{
	QRegularExpression regEx(QLatin1Literal("_GTK_FRAME_EXTENTS\\(CARDINAL\\) = (.*)"));
	return regEx.match(xpropOutput);
}

QByteArray GnomeX11Wrapper::getXpropOutput(xcb_window_t windowId)
{
	QStringList xpropArguments = {QLatin1String("-id"), QString::number(windowId) };
	QProcess xprop;
	xprop.start(QLatin1String("xprop"), xpropArguments);
	xprop.waitForFinished();
	return xprop.readAll();
}
