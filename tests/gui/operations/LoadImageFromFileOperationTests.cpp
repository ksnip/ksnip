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

void LoadImageFromFileOperationTests::Execute_Should_ShowNotificationAndNotOpenImage_When_PathToImageCannotBeOpened()
{
	// arrange
	ImageProcessorMock imageProcessorMock;
	ServiceLocatorMock serviceLocatorMock;
	ToastServiceMock toastServiceMock;
	serviceLocatorMock.fileService_mock()->openPixmap_set(QPixmap());
	LoadImageFromFileOperation operation(&imageProcessorMock, QLatin1String("/path/image.png"), &toastServiceMock, &serviceLocatorMock);

	// act
	auto result = operation.execute();

	// assert
	QCOMPARE(result, false);
	QCOMPARE(imageProcessorMock.processImage_callCounter(), 0);
	QCOMPARE(serviceLocatorMock.recentImageService_mock()->storeImagePath_callCounter(), 0);
	QCOMPARE(toastServiceMock.showWarningToast_callCounter(QLatin1String("Unable to open image from path /path/image.png")), 1);
}

void LoadImageFromFileOperationTests::Execute_Should_OpenImageAndNotShowNotification_When_PathToImageCanBeOpened()
{
	// arrange
	ImageProcessorMock imageProcessorMock;
	ServiceLocatorMock serviceLocatorMock;
	ToastServiceMock toastServiceMock;
	serviceLocatorMock.fileService_mock()->openPixmap_set(QPixmap(100, 100));
	LoadImageFromFileOperation operation(&imageProcessorMock, QLatin1String("/path/image.png"), &toastServiceMock, &serviceLocatorMock);

	// act
	auto result = operation.execute();

	// assert
	QCOMPARE(result, true);
	QCOMPARE(imageProcessorMock.processImage_callCounter(), 1);
	QCOMPARE(serviceLocatorMock.recentImageService_mock()->storeImagePath_callCounter(QLatin1String("/path/image.png")), 1);
	QCOMPARE(toastServiceMock.showWarningToast_callCounter(), 0);
}

QTEST_MAIN(LoadImageFromFileOperationTests)
