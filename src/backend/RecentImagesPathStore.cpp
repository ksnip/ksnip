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

#include "RecentImagesPathStore.h"


RecentImagesPathStore::RecentImagesPathStore()
	: mSettingsGroupPrefix("recentImagesPath"),
	  mSettingsGroupKey("imagePath"),
	  mMaxRecentItems(10)
{
	loadRecentImagesPath();
}

void RecentImagesPathStore::loadRecentImagesPath()
{
	const auto numRecentImagesPath = mSettings.beginReadArray(mSettingsGroupPrefix);
	for (int i=0; i<numRecentImagesPath; ++i) {
		mSettings.setArrayIndex(i);
		const auto recentImagePath = mSettings.value(mSettingsGroupKey).toString();
		mRecentImagesPath.enqueue(recentImagePath);
	}
	mSettings.endArray();
}

void RecentImagesPathStore::storeImagePath(const QString &imagePath)
{
	if (mRecentImagesPath.contains(imagePath)) {
		return;
	}

	if (mRecentImagesPath.size() == mMaxRecentItems) {
		mRecentImagesPath.dequeue();
	}

	mRecentImagesPath.enqueue(imagePath);
	saveRecentImagesPath();
}

void RecentImagesPathStore::saveRecentImagesPath()
{
	mSettings.beginWriteArray(mSettingsGroupPrefix);
	for (int i=0 ; i<mRecentImagesPath.size(); ++i) {
		mSettings.setArrayIndex(i);
		mSettings.setValue(mSettingsGroupKey, mRecentImagesPath.at(i));
	}
	mSettings.endArray();
	mSettings.sync();
}

QStringList RecentImagesPathStore::getRecentImagesPath() const
{
	return mRecentImagesPath;
}
