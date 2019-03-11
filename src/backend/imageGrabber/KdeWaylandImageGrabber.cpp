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

KdeWaylandImageGrabber::KdeWaylandImageGrabber() : AbstractImageGrabber(new LinuxSnippingArea)
{
	addSupportedCaptureMode(CaptureModes::WindowUnderCursor);
	addSupportedCaptureMode(CaptureModes::CurrentScreen);
	addSupportedCaptureMode(CaptureModes::FullScreen);
}

QRect KdeWaylandImageGrabber::fullScreenRect() const
{
	// Not Supported for Kde Wayland
	return {};
}

QRect KdeWaylandImageGrabber::activeWindowRect() const
{
	// Not Supported for Kde Wayland
	return {};
}

void KdeWaylandImageGrabber::grab()
{
    if (mCaptureMode == CaptureModes::FullScreen) {
        prepareDBus(QStringLiteral("screenshotFullscreen"), mCaptureCursor);
    } else if (mCaptureMode == CaptureModes::CurrentScreen) {
        prepareDBus(QStringLiteral("screenshotScreen"), mCaptureCursor);
    } else {
        int mask = 1;
        if (mCaptureCursor) {
            mask |= 1 << 1;
        }
        prepareDBus(QStringLiteral("interactive"), mask);
    }
}

ImageWithPosition KdeWaylandImageGrabber::getCursorWithPosition() const
{
	// Not Supported for Kde Wayland
	return ImageWithPosition();
}

template<typename T>
void KdeWaylandImageGrabber::prepareDBus(const QString& mode, T mask)
{
    int pipeFds[2];
    if (pipe2(pipeFds, O_CLOEXEC | O_NONBLOCK) != 0) {
        emit canceled();
        return;
    }

    callDBus(pipeFds[1], mode, mask);
    startReadImage(pipeFds[0]);

    close(pipeFds[1]);
}

template<typename T>
void KdeWaylandImageGrabber::callDBus(int writeFd, const QString& mode, T mask)
{
    QDBusInterface interface(QStringLiteral("org.kde.KWin"), QStringLiteral("/Screenshot"), QStringLiteral("org.kde.kwin.Screenshot"));
    interface.asyncCall(mode, QVariant::fromValue(QDBusUnixFileDescriptor(writeFd)), mask);
}

void KdeWaylandImageGrabber::startReadImage(int readPipe)
{
    auto watcher = new QFutureWatcher<QImage>(this);
    QObject::connect(watcher, &QFutureWatcher<QImage>::finished, this,
    [watcher, this] {
        watcher->deleteLater();
        auto image = watcher->result();
        emit finished(QPixmap::fromImage(image));
    });
    watcher->setFuture(QtConcurrent::run(readImage, readPipe));
}
