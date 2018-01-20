/*
 * Copyright (C) 2018 Damir Porobic <https://github.com/damirporobic>
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

#ifndef GNOMEWAYLANDIMAGEGRABBER_H
#define GNOMEWAYLANDIMAGEGRABBER_H

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>

#include "AbstractImageGrabber.h"

class GnomeWaylandImageGrabber : public AbstractImageGrabber
{
public:
    virtual void grabImage(CaptureModes captureMode, bool capureCursor = true, int delay = 0) override;
    virtual bool isCaptureModeSupported(CaptureModes captureMode) override;

protected:
    virtual void grab() override;


};

#endif // GNOMEWAYLANDIMAGEGRABBER_H
