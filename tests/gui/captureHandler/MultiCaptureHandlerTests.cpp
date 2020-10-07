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

#include "MultiCaptureHandlerTests.h"

void MultiCaptureHandlerTests::TestCopy_Should_CopyCurrentTabImageToClipboard()
{
	auto index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ClipboardMock clipboardMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &clipboardMock, nullptr, tabStateHandlerMock, nullptr);
	tabStateHandlerMock->currentTabIndex_set(index);
	imageAnnotatorMock.imageAt_set(index, QImage());

	multiCaptureHandler.copy();

	QCOMPARE(imageAnnotatorMock.imageAt_callCounter(index), 1);
	QCOMPARE(clipboardMock.setImage_set(), imageAnnotatorMock.imageAt(index));
}

void MultiCaptureHandlerTests::TestCopyToClipboardTab_Should_FetchCorrectImageFromAnnotator_And_CopyItToClipboard()
{
	int index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ClipboardMock clipboardMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &clipboardMock, nullptr, tabStateHandlerMock, nullptr);
	tabStateHandlerMock->currentTabIndex_set(index);
	imageAnnotatorMock.imageAt_set(index, QImage());
	auto customActions = imageAnnotatorMock.tabContextMenuActions_get();

	for(auto action : customActions) {
		if(action->text() == QLatin1Literal("Copy")) {
			action->setData(index);
			action->trigger();
		}
	}

	QCOMPARE(imageAnnotatorMock.imageAt_callCounter(index), 1);
	QCOMPARE(clipboardMock.setImage_set(), imageAnnotatorMock.imageAt(index));
}

void MultiCaptureHandlerTests::TestCopyPathToClipboardTab_Should_FetchCorrectPathFromTabStateHandler_And_CopyItToClipboard()
{
	int index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ClipboardMock clipboardMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &clipboardMock, nullptr, tabStateHandlerMock, nullptr);
	tabStateHandlerMock->currentTabIndex_set(index);
	tabStateHandlerMock->path_set(index, QLatin1Literal("lala"));
	auto customActions = imageAnnotatorMock.tabContextMenuActions_get();

	for(auto action : customActions) {
		if(action->text() == QLatin1Literal("Copy Path")) {
			action->setData(index);
			action->trigger();
		}
	}

	QCOMPARE(tabStateHandlerMock->path_callCounter(index), 1);
	QCOMPARE(clipboardMock.setText_get(), tabStateHandlerMock->path(index));
}

void MultiCaptureHandlerTests::TestOpenDirectoryTab_Should_FetchCorrectPathFromTabStateHandler_And_PassTheParentDirectoryOnlyToDesktopService()
{
	int index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ClipboardMock clipboardMock;
	auto desktopService = new DesktopServiceMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &clipboardMock, desktopService, tabStateHandlerMock, nullptr);
	tabStateHandlerMock->currentTabIndex_set(index);
	tabStateHandlerMock->path_set(index, QLatin1Literal("/la/la.png"));
	auto customActions = imageAnnotatorMock.tabContextMenuActions_get();

	for(auto action : customActions) {
		if(action->text() == QLatin1Literal("Open Directory")) {
			action->setData(index);
			action->trigger();
		}
	}

	QCOMPARE(tabStateHandlerMock->path_callCounter(index), 1);
	QCOMPARE(desktopService->openUrl_get().toString(), QLatin1Literal("/la"));
}

void MultiCaptureHandlerTests::TestUpdateContextMenuActions_Should_SetAllActionThatRequirePathToEnabled_When_PathIsValid()
{
	int index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ClipboardMock clipboardMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &clipboardMock, nullptr, tabStateHandlerMock, nullptr);
	tabStateHandlerMock->currentTabIndex_set(index);
	tabStateHandlerMock->isPathValid_set(index, true);
	auto customActions = imageAnnotatorMock.tabContextMenuActions_get();
	QAction *saveContextMenuAction = nullptr;
	QAction *saveAsContextMenuAction = nullptr;
	QAction *openDirectoryContextMenuAction = nullptr;
	QAction *copyPathToClipboardContextMenuAction = nullptr;
	QAction *copyToClipboardContextMenuAction = nullptr;
	for(auto action : customActions) {
		if(action->text() == QLatin1Literal("Save")) {
			saveContextMenuAction = action;
		}
		if(action->text() == QLatin1Literal("Save As")) {
			saveAsContextMenuAction = action;
		}
		if(action->text() == QLatin1Literal("Open Directory")) {
			openDirectoryContextMenuAction = action;
		}
		if(action->text() ==QLatin1Literal("Copy Path")) {
			copyPathToClipboardContextMenuAction = action;
		}
		if(action->text() == QLatin1Literal("Copy")) {
			copyToClipboardContextMenuAction = action;
		}
	}

	imageAnnotatorMock.tabContextMenuOpened_emit(index);

	QCOMPARE(saveContextMenuAction->isEnabled(), true);
	QCOMPARE(saveAsContextMenuAction->isEnabled(), true);
	QCOMPARE(openDirectoryContextMenuAction->isEnabled(), true);
	QCOMPARE(copyPathToClipboardContextMenuAction->isEnabled(), true);
	QCOMPARE(copyToClipboardContextMenuAction->isEnabled(), true);
}

void MultiCaptureHandlerTests::TestUpdateContextMenuActions_Should_SetAllActionThatRequirePathToDisabled_When_PathIsNotValid()
{
	int index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ClipboardMock clipboardMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &clipboardMock, nullptr, tabStateHandlerMock, nullptr);
	tabStateHandlerMock->currentTabIndex_set(index);
	tabStateHandlerMock->isPathValid_set(index, false);
	auto customActions = imageAnnotatorMock.tabContextMenuActions_get();
	QAction *saveContextMenuAction = nullptr;
	QAction *saveAsContextMenuAction = nullptr;
	QAction *openDirectoryContextMenuAction = nullptr;
	QAction *copyPathToClipboardContextMenuAction = nullptr;
	QAction *copyToClipboardContextMenuAction = nullptr;
	for(auto action : customActions) {
		if(action->text() == QLatin1Literal("Save")) {
			saveContextMenuAction = action;
		}
		if(action->text() == QLatin1Literal("Save As")) {
			saveAsContextMenuAction = action;
		}
		if(action->text() == QLatin1Literal("Open Directory")) {
			openDirectoryContextMenuAction = action;
		}
		if(action->text() ==QLatin1Literal("Copy Path")) {
			copyPathToClipboardContextMenuAction = action;
		}
		if(action->text() == QLatin1Literal("Copy")) {
			copyToClipboardContextMenuAction = action;
		}
	}

	imageAnnotatorMock.tabContextMenuOpened_emit(index);

	QCOMPARE(saveContextMenuAction->isEnabled(), true);
	QCOMPARE(saveAsContextMenuAction->isEnabled(), true);
	QCOMPARE(openDirectoryContextMenuAction->isEnabled(), false);
	QCOMPARE(copyPathToClipboardContextMenuAction->isEnabled(), false);
	QCOMPARE(copyToClipboardContextMenuAction->isEnabled(), true);
}

void MultiCaptureHandlerTests::TestUpdateContextMenuActions_Should_SetSaveActionToDisabled_When_CaptureSaved()
{
	int index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ClipboardMock clipboardMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &clipboardMock, nullptr, tabStateHandlerMock, nullptr);
	tabStateHandlerMock->currentTabIndex_set(index);
	tabStateHandlerMock->isSaved_set(index, true);
	auto customActions = imageAnnotatorMock.tabContextMenuActions_get();
	QAction *saveContextMenuAction = nullptr;
	for(auto action : customActions) {
		if(action->text() == QLatin1Literal("Save")) {
			saveContextMenuAction = action;
		}
	}

	imageAnnotatorMock.tabContextMenuOpened_emit(index);

	QCOMPARE(saveContextMenuAction->isEnabled(), false);
}

void MultiCaptureHandlerTests::TestUpdateContextMenuActions_Should_SetSaveActionToEnabled_When_CaptureNotSaved()
{
	int index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ClipboardMock clipboardMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &clipboardMock, nullptr, tabStateHandlerMock, nullptr);
	tabStateHandlerMock->currentTabIndex_set(index);
	tabStateHandlerMock->isSaved_set(index, false);
	auto customActions = imageAnnotatorMock.tabContextMenuActions_get();
	QAction *saveContextMenuAction = nullptr;
	for(auto action : customActions) {
		if(action->text() == QLatin1Literal("Save")) {
			saveContextMenuAction = action;
		}
	}

	imageAnnotatorMock.tabContextMenuOpened_emit(index);

	QCOMPARE(saveContextMenuAction->isEnabled(), true);
}

QTEST_MAIN(MultiCaptureHandlerTests)
