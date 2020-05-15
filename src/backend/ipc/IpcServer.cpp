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

#include "IpcServer.h"

IpcServer::IpcServer() :
	mLocalServer(new QLocalServer())
{
	mLocalServer->setSocketOptions(QLocalServer::WorldAccessOption);
}

IpcServer::~IpcServer()
{
	delete mLocalServer;
}

bool IpcServer::listen(const QString &name)
{
	auto hasStarted = mLocalServer->listen(name);
	connect(mLocalServer, &QLocalServer::newConnection, this, &IpcServer::newConnection);

	return hasStarted;
}

void IpcServer::newConnection()
{
	auto clientConnection = mLocalServer->nextPendingConnection();
	connect(clientConnection, &QLocalSocket::readyRead, this, &IpcServer::processData);
}

void IpcServer::processData()
{
	auto clientSocket = dynamic_cast<QLocalSocket*>(sender());
	auto data = clientSocket->readAll();
	emit received(data);
}

