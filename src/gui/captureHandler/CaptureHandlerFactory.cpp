/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "CaptureHandlerFactory.h"

ICaptureHandler* CaptureHandlerFactory::create(
		IImageAnnotator *imageAnnotator,
		QSharedPointer<INotificationService> &notificationService,
		DependencyInjector *dependencyInjector,
		QWidget *parent)
{
	auto config = dependencyInjector->get<IConfig>();

	if(config->useTabs()) {
		return new MultiCaptureHandler(
				imageAnnotator,
				notificationService,
				dependencyInjector->get<ICaptureTabStateHandler>(),
				config,
				dependencyInjector->get<IClipboard>(),
				dependencyInjector->get<IDesktopService>(),
				dependencyInjector->get<IFileService>(),
				dependencyInjector->get<IMessageBoxService>(),
				dependencyInjector->get<IRecentImageService>(),
				dependencyInjector->get<IImageSaver>(),
				dependencyInjector->get<ISavePathProvider>(),
				dependencyInjector->get<IIconLoader>(),
				dependencyInjector->get<IFileDialogService>(),
				parent);
	} else {
		return new SingleCaptureHandler(
				imageAnnotator,
				notificationService,
				dependencyInjector->get<IClipboard>(),
				dependencyInjector->get<IDesktopService>(),
				dependencyInjector->get<IFileService>(),
				dependencyInjector->get<IMessageBoxService>(),
				dependencyInjector->get<IRecentImageService>(),
				dependencyInjector->get<IImageSaver>(),
				dependencyInjector->get<ISavePathProvider>(),
				dependencyInjector->get<IFileDialogService>(),
				config,
				parent);
	}
}
