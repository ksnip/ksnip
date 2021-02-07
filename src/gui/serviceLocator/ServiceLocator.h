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

#ifndef KSNIP_SERVICELOCATOR_H
#define KSNIP_SERVICELOCATOR_H

#include "IServiceLocator.h"
#include "src/gui/fileService/FileService.h"
#include "src/gui/messageBoxService/MessageBoxService.h"
#include "src/gui/clipboard/ClipboardAdapter.h"
#include "src/gui/desktopService/DesktopServiceAdapter.h"
#include "src/backend/recentImages/RecentImagesPathStore.h"
#include "src/backend/recentImages/ImagePathStorage.h"

class ServiceLocator : public IServiceLocator
{
public:
	explicit ServiceLocator();
	ServiceLocator(ServiceLocator &other);
	~ServiceLocator() override;
	IMessageBoxService* messageBoxService() const override;
	IFileService* fileService() const override;
	IClipboard* clipboard() const override;
	IDesktopService* desktopService() const override;
	IRecentImageService* recentImageService() const override;

private:
	IFileService *mFileService;
	IMessageBoxService *mMessageBoxService;
	IClipboard *mClipboard;
	IDesktopService *mDesktopService;
	IRecentImageService *mRecentImageService;
};

#endif //KSNIP_SERVICELOCATOR_H
