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

void DeleteImageOperationTests::Execute_Should_ReturnFalse_When_MessageBoxResponseWasCancel()
{
	auto path = QLatin1Literal("/la/la");
	auto messageBoxServiceMock = new MessageBoxServiceMock;
	messageBoxServiceMock->okCancel_set(false);
	auto fileServiceMock = new FileServiceMock;
	DeleteImageOperation operation(path, fileServiceMock, messageBoxServiceMock);

	auto result = operation.execute();

	QCOMPARE(result, false);
	QCOMPARE(fileServiceMock->remove_callCounter(path), 0);
}

void DeleteImageOperationTests::Execute_Should_ReturnTrue_When_MessageBoxResponseWasTrue_And_FileServiceSaveSuccessfully()
{
	auto path = QLatin1Literal("/la/la");
	auto messageBoxServiceMock = new MessageBoxServiceMock;
	messageBoxServiceMock->okCancel_set(true);
	auto fileServiceMock = new FileServiceMock;
	fileServiceMock->remove_set(true);
	DeleteImageOperation operation(path, fileServiceMock, messageBoxServiceMock);

	auto result = operation.execute();

	QCOMPARE(result, true);
	QCOMPARE(fileServiceMock->remove_callCounter(path), 1);
}

void DeleteImageOperationTests::Execute_Should_ReturnFalse_When_MessageBoxResponseWasTrue_And_FileServiceSaveFailed()
{
	auto path = QLatin1Literal("/la/la");
	auto messageBoxServiceMock = new MessageBoxServiceMock;
	messageBoxServiceMock->okCancel_set(true);
	auto fileServiceMock = new FileServiceMock;
	fileServiceMock->remove_set(false);
	DeleteImageOperation operation(path, fileServiceMock, messageBoxServiceMock);

	auto result = operation.execute();

	QCOMPARE(result, false);
	QCOMPARE(fileServiceMock->remove_callCounter(path), 1);
}

QTEST_MAIN(DeleteImageOperationTests)
