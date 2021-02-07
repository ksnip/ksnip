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

void SingleCaptureHandlerTests::RemoveImage_Should_CleanupAnnotationData_When_ImageDeleted()
{
	ImageAnnotatorMock imageAnnotatorMock;
	ServiceLocatorMock serviceLocatorMock;
	serviceLocatorMock.messageBoxService_mock()->okCancel_set(true);
	serviceLocatorMock.fileService_mock()->remove_set(true);
	SingleCaptureHandler captureHandler(&imageAnnotatorMock, nullptr, &serviceLocatorMock, nullptr);
	auto capture = CaptureFromFileDto(QPixmap(), QLatin1Literal("lala"));
	captureHandler.load(capture);

	captureHandler.removeImage();

	QCOMPARE(imageAnnotatorMock.hide_callCounter(), 1);
	QCOMPARE(captureHandler.path(), QString());
	QCOMPARE(captureHandler.isSaved(), true);
}

void SingleCaptureHandlerTests::RemoveImage_Should_NotCleanupAnnotationData_When_ImageWasNotDeleted()
{
	ImageAnnotatorMock imageAnnotatorMock;
	ServiceLocatorMock serviceLocatorMock;
	serviceLocatorMock.messageBoxService_mock()->okCancel_set(false);
	SingleCaptureHandler captureHandler(&imageAnnotatorMock, nullptr, &serviceLocatorMock, nullptr);
	auto capture = CaptureFromFileDto(QPixmap(), QLatin1Literal("lala"));
	captureHandler.load(capture);

	captureHandler.removeImage();

	QCOMPARE(imageAnnotatorMock.hide_callCounter(), 0);
	QCOMPARE(captureHandler.path(), capture.path);
	QCOMPARE(captureHandler.isSaved(), true);
}

void SingleCaptureHandlerTests::Load_Should_SetPathAndIsSavedToValuesFromCaptureDto_When_CaptureLoadedFromFile()
{
	ImageAnnotatorMock imageAnnotatorMock;
	ServiceLocatorMock serviceLocatorMock;
	SingleCaptureHandler captureHandler(&imageAnnotatorMock, nullptr, &serviceLocatorMock, nullptr);
	auto capture = CaptureFromFileDto(QPixmap(), QLatin1Literal("lala"));

	captureHandler.load(capture);

	QCOMPARE(captureHandler.path(), capture.path);
	QCOMPARE(captureHandler.isSaved(), true);
}

void SingleCaptureHandlerTests::Load_Should_SetPathToEmptyAndIsSavedToFalse_When_CaptureNotLoadedFromFile()
{
	ImageAnnotatorMock imageAnnotatorMock;
	ServiceLocatorMock serviceLocatorMock;
	SingleCaptureHandler captureHandler(&imageAnnotatorMock, nullptr, &serviceLocatorMock, nullptr);
	auto capture = CaptureDto(QPixmap());

	captureHandler.load(capture);

	QCOMPARE(captureHandler.path(), QString());
	QCOMPARE(captureHandler.isSaved(), false);
}

QTEST_MAIN(SingleCaptureHandlerTests)