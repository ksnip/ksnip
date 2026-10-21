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

#include "MacConfig.h"

MacConfig::MacConfig(const QSharedPointer<IDirectoryPathProvider> &directoryPathProvider) : Config(directoryPathProvider)
{

}

bool MacConfig::isFreezeImageWhileSnippingEnabledReadOnly() const
{
	return true;
}

bool MacConfig::freezeImageWhileSnippingEnabled() const
{
	return true;
}

bool MacConfig::globalHotKeysEnabled() const
{
	// Opt-in on macOS, the default hot keys use Option+Shift which is also
	// how special characters are typed and could clash with normal typing.
	return loadValue(ConfigOptions::globalHotKeysEnabledString(), false).toBool();
}