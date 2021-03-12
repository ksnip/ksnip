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
#include "tests/mocks/CaptureTabStateHandlerMock.h"
#include "tests/mocks/ServiceLocatorMock.h"

class MultiCaptureHandlerTests : public QObject
{
	Q_OBJECT
private slots:
	void Copy_Should_CopyCurrentTabImageToClipboard();
	void CopyToClipboardTab_Should_FetchCorrectImageFromAnnotator_And_CopyItToClipboard();
	void CopyPathToClipboardTab_Should_FetchCorrectPathFromTabStateHandler_And_CopyItToClipboard();
	void OpenDirectoryTab_Should_FetchCorrectPathFromTabStateHandler_And_PassTheParentDirectoryOnlyToDesktopService();
	void UpdateContextMenuActions_Should_SetAllActionThatRequirePathToEnabled_When_PathIsValid();
	void UpdateContextMenuActions_Should_SetAllActionThatRequirePathToDisabled_When_PathIsNotValid();
	void UpdateContextMenuActions_Should_SetSaveActionToDisabled_When_CaptureSaved();
	void UpdateContextMenuActions_Should_SetSaveActionToEnabled_When_CaptureNotSaved();
	void CopyPath_Should_CopyCurrentTabPathToClipboard();
	void OpenDirectory_Should_FetchCurrentTabPathFromTabStateHandler_And_PassTheParentDirectoryOnlyToDesktopService();
	void RemoveImage_Should_NotRemoveTab_When_OperationDidNotDeleteImage();
	void RemoveImage_Should_RemoveTab_When_OperationDidDeleteImage();
};

#endif //KSNIP_MULTICAPTUREHANDLERTESTS_H
