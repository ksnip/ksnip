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
{
	loadRecentImages();
}

void RecentImagesStore::loadRecentImages()
{
	const auto numRecentImages = mSettings.beginReadArray("recentImages");
	for (int i=0; i<numRecentImages; ++i) {
		mSettings.setArrayIndex(i);
		const auto recentImagePath = mSettings.value("imagePath").toString();
		mRecentImages.enqueue(recentImagePath);
	}
	mSettings.endArray();
}

void RecentImagesStore::storeImage(const QString &image)
{
	static const uint maxRecentImages = 10;

	if (mRecentImages.contains(image)) {
		return;
	}

	if (mRecentImages.size() == maxRecentImages) {
		mRecentImages.dequeue();
	}

	mRecentImages.enqueue(image);
	saveRecentImages();
}

void RecentImagesStore::saveRecentImages()
{
	mSettings.beginWriteArray("recentImages");
	for (int i=0 ; i<mRecentImages.size(); ++i) {
		mSettings.setArrayIndex(i);
		mSettings.setValue("imagePath", mRecentImages.at(i));
	}
	mSettings.endArray();
	mSettings.sync();
}

QStringList RecentImagesStore::getRecentImages() const
{
	return mRecentImages;
}
