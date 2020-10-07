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

#ifndef KSNIP_MULTICAPTUREHANDLERTESTS_H
#define KSNIP_MULTICAPTUREHANDLERTESTS_H

#include <QtTest>

#include "src/gui/captureHandler/MultiCaptureHandler.h"
#include "tests/mocks/ImageAnnotatorMock.h"
#include "tests/mocks/ClipboardMock.h"
#include "tests/mocks/DesktopServiceMock.h"
#include "tests/mocks/CaptureTabStateHandlerMock.h"

class MultiCaptureHandlerTests : public QObject
{
Q_OBJECT
private slots:
	void TestCopy_Should_CopyCurrentTabImageToClipboard();
	void TestCopyToClipboardTab_Should_FetchCorrectImageFromAnnotator_And_CopyItToClipboard();
	void TestCopyPathToClipboardTab_Should_FetchCorrectPathFromTabStateHandler_And_CopyItToClipboard();
	void TestOpenDirectoryTab_Should_FetchCorrectPathFromTabStateHandler_And_PassTheParentDirectoryOnlyToDesktopService();
	void TestUpdateContextMenuActions_Should_SetAllActionThatRequirePathToEnabled_When_PathIsValid();
	void TestUpdateContextMenuActions_Should_SetAllActionThatRequirePathToDisabled_When_PathIsNotValid();
	void TestUpdateContextMenuActions_Should_SetSaveActionToDisabled_When_CaptureSaved();
	void TestUpdateContextMenuActions_Should_SetSaveActionToEnabled_When_CaptureNotSaved();
};

#endif //KSNIP_MULTICAPTUREHANDLERTESTS_H
