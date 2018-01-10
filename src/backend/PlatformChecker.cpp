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

#include "PlatformChecker.h"

PlatformChecker* PlatformChecker::instance()
{
    static PlatformChecker instance;
    return &instance;
}

PlatformChecker::Platform PlatformChecker::platform() const
{
    return mPlatform;
}

PlatformChecker::DE PlatformChecker::de() const
{
    return mDe;
}

void PlatformChecker::checkPlatform()
{
    if (QX11Info::isPlatformX11()) {
        qCritical("Platform: X11");
        mPlatform = Platform::X11;
    } else if (QGuiApplication::platformName().startsWith(QLatin1String("wayland"), Qt::CaseInsensitive)) {
        qCritical("Platform: Wayland");
        mPlatform = Platform::Wayland;
    } else {
        qCritical("Platform: Unknown");
        mPlatform = Platform::Unknown;
    }
}

void PlatformChecker::checkDe()
{
    auto output = getEnviromentVariable("XDG_CURRENT_DESKTOP");
    if (output.contains(QLatin1String("kde"), Qt::CaseInsensitive)) {
        qCritical("Window Manager: KDE");
        mDe = DE::KDE;
    } else if (output.contains(QLatin1String("gnome"), Qt::CaseInsensitive)) {
        qCritical("Window Manager: Gnome");
        mDe = DE::KDE;
    } else {
        qCritical("Window Manager: Unknown");
        mDe = DE::Unknown;
    }
}

PlatformChecker::PlatformChecker()
{
    checkPlatform();
    checkDe();
}

QString PlatformChecker::getEnviromentVariable(const QString& variable) const
{
    QString value;
    FILE* stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    auto command = variable.trimmed();
    command.prepend("echo $");
    command.append(" 2>&1");

    stream = popen(command.toLatin1(), "r");

    if (stream) {
        while (!feof(stream)) {
            if (fgets(buffer, max_buffer, stream) != NULL) {
                value.append(buffer);
            }
        }
        pclose(stream);
    }
    return value;
}
