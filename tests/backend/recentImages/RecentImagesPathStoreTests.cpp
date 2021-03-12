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

#include "RecentImagesPathStoreTests.h"

void RecentImagesPathStoreTests::GetRecentImagesPath_Should_ReturnEmptyStringList_When_Initialized()
{
	// arrange
	auto imagePathStorageMock = new ImagePathStorageMock;
	RecentImagesPathStore recentImagesPathStore(imagePathStorageMock);

	// act
	auto recentImagesPath = recentImagesPathStore.getRecentImagesPath();

	// assert
	QCOMPARE(recentImagesPath.size(), 0);
}

void RecentImagesPathStoreTests::GetRecentImagesPath_Should_ReturnNonEmptyStringList_When_ImagesAreStored()
{
	// arrange
	auto imagePathStorageMock = new ImagePathStorageMock;
	RecentImagesPathStore recentImagesPathStore(imagePathStorageMock);
	recentImagesPathStore.storeImagePath("/path/image.png");
	recentImagesPathStore.storeImagePath("/path/image2.png");

	// act
	auto recentImagesPath =	recentImagesPathStore.getRecentImagesPath();

	// assert
	QCOMPARE(recentImagesPath.size(), 2);
	QCOMPARE(recentImagesPath.at(0), QStringLiteral("/path/image2.png"));
	QCOMPARE(recentImagesPath.at(1), QStringLiteral("/path/image.png"));
}

void RecentImagesPathStoreTests::GetRecentImagesPath_Should_ReturnListOfEntriesInReversedOrder()
{
	// arrange
	auto imagePathStorageMock = new ImagePathStorageMock;
	RecentImagesPathStore recentImagesPathStore(imagePathStorageMock);
	recentImagesPathStore.storeImagePath("/path/image1.png");
	recentImagesPathStore.storeImagePath("/path/image2.png");
	recentImagesPathStore.storeImagePath("/path/image3.png");
	recentImagesPathStore.storeImagePath("/path/image4.png");
	recentImagesPathStore.storeImagePath("/path/image5.png");
	recentImagesPathStore.storeImagePath("/path/image6.png");
	recentImagesPathStore.storeImagePath("/path/image7.png");
	recentImagesPathStore.storeImagePath("/path/image8.png");
	recentImagesPathStore.storeImagePath("/path/image9.png");
	recentImagesPathStore.storeImagePath("/path/image10.png");

	// act
	auto recentImagesPath =	recentImagesPathStore.getRecentImagesPath();

	// assert
	QCOMPARE(recentImagesPath.size(), 10);
	QCOMPARE(recentImagesPath[0], QStringLiteral("/path/image10.png"));
	QCOMPARE(recentImagesPath[1], QStringLiteral("/path/image9.png"));
	QCOMPARE(recentImagesPath[2], QStringLiteral("/path/image8.png"));
	QCOMPARE(recentImagesPath[3], QStringLiteral("/path/image7.png"));
	QCOMPARE(recentImagesPath[4], QStringLiteral("/path/image6.png"));
	QCOMPARE(recentImagesPath[5], QStringLiteral("/path/image5.png"));
	QCOMPARE(recentImagesPath[6], QStringLiteral("/path/image4.png"));
	QCOMPARE(recentImagesPath[7], QStringLiteral("/path/image3.png"));
	QCOMPARE(recentImagesPath[8], QStringLiteral("/path/image2.png"));
	QCOMPARE(recentImagesPath[9], QStringLiteral("/path/image1.png"));
}

void RecentImagesPathStoreTests::StoreImagesPath_Should_NotSavePath_When_PathAlreadyStored()
{
	// arrange
	auto imagePathStorageMock = new ImagePathStorageMock;
	RecentImagesPathStore recentImagesPathStore(imagePathStorageMock);
	recentImagesPathStore.storeImagePath("/path/image.png");
	recentImagesPathStore.storeImagePath("/path/image2.png");

	// act
	recentImagesPathStore.storeImagePath("/path/image.png");

	// assert
	auto recentImagesPath =	recentImagesPathStore.getRecentImagesPath();
	QCOMPARE(recentImagesPath.size(), 2);
	QCOMPARE(imagePathStorageMock->count(), 2);
	QCOMPARE(imagePathStorageMock->store_callCounter(0), 1);
	QCOMPARE(imagePathStorageMock->store_callCounter(1), 1);
}

void RecentImagesPathStoreTests::StoreImagesPath_Should_DropOlderPaths_When_MoreThenTenPathsAdded()
{
	// arrange
	auto imagePathStorageMock = new ImagePathStorageMock;
	RecentImagesPathStore recentImagesPathStore(imagePathStorageMock);
	recentImagesPathStore.storeImagePath("/path/image1.png");
	recentImagesPathStore.storeImagePath("/path/image2.png");
	recentImagesPathStore.storeImagePath("/path/image3.png");
	recentImagesPathStore.storeImagePath("/path/image4.png");
	recentImagesPathStore.storeImagePath("/path/image5.png");
	recentImagesPathStore.storeImagePath("/path/image6.png");
	recentImagesPathStore.storeImagePath("/path/image7.png");
	recentImagesPathStore.storeImagePath("/path/image8.png");
	recentImagesPathStore.storeImagePath("/path/image9.png");
	recentImagesPathStore.storeImagePath("/path/image10.png");

	// act
	recentImagesPathStore.storeImagePath("/path/image11.png");
	recentImagesPathStore.storeImagePath("/path/image12.png");

	// assert
	auto recentImagesPath =	recentImagesPathStore.getRecentImagesPath();
	QCOMPARE(recentImagesPath.size(), 10);
	QCOMPARE(recentImagesPath[0], QStringLiteral("/path/image12.png"));
	QCOMPARE(recentImagesPath[1], QStringLiteral("/path/image11.png"));
	QCOMPARE(recentImagesPath[2], QStringLiteral("/path/image10.png"));
	QCOMPARE(recentImagesPath[3], QStringLiteral("/path/image9.png"));
	QCOMPARE(recentImagesPath[4], QStringLiteral("/path/image8.png"));
	QCOMPARE(recentImagesPath[5], QStringLiteral("/path/image7.png"));
	QCOMPARE(recentImagesPath[6], QStringLiteral("/path/image6.png"));
	QCOMPARE(recentImagesPath[7], QStringLiteral("/path/image5.png"));
	QCOMPARE(recentImagesPath[8], QStringLiteral("/path/image4.png"));
	QCOMPARE(recentImagesPath[9], QStringLiteral("/path/image3.png"));
}

QTEST_MAIN(RecentImagesPathStoreTests)
