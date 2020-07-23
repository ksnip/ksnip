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

#include "PathHelperTests.h"

void PathHelperTests::TestIsPathValid_Should_ReturnFalse_When_StringEmpty()
{
	auto input = QStringLiteral("");
	auto result = PathHelper::isPathValid(input);

	QCOMPARE(result, false);
}

void PathHelperTests::TestIsPathValid_Should_ReturnFalse_When_StringNull()
{
	auto input = QString();
	auto result = PathHelper::isPathValid(input);

	QCOMPARE(result, false);
}

void PathHelperTests::TestIsPathValid_Should_ReturnTrue_When_StringHasContent()
{
	auto input = QStringLiteral("lala");
	auto result = PathHelper::isPathValid(input);

	QCOMPARE(result, true);
}

void PathHelperTests::TestExtractParentDirectory_Should_ReturnStringWithParentDirectoryPath()
{
	auto expected = QStringLiteral("/theRoot/theHome/myHome");
	auto result = PathHelper::extractParentDirectory(expected + QStringLiteral("/theFile.me"));

	QCOMPARE(result, expected);
}

void PathHelperTests::TestExtractFilename_Should_ReturnStringWithFilenameWithoutFormat_When_FormatExists()
{
	auto expected = QStringLiteral("theFile");
	auto result = PathHelper::extractFilename(QStringLiteral("/theRoot/theHome/myHome/") + expected + QStringLiteral(".me"));

	QCOMPARE(result, expected);
}

void PathHelperTests::TestExtractFilename_Should_ReturnStringWithFilenameWithoutFormat_When_NoFormatExists()
{
	auto expected = QStringLiteral("theFile");
	auto result = PathHelper::extractFilename(QStringLiteral("/theRoot/theHome/myHome/") + expected);

	QCOMPARE(result, expected);
}

void PathHelperTests::TestExtractFilenameWithFormat_Should_ReturnStringWithFilenameWithFormat_When_FormatExists()
{
	auto expected = QStringLiteral("theFile.me");
	auto result = PathHelper::extractFilenameWithFormat(QStringLiteral("/theRoot/theHome/myHome/") + expected);

	QCOMPARE(result, expected);
}

void PathHelperTests::TestExtractFilenameWithFormat_Should_ReturnStringWithFilenameWithFormat_When_NoFormatExists()
{
	auto expected = QStringLiteral("theFile");
	auto result = PathHelper::extractFilenameWithFormat(QStringLiteral("/theRoot/theHome/myHome/") + expected);

	QCOMPARE(result, expected);
}

void PathHelperTests::TestExtractFormat_Should_ReturnWithFormat_When_FormatExists()
{
	auto expected = QStringLiteral("me");
	auto result = PathHelper::extractFormat(QStringLiteral("/theRoot/theHome/myHome/theFile.") + expected);

	QCOMPARE(result, expected);
}

void PathHelperTests::TestExtractFormat_Should_ReturnEmptyString_When_NoFormatExists()
{
	auto result = PathHelper::extractFormat(QStringLiteral("/theRoot/theHome/myHome/theFile"));

	QCOMPARE(result, QStringLiteral(""));
}

QTEST_MAIN(PathHelperTests)
