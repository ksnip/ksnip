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

#include "SingleCaptureHandlerTests.h"

#include "src/gui/captureHandler/SingleCaptureHandler.h"

#include "tests/mocks/gui/imageAnnotator/ImageAnnotatorMock.h"
#include "tests/mocks/gui/NotificationServiceMock.h"
#include "tests/mocks/gui/fileService/FileServiceMock.h"
#include "tests/mocks/gui/desktopService/DesktopServiceMock.h"
#include "tests/mocks/gui/clipboard/ClipboardMock.h"
#include "tests/mocks/gui/messageBoxService/MessageBoxServiceMock.h"
#include "tests/mocks/backend/recentImages/RecentImageServiceMock.h"

void SingleCaptureHandlerTests::RemoveImage_Should_CleanupAnnotationData_When_ImageDeleted()
{
	// arrange
	ImageAnnotatorMock imageAnnotatorMock;
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto clipboardMock = QSharedPointer<ClipboardMock>(new ClipboardMock);
	auto desktopServiceMock = QSharedPointer<DesktopServiceMock>(new DesktopServiceMock);
	auto fileServiceMock = QSharedPointer<FileServiceMock>(new FileServiceMock);
	auto messageBoxServiceMock = QSharedPointer<MessageBoxServiceMock>(new MessageBoxServiceMock);
	auto recentImageServiceMock = QSharedPointer<RecentImageServiceMock>(new RecentImageServiceMock);

	EXPECT_CALL(imageAnnotatorMock, loadImage(testing::_));
	EXPECT_CALL(imageAnnotatorMock, setTabBarAutoHide(testing::_));

	EXPECT_CALL(*messageBoxServiceMock, okCancel(testing::_, testing::_))
			.WillRepeatedly([=](const QString &title, const QString &question) {
				return true;
			});

	EXPECT_CALL(*fileServiceMock, remove(testing::_))
			.Times(testing::Exactly(1))
			.WillRepeatedly([=](const QString &path) {
				return true;
			});

	EXPECT_CALL(imageAnnotatorMock, hide()).Times(testing::Exactly(1));

	SingleCaptureHandler captureHandler(
			&imageAnnotatorMock,
			notificationServiceMock,
			clipboardMock,
			desktopServiceMock,
			fileServiceMock,
			messageBoxServiceMock,
			recentImageServiceMock,
			nullptr);

	auto capture = CaptureFromFileDto(QPixmap(), QLatin1Literal("lala"));
	captureHandler.load(capture);

	// act
	captureHandler.removeImage();

	// assert
    QCOMPARE(captureHandler.path(), QString());
    QCOMPARE(captureHandler.isSaved(), true);
}

void SingleCaptureHandlerTests::RemoveImage_Should_NotCleanupAnnotationData_When_ImageWasNotDeleted()
{
	// arrange
	ImageAnnotatorMock imageAnnotatorMock;
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto clipboardMock = QSharedPointer<ClipboardMock>(new ClipboardMock);
	auto desktopServiceMock = QSharedPointer<DesktopServiceMock>(new DesktopServiceMock);
	auto fileServiceMock = QSharedPointer<FileServiceMock>(new FileServiceMock);
	auto messageBoxServiceMock = QSharedPointer<MessageBoxServiceMock>(new MessageBoxServiceMock);
	auto recentImageServiceMock = QSharedPointer<RecentImageServiceMock>(new RecentImageServiceMock);

	EXPECT_CALL(imageAnnotatorMock, loadImage(testing::_));
	EXPECT_CALL(imageAnnotatorMock, setTabBarAutoHide(testing::_));

	EXPECT_CALL(*messageBoxServiceMock, okCancel(testing::_, testing::_))
			.WillRepeatedly([=](const QString &title, const QString &question) {
				return false;
			});

	EXPECT_CALL(imageAnnotatorMock, hide()).Times(testing::Exactly(0));

	SingleCaptureHandler captureHandler(
			&imageAnnotatorMock,
			notificationServiceMock,
			clipboardMock,
			desktopServiceMock,
			fileServiceMock,
			messageBoxServiceMock,
			recentImageServiceMock,
			nullptr);
	auto capture = CaptureFromFileDto(QPixmap(), QLatin1Literal("lala"));
	captureHandler.load(capture);

	// act
	captureHandler.removeImage();

	// assert
    QCOMPARE(captureHandler.path(), capture.path);
    QCOMPARE(captureHandler.isSaved(), true);
}

void SingleCaptureHandlerTests::Load_Should_SetPathAndIsSavedToValuesFromCaptureDto_When_CaptureLoadedFromFile()
{
	// arrange
	ImageAnnotatorMock imageAnnotatorMock;
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto clipboardMock = QSharedPointer<ClipboardMock>(new ClipboardMock);
	auto desktopServiceMock = QSharedPointer<DesktopServiceMock>(new DesktopServiceMock);
	auto fileServiceMock = QSharedPointer<FileServiceMock>(new FileServiceMock);
	auto messageBoxServiceMock = QSharedPointer<MessageBoxServiceMock>(new MessageBoxServiceMock);
	auto recentImageServiceMock = QSharedPointer<RecentImageServiceMock>(new RecentImageServiceMock);

	EXPECT_CALL(imageAnnotatorMock, loadImage(testing::_));
	EXPECT_CALL(imageAnnotatorMock, setTabBarAutoHide(testing::_));

	SingleCaptureHandler captureHandler(
			&imageAnnotatorMock,
			notificationServiceMock,
			clipboardMock,
			desktopServiceMock,
			fileServiceMock,
			messageBoxServiceMock,
			recentImageServiceMock,
			nullptr);

	auto capture = CaptureFromFileDto(QPixmap(), QLatin1Literal("lala"));

	// act
	captureHandler.load(capture);

	// assert
    QCOMPARE(captureHandler.path(), capture.path);
    QCOMPARE(captureHandler.isSaved(), true);
}

void SingleCaptureHandlerTests::Load_Should_SetPathToEmptyAndIsSavedToFalse_When_CaptureNotLoadedFromFile()
{
	// arrange
	ImageAnnotatorMock imageAnnotatorMock;
	auto notificationServiceMock = QSharedPointer<NotificationServiceMock>(new NotificationServiceMock);
	auto clipboardMock = QSharedPointer<ClipboardMock>(new ClipboardMock);
	auto desktopServiceMock = QSharedPointer<DesktopServiceMock>(new DesktopServiceMock);
	auto fileServiceMock = QSharedPointer<FileServiceMock>(new FileServiceMock);
	auto messageBoxServiceMock = QSharedPointer<MessageBoxServiceMock>(new MessageBoxServiceMock);
	auto recentImageServiceMock = QSharedPointer<RecentImageServiceMock>(new RecentImageServiceMock);

	EXPECT_CALL(imageAnnotatorMock, loadImage(testing::_));
	EXPECT_CALL(imageAnnotatorMock, setTabBarAutoHide(testing::_));

	SingleCaptureHandler captureHandler(
			&imageAnnotatorMock,
			notificationServiceMock,
			clipboardMock,
			desktopServiceMock,
			fileServiceMock,
			messageBoxServiceMock,
			recentImageServiceMock,
			nullptr);
	auto capture = CaptureDto(QPixmap());

	// act
	captureHandler.load(capture);

	// assert
	QCOMPARE(captureHandler.path(), QString());
    QCOMPARE(captureHandler.isSaved(), false);
}

QTEST_MAIN(SingleCaptureHandlerTests)
