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

/*
 * Most part of this class comes from the KWinWaylandImageGrabber implementation
 * from KDE Spectacle, implemented by Martin Graesslin <mgraesslin@kde.org>
 */

#include "KdeWaylandImageGrabber.h"

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

void KdeWaylandImageGrabber::grabImage(CaptureModes captureMode, bool capureCursor, int delay)
{
    mCaptureCursor = capureCursor;
    mCaptureDelay = delay;
    if (isCaptureModeSupported(captureMode)) {
        mCaptureMode = captureMode;
    } else {
        mCaptureMode = CaptureModes::FullScreen;
    }

    QTimer::singleShot(mCaptureDelay, this, &KdeWaylandImageGrabber::grab);
}

bool KdeWaylandImageGrabber::isCaptureModeSupported(CaptureModes captureMode)
{
    if (captureMode == CaptureModes::WindowUnderCursor ||
            captureMode == CaptureModes::CurrentScreen ||
            captureMode == CaptureModes::FullScreen) {
        return true;
    } else {
        return false;
    }
}

void KdeWaylandImageGrabber::grab()
{
    int pipeFds[2];
    if (pipe2(pipeFds, O_CLOEXEC | O_NONBLOCK) != 0) {
        emit canceled();
        return;
    }

    callDBus(pipeFds[1]);
    startReadImage(pipeFds[0]);

    close(pipeFds[1]);
}

void KdeWaylandImageGrabber::startReadImage(int readPipe)
{
    QFutureWatcher<QImage>* watcher = new QFutureWatcher<QImage>(this);
    QObject::connect(watcher, &QFutureWatcher<QImage>::finished, this,
    [watcher, this] {
        watcher->deleteLater();
        const QImage img = watcher->result();
        emit finished(QPixmap::fromImage(img));
    });
    watcher->setFuture(QtConcurrent::run(readImage, readPipe));
}

void KdeWaylandImageGrabber::callDBus(int writeFd)
{
    QDBusInterface interface(QStringLiteral("org.kde.KWin"), QStringLiteral("/Screenshot"), QStringLiteral("org.kde.kwin.Screenshot"));
    static const QMap<CaptureModes, QString> s_hash = {
        {CaptureModes::WindowUnderCursor, QStringLiteral("interactive")},
        {CaptureModes::CurrentScreen, QStringLiteral("screenshotScreen")},
        {CaptureModes::FullScreen, QStringLiteral("screenshotFullscreen")}
    };
    auto it = s_hash.find(mCaptureMode);
    Q_ASSERT(it != s_hash.end());
    interface.asyncCall(it.value(), QVariant::fromValue(QDBusUnixFileDescriptor(writeFd)), mCaptureCursor);
}
