/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "GnomeWaylandImageGrabber.h"

void GnomeWaylandImageGrabber::grabImage(CaptureModes captureMode, bool capureCursor, int delay)
{
    mCaptureCursor = capureCursor;
    mCaptureDelay = delay;

    if (isCaptureModeSupported(captureMode)) {
        mCaptureMode = captureMode;
    } else {
        qWarning("Unsupported Capture Mode selected, falling back to full screen.");
        mCaptureMode = CaptureModes::FullScreen;
    }

    if (mCaptureMode == CaptureModes::RectArea) {
        openSnippingArea();
    } else {
        QTimer::singleShot(mCaptureDelay, this, &GnomeWaylandImageGrabber::grab);
    }
}

void GnomeWaylandImageGrabber::grab()
{
    QDBusInterface interface(QStringLiteral("org.gnome.Shell.Screenshot"), QStringLiteral("/org/gnome/Shell/Screenshot"), QStringLiteral("org.gnome.Shell.Screenshot"));
    QDBusPendingReply<bool, QString> reply;
    if (mCaptureMode == CaptureModes::ActiveWindow) {
        reply = interface.asyncCall(QStringLiteral("ScreenshotWindow"), true, mCaptureCursor, false, tmpScreenshotFilename());
    } else {
        reply = interface.asyncCall(QStringLiteral("Screenshot"), mCaptureCursor, false, tmpScreenshotFilename());
    }

    reply.waitForFinished();

    if (reply.isError()) {
        qCritical("Invalid reply from DBus: %s", qPrintable(reply.error().message()));
        emit canceled();
    } else {
        auto pathToTmpScreenshot = reply.argumentAt<1>();
        postProcessing(QPixmap(pathToTmpScreenshot));
    }
}

bool GnomeWaylandImageGrabber::isCaptureModeSupported(CaptureModes captureMode)
{
    if (captureMode == CaptureModes::RectArea ||
            captureMode == CaptureModes::ActiveWindow ||
            captureMode == CaptureModes::FullScreen) {
        return true;
    } else {
        return false;
    }
}

void GnomeWaylandImageGrabber::postProcessing(const QPixmap& pixmap)
{
    if (mCaptureMode == CaptureModes::RectArea) {
        mCaptureRect = selectedSnippingAreaRect();
        emit finished(pixmap.copy(mCaptureRect));
    } else {
        emit finished(pixmap);
    }
}

QString GnomeWaylandImageGrabber::tmpScreenshotFilename() const
{
    auto path = QStringLiteral("/tmp/");
    auto filename = QStringLiteral("ksnip-") + QString::number(MathHelper::randomInt());
    auto extension = QStringLiteral(".png");
    return path + filename + extension;
}
