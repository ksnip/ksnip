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

#include "DeleteImageOperationTests.h"

#include "src/gui/operations/DeleteImageOperation.h"

#include "tests/utils/TestRunner.h"
#include "tests/mocks/gui/messageBoxService/MessageBoxServiceMock.h"
#include "tests/mocks/gui/fileService/FileServiceMock.h"

void DeleteImageOperationTests::Execute_Should_ReturnFalse_When_MessageBoxResponseWasCancel()
{
	// arrange
	auto path = QString("/la/la");
	MessageBoxServiceMock messageBoxServiceMock;
	FileServiceMock fileServiceMock;

	EXPECT_CALL(messageBoxServiceMock, okCancel(testing::_, testing::_))
			.WillRepeatedly([=](const QString &title, const QString &question) {
				return false;
			});

	DeleteImageOperation operation(path, &fileServiceMock, &messageBoxServiceMock);

	EXPECT_CALL(fileServiceMock, remove(path)).Times(testing::Exactly(0));

	// act
	auto result = operation.execute();

	// assert
    QCOMPARE(result, false);
}

void DeleteImageOperationTests::Execute_Should_ReturnTrue_When_MessageBoxResponseWasTrue_And_FileServiceSaveSuccessfully()
{
	// arrange
	auto path = QString("/la/la");
	MessageBoxServiceMock messageBoxServiceMock;
	FileServiceMock fileServiceMock;

	EXPECT_CALL(messageBoxServiceMock, okCancel(testing::_, testing::_))
			.WillRepeatedly([=](const QString &title, const QString &question) {
				return true;
			});

	EXPECT_CALL(fileServiceMock, remove(path))
			.Times(testing::Exactly(1))
			.WillRepeatedly([=](const QString &path) {
				return true;
			});

	DeleteImageOperation operation(path, &fileServiceMock, &messageBoxServiceMock);

	// act
	auto result = operation.execute();

	// assert
    QCOMPARE(result, true);
}

void DeleteImageOperationTests::Execute_Should_ReturnFalse_When_MessageBoxResponseWasTrue_And_FileServiceSaveFailed()
{
	// arrange
	auto path = QString("/la/la");
	MessageBoxServiceMock messageBoxServiceMock;
	FileServiceMock fileServiceMock;

	EXPECT_CALL(messageBoxServiceMock, okCancel(testing::_, testing::_))
			.WillRepeatedly([=](const QString &title, const QString &question) {
				return true;
			});

	EXPECT_CALL(fileServiceMock, remove(path))
			.Times(testing::Exactly(1))
			.WillRepeatedly([=](const QString &path) {
				return false;
			});

	DeleteImageOperation operation(path, &fileServiceMock, &messageBoxServiceMock);

	// act
	auto result = operation.execute();

	// assert
	QCOMPARE(result, false);
}

TEST_MAIN(DeleteImageOperationTests)
