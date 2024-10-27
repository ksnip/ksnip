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

SingleInstanceServerBootstrapper::SingleInstanceServerBootstrapper(DependencyInjector *dependencyInjector) :
	StandAloneBootstrapper(dependencyInjector),
	mIpcServer(new IpcServer),
	mUsernameProvider(dependencyInjector->get<IUsernameProvider>())
{
}

SingleInstanceServerBootstrapper::~SingleInstanceServerBootstrapper()
{
	delete mIpcServer;
}

int SingleInstanceServerBootstrapper::start(const QApplication &app)
{
	startServer();
	return StandAloneBootstrapper::start(app);
}

void SingleInstanceServerBootstrapper::startServer() const
{
    mIpcServer->listen(SingleInstance::ServerName.arg(mUsernameProvider->getUsername()));
	connect(mIpcServer, &IpcServer::received, this, &SingleInstanceServerBootstrapper::processData);
}

void SingleInstanceServerBootstrapper::processData(const QByteArray &data)
{
	mLogger->log(QLatin1String("Single instance server received data from client"));
	auto parameter = mParameterTranslator.translate(data);
	switch (parameter.startupMode) {
		case SingleInstanceStartupModes::Start:
            mLogger->log(QLatin1String("Start triggered."));
			show();
			break;
		case SingleInstanceStartupModes::Edit:
            if(parameter.isImageAsByteArraySet()) {
                mLogger->log(QLatin1String("Edit triggered with image received as byte array"));
                QPixmap pixmap;
                pixmap.loadFromData(parameter.imageAsByteArray);
                mMainWindow->processCapture(CaptureDto(pixmap));
            } else {
                mLogger->log(QLatin1String("Edit triggered with image received as image path"));
                processImage(parameter.imagePath);
            }
			break;
		case SingleInstanceStartupModes::Capture:
            mLogger->log(QLatin1String("Capture triggered"));
			capture(parameter);
			break;
	}
}

void SingleInstanceServerBootstrapper::capture(const SingleInstanceParameter &parameter) const
{
	mLogger->log(QLatin1String("Single instance server was request to take screenshot"));
	mMainWindow->captureScreenshot(parameter.captureMode, parameter.captureCursor, parameter.delay);
}

void SingleInstanceServerBootstrapper::show() const
{
	mLogger->log(QLatin1String("Single instance server was request to show main window"));
	mMainWindow->show();
}

void SingleInstanceServerBootstrapper::processImage(const QString &imagePath)
{
	mLogger->log(QString("Single instance server was request to open image %1.").arg(imagePath));
	QPixmap pixmap(imagePath);
	auto captureDto = CaptureFromFileDto(pixmap, imagePath);
	mMainWindow->processCapture(captureDto);
}
