/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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

bool PlatformChecker::isSnap() const
{
	return mPackageManager == PackageManager::Snap;
}

void PlatformChecker::checkPlatform()
{
    CommandRunner runner;
    auto output = runner.getEnvironmentVariable(QStringLiteral("XDG_SESSION_TYPE"));
    if (outputContainsValue(output, QStringLiteral("x11"))) {
        mPlatform = Platform::X11;
    } else if (outputContainsValue(output, QStringLiteral("wayland"))) {
        mPlatform = Platform::Wayland;
    } else {
        mPlatform = Platform::Unknown;
    }
}

void PlatformChecker::checkEnvironment()
{
    CommandRunner runner;
    auto output = runner.getEnvironmentVariable(QStringLiteral("XDG_CURRENT_DESKTOP"));
    if (outputContainsValue(output, QStringLiteral("kde"))) {
        mEnvironment = Environment::KDE;
    } else if (outputContainsValue(output, QStringLiteral("gnome")) || outputContainsValue(output, QStringLiteral("unity"))) {
        mEnvironment = Environment::Gnome;
    } else {
        mEnvironment = Environment::Unknown;
    }
}

void PlatformChecker::checkCheckPackageManager()
{
	CommandRunner runner;
	if (runner.isEnvironmentVariableSet(QStringLiteral("SNAP"))) {
		mPackageManager = PackageManager::Snap;
	} else {
		mPackageManager = PackageManager::Unknown;
	}
}

bool PlatformChecker::outputContainsValue(const QString& output, const QString& value) const
{
    return output.contains(value.toLatin1(), Qt::CaseInsensitive);
}

PlatformChecker::PlatformChecker() :
	mEnvironment(Environment::Unknown),
	mPlatform(Platform::Unknown),
	mPackageManager(PackageManager::Unknown)
{
    checkPlatform();
    checkEnvironment();
    checkCheckPackageManager();
}
