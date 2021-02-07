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

#ifndef KSNIP_SERVICELOCATORMOCK_H
#define KSNIP_SERVICELOCATORMOCK_H

#include "src/gui/serviceLocator/IServiceLocator.h"
#include "tests/mocks/MessageBoxServiceMock.h"
#include "tests/mocks/FileServiceMock.h"
#include "tests/mocks/ClipboardMock.h"
#include "tests/mocks/DesktopServiceMock.h"
#include "tests/mocks/RecentImageServiceMock.h"

class ServiceLocatorMock : public IServiceLocator
{
public:
	explicit ServiceLocatorMock();
	~ServiceLocatorMock() override;
	IMessageBoxService* messageBoxService() const override;
	IFileService* fileService() const override;
	IClipboard* clipboard() const override;
	IDesktopService* desktopService() const override;
	IRecentImageService* recentImageService() const override;

	// Mock Methods
	MessageBoxServiceMock* messageBoxService_mock() const;
	FileServiceMock* fileService_mock() const;
	ClipboardMock* clipboard_mock() const;
	DesktopServiceMock* desktopService_mock() const;
	RecentImageServiceMock* recentImageService_mock() const;

private:
	MessageBoxServiceMock *mMessageBoxServiceMock;
	FileServiceMock *mFileServiceMock;
	ClipboardMock *mClipboardMock;
	DesktopServiceMock *mDesktopServiceMock;
	RecentImageServiceMock *mRecentImageServiceMock;
};

#endif //KSNIP_SERVICELOCATORMOCK_H
