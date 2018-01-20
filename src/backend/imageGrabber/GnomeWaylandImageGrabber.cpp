/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "GnomeWaylandImageGrabber.h"

void GnomeWaylandImageGrabber::grabImage(CaptureModes captureMode, bool capureCursor, int delay)
{
    mCaptureMode = captureMode;
    mCaptureCursor = capureCursor;

    qCritical("Called grabImage on GnomeWaylandImageGrabber.");

    grab();
}

void GnomeWaylandImageGrabber::grab()
{
    if (!QDBusConnection::sessionBus().isConnected()) {
        qCritical("Cannot connect to the D-Bus session bus.");
        return;
    }

    QDBusInterface dbusInterface("org.gnome.Shell.Screenshot", "/org/gnome/Shell/Screenshot", "org.gnome.Shell.Screenshot", QDBusConnection::sessionBus());
    if (dbusInterface.isValid()) {
        QDBusReply<double> reply = dbusInterface.call("ScreenshotWindow", 200, 200, true);
        if (reply.isValid()) {
            printf("Reply from multiply was: %e", reply.value());
        } else {
            qCritical("Call to multiply failed:" + reply.error().message().toLatin1());
            return;
        }
    } else {
        qCritical("Dbus Interface not valid.");
    }

    qCritical("No D-Bus interface found!");
    return;
}

bool GnomeWaylandImageGrabber::isCaptureModeSupported(CaptureModes captureMode)
{
    return true;
}
