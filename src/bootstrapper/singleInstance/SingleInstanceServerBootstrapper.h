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

#ifndef KSNIP_SINGLEINSTANCESERVERBOOTSTRAPPER_H
#define KSNIP_SINGLEINSTANCESERVERBOOTSTRAPPER_H

#include "src/bootstrapper/StandAloneBootstrapper.h"
#include "src/bootstrapper/singleInstance/SingleInstanceConstants.h"
#include "src/bootstrapper/singleInstance/SingleInstanceParameterTranslator.h"
#include "src/backend/ipc/IpcServer.h"

class SingleInstanceServerBootstrapper : public QObject, public StandAloneBootstrapper
{
	Q_OBJECT
public:
	SingleInstanceServerBootstrapper();
	~SingleInstanceServerBootstrapper() override;
	int start(const QApplication &app) override;

private:
	IpcServer *mIpcServer;
	SingleInstanceParameterTranslator mParameterTranslator;

	void show() const;
	void processImage(const QString &imagePath);
	void capture(const SingleInstanceParameter &parameter) const;

private slots:
	void processData(const QByteArray &data);
	void startServer() const;
};

#endif //KSNIP_SINGLEINSTANCESERVERBOOTSTRAPPER_H
