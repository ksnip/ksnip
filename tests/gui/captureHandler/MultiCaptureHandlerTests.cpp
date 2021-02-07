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

void MultiCaptureHandlerTests::Copy_Should_CopyCurrentTabImageToClipboard()
{
	auto index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ServiceLocatorMock serviceLocatorMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &serviceLocatorMock, tabStateHandlerMock, nullptr);
	tabStateHandlerMock->currentTabIndex_set(index);
	imageAnnotatorMock.imageAt_set(index, QImage());

	multiCaptureHandler.copy();

	QCOMPARE(imageAnnotatorMock.imageAt_callCounter(index), 1);
	QCOMPARE(serviceLocatorMock.clipboard_mock()->setImage_set(), imageAnnotatorMock.imageAt(index));
}

void MultiCaptureHandlerTests::CopyToClipboardTab_Should_FetchCorrectImageFromAnnotator_And_CopyItToClipboard()
{
	int index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ServiceLocatorMock serviceLocatorMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &serviceLocatorMock, tabStateHandlerMock, nullptr);
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
	QCOMPARE(serviceLocatorMock.clipboard_mock()->setImage_set(), imageAnnotatorMock.imageAt(index));
}

void MultiCaptureHandlerTests::CopyPathToClipboardTab_Should_FetchCorrectPathFromTabStateHandler_And_CopyItToClipboard()
{
	int index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ClipboardMock clipboardMock;
	ServiceLocatorMock serviceLocatorMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &serviceLocatorMock, tabStateHandlerMock, nullptr);
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
	QCOMPARE(serviceLocatorMock.clipboard_mock()->setText_get(), tabStateHandlerMock->path(index));
}

void MultiCaptureHandlerTests::OpenDirectoryTab_Should_FetchCorrectPathFromTabStateHandler_And_PassTheParentDirectoryOnlyToDesktopService()
{
	int index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ServiceLocatorMock serviceLocatorMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &serviceLocatorMock, tabStateHandlerMock, nullptr);
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
	QCOMPARE(serviceLocatorMock.desktopService_mock()->openFile_get().toString(), QLatin1Literal("/la"));
}

void MultiCaptureHandlerTests::UpdateContextMenuActions_Should_SetAllActionThatRequirePathToEnabled_When_PathIsValid()
{
	int index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ServiceLocatorMock serviceLocatorMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &serviceLocatorMock, tabStateHandlerMock, nullptr);
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

void MultiCaptureHandlerTests::UpdateContextMenuActions_Should_SetAllActionThatRequirePathToDisabled_When_PathIsNotValid()
{
	int index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ServiceLocatorMock serviceLocatorMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &serviceLocatorMock, tabStateHandlerMock, nullptr);
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

void MultiCaptureHandlerTests::UpdateContextMenuActions_Should_SetSaveActionToDisabled_When_CaptureSaved()
{
	int index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ServiceLocatorMock serviceLocatorMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &serviceLocatorMock, tabStateHandlerMock, nullptr);
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

void MultiCaptureHandlerTests::UpdateContextMenuActions_Should_SetSaveActionToEnabled_When_CaptureNotSaved()
{
	int index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ServiceLocatorMock serviceLocatorMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &serviceLocatorMock, tabStateHandlerMock, nullptr);
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

void MultiCaptureHandlerTests::CopyPath_Should_CopyCurrentTabPathToClipboard()
{
	auto path = QLatin1Literal("lala");
	auto index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ServiceLocatorMock serviceLocatorMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &serviceLocatorMock, tabStateHandlerMock, nullptr);
	tabStateHandlerMock->currentTabIndex_set(index);
	tabStateHandlerMock->path_set(index, path);

	multiCaptureHandler.copyPath();

	QCOMPARE(tabStateHandlerMock->path_callCounter(index), 1);
	QCOMPARE(serviceLocatorMock.clipboard_mock()->setText_get(), path);
}

void MultiCaptureHandlerTests::OpenDirectory_Should_FetchCurrentTabPathFromTabStateHandler_And_PassTheParentDirectoryOnlyToDesktopService()
{
	auto index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ServiceLocatorMock serviceLocatorMock;
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &serviceLocatorMock, tabStateHandlerMock, nullptr);
	tabStateHandlerMock->currentTabIndex_set(index);
	tabStateHandlerMock->path_set(index, QLatin1String("/la/la.png"));

	multiCaptureHandler.openDirectory();

	QCOMPARE(tabStateHandlerMock->path_callCounter(index), 1);
	QCOMPARE(serviceLocatorMock.desktopService_mock()->openFile_get().toString(), QLatin1String("/la"));
}

void MultiCaptureHandlerTests::RemoveImage_Should_NotRemoveTab_When_OperationDidNotDeleteImage()
{
	auto path = QLatin1Literal("lala");
	auto index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ServiceLocatorMock serviceLocatorMock;
	serviceLocatorMock.messageBoxService_mock()->okCancel_set(false);
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &serviceLocatorMock, tabStateHandlerMock, nullptr);
	tabStateHandlerMock->currentTabIndex_set(index);
	tabStateHandlerMock->path_set(index, path);

	multiCaptureHandler.removeImage();

	QCOMPARE(imageAnnotatorMock.removeTab_callCounter(index), 0);
}

void MultiCaptureHandlerTests::RemoveImage_Should_RemoveTab_When_OperationDidDeleteImage()
{
	auto path = QLatin1Literal("lala");
	auto index = 22;
	ImageAnnotatorMock imageAnnotatorMock;
	ServiceLocatorMock serviceLocatorMock;
	serviceLocatorMock.messageBoxService_mock()->okCancel_set(true);
	serviceLocatorMock.fileService_mock()->remove_set(true);
	auto tabStateHandlerMock = new CaptureTabStateHandlerMock;
	MultiCaptureHandler multiCaptureHandler(&imageAnnotatorMock, nullptr, &serviceLocatorMock, tabStateHandlerMock, nullptr);
	tabStateHandlerMock->currentTabIndex_set(index);
	tabStateHandlerMock->path_set(index, path);

	multiCaptureHandler.removeImage();

	QCOMPARE(imageAnnotatorMock.removeTab_callCounter(index), 1);
}

QTEST_MAIN(MultiCaptureHandlerTests)
