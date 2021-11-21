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

#include "WaylandConfig.h"

WaylandConfig::WaylandConfig(const QSharedPointer<IDirectoryPathProvider> &directoryPathProvider, const QSharedPointer<IPlatformChecker> &platformChecker) :
	Config(directoryPathProvider),
	mPlatformChecker(platformChecker)
{

}

bool WaylandConfig::isFreezeImageWhileSnippingEnabledReadOnly() const
{
	return true;
}

bool WaylandConfig::freezeImageWhileSnippingEnabled() const
{
	return false;
}

bool WaylandConfig::isGlobalHotKeysEnabledReadOnly() const
{
	return true;
}

bool WaylandConfig::globalHotKeysEnabled() const
{
	return false;
}

bool WaylandConfig::isSnippingAreaMagnifyingGlassEnabledReadOnly() const
{
	return true;
}

bool WaylandConfig::snippingAreaMagnifyingGlassEnabled() const
{
	return false;
}

bool WaylandConfig::isForceGenericWaylandEnabledReadOnly() const
{
    return isOnlyGenericScreenshotSupported();
}

bool WaylandConfig::isScaleGenericWaylandScreenshotEnabledReadOnly() const
{
    return false;
}

bool WaylandConfig::forceGenericWaylandEnabled() const
{
	if (isOnlyGenericScreenshotSupported()) {
		return true;
	}
	return Config::forceGenericWaylandEnabled();
}

bool WaylandConfig::isOnlyGenericScreenshotSupported() const
{
	return mPlatformChecker->gnomeVersion() >= 41 || mPlatformChecker->isSnap();
}
