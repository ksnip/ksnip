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

#include "WaylandImageGrabber.h"

WaylandImageGrabber::WaylandImageGrabber() : AbstractImageGrabber(new LinuxSnippingArea)
{
	addSupportedCaptureMode(CaptureModes::RectArea);
	addSupportedCaptureMode(CaptureModes::LastRectArea);
	addSupportedCaptureMode(CaptureModes::FullScreen);
	addSupportedCaptureMode(CaptureModes::CurrentScreen);
}

QRect WaylandImageGrabber::fullScreenRect() const
{
	return {};
}

QRect WaylandImageGrabber::activeWindowRect() const
{
	return {};
}

void WaylandImageGrabber::grab()
{
	QDBusInterface interface(QStringLiteral("org.freedesktop.portal.Screenshot"), QStringLiteral("/org/freedesktop/portal/Screenshot"), QStringLiteral("org.freedesktop.portal.Screenshot"));
	QDBusPendingReply<bool, QString> reply;

	reply = interface.asyncCall(QStringLiteral("Screenshot"), "s", "a");

	reply.waitForFinished();

	if (reply.isError()) {
		qCritical("Invalid reply from DBus: %s", qPrintable(reply.error().message()));
		emit canceled();
	} else {
		qCritical("Dbus success");
		emit canceled();
	}
}

CursorDto WaylandImageGrabber::getCursorWithPosition() const
{
	return CursorDto();
}
