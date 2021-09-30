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

#include <QCoreApplication>

#include <gtest/gtest.h>

#include "src/backend/commandLine/CommandLineCaptureHandler.h"

#include "tests/mocks/backend/uploader/UploadHandlerMock.h"
#include "tests/mocks/backend/imageGrabber/ImageGrabberMock.h"

TEST(CommandLineCaptureHandler, CaptureAndProcessScreenshot_Should_CallUploader_When_UploadOptionSet)
{
	// arrange
	auto imageGrabber = QSharedPointer<IImageGrabber>(new ImageGrabberMock);
	auto uploadHandler = QSharedPointer<IUploadHandler>(new UploadHandlerMock);

	auto imageGrabberMock = dynamic_cast<ImageGrabberMock*>(imageGrabber.data());
	auto uploadHandlerMock = dynamic_cast<UploadHandlerMock*>(uploadHandler.data());

	CommandLineCaptureParameter parameter;
	parameter.isWithUpload = true;

	auto captureDto = CaptureDto(QPixmap());


	EXPECT_CALL(*imageGrabberMock, grabImage(testing::_, testing::_, testing::_))
		.WillRepeatedly([imageGrabberMock, captureDto](CaptureModes mode, bool cursor, int delay) {
		imageGrabberMock->finished(captureDto);
	});

	EXPECT_CALL(*uploadHandlerMock, upload(captureDto.screenshot.toImage())).Times(testing::Exactly(1));

	CommandLineCaptureHandler commandLineCaptureHandler(imageGrabber, uploadHandler);

	// act & assert
	commandLineCaptureHandler.captureAndProcessScreenshot(parameter);
}

TEST(CommandLineCaptureHandler, CaptureAndProcessScreenshot_Should_NotCallUploader_When_UploadOptionNotSet)
{
	// arrange
	auto imageGrabber = QSharedPointer<IImageGrabber>(new ImageGrabberMock);
	auto uploadHandler = QSharedPointer<IUploadHandler>(new UploadHandlerMock);

	auto imageGrabberMock = dynamic_cast<ImageGrabberMock*>(imageGrabber.data());
	auto uploadHandlerMock = dynamic_cast<UploadHandlerMock*>(uploadHandler.data());

	CommandLineCaptureParameter parameter;
	parameter.isWithUpload = false;

	EXPECT_CALL(*imageGrabberMock, grabImage(testing::_, testing::_, testing::_))
			.WillRepeatedly([imageGrabberMock](CaptureModes mode, bool cursor, int delay) {
				imageGrabberMock->finished(CaptureDto(QPixmap()));
			});

	EXPECT_CALL(*uploadHandlerMock, upload(testing::_)).Times(testing::Exactly(0));

	CommandLineCaptureHandler commandLineCaptureHandler(imageGrabber, uploadHandler);

	// act & assert
	commandLineCaptureHandler.captureAndProcessScreenshot(parameter);
}

int main(int argc, char **argv) {
	QCoreApplication guiApplication(argc, argv);
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
