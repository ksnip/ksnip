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

#ifndef KSNIP_ISERVICELOCATOR_H
#define KSNIP_ISERVICELOCATOR_H

#include "src/gui/fileService/IFileService.h"
#include "src/gui/messageBoxService/IMessageBoxService.h"
#include "src/gui/clipboard/IClipboard.h"
#include "src/gui/desktopService/IDesktopService.h"
#include "src/backend/recentImages/IRecentImageService.h"

class IServiceLocator
{
public:
	explicit IServiceLocator() = default;
	virtual ~IServiceLocator() = default;
	virtual IMessageBoxService* messageBoxService() const = 0;
	virtual IFileService* fileService() const = 0;
	virtual IClipboard* clipboard() const = 0;
	virtual IDesktopService* desktopService() const = 0;
	virtual IRecentImageService* recentImageService() const = 0;
};

#endif //KSNIP_ISERVICELOCATOR_H
