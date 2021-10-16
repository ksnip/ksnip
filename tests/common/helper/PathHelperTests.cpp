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

#include "PathHelperTests.h"

#include "src/common/helper/PathHelper.h"

#include "tests/utils/TestRunner.h"

void PathHelperTests::IsPathValid_Should_ReturnFalse_When_StringEmpty()
{
	// arrange
	auto input = QStringLiteral("");

	// act
	auto result = PathHelper::isPathValid(input);

	// assert
	QCOMPARE(result, false);
}

void PathHelperTests::IsPathValid_Should_ReturnFalse_When_StringNull()
{
	// arrange
	auto input = QString();

	// act
	auto result = PathHelper::isPathValid(input);

	// assert
    QCOMPARE(result, false);
}

void PathHelperTests::IsPathValid_Should_ReturnTrue_When_StringHasContent()
{
	// arrange
	auto input = QStringLiteral("lala");

	// act
	auto result = PathHelper::isPathValid(input);

	// assert
    QCOMPARE(result, true);
}

void PathHelperTests::IsPipePath_Should_ReturnTrue_When_PathIsDash()
{
	// arrange
	auto input = QStringLiteral("-");

	// act
	auto result = PathHelper::isPipePath(input);

	// assert
    QCOMPARE(result, true);
}

void PathHelperTests::IsPipePath_Should_ReturnFalse_When_PathIsNull()
{
	// arrange
	auto input = QString();

	// act
	auto result = PathHelper::isPipePath(input);

	// assert
    QCOMPARE(result, false);
}

void PathHelperTests::IsPipePath_Should_ReturnFalse_When_PathIsEmpty()
{
	// arrange
	auto input = QLatin1Literal("");

	// act
	auto result = PathHelper::isPipePath(input);

	// assert
    QCOMPARE(result, false);
}

void PathHelperTests::ExtractParentDirectory_Should_ReturnStringWithParentDirectoryPath()
{
	// arrange
	auto expected = QStringLiteral("/theRoot/theHome/myHome");

	// act
	auto result = PathHelper::extractParentDirectory(expected + QStringLiteral("/theFile.me"));

	// assert
    QCOMPARE(result, expected);
}

void PathHelperTests::ExtractFilename_Should_ReturnStringWithFilenameWithoutFormat_When_FormatExists()
{
	// arrange
	auto expected = QStringLiteral("theFile");

	// act
	auto result = PathHelper::extractFilename(QStringLiteral("/theRoot/theHome/myHome/") + expected + QStringLiteral(".me"));

	// assert
    QCOMPARE(result, expected);
}

void PathHelperTests::ExtractFilename_Should_ReturnStringWithFilenameWithoutFormat_When_NoFormatExists()
{
	// arrange
	auto expected = QStringLiteral("theFile");

	// act
	auto result = PathHelper::extractFilename(QStringLiteral("/theRoot/theHome/myHome/") + expected);

	// assert
    QCOMPARE(result, expected);
}

void PathHelperTests::ExtractFilenameWithFormat_Should_ReturnStringWithFilenameWithFormat_When_FormatExists()
{
	// arrange
	auto expected = QStringLiteral("theFile.me");

	// act
	auto result = PathHelper::extractFilenameWithFormat(QStringLiteral("/theRoot/theHome/myHome/") + expected);

	// assert
    QCOMPARE(result, expected);
}

void PathHelperTests::ExtractFilenameWithFormat_Should_ReturnStringWithFilenameWithFormat_When_NoFormatExists()
{
	// arrange
	auto expected = QStringLiteral("theFile");

	// act
	auto result = PathHelper::extractFilenameWithFormat(QStringLiteral("/theRoot/theHome/myHome/") + expected);

	// assert
    QCOMPARE(result, expected);
}

void PathHelperTests::ExtractFormat_Should_ReturnWithFormat_When_FormatExists()
{
	// arrange
	auto expected = QStringLiteral("me");

	// act
	auto result = PathHelper::extractFormat(QStringLiteral("/theRoot/theHome/myHome/theFile.") + expected);

	// assert
    QCOMPARE(result, expected);
}

void PathHelperTests::ExtractFormat_Should_ReturnEmptyString_When_NoFormatExists()
{
	// arrange
	auto path = QStringLiteral("/theRoot/theHome/myHome/theFile");

	// act
	auto result = PathHelper::extractFormat(path);

	// assert
    QCOMPARE(result, QStringLiteral(""));
}

TEST_MAIN(PathHelperTests)
