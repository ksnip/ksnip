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

#ifndef KSNIP_FREEDESKTOPNOTIFICATIONSERVICE_H
#define KSNIP_FREEDESKTOPNOTIFICATIONSERVICE_H

#include <QString>
#include <QObject>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusMessage>

#include "src/gui/INotificationService.h"
#include "src/common/platform/PlatformChecker.h"

class FreeDesktopNotificationService : public QObject, public INotificationService
{
	Q_OBJECT
public:
	FreeDesktopNotificationService();
	~FreeDesktopNotificationService() override = default;

	void showInfo(const QString &title, const QString &message, const QString &contentUrl) override;
	void showWarning(const QString &title, const QString &message, const QString &contentUrl) override;
	void showCritical(const QString &title, const QString &message, const QString &contentUrl) override;

protected:
	void showToast(const QString &title, const QString &message, const QString &contentUrl, const QString &appIcon);
	virtual QVariantMap getHintsMap(const QString &contentUrl);

private:
	QDBusInterface *mDBusInterface;
	const int mNotificationTimeout;
};

#endif //KSNIP_FREEDESKTOPNOTIFICATIONSERVICE_H
