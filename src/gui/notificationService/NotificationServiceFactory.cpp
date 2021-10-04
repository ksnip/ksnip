/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "NotificationServiceFactory.h"
#include "src/backend/config/ConfigProvider.h"

#if defined(UNIX_X11)
#include "FreeDesktopNotificationService.h"
#endif

QSharedPointer<INotificationService> NotificationServiceFactory::create(INotificationService *defaultNotificationService)
{
#if defined(UNIX_X11)
	if (ConfigProvider::instance()->platformSpecificNotificationServiceEnabled()) {
		return QSharedPointer<INotificationService>(new FreeDesktopNotificationService());
	} else {
		return QSharedPointer<INotificationService>(defaultNotificationService);
	}
#else
	return QSharedPointer<INotificationService>(defaultNotificationService);
#endif
}
