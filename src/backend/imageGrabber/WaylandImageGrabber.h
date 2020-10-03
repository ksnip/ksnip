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

#ifndef KSNIP_WAYLANDIMAGEGRABBER_H
#define KSNIP_WAYLANDIMAGEGRABBER_H

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>

#include "AbstractImageGrabber.h"
#include "src/gui/snippingArea/LinuxSnippingArea.h"
#include "src/common/dtos/CaptureFromFileDto.h"
#include "src/common/platform/HdpiScaler.h"

class WaylandImageGrabber  : public AbstractImageGrabber
{
    Q_OBJECT
public:
	explicit WaylandImageGrabber();

public slots:
    void gotScreenshotResponse(uint response, const QVariantMap& results);

protected:
	void grab() override;

private:
	int mRequestTokenCounter;
    HdpiScaler mHdpiScaler;

	QString getRequestToken();

    static QString getPathToScreenshot(const QVariantMap &results);
    static bool isTemporaryImage(const QString &path);
    static bool isResponseValid(uint response, const QVariantMap &results);
    QDBusMessage getDBusMessage();

private slots:
    void portalResponse(QDBusPendingCallWatcher *watcher);

    QPixmap createPixmapFromPath(const QString &path) const;
};

#endif //KSNIP_WAYLANDIMAGEGRABBER_H
