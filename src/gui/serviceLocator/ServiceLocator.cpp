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

#include "ServiceLocator.h"

ServiceLocator::ServiceLocator() :
	mMessageBoxService(new MessageBoxService),
	mFileService(new FileService),
	mClipboard(new ClipboardAdapter),
	mDesktopService(new DesktopServiceAdapter),
	mRecentImageService(new RecentImagesPathStore(new ImagePathStorage))
{

}

ServiceLocator::ServiceLocator(ServiceLocator &other) :
	mMessageBoxService(new MessageBoxService),
	mFileService(new FileService),
	mClipboard(new ClipboardAdapter),
	mDesktopService(new DesktopServiceAdapter),
	mRecentImageService(new RecentImagesPathStore(new ImagePathStorage))
{

}

ServiceLocator::~ServiceLocator()
{
	delete mMessageBoxService;
	delete mFileService;
	delete mClipboard;
	delete mDesktopService;
	delete mRecentImageService;
}

IMessageBoxService* ServiceLocator::messageBoxService() const
{
	return mMessageBoxService;
}

IFileService* ServiceLocator::fileService() const
{
	return mFileService;
}

IClipboard *ServiceLocator::clipboard() const
{
	return mClipboard;
}

IDesktopService *ServiceLocator::desktopService() const
{
	return mDesktopService;
}

IRecentImageService *ServiceLocator::recentImageService() const
{
	return mRecentImageService;
}
