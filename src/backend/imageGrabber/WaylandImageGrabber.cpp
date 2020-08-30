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
	AbstractImageGrabber(new LinuxSnippingArea),
	mRequestTokenCounter(1)
{
	addSupportedCaptureMode(CaptureModes::RectArea);
	addSupportedCaptureMode(CaptureModes::LastRectArea);
	addSupportedCaptureMode(CaptureModes::FullScreen);
	addSupportedCaptureMode(CaptureModes::CurrentScreen);
}

QRect WaylandImageGrabber::fullScreenRect() const
{
	return {};
}

QRect WaylandImageGrabber::activeWindowRect() const
{
	return {};
}

void WaylandImageGrabber::grab()
{
	auto message = QDBusMessage::createMethodCall(QLatin1String("org.freedesktop.portal.Desktop"),
	                                                      QLatin1String("/org/freedesktop/portal/desktop"),
	                                                      QLatin1String("org.freedesktop.portal.Screenshot"),
	                                                      QLatin1String("Screenshot"));

	message << QLatin1String("x11:") << QVariantMap{{QLatin1String("interactive"), true}, {QLatin1String("handle_token"), getRequestToken()}};

	auto pendingCall = QDBusConnection::sessionBus().asyncCall(message);
	auto watcher = new QDBusPendingCallWatcher(pendingCall);
	connect(watcher, &QDBusPendingCallWatcher::finished, [this] (QDBusPendingCallWatcher *watcher) {
		QDBusPendingReply<QDBusObjectPath> reply = *watcher;
		if (reply.isError()) {
			qDebug("Couldn't get reply");
			qWarning("Error: %s", qPrintable(reply.error().message()));
		} else {
			QDBusConnection::sessionBus().connect(QString(),
			                                      reply.value().path(),
			                                      QLatin1String("org.freedesktop.portal.Request"),
			                                      QLatin1String("Response"),
			                                      this,
			                                      SLOT(gotScreenshotResponse(uint,QVariantMap)));
		}
	});
}

CursorDto WaylandImageGrabber::getCursorWithPosition() const
{
	return CursorDto();
}

void WaylandImageGrabber::gotScreenshotResponse(uint response, const QVariantMap& results)
{
	if (!response) {
		if (results.contains(QLatin1String("uri"))) {
			qDebug("Success");
			emit finished(CaptureDto(QPixmap::fromImage(QImage(results.value(QLatin1String("uri")).toString()))));
		}
	} else {
		qDebug("Failed to take screenshot");
	}
}


QString WaylandImageGrabber::getRequestToken()
{
	mRequestTokenCounter += 1;
	return QString("u%1").arg(mRequestTokenCounter);
}
