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

bool PlatformChecker::isX11() const
{
    return mPlatform == Platform::X11;
}

bool PlatformChecker::isWayland() const
{
    return mPlatform == Platform::Wayland;
}

bool PlatformChecker::isKde() const
{
    return mEnvironment == Environment::KDE;
}

bool PlatformChecker::isGnome() const
{
    return mEnvironment == Environment::Gnome;
}

void PlatformChecker::checkPlatform()
{
    CommandRunner runner;
    auto output = runner.getEnviromentVariable("XDG_SESSION_TYPE");
    if (outputContainsValue(output, "x11")) {
        mPlatform = Platform::X11;
    } else if (outputContainsValue(output, "wayland")) {
        mPlatform = Platform::Wayland;
    } else {
        mPlatform = Platform::Unknown;
    }
}

void PlatformChecker::checkEnvironment()
{
    CommandRunner runner;
    auto output = runner.getEnviromentVariable("XDG_CURRENT_DESKTOP");
    if (outputContainsValue(output, "kde")) {
        mEnvironment = Environment::KDE;
    } else if (outputContainsValue(output, "gnome")) {
        mEnvironment = Environment::Gnome;
    } else {
        mEnvironment = Environment::Unknown;
    }
}

bool PlatformChecker::outputContainsValue(const QString& output, const QString& value) const
{
    return output.contains(value.toLatin1(), Qt::CaseInsensitive);
}

PlatformChecker::PlatformChecker()
{
    checkPlatform();
    checkEnvironment();
}
