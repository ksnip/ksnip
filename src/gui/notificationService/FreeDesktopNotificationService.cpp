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

#include <QCoreApplication>
#include <QList>
#include <QVariant>

#include "FreeDesktopNotificationService.h"

static const char * const FREEDESKTOP_STANDARD_INFO_ICON	= "dialog-information";
static const char * const FREEDESKTOP_STANDARD_WARN_ICON	= "dialog-warning";
static const char * const FREEDESKTOP_STANDARD_ERR_ICON		= "dialog-error";

FreeDesktopNotificationService::FreeDesktopNotificationService()
{
	mDBusInterface = new QDBusInterface(QStringLiteral("org.freedesktop.Notifications"),
					   QStringLiteral("/org/freedesktop/Notifications"),
					   QStringLiteral("org.freedesktop.Notifications"),
					   QDBusConnection::sessionBus()
					   );
}

void FreeDesktopNotificationService::showInfoToast(const QString &title, const QString &message, const QString &contentUrl)
{
	showToast(title, message, contentUrl, FREEDESKTOP_STANDARD_INFO_ICON);
}

void FreeDesktopNotificationService::showWarningToast(const QString &title, const QString &message, const QString &contentUrl)
{
	showToast(title, message, contentUrl, FREEDESKTOP_STANDARD_WARN_ICON);
}

void FreeDesktopNotificationService::showCriticalToast(const QString &title, const QString &message, const QString &contentUrl)
{
	showToast(title, message, contentUrl, FREEDESKTOP_STANDARD_ERR_ICON);
}

void FreeDesktopNotificationService::showToast(const QString &title, const QString &message, const QString &contentUrl, const QString &appIcon)
{
	QList<QVariant> args;
	QVariantMap hintsMap;

	if (!contentUrl.isEmpty()) {
		if (PlatformChecker::instance()->isKde()) {
			hintsMap["x-kde-urls"] = QStringList(contentUrl);
		} else {
			hintsMap["image-path"] = "file://" + contentUrl;
		}
	}

	args << qAppName()						// app_name
		 << static_cast<unsigned int>(0)	// replaces_id (0 = does not replace existing notification)
		 << appIcon							// app_icon
		 << title							// summary
		 << message							// body
		 << QStringList()					// actions
		 << hintsMap						// hints
		 << NOTIFICATION_TIMEOUT;			// expire_timeout

	mDBusInterface->callWithArgumentList(QDBus::NoBlock,
										 QStringLiteral("Notify"),
										 args);
}
