/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#include "SavePathProvider.h"

SavePathProvider::SavePathProvider()
{
    mConfig = KsnipConfigProvider::instance();
}

QString SavePathProvider::savePath() const
{
    return UniqueNameProvider::makeUniqueFilename(saveDirectory(), getFilename(), getFormat(mConfig->saveFormat()));
}

QString SavePathProvider::savePathWithFormat(const QString &format) const
{
    return UniqueNameProvider::makeUniqueFilename(saveDirectory(), getFilename(), getFormat(format));
}

QString SavePathProvider::getFilename() const
{
	auto filename = WildcardResolver::replaceDateTimeWildcards(mConfig->saveFilename());
	return WildcardResolver::replaceNumberWildcards(filename, saveDirectory(), getFormat(mConfig->saveFormat()));
}

QString SavePathProvider::getFormat(const QString &format) const
{
    return format.startsWith(QLatin1Char('.')) ? format : QLatin1Char('.') + format;
}

QString SavePathProvider::saveDirectory() const
{
	return WildcardResolver::replaceDateTimeWildcards(mConfig->saveDirectory());
}

