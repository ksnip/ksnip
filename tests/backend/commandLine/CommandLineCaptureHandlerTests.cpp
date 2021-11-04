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

#include "CommandLineCaptureHandlerTests.h"

#include "src/backend/commandLine/CommandLineCaptureHandler.h"

#include "tests/utils/TestRunner.h"
#include "tests/mocks/backend/uploader/UploadHandlerMock.h"
#include "tests/mocks/backend/imageGrabber/ImageGrabberMock.h"
#include "tests/mocks/backend/saver/ImageSaverMock.h"
#include "tests/mocks/backend/saver/SavePathProviderMock.h"

void CommandLineCaptureHandlerTests::CaptureAndProcessScreenshot_Should_CallUploader_When_UploadOptionSet()
{
	// arrange
	auto imageGrabberMock = QSharedPointer<ImageGrabberMock>(new ImageGrabberMock);
	auto uploadHandlerMock = QSharedPointer<UploadHandlerMock>(new UploadHandlerMock);

	CommandLineCaptureParameter parameter;
	parameter.isWithUpload = true;

	auto captureDto = CaptureDto(QPixmap());

	EXPECT_CALL(*imageGrabberMock, grabImage(testing::_, testing::_, testing::_))
		.WillRepeatedly([imageGrabberMock, captureDto](CaptureModes mode, bool cursor, int delay) {
			imageGrabberMock->finished(captureDto);
			testing::Mock::VerifyAndClearExpectations(imageGrabberMock.get());
		});

	EXPECT_CALL(*uploadHandlerMock, upload(captureDto.screenshot.toImage())).Times(testing::Exactly(1));

	CommandLineCaptureHandler commandLineCaptureHandler(imageGrabberMock, uploadHandlerMock, nullptr, nullptr);

	// act & assert
	commandLineCaptureHandler.captureAndProcessScreenshot(parameter);
}

void CommandLineCaptureHandlerTests::CaptureAndProcessScreenshot_Should_NotCallUploader_When_UploadOptionNotSet()
{
	// arrange
	auto imageGrabberMock = QSharedPointer<ImageGrabberMock>(new ImageGrabberMock);
	auto uploadHandlerMock = QSharedPointer<UploadHandlerMock>(new UploadHandlerMock);

	CommandLineCaptureParameter parameter;
	parameter.isWithUpload = false;

	EXPECT_CALL(*imageGrabberMock, grabImage(testing::_, testing::_, testing::_))
			.WillRepeatedly([imageGrabberMock](CaptureModes mode, bool cursor, int delay) {
				imageGrabberMock->finished(CaptureDto(QPixmap()));
				testing::Mock::VerifyAndClearExpectations(imageGrabberMock.get());
			});

	EXPECT_CALL(*uploadHandlerMock, upload(testing::_)).Times(testing::Exactly(0));

	CommandLineCaptureHandler commandLineCaptureHandler(imageGrabberMock, uploadHandlerMock, nullptr, nullptr);

	// act & assert
	commandLineCaptureHandler.captureAndProcessScreenshot(parameter);
}

void CommandLineCaptureHandlerTests::CaptureAndProcessScreenshot_Should_CallImageSaverWithDefaultSavePath_When_SaveOptionSetAndSavePathEmpty()
{
	// arrange
	auto defaultSavePath = QString("/my/default/save/path");
	auto imageGrabberMock = QSharedPointer<ImageGrabberMock>(new ImageGrabberMock);
	auto uploadHandlerMock = QSharedPointer<UploadHandlerMock>(new UploadHandlerMock);
	auto imageSaverMock = QSharedPointer<ImageSaverMock>(new ImageSaverMock);
	auto savePathProviderMock = QSharedPointer<SavePathProviderMock>(new SavePathProviderMock);

	CommandLineCaptureParameter parameter;
	parameter.isWithSave = true;
	parameter.savePath = QString();

	EXPECT_CALL(*imageGrabberMock, grabImage(testing::_, testing::_, testing::_))
			.WillRepeatedly([imageGrabberMock](CaptureModes mode, bool cursor, int delay) {
				imageGrabberMock->finished(CaptureDto(QPixmap()));
				testing::Mock::VerifyAndClearExpectations(imageGrabberMock.get());
			});

	EXPECT_CALL(*imageSaverMock, save(testing::_, defaultSavePath))
			.Times(testing::Exactly(1))
			.WillRepeatedly([=]() {
				return true;
			});

	EXPECT_CALL(*savePathProviderMock, savePath())
			.Times(testing::Exactly(1))
			.WillRepeatedly([defaultSavePath]() {
				return defaultSavePath;
			});

	CommandLineCaptureHandler commandLineCaptureHandler(imageGrabberMock, uploadHandlerMock, imageSaverMock, savePathProviderMock);

	// act & assert
	commandLineCaptureHandler.captureAndProcessScreenshot(parameter);
}

void CommandLineCaptureHandlerTests::CaptureAndProcessScreenshot_Should_CallImageSaverWithSavePath_When_SaveOptionSetAndSavePathNotEmpty()
{
	// arrange
	auto savePath = QString("/my/default/save/path");
	auto captureDto = CaptureDto(QPixmap());
	auto imageGrabberMock = QSharedPointer<ImageGrabberMock>(new ImageGrabberMock);
	auto uploadHandlerMock = QSharedPointer<UploadHandlerMock>(new UploadHandlerMock);
	auto imageSaverMock = QSharedPointer<ImageSaverMock>(new ImageSaverMock);
	auto savePathProviderMock = QSharedPointer<SavePathProviderMock>(new SavePathProviderMock);

	CommandLineCaptureParameter parameter;
	parameter.isWithSave = true;
	parameter.savePath = savePath;

	EXPECT_CALL(*imageGrabberMock, grabImage(testing::_, testing::_, testing::_))
			.WillRepeatedly([imageGrabberMock, captureDto](CaptureModes mode, bool cursor, int delay) {
				imageGrabberMock->finished(captureDto);
				testing::Mock::VerifyAndClearExpectations(imageGrabberMock.get());
			});

	EXPECT_CALL(*imageSaverMock, save(captureDto.screenshot.toImage(), savePath))
			.Times(testing::Exactly(1))
			.WillRepeatedly([=]() {
				return true;
			});

	EXPECT_CALL(*savePathProviderMock, savePath())
			.Times(testing::Exactly(0));

	CommandLineCaptureHandler commandLineCaptureHandler(imageGrabberMock, uploadHandlerMock, imageSaverMock, savePathProviderMock);

	// act & assert
	commandLineCaptureHandler.captureAndProcessScreenshot(parameter);
}

TEST_MAIN(CommandLineCaptureHandlerTests)
