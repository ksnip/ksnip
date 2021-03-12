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

RecentImagesPathStore::RecentImagesPathStore(IImagePathStorage *imagePathStorage) :
	mImagePathStorage(imagePathStorage),
	mMaxRecentItems(10)
{
	Q_ASSERT(mImagePathStorage != nullptr);

	loadRecentImagesPath();
}

RecentImagesPathStore::~RecentImagesPathStore()
{
	delete mImagePathStorage;
}

void RecentImagesPathStore::loadRecentImagesPath()
{
	const auto storedImageCount = mImagePathStorage->count();
	for (auto i = 0; i < storedImageCount; ++i) {
		mRecentImagesPathCache.enqueue(mImagePathStorage->load(i));
	}
}

void RecentImagesPathStore::storeImagePath(const QString &imagePath)
{
	if (mRecentImagesPathCache.contains(imagePath)) {
		return;
	}

	if (mRecentImagesPathCache.size() == mMaxRecentItems) {
		mRecentImagesPathCache.dequeue();
	}

	mRecentImagesPathCache.enqueue(imagePath);
	saveRecentImagesPath();
}

void RecentImagesPathStore::saveRecentImagesPath()
{
	for (auto i = 0 ; i < mRecentImagesPathCache.size(); ++i) {
		mImagePathStorage->store(mRecentImagesPathCache.at(i), i);
	}
}

QStringList RecentImagesPathStore::getRecentImagesPath() const
{
	QStringList reversedList = mRecentImagesPathCache;
	std::reverse(reversedList.begin(), reversedList.end());

	return reversedList;
}
