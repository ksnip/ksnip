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

#ifndef KSNIP_RECENTIMAGESPATHSTORETESTS_H
#define KSNIP_RECENTIMAGESPATHSTORETESTS_H

#include <QtTest>

#include "src/backend/recentImages/RecentImagesPathStore.h"

#include "tests/mocks/ImagePathStorageMock.h"

class RecentImagesPathStoreTests : public QObject
{
	Q_OBJECT
private slots:
	void GetRecentImagesPath_Should_ReturnEmptyStringList_When_Initialized();
	void GetRecentImagesPath_Should_ReturnNonEmptyStringList_When_ImagesAreStored();
	void GetRecentImagesPath_Should_ReturnListOfEntriesInReversedOrder();
	void StoreImagesPath_Should_NotSavePath_When_PathAlreadyStored();
	void StoreImagesPath_Should_DropOlderPaths_When_MoreThenTenPathsAdded();
};

#endif //KSNIP_RECENTIMAGESPATHSTORETESTS_H

