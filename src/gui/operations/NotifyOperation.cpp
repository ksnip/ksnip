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

#include "NotifyOperation.h"

NotifyOperation::NotifyOperation(IToastService *toastService, const QString &title, const QString &message, const QString &contentUrl, NotificationTypes notificationType)
	: NotifyOperation(toastService, title, message, notificationType)
{
	mContentUrl = contentUrl;
}

NotifyOperation::NotifyOperation(IToastService *toastService, const QString &title, const QString &message, NotificationTypes notificationType) :
	mToastService(toastService),
	mTitle(title),
	mMessage(message),
	mNotificationType(notificationType)
{
	Q_ASSERT(mToastService != nullptr);
}

bool NotifyOperation::execute()
{
	switch (mNotificationType) {
		case NotificationTypes::Information:
			mToastService->showInfoToast(mTitle, mMessage, mContentUrl);
			qInfo("%s: %s", qPrintable(mTitle), qPrintable(mMessage));
			break;
		case NotificationTypes::Warning:
			mToastService->showWarningToast(mTitle, mMessage, mContentUrl);
			qWarning("%s: %s", qPrintable(mTitle), qPrintable(mMessage));
			break;
		case NotificationTypes::Critical:
			mToastService->showCriticalToast(mTitle, mMessage, mContentUrl);
			qCritical("%s: %s", qPrintable(mTitle), qPrintable(mMessage));
			break;
	}
	return true;
}

