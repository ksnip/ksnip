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

#include "ActionTests.h"

#include "src/gui/actions/Action.h"

void ActionTests::EqualsOperator_Should_ReturnTrue_When_AllValuesMatch()
{
	// arrange
	Action action1;
	action1.setName("Name");
	action1.setShortcut(Qt::CTRL + Qt::Key_A);
	action1.setIsCaptureEnabled(true);
	action1.setIncludeCursor(true);
	action1.setCaptureDelay(2000);
	action1.setCaptureMode(CaptureModes::FullScreen);
	action1.setIsSaveEnabled(true);
	action1.setIsCopyToClipboardEnabled(true);
	action1.setIsUploadEnabled(true);
	action1.setIsOpenDirectoryEnabled(true);
	action1.setIsPinImageEnabled(true);
	action1.setIsHideMainWindowEnabled(true);

	Action action2;
	action2.setName(action1.name());
	action2.setShortcut(action1.shortcut());
	action2.setIsCaptureEnabled(action1.isCaptureEnabled());
	action2.setIncludeCursor(action1.includeCursor());
	action2.setCaptureDelay(action1.captureDelay());
	action2.setCaptureMode(action1.captureMode());
	action2.setIsSaveEnabled(action1.isSaveEnabled());
	action2.setIsCopyToClipboardEnabled(action1.isCopyToClipboardEnabled());
	action2.setIsUploadEnabled(action1.isUploadEnabled());
	action2.setIsOpenDirectoryEnabled(action1.isOpenDirectoryEnabled());
	action2.setIsPinImageEnabled(action1.isPinImageEnabled());
	action2.setIsHideMainWindowEnabled(action1.isHideMainWindowEnabled());

	// act
	auto result = action1 == action2;

	// assert
	QCOMPARE(result, true);
}

void ActionTests::EqualsOperator_Should_ReturnFalse_When_NameIsDifferent()
{
	// arrange
	Action action1;
	action1.setName("Name");
	action1.setShortcut(Qt::CTRL + Qt::Key_A);
	action1.setIsCaptureEnabled(true);
	action1.setIncludeCursor(true);
	action1.setCaptureDelay(2000);
	action1.setCaptureMode(CaptureModes::FullScreen);
	action1.setIsSaveEnabled(true);
	action1.setIsCopyToClipboardEnabled(true);
	action1.setIsUploadEnabled(true);
	action1.setIsOpenDirectoryEnabled(true);
	action1.setIsPinImageEnabled(true);
	action1.setIsHideMainWindowEnabled(true);

	Action action2;
	action2.setName("Other");
	action2.setShortcut(action1.shortcut());
	action2.setIsCaptureEnabled(action1.isCaptureEnabled());
	action2.setIncludeCursor(action1.includeCursor());
	action2.setCaptureDelay(action1.captureDelay());
	action2.setCaptureMode(action1.captureMode());
	action2.setIsSaveEnabled(action1.isSaveEnabled());
	action2.setIsCopyToClipboardEnabled(action1.isCopyToClipboardEnabled());
	action2.setIsUploadEnabled(action1.isUploadEnabled());
	action2.setIsOpenDirectoryEnabled(action1.isOpenDirectoryEnabled());
	action2.setIsPinImageEnabled(action1.isPinImageEnabled());
	action2.setIsHideMainWindowEnabled(action1.isHideMainWindowEnabled());

	// act
	auto result = action1 == action2;

	// assert
    QCOMPARE(result, false);
}

void ActionTests::EqualsOperator_Should_ReturnFalse_When_ShortcutDifferent()
{
	// arrange
	Action action1;
	action1.setName("Name");
	action1.setShortcut(Qt::CTRL + Qt::Key_A);
	action1.setIsCaptureEnabled(true);
	action1.setIncludeCursor(true);
	action1.setCaptureDelay(2000);
	action1.setCaptureMode(CaptureModes::FullScreen);
	action1.setIsSaveEnabled(true);
	action1.setIsCopyToClipboardEnabled(true);
	action1.setIsUploadEnabled(true);
	action1.setIsOpenDirectoryEnabled(true);
	action1.setIsPinImageEnabled(true);
	action1.setIsHideMainWindowEnabled(true);

	Action action2;
	action2.setName(action1.name());
	action2.setShortcut(QKeySequence(Qt::CTRL + Qt::Key_B));
	action2.setIsCaptureEnabled(action1.isCaptureEnabled());
	action2.setIncludeCursor(action1.includeCursor());
	action2.setCaptureDelay(action1.captureDelay());
	action2.setCaptureMode(action1.captureMode());
	action2.setIsSaveEnabled(action1.isSaveEnabled());
	action2.setIsCopyToClipboardEnabled(action1.isCopyToClipboardEnabled());
	action2.setIsUploadEnabled(action1.isUploadEnabled());
	action2.setIsOpenDirectoryEnabled(action1.isOpenDirectoryEnabled());
	action2.setIsPinImageEnabled(action1.isPinImageEnabled());
	action2.setIsHideMainWindowEnabled(action1.isHideMainWindowEnabled());

	// act
	auto result = action1 == action2;

	// assert
    QCOMPARE(result, false);
}

void ActionTests::EqualsOperator_Should_ReturnFalse_When_IsCaptureEnabledDifferent()
{
	// arrange
	Action action1;
	action1.setName("Name");
	action1.setShortcut(Qt::CTRL + Qt::Key_A);
	action1.setIsCaptureEnabled(true);
	action1.setIncludeCursor(true);
	action1.setCaptureDelay(2000);
	action1.setCaptureMode(CaptureModes::FullScreen);
	action1.setIsSaveEnabled(true);
	action1.setIsCopyToClipboardEnabled(true);
	action1.setIsUploadEnabled(true);
	action1.setIsOpenDirectoryEnabled(true);
	action1.setIsPinImageEnabled(true);
	action1.setIsHideMainWindowEnabled(true);

	Action action2;
	action2.setName(action1.name());
	action2.setShortcut(action1.shortcut());
	action2.setIsCaptureEnabled(false);
	action2.setIncludeCursor(action1.includeCursor());
	action2.setCaptureDelay(action1.captureDelay());
	action2.setCaptureMode(action1.captureMode());
	action2.setIsSaveEnabled(action1.isSaveEnabled());
	action2.setIsCopyToClipboardEnabled(action1.isCopyToClipboardEnabled());
	action2.setIsUploadEnabled(action1.isUploadEnabled());
	action2.setIsOpenDirectoryEnabled(action1.isOpenDirectoryEnabled());
	action2.setIsPinImageEnabled(action1.isPinImageEnabled());
	action2.setIsHideMainWindowEnabled(action1.isHideMainWindowEnabled());

	// act
	auto result = action1 == action2;

	// assert
    QCOMPARE(result, false);
}

void ActionTests::EqualsOperator_Should_ReturnFalse_When_IncludeCursorDifferent()
{
	// arrange
	Action action1;
	action1.setName("Name");
	action1.setShortcut(Qt::CTRL + Qt::Key_A);
	action1.setIsCaptureEnabled(true);
	action1.setIncludeCursor(true);
	action1.setCaptureDelay(2000);
	action1.setCaptureMode(CaptureModes::FullScreen);
	action1.setIsSaveEnabled(true);
	action1.setIsCopyToClipboardEnabled(true);
	action1.setIsUploadEnabled(true);
	action1.setIsOpenDirectoryEnabled(true);
	action1.setIsPinImageEnabled(true);
	action1.setIsHideMainWindowEnabled(true);

	Action action2;
	action2.setName(action1.name());
	action2.setShortcut(action1.shortcut());
	action2.setIsCaptureEnabled(action1.isCaptureEnabled());
	action2.setIncludeCursor(false);
	action2.setCaptureDelay(action1.captureDelay());
	action2.setCaptureMode(action1.captureMode());
	action2.setIsSaveEnabled(action1.isSaveEnabled());
	action2.setIsCopyToClipboardEnabled(action1.isCopyToClipboardEnabled());
	action2.setIsUploadEnabled(action1.isUploadEnabled());
	action2.setIsOpenDirectoryEnabled(action1.isOpenDirectoryEnabled());
	action2.setIsPinImageEnabled(action1.isPinImageEnabled());
	action2.setIsHideMainWindowEnabled(action1.isHideMainWindowEnabled());

	// act
	auto result = action1 == action2;

	// assert
    QCOMPARE(result, false);
}

void ActionTests::EqualsOperator_Should_ReturnFalse_When_CaptureDelayDifferent()
{
	// arrange
	Action action1;
	action1.setName("Name");
	action1.setShortcut(Qt::CTRL + Qt::Key_A);
	action1.setIsCaptureEnabled(true);
	action1.setIncludeCursor(true);
	action1.setCaptureDelay(2000);
	action1.setCaptureMode(CaptureModes::FullScreen);
	action1.setIsSaveEnabled(true);
	action1.setIsCopyToClipboardEnabled(true);
	action1.setIsUploadEnabled(true);
	action1.setIsOpenDirectoryEnabled(true);
	action1.setIsPinImageEnabled(true);
	action1.setIsHideMainWindowEnabled(true);

	Action action2;
	action2.setName(action1.name());
	action2.setShortcut(action1.shortcut());
	action2.setIsCaptureEnabled(action1.isCaptureEnabled());
	action2.setIncludeCursor(action1.includeCursor());
	action2.setCaptureDelay(5000);
	action2.setCaptureMode(action1.captureMode());
	action2.setIsSaveEnabled(action1.isSaveEnabled());
	action2.setIsCopyToClipboardEnabled(action1.isCopyToClipboardEnabled());
	action2.setIsUploadEnabled(action1.isUploadEnabled());
	action2.setIsOpenDirectoryEnabled(action1.isOpenDirectoryEnabled());
	action2.setIsPinImageEnabled(action1.isPinImageEnabled());
	action2.setIsHideMainWindowEnabled(action1.isHideMainWindowEnabled());

	// act
	auto result = action1 == action2;

	// assert
    QCOMPARE(result, false);
}

void ActionTests::EqualsOperator_Should_ReturnFalse_When_CaptureModeDifferent()
{
	// arrange
	Action action1;
	action1.setName("Name");
	action1.setShortcut(Qt::CTRL + Qt::Key_A);
	action1.setIsCaptureEnabled(true);
	action1.setIncludeCursor(true);
	action1.setCaptureDelay(2000);
	action1.setCaptureMode(CaptureModes::FullScreen);
	action1.setIsSaveEnabled(true);
	action1.setIsCopyToClipboardEnabled(true);
	action1.setIsUploadEnabled(true);
	action1.setIsOpenDirectoryEnabled(true);
	action1.setIsPinImageEnabled(true);
	action1.setIsHideMainWindowEnabled(true);

	Action action2;
	action2.setName(action1.name());
	action2.setShortcut(action1.shortcut());
	action2.setIsCaptureEnabled(action1.isCaptureEnabled());
	action2.setIncludeCursor(action1.includeCursor());
	action2.setCaptureDelay(action1.captureDelay());
	action2.setCaptureMode(CaptureModes::RectArea);
	action2.setIsSaveEnabled(action1.isSaveEnabled());
	action2.setIsCopyToClipboardEnabled(action1.isCopyToClipboardEnabled());
	action2.setIsUploadEnabled(action1.isUploadEnabled());
	action2.setIsOpenDirectoryEnabled(action1.isOpenDirectoryEnabled());
	action2.setIsPinImageEnabled(action1.isPinImageEnabled());
	action2.setIsHideMainWindowEnabled(action1.isHideMainWindowEnabled());

	// act
	auto result = action1 == action2;

	// assert
    QCOMPARE(result, false);
}

void ActionTests::EqualsOperator_Should_ReturnFalse_When_IsSaveEnabledDifferent()
{
	// arrange
	Action action1;
	action1.setName("Name");
	action1.setShortcut(Qt::CTRL + Qt::Key_A);
	action1.setIsCaptureEnabled(true);
	action1.setIncludeCursor(true);
	action1.setCaptureDelay(2000);
	action1.setCaptureMode(CaptureModes::FullScreen);
	action1.setIsSaveEnabled(true);
	action1.setIsCopyToClipboardEnabled(true);
	action1.setIsUploadEnabled(true);
	action1.setIsOpenDirectoryEnabled(true);
	action1.setIsPinImageEnabled(true);
	action1.setIsHideMainWindowEnabled(true);

	Action action2;
	action2.setName(action1.name());
	action2.setShortcut(action1.shortcut());
	action2.setIsCaptureEnabled(action1.isCaptureEnabled());
	action2.setIncludeCursor(action1.includeCursor());
	action2.setCaptureDelay(action1.captureDelay());
	action2.setCaptureMode(action1.captureMode());
	action2.setIsSaveEnabled(false);
	action2.setIsCopyToClipboardEnabled(action1.isCopyToClipboardEnabled());
	action2.setIsUploadEnabled(action1.isUploadEnabled());
	action2.setIsOpenDirectoryEnabled(action1.isOpenDirectoryEnabled());
	action2.setIsPinImageEnabled(action1.isPinImageEnabled());
	action2.setIsHideMainWindowEnabled(action1.isHideMainWindowEnabled());

	// act
	auto result = action1 == action2;

	// assert
    QCOMPARE(result, false);
}

void ActionTests::EqualsOperator_Should_ReturnFalse_When_IsCopyToClipboardEnabledDifferent()
{
	// arrange
	Action action1;
	action1.setName("Name");
	action1.setShortcut(Qt::CTRL + Qt::Key_A);
	action1.setIsCaptureEnabled(true);
	action1.setIncludeCursor(true);
	action1.setCaptureDelay(2000);
	action1.setCaptureMode(CaptureModes::FullScreen);
	action1.setIsSaveEnabled(true);
	action1.setIsCopyToClipboardEnabled(true);
	action1.setIsUploadEnabled(true);
	action1.setIsOpenDirectoryEnabled(true);
	action1.setIsPinImageEnabled(true);
	action1.setIsHideMainWindowEnabled(true);

	Action action2;
	action2.setName(action1.name());
	action2.setShortcut(action1.shortcut());
	action2.setIsCaptureEnabled(action1.isCaptureEnabled());
	action2.setIncludeCursor(action1.includeCursor());
	action2.setCaptureDelay(action1.captureDelay());
	action2.setCaptureMode(action1.captureMode());
	action2.setIsSaveEnabled(action1.isSaveEnabled());
	action2.setIsCopyToClipboardEnabled(false);
	action2.setIsUploadEnabled(action1.isUploadEnabled());
	action2.setIsOpenDirectoryEnabled(action1.isOpenDirectoryEnabled());
	action2.setIsPinImageEnabled(action1.isPinImageEnabled());
	action2.setIsHideMainWindowEnabled(action1.isHideMainWindowEnabled());

	// act
	auto result = action1 == action2;

	// assert
    QCOMPARE(result, false);
}

void ActionTests::EqualsOperator_Should_ReturnFalse_When_IsUploadEnabledDifferent()
{
	// arrange
	Action action1;
	action1.setName("Name");
	action1.setShortcut(Qt::CTRL + Qt::Key_A);
	action1.setIsCaptureEnabled(true);
	action1.setIncludeCursor(true);
	action1.setCaptureDelay(2000);
	action1.setCaptureMode(CaptureModes::FullScreen);
	action1.setIsSaveEnabled(true);
	action1.setIsCopyToClipboardEnabled(true);
	action1.setIsUploadEnabled(true);
	action1.setIsOpenDirectoryEnabled(true);
	action1.setIsPinImageEnabled(true);
	action1.setIsHideMainWindowEnabled(true);

	Action action2;
	action2.setName(action1.name());
	action2.setShortcut(action1.shortcut());
	action2.setIsCaptureEnabled(action1.isCaptureEnabled());
	action2.setIncludeCursor(action1.includeCursor());
	action2.setCaptureDelay(action1.captureDelay());
	action2.setCaptureMode(action1.captureMode());
	action2.setIsSaveEnabled(action1.isSaveEnabled());
	action2.setIsCopyToClipboardEnabled(action1.isCopyToClipboardEnabled());
	action2.setIsUploadEnabled(false);
	action2.setIsOpenDirectoryEnabled(action1.isOpenDirectoryEnabled());
	action2.setIsPinImageEnabled(action1.isPinImageEnabled());
	action2.setIsHideMainWindowEnabled(action1.isHideMainWindowEnabled());

	// act
	auto result = action1 == action2;

	// assert
    QCOMPARE(result, false);
}

void ActionTests::EqualsOperator_Should_ReturnFalse_When_IsOpenDirectoryEnabledDifferent()
{
	// arrange
	Action action1;
	action1.setName("Name");
	action1.setShortcut(Qt::CTRL + Qt::Key_A);
	action1.setIsCaptureEnabled(true);
	action1.setIncludeCursor(true);
	action1.setCaptureDelay(2000);
	action1.setCaptureMode(CaptureModes::FullScreen);
	action1.setIsSaveEnabled(true);
	action1.setIsCopyToClipboardEnabled(true);
	action1.setIsUploadEnabled(true);
	action1.setIsOpenDirectoryEnabled(true);
	action1.setIsPinImageEnabled(true);
	action1.setIsHideMainWindowEnabled(true);

	Action action2;
	action2.setName(action1.name());
	action2.setShortcut(action1.shortcut());
	action2.setIsCaptureEnabled(action1.isCaptureEnabled());
	action2.setIncludeCursor(action1.includeCursor());
	action2.setCaptureDelay(action1.captureDelay());
	action2.setCaptureMode(action1.captureMode());
	action2.setIsSaveEnabled(action1.isSaveEnabled());
	action2.setIsCopyToClipboardEnabled(action1.isCopyToClipboardEnabled());
	action2.setIsUploadEnabled(action1.isUploadEnabled());
	action2.setIsOpenDirectoryEnabled(false);
	action2.setIsPinImageEnabled(action1.isPinImageEnabled());
	action2.setIsHideMainWindowEnabled(action1.isHideMainWindowEnabled());

	// act
	auto result = action1 == action2;

	// assert
    QCOMPARE(result, false);
}

void ActionTests::EqualsOperator_Should_ReturnFalse_When_IsPinScreenshotEnabledDifferent()
{
	// arrange
	Action action1;
	action1.setName("Name");
	action1.setShortcut(Qt::CTRL + Qt::Key_A);
	action1.setIsCaptureEnabled(true);
	action1.setIncludeCursor(true);
	action1.setCaptureDelay(2000);
	action1.setCaptureMode(CaptureModes::FullScreen);
	action1.setIsSaveEnabled(true);
	action1.setIsCopyToClipboardEnabled(true);
	action1.setIsUploadEnabled(true);
	action1.setIsOpenDirectoryEnabled(true);
	action1.setIsPinImageEnabled(true);
	action1.setIsHideMainWindowEnabled(true);

	Action action2;
	action2.setName(action1.name());
	action2.setShortcut(action1.shortcut());
	action2.setIsCaptureEnabled(action1.isCaptureEnabled());
	action2.setIncludeCursor(action1.includeCursor());
	action2.setCaptureDelay(action1.captureDelay());
	action2.setCaptureMode(action1.captureMode());
	action2.setIsSaveEnabled(action1.isSaveEnabled());
	action2.setIsCopyToClipboardEnabled(action1.isCopyToClipboardEnabled());
	action2.setIsUploadEnabled(action1.isUploadEnabled());
	action2.setIsOpenDirectoryEnabled(action1.isOpenDirectoryEnabled());
	action2.setIsPinImageEnabled(false);
	action2.setIsHideMainWindowEnabled(action1.isHideMainWindowEnabled());

	// act
	auto result = action1 == action2;

	// assert
    QCOMPARE(result, false);
}

void ActionTests::EqualsOperator_Should_ReturnFalse_When_IsHideMainWindowEnabledDifferent()
{
	// arrange
	Action action1;
	action1.setName("Name");
	action1.setShortcut(Qt::CTRL + Qt::Key_A);
	action1.setIsCaptureEnabled(true);
	action1.setIncludeCursor(true);
	action1.setCaptureDelay(2000);
	action1.setCaptureMode(CaptureModes::FullScreen);
	action1.setIsSaveEnabled(true);
	action1.setIsCopyToClipboardEnabled(true);
	action1.setIsUploadEnabled(true);
	action1.setIsOpenDirectoryEnabled(true);
	action1.setIsPinImageEnabled(true);
	action1.setIsHideMainWindowEnabled(true);

	Action action2;
	action2.setName(action1.name());
	action2.setShortcut(action1.shortcut());
	action2.setIsCaptureEnabled(action1.isCaptureEnabled());
	action2.setIncludeCursor(action1.includeCursor());
	action2.setCaptureDelay(action1.captureDelay());
	action2.setCaptureMode(action1.captureMode());
	action2.setIsSaveEnabled(action1.isSaveEnabled());
	action2.setIsCopyToClipboardEnabled(action1.isCopyToClipboardEnabled());
	action2.setIsUploadEnabled(action1.isUploadEnabled());
	action2.setIsOpenDirectoryEnabled(action1.isOpenDirectoryEnabled());
	action2.setIsPinImageEnabled(action1.isPinImageEnabled());
	action2.setIsHideMainWindowEnabled(false);

	// act
	auto result = action1 == action2;

	// assert
    QCOMPARE(result, false);
}

QTEST_MAIN(ActionTests)
