/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "SingleInstanceServerBootstrapper.h"

SingleInstanceServerBootstrapper::SingleInstanceServerBootstrapper() :
	mIpcServer(new IpcServer)
{
}

SingleInstanceServerBootstrapper::~SingleInstanceServerBootstrapper()
{
	delete mIpcServer;
}

int SingleInstanceServerBootstrapper::start(const QApplication &app)
{
	mIpcServer->listen(SingleInstance::ServerName);

	QObject::connect(mIpcServer, &IpcServer::received, [](const QByteArray &data) {
		qDebug("Client sent: %s", qPrintable(data));
	});

	return StandAloneBootstrapper::start(app);
}
