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

#include <gtest/gtest.h>

#include "src/backend/recentImages/RecentImagesPathStore.h"

#include "tests/mocks/backend/recentImages/ImagePathStorageMock.h"

TEST(RecentImagesPathStoreTests, GetRecentImagesPath_Should_ReturnEmptyStringList_When_Initialized)
{
	// arrange
	auto imagePathStorageMock = new ImagePathStorageMock;
	RecentImagesPathStore recentImagesPathStore(imagePathStorageMock);

	// act
	auto recentImagesPath = recentImagesPathStore.getRecentImagesPath();

	// assert
	EXPECT_EQ(recentImagesPath.size(), 0);
}

TEST(RecentImagesPathStoreTests, GetRecentImagesPath_Should_ReturnNonEmptyStringList_When_ImagesAreStored)
{
	// arrange
	auto imagePathStorageMock = new ImagePathStorageMock;
	RecentImagesPathStore recentImagesPathStore(imagePathStorageMock);
	recentImagesPathStore.storeImagePath("/path/image.png");
	recentImagesPathStore.storeImagePath("/path/image2.png");

	// act
	auto recentImagesPath =	recentImagesPathStore.getRecentImagesPath();

	// assert
	EXPECT_EQ(recentImagesPath.size(), 2);
	EXPECT_EQ(recentImagesPath.at(0), QStringLiteral("/path/image2.png"));
	EXPECT_EQ(recentImagesPath.at(1), QStringLiteral("/path/image.png"));
}

TEST(RecentImagesPathStoreTests, GetRecentImagesPath_Should_ReturnListOfEntriesInReversedOrder)
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
	EXPECT_EQ(recentImagesPath.size(), 10);
	EXPECT_EQ(recentImagesPath[0], QStringLiteral("/path/image10.png"));
	EXPECT_EQ(recentImagesPath[1], QStringLiteral("/path/image9.png"));
	EXPECT_EQ(recentImagesPath[2], QStringLiteral("/path/image8.png"));
	EXPECT_EQ(recentImagesPath[3], QStringLiteral("/path/image7.png"));
	EXPECT_EQ(recentImagesPath[4], QStringLiteral("/path/image6.png"));
	EXPECT_EQ(recentImagesPath[5], QStringLiteral("/path/image5.png"));
	EXPECT_EQ(recentImagesPath[6], QStringLiteral("/path/image4.png"));
	EXPECT_EQ(recentImagesPath[7], QStringLiteral("/path/image3.png"));
	EXPECT_EQ(recentImagesPath[8], QStringLiteral("/path/image2.png"));
	EXPECT_EQ(recentImagesPath[9], QStringLiteral("/path/image1.png"));
}

TEST(RecentImagesPathStoreTests, StoreImagesPath_Should_NotSavePath_When_PathAlreadyStored)
{
	// arrange
	auto path1 = QStringLiteral("/path/image.png");
	auto path2 = QStringLiteral("/path/image2.png");
	auto imagePathStorageMock = new ImagePathStorageMock;
	RecentImagesPathStore recentImagesPathStore(imagePathStorageMock);

	EXPECT_CALL(*imagePathStorageMock, store(path1, 0)).Times(testing::Exactly(1));

	// act
	recentImagesPathStore.storeImagePath(path1);
	recentImagesPathStore.storeImagePath(path1);

	// assert
	auto recentImagesPath =	recentImagesPathStore.getRecentImagesPath();
	EXPECT_EQ(recentImagesPath.size(), 1);
}

TEST(RecentImagesPathStoreTests, StoreImagesPath_Should_DropOlderPaths_When_MoreThenTenPathsAdded)
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
	EXPECT_EQ(recentImagesPath.size(), 10);
	EXPECT_EQ(recentImagesPath[0], QStringLiteral("/path/image12.png"));
	EXPECT_EQ(recentImagesPath[1], QStringLiteral("/path/image11.png"));
	EXPECT_EQ(recentImagesPath[2], QStringLiteral("/path/image10.png"));
	EXPECT_EQ(recentImagesPath[3], QStringLiteral("/path/image9.png"));
	EXPECT_EQ(recentImagesPath[4], QStringLiteral("/path/image8.png"));
	EXPECT_EQ(recentImagesPath[5], QStringLiteral("/path/image7.png"));
	EXPECT_EQ(recentImagesPath[6], QStringLiteral("/path/image6.png"));
	EXPECT_EQ(recentImagesPath[7], QStringLiteral("/path/image5.png"));
	EXPECT_EQ(recentImagesPath[8], QStringLiteral("/path/image4.png"));
	EXPECT_EQ(recentImagesPath[9], QStringLiteral("/path/image3.png"));
}
