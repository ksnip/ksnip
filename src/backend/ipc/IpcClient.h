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

#ifndef KSNIP_IPCCLIENT_H
#define KSNIP_IPCCLIENT_H

#include <QLocalSocket>

class IpcClient : public QObject
{
	Q_OBJECT
public:
	IpcClient();
	~IpcClient() override;
	void start();
	void send(const QByteArray &data);

private:
	QLocalSocket *mLocalSocket;
};


#endif //KSNIP_IPCCLIENT_H
