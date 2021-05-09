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

#include "ActionTest.h"

QTEST_MAIN(ActionTest)

void ActionTest::EqualsOperator_Should_ReturnTrue_When_AllValuesMatch()
{
	// arrange
	QFETCH(QString, name);
	QFETCH(QKeySequence, shortcut);
	QFETCH(bool, captureEnabled);
	QFETCH(bool, includeCursor);
	QFETCH(int, delay);
	QFETCH(CaptureModes, captureMode);
	QFETCH(bool, save);
	QFETCH(bool, copy);
	QFETCH(bool, upload);
	QFETCH(bool, openDirectory);
	QFETCH(bool, pin);
	QFETCH(bool, hide);
	QFETCH(bool, expected);

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
	action1.setIsPinScreenshotEnabled(true);
	action1.setIsHideMainWindowEnabled(true);

	Action action2;
	action2.setName(name);
	action2.setShortcut(shortcut);
	action2.setIsCaptureEnabled(captureEnabled);
	action2.setIncludeCursor(includeCursor);
	action2.setCaptureDelay(delay);
	action2.setCaptureMode(captureMode);
	action2.setIsSaveEnabled(save);
	action2.setIsCopyToClipboardEnabled(copy);
	action2.setIsUploadEnabled(upload);
	action2.setIsOpenDirectoryEnabled(openDirectory);
	action2.setIsPinScreenshotEnabled(pin);
	action2.setIsHideMainWindowEnabled(hide);

	// act
	auto result = action1 == action2;

	// assert
	QCOMPARE(result, expected);
}

void ActionTest::EqualsOperator_Should_ReturnTrue_When_AllValuesMatch_data()
{
	QTest::addColumn<QString>("name");
	QTest::addColumn<QKeySequence>("shortcut");
	QTest::addColumn<bool>("captureEnabled");
	QTest::addColumn<bool>("includeCursor");
	QTest::addColumn<int>("delay");
	QTest::addColumn<CaptureModes>("captureMode");
	QTest::addColumn<bool>("save");
	QTest::addColumn<bool>("copy");
	QTest::addColumn<bool>("upload");
	QTest::addColumn<bool>("openDirectory");
	QTest::addColumn<bool>("pin");
	QTest::addColumn<bool>("hide");
	QTest::addColumn<bool>("expected");

	QTest::newRow("01. All set") << "Name" << QKeySequence(Qt::CTRL + Qt::Key_A) << true << true << 2000 << CaptureModes::FullScreen << true << true << true << true << true << true << true;
	QTest::newRow("02. Name differ") << "Other" << QKeySequence(Qt::CTRL + Qt::Key_A) << true << true << 2000 << CaptureModes::FullScreen << true << true << true << true << true << true << false;
	QTest::newRow("03. Shortcut differ") << "Name" << QKeySequence(Qt::CTRL + Qt::Key_B) << true << true << 2000 << CaptureModes::FullScreen << true << true << true << true << true << true << false;
	QTest::newRow("04. Capture enabled differ") << "Name" << QKeySequence(Qt::CTRL + Qt::Key_A) << false << true << 2000 << CaptureModes::FullScreen << true << true << true << true << true << true << false;
	QTest::newRow("05. Cursor included differ") << "Name" << QKeySequence(Qt::CTRL + Qt::Key_A) << true << false << 2000 << CaptureModes::FullScreen << true << true << true << true << true << true << false;
	QTest::newRow("06. Delay differ") << "Name" << QKeySequence(Qt::CTRL + Qt::Key_A) << true << true << 3000 << CaptureModes::FullScreen << true << true << true << true << true << true << false;
	QTest::newRow("06. Capture mode differ") << "Name" << QKeySequence(Qt::CTRL + Qt::Key_A) << true << true << 2000 << CaptureModes::RectArea << true << true << true << true << true << true << false;
	QTest::newRow("07. Save differ") << "Name" << QKeySequence(Qt::CTRL + Qt::Key_A) << true << true << 2000 << CaptureModes::FullScreen << false << true << true << true << true << true << false;
	QTest::newRow("08. Copy differ") << "Name" << QKeySequence(Qt::CTRL + Qt::Key_A) << true << true << 2000 << CaptureModes::FullScreen << true << false << true << true << true << true << false;
	QTest::newRow("09. Upload differ") << "Name" << QKeySequence(Qt::CTRL + Qt::Key_A) << true << true << 2000 << CaptureModes::FullScreen << true << true << false << true << true << true << false;
	QTest::newRow("10. Open directory differ") << "Name" << QKeySequence(Qt::CTRL + Qt::Key_A) << true << true << 2000 << CaptureModes::FullScreen << true << true << true << false << false << true << false;
	QTest::newRow("11. Pin differ") << "Name" << QKeySequence(Qt::CTRL + Qt::Key_A) << true << true << 2000 << CaptureModes::FullScreen << true << true << true << true << false << true << false;
	QTest::newRow("12. Hide differ") << "Name" << QKeySequence(Qt::CTRL + Qt::Key_A) << true << true << 2000 << CaptureModes::FullScreen << true << true << true << true << true << false << false;
}
