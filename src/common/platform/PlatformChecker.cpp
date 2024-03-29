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

PlatformChecker::PlatformChecker(const QSharedPointer<ICommandRunner> &commandRunner) :
	mCommandRunner(commandRunner),
	mEnvironment(Environment::Unknown),
	mPlatform(Platform::Unknown),
	mPackageManager(PackageManager::Unknown),
	mGnomeVersion(-1),
	mIsPlatformChecked(false),
	mIsEnvironmentChecked(false),
	mIsPacketManagerChecked(false),
	mIsGnomeVersionChecked(false)
{
}

bool PlatformChecker::isX11()
{
	checkPlatform();
	return mPlatform == Platform::X11;
}

bool PlatformChecker::isWayland()
{
	checkPlatform();
    return mPlatform == Platform::Wayland;
}

bool PlatformChecker::isKde()
{
	checkEnvironment();
    return mEnvironment == Environment::KDE;
}

bool PlatformChecker::isGnome()
{
	checkEnvironment();
    return mEnvironment == Environment::Gnome;
}

bool PlatformChecker::isSnap()
{
	checkPackageManager();
	return mPackageManager == PackageManager::Snap;
}

int PlatformChecker::gnomeVersion()
{
	checkVersion();
    return mGnomeVersion;
}

void PlatformChecker::checkPlatform()
{
	if(!mIsPlatformChecked) {
		auto output = mCommandRunner->getEnvironmentVariable(QLatin1String("XDG_SESSION_TYPE"));
		if (outputContainsValue(output, QLatin1String("x11"))) {
			mPlatform = Platform::X11;
		} else if (outputContainsValue(output, QLatin1String("wayland"))) {
			mPlatform = Platform::Wayland;
		} else {
			mPlatform = Platform::Unknown;
		}
	}
	mIsPlatformChecked = true;
}

void PlatformChecker::checkEnvironment()
{
	if(!mIsEnvironmentChecked) {
		auto output = mCommandRunner->getEnvironmentVariable(QLatin1String("XDG_CURRENT_DESKTOP"));
		if (outputContainsValue(output, QLatin1String("kde"))) {
			mEnvironment = Environment::KDE;
		} else if (outputContainsValue(output, QLatin1String("gnome")) || outputContainsValue(output, QLatin1String("unity"))) {
			mEnvironment = Environment::Gnome;
		} else {
			mEnvironment = Environment::Unknown;
		}
	}
	mIsEnvironmentChecked = true;
}

void PlatformChecker::checkPackageManager()
{
	if(!mIsPacketManagerChecked) {
		if (mCommandRunner->isEnvironmentVariableSet(QLatin1String("SNAP"))) {
			mPackageManager = PackageManager::Snap;
		} else {
			mPackageManager = PackageManager::Unknown;
		}
		mIsPacketManagerChecked = true;
	}
}

bool PlatformChecker::outputContainsValue(const QString& output, const QString& value)
{
    return output.contains(value.toLatin1(), Qt::CaseInsensitive);
}

void PlatformChecker::checkVersion()
{
    if(!mIsGnomeVersionChecked && isGnome()) {
		auto path = QLatin1String("/usr/share/gnome/gnome-version.xml");
		QRegularExpression regex("<platform>(.+?)</platform>");
		bool isParseSuccessful;
		auto value = regex.match(mCommandRunner->readFile(path)).captured(1).toInt(&isParseSuccessful);
		if(isParseSuccessful) {
			mGnomeVersion = value;
		}
	}
	mIsGnomeVersionChecked = true;
}
