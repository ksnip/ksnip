/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "RecentImageServiceMock.h"

void RecentImageServiceMock::storeImagePath(const QString &imagePath)
{
	mLastStoreImagePathParameter = imagePath;
	mStoreImagePathCallCounter.increment(imagePath);
}

QStringList RecentImageServiceMock::getRecentImagesPath() const
{
	auto ptr =  const_cast<RecentImageServiceMock*>(this);
	ptr->mGetRecentImagesPathCallCounter.increment(0);
	return mGetRecentImagesPathResult;
}

QString RecentImageServiceMock::storeImagePath_get() const
{
	return mLastStoreImagePathParameter;
}

int RecentImageServiceMock::storeImagePath_callCounter(const QString &path) const
{
	return mStoreImagePathCallCounter.count(path);
}

int RecentImageServiceMock::storeImagePath_callCounter() const
{
	return mStoreImagePathCallCounter.count();
}

void RecentImageServiceMock::getRecentImagesPath_set(const QStringList &imagePaths)
{
	mGetRecentImagesPathResult = imagePaths;
}

int RecentImageServiceMock::getRecentImagesPath_callCounter() const
{
	return mGetRecentImagesPathCallCounter.count(0);
}
