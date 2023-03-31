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

#include "SingleInstanceClientBootstrapper.h"

SingleInstanceClientBootstrapper::SingleInstanceClientBootstrapper(DependencyInjector *dependencyInjector) :
	StandAloneBootstrapper(dependencyInjector),
	mIpcClient(new IpcClient),
    mImageFromStdInputReader(dependencyInjector->get<IImageFromStdInputReader>())
{
	mIpcClient->connectTo(SingleInstance::ServerName);
}

SingleInstanceClientBootstrapper::~SingleInstanceClientBootstrapper()
{
	delete mIpcClient;
}

int SingleInstanceClientBootstrapper::start(const QApplication &app)
{
	createCommandLineParser(app);

	if (isVersionRequested()) {
		return showVersion();
	} else {
		return notifyServer();
	}
}

bool SingleInstanceClientBootstrapper::isImagePathValid(const QString &imagePath)
{
	QPixmap pixmap(imagePath);
	return !pixmap.isNull();
}

int SingleInstanceClientBootstrapper::notifyServer() const
{
	SingleInstanceParameter parameter;
	if (isStartedWithoutArguments()) {
        mLogger->log(QLatin1String("Starting without arguments"));
		parameter = SingleInstanceParameter();
	} else if (isEditRequested()) {
		auto imagePath = getImagePath();
        if (PathHelper::isPipePath(imagePath)) {
            mLogger->log(QLatin1String("Edit image from stdin"));
            auto imageAsByteArray = mImageFromStdInputReader->read();
            parameter = SingleInstanceParameter(imageAsByteArray.toBase64());
        } else if (isImagePathValid(imagePath)) {
            mLogger->log(QLatin1String("Edit image from file path"));
            parameter = SingleInstanceParameter(imagePath);
		} else {
            qWarning("Unable to open image file %s.", qPrintable(imagePath));
            return 1;
        }
	} else {
		parameter = SingleInstanceParameter(getCaptureMode(), getSave(), getSavePath(), getCaptureCursor(), getDelay());
	}
	mIpcClient->send(mParameterTranslator.translate(parameter));

	mLogger->log(QLatin1String("Notification sent to server, closing client.."));

	return 0;
}

