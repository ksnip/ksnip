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

SingleInstanceClientBootstrapper::SingleInstanceClientBootstrapper() :
	mIpcClient(new IpcClient)
{
	mIpcClient->connectTo(SingleInstance::ServerName);
}

SingleInstanceClientBootstrapper::~SingleInstanceClientBootstrapper()
{
	delete mIpcClient;
}

int SingleInstanceClientBootstrapper::start(const QApplication &app)
{
	createImageGrabber();
	createCommandLineParser(app);

	if (isVersionRequested()) {
		return showVersion();
	} else {
		return notifyServer();
	}
}

bool SingleInstanceClientBootstrapper::isImagePathValid(const QString &imagePath) const
{
	QPixmap pixmap(imagePath);
	auto imageValid = pixmap.isNull();
	return imageValid;
}

int SingleInstanceClientBootstrapper::notifyServer() const
{
	SingleInstanceParameter parameter;
	if (isStartedWithoutArguments()) {
		parameter = SingleInstanceParameter();
	} else if (isEditRequested()) {
		auto imagePath = getImagePath();
		if (isImagePathValid(imagePath)) {
			qWarning("Unable to open image file %s.", qPrintable(imagePath));
			return 1;
		}

		parameter = SingleInstanceParameter(imagePath);
	} else {
		parameter = SingleInstanceParameter(getCaptureMode(), getSave(), getCaptureCursor(), getDelay());
	}
	mIpcClient->send(mParameterTranslator.translate(parameter));

	return 0;
}

