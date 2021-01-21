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

#include "RecentImagesStore.h"


RecentImagesStore::RecentImagesStore()
	: mSettingsGroupPrefix("recentImages"),
	  mSettingsGroupKey("imagePath"),
	  mMaxRecentItems(10)
{
	loadRecentImages();
}

void RecentImagesStore::loadRecentImages()
{
	const auto numRecentImages = mSettings.beginReadArray(mSettingsGroupPrefix);
	for (int i=0; i<numRecentImages; ++i) {
		mSettings.setArrayIndex(i);
		const auto recentImagePath = mSettings.value(mSettingsGroupKey).toString();
		mRecentImages.enqueue(recentImagePath);
	}
	mSettings.endArray();
}

void RecentImagesStore::storeImage(const QString &image)
{
	if (mRecentImages.contains(image)) {
		return;
	}

	if (mRecentImages.size() == mMaxRecentItems) {
		mRecentImages.dequeue();
	}

	mRecentImages.enqueue(image);
	saveRecentImages();
}

void RecentImagesStore::saveRecentImages()
{
	mSettings.beginWriteArray(mSettingsGroupPrefix);
	for (int i=0 ; i<mRecentImages.size(); ++i) {
		mSettings.setArrayIndex(i);
		mSettings.setValue(mSettingsGroupKey, mRecentImages.at(i));
	}
	mSettings.endArray();
	mSettings.sync();
}

QStringList RecentImagesStore::getRecentImages() const
{
	return mRecentImages;
}
