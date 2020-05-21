/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_NOTIFYOPERATION_H
#define KSNIP_NOTIFYOPERATION_H

#include "src/gui/TrayIcon.h"
#include "src/common/enum/NotificationTypes.h"

class NotifyOperation
{
public:
	NotifyOperation(IToastService *toastService, const QString &title, const QString &message, const QString &contentUrl, NotificationTypes notificationType);
	NotifyOperation(IToastService *toastService, const QString &title, const QString &message, NotificationTypes notificationType);
	~NotifyOperation() = default;
	bool execute();

private:
	IToastService *mToastService;
	QString mTitle;
	QString mMessage;
	QString mContentUrl;
	NotificationTypes mNotificationType;
};

#endif //KSNIP_NOTIFYOPERATION_H
