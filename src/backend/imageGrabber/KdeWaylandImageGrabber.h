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

#ifndef KSNIP_KDEWAYLANDIMAGEGRABBER_H
#define KSNIP_KDEWAYLANDIMAGEGRABBER_H

#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusPendingCall>
#include <QtDBus/QDBusPendingReply>
#include <QtDBus/QDBusUnixFileDescriptor>

#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <qplatformdefs.h>

#include <errno.h>

#include "AbstractImageGrabber.h"
#include "src/gui/snippingArea/LinuxSnippingArea.h"

class KdeWaylandImageGrabber : public AbstractImageGrabber
{
public:
    explicit KdeWaylandImageGrabber();

protected:
	void grab() override;

private:
    void startReadImage(int readPipe);
    template<typename T>
    void prepareDBus(const QString& mode, T mask);
    template<typename T>
    void callDBus(int writeFd, const QString& mode, T mask);
};

#endif // KSNIP_KDEWAYLANDIMAGEGRABBER_H
