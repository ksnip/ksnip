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

#include "ServiceLocatorMock.h"

ServiceLocatorMock::ServiceLocatorMock() :
	mMessageBoxServiceMock(new MessageBoxServiceMock),
	mFileServiceMock(new FileServiceMock),
	mClipboardMock(new ClipboardMock),
	mDesktopServiceMock(new DesktopServiceMock),
	mRecentImageServiceMock(new RecentImageServiceMock)
{

}

ServiceLocatorMock::~ServiceLocatorMock()
{
	delete mMessageBoxServiceMock;
	delete mFileServiceMock;
	delete mClipboardMock;
	delete mDesktopServiceMock;
	delete mRecentImageServiceMock;
}

IMessageBoxService *ServiceLocatorMock::messageBoxService() const
{
	return mMessageBoxServiceMock;
}

IFileService *ServiceLocatorMock::fileService() const
{
	return mFileServiceMock;
}

IClipboard *ServiceLocatorMock::clipboard() const
{
	return mClipboardMock;
}

IDesktopService *ServiceLocatorMock::desktopService() const
{
	return mDesktopServiceMock;
}

IRecentImageService *ServiceLocatorMock::recentImageService() const
{
	return mRecentImageServiceMock;
}

MessageBoxServiceMock *ServiceLocatorMock::messageBoxService_mock() const
{
	return mMessageBoxServiceMock;
}

FileServiceMock *ServiceLocatorMock::fileService_mock() const
{
	return mFileServiceMock;
}

ClipboardMock *ServiceLocatorMock::clipboard_mock() const
{
	return mClipboardMock;
}

DesktopServiceMock *ServiceLocatorMock::desktopService_mock() const
{
	return mDesktopServiceMock;
}

RecentImageServiceMock *ServiceLocatorMock::recentImageService_mock() const
{
	return mRecentImageServiceMock;
}
