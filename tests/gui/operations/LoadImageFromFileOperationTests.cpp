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

#include "LoadImageFromFileOperationTests.h"

#include "src/gui/operations/LoadImageFromFileOperation.h"

#include "tests/utils/TestRunner.h"
#include "tests/mocks/gui/NotificationServiceMock.h"
#include "tests/mocks/gui/ImageProcessorMock.h"
#include "tests/mocks/gui/fileService/FileServiceMock.h"
#include "tests/mocks/backend/recentImages/RecentImageServiceMock.h"
#include "tests/mocks/backend/config/ConfigMock.h"

void LoadImageFromFileOperationTests::Execute_Should_ShowNotificationAndNotOpenImage_When_PathToImageCannotBeOpened()
{
	// arrange
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto imageProcessorMock = QSharedPointer<ImageProcessorMock>(new ImageProcessorMock);
	auto recentImageServiceMock = QSharedPointer<RecentImageServiceMock>(new RecentImageServiceMock);
	auto fileServiceMock = QSharedPointer<FileServiceMock>(new FileServiceMock);
	auto configMock = QSharedPointer<ConfigMock>(new ConfigMock);

	EXPECT_CALL(*fileServiceMock, openPixmap(testing::_))
			.WillRepeatedly([=](const QString &path) {
				return QPixmap();
			});

	EXPECT_CALL(*imageProcessorMock, processImage(testing::_)).Times(testing::Exactly(0));
	EXPECT_CALL(*recentImageServiceMock, storeImagePath(testing::_)).Times(testing::Exactly(0));
	EXPECT_CALL(*notificationServiceMock, showWarning(testing::_, QString("Unable to open image from path /path/image.png"), testing::_))
		.Times(testing::Exactly(1));

	EXPECT_CALL(*configMock, trayIconNotificationsEnabled())
		.Times(testing::Exactly(1))
		.WillRepeatedly([=]() {
			return true;
		});

	LoadImageFromFileOperation operation(QLatin1String("/path/image.png"), imageProcessorMock, notificationServiceMock, recentImageServiceMock, fileServiceMock, configMock);

	// act
	auto result = operation.execute();

	// assert
	QCOMPARE(result, false);
}

void LoadImageFromFileOperationTests::Execute_Should_OpenImageAndNotShowNotification_When_PathToImageCanBeOpened()
{
	// arrange
	auto imagePath = QString("/path/image.png");
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto imageProcessorMock = QSharedPointer<ImageProcessorMock>(new ImageProcessorMock);
	auto recentImageServiceMock = QSharedPointer<RecentImageServiceMock>(new RecentImageServiceMock);
	auto fileServiceMock = QSharedPointer<FileServiceMock>(new FileServiceMock);
	auto configMock = QSharedPointer<ConfigMock>(new ConfigMock);

	EXPECT_CALL(*fileServiceMock, openPixmap(imagePath))
			.WillRepeatedly([=](const QString &path) {
				return QPixmap(100, 100);
			});

	EXPECT_CALL(*imageProcessorMock, processImage(testing::_)).Times(testing::Exactly(1));
	EXPECT_CALL(*recentImageServiceMock, storeImagePath(imagePath)).Times(testing::Exactly(1));
	EXPECT_CALL(*notificationServiceMock, showWarning(testing::_, testing::_, testing::_)).Times(testing::Exactly(0));

	EXPECT_CALL(*configMock, trayIconNotificationsEnabled()).Times(testing::Exactly(0));

	LoadImageFromFileOperation operation(imagePath, imageProcessorMock, notificationServiceMock, recentImageServiceMock, fileServiceMock, configMock);

	// act
	auto result = operation.execute();

	// assert
	QCOMPARE(result, true);
}

TEST_MAIN(LoadImageFromFileOperationTests)
