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

static int readData(int fd, QByteArray& data)
{
    // implementation based on QtWayland file qwaylanddataoffer.cpp
    char buffer[4096];
    int retryCount = 0;
    int n;
    while (true) {
        n = QT_READ(fd, buffer, sizeof buffer);
        // give user 30 sec to click a window, afterwards considered as error
        if (n == -1 && (errno == EAGAIN) && ++retryCount < 30000) {
            usleep(1000);
        } else {
            break;
        }
    }
    if (n > 0) {
        data.append(buffer, n);
        n = readData(fd, data);
    }
    return n;
}

static QImage readImage(int pipeFd)
{
    QByteArray content;
    if (readData(pipeFd, content) != 0) {
        close(pipeFd);
        return QImage();
    }
    close(pipeFd);
    QDataStream dataStream(content);
    QImage image;
    dataStream >> image;
    return image;
};

void GnomeWaylandImageGrabber::grabImage(CaptureModes captureMode, bool capureCursor, int delay)
{
    mCaptureMode = captureMode;
    mCaptureCursor = capureCursor;

    qCritical("Called grabImage on GnomeWaylandImageGrabber.");

    grab();
}

void GnomeWaylandImageGrabber::grab()
{
    // It's possible to take a screenshot like this but it saves the screenshot
    // to a file
//     if (!QDBusConnection::sessionBus().isConnected()) {
//         qCritical("Cannot connect to the D-Bus session bus.");
//         return;
//     }
// 
//     QDBusInterface dbusInterface("org.gnome.Shell.Screenshot", "/org/gnome/Shell/Screenshot", "org.gnome.Shell.Screenshot", QDBusConnection::sessionBus());
//     if (dbusInterface.isValid()) {
//         QDBusReply<double> reply = dbusInterface.call("Screenshot", true, true, "~/screenshot-ksnip");
//         if (reply.isValid()) {
//             printf("Reply from bus was: %e", reply.value());
//         } else {
//             printf("Call to bus failed: %s", qPrintable(reply.error().message()));
//             return;
//         }
//     } else {
//         qCritical("Dbus Interface not valid.");
//     }
// 
//     qCritical("No D-Bus interface found!");
//     return;


    int pipeFds[2];
    if (pipe2(pipeFds, O_CLOEXEC | O_NONBLOCK) != 0) {
        emit canceled();
        return;
    }

    QDBusInterface interface(QStringLiteral("org.gnome.Shell.Screenshot"), QStringLiteral("/org/gnome/Shell/Screenshot"), QStringLiteral("org.gnome.Shell.Screenshot"));
    interface.asyncCall("Screenshot", true, true, QVariant::fromValue(QDBusUnixFileDescriptor(pipeFds[1])));

    auto watcher = new QFutureWatcher<QImage>(this);
    QObject::connect(watcher, &QFutureWatcher<QImage>::finished, this,
    [watcher, this] {
        watcher->deleteLater();
        auto image = watcher->result();
        emit finished(QPixmap::fromImage(image));
    });
    watcher->setFuture(QtConcurrent::run(readImage, pipeFds[1]));
}

bool GnomeWaylandImageGrabber::isCaptureModeSupported(CaptureModes captureMode)
{
    return true;
}
