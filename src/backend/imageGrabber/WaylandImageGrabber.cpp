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

#include "WaylandImageGrabber.h"

WaylandImageGrabber::WaylandImageGrabber() :
        AbstractImageGrabber(),
        mRequestTokenCounter(1)
{
	addSupportedCaptureMode(CaptureModes::Portal);
}

void WaylandImageGrabber::grab()
{
    auto message = getDBusMessage();
    auto pendingCall = QDBusConnection::sessionBus().asyncCall(message);
	auto watcher = new QDBusPendingCallWatcher(pendingCall);
	connect(watcher, &QDBusPendingCallWatcher::finished, this, &WaylandImageGrabber::portalResponse);
}

QDBusMessage WaylandImageGrabber::getDBusMessage()
{
    auto message = QDBusMessage::createMethodCall(
            QLatin1String("org.freedesktop.portal.Desktop"),
            QLatin1String("/org/freedesktop/portal/desktop"),
            QLatin1String("org.freedesktop.portal.Screenshot"),
            QLatin1String("Screenshot"));

    message << QLatin1String("wayland:") << QVariantMap{
        {QLatin1String("interactive"), false},
        {QLatin1String("handle_token"), getRequestToken()}
    };
    return message;
}

void WaylandImageGrabber::gotScreenshotResponse(uint response, const QVariantMap& results)
{
	if (isResponseValid(response, results)) {
        auto path = getPathToScreenshot(results);
        auto screenshot = createPixmapFromPath(path);
        if(isTemporaryImage(path)) {
            emit finished(CaptureDto(screenshot));
        } else {
            emit finished(CaptureFromFileDto(screenshot, path));
        }
	} else {
        qCritical("Failed to take screenshot");
    }
}

QPixmap WaylandImageGrabber::createPixmapFromPath(const QString &path) const
{
    auto capture = QPixmap::fromImage(QImage(path));
    if(mConfig->scaleGenericWaylandScreenshotsEnabled()) {
        qDebug("Scale factor: %s", qPrintable(QString::number(mHdpiScaler.scaleFactor())));
        capture.setDevicePixelRatio(mHdpiScaler.scaleFactor());
    }

    return capture;
}

bool WaylandImageGrabber::isResponseValid(uint response, const QVariantMap &results)
{
    return !response && results.contains(QLatin1String("uri"));
}

bool WaylandImageGrabber::isTemporaryImage(const QString &path)
{
    return path.contains(QLatin1String("/tmp/"));
}

QString WaylandImageGrabber::getPathToScreenshot(const QVariantMap &results)
{
    auto uri = results.value(QLatin1String("uri")).toString();
    return uri.remove(QLatin1String("file://"));
}

QString WaylandImageGrabber::getRequestToken()
{
	mRequestTokenCounter += 1;
	return QString("u%1").arg(mRequestTokenCounter);
}

void WaylandImageGrabber::portalResponse(QDBusPendingCallWatcher *watcher)
{
    QDBusPendingReply<QDBusObjectPath> reply = *watcher;

    if (reply.isError()) {
        qCritical("Error: %s", qPrintable(reply.error().message()));
    } else {
        QDBusConnection::sessionBus().connect(QString(),
                                              reply.value().path(),
                                              QLatin1String("org.freedesktop.portal.Request"),
                                              QLatin1String("Response"),
                                              this,
                                              SLOT(gotScreenshotResponse(uint,QVariantMap)));
    }
}
