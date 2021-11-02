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

#include "MultiCaptureHandler.h"

MultiCaptureHandler::MultiCaptureHandler(
		IImageAnnotator *imageAnnotator,
		const QSharedPointer<INotificationService> &notificationService,
		const QSharedPointer<ICaptureTabStateHandler> &captureTabStateHandler,
		const QSharedPointer<IConfig> &config,
		const QSharedPointer<IClipboard> &clipboard,
		const QSharedPointer<IDesktopService> &desktopService,
		const QSharedPointer<IFileService> &fileService,
		const QSharedPointer<IMessageBoxService> &messageBoxService,
		const QSharedPointer<IRecentImageService> &recentImageService,
		const QSharedPointer<IImageSaver> &imageSaver,
		const QSharedPointer<ISavePathProvider> &savePathProvider,
		const QSharedPointer<IIconLoader> &iconLoader,
		const QSharedPointer<IFileDialogService> &fileDialogService,
		QWidget *parent) :
	mImageAnnotator(imageAnnotator),
	mNotificationService(notificationService),
	mParent(parent),
	mCaptureChangeListener(nullptr),
	mTabStateHandler(captureTabStateHandler),
	mConfig(config),
	mClipboard(clipboard),
	mDesktopService(desktopService),
	mMessageBoxService(messageBoxService),
	mFileService(fileService),
	mRecentImageService(recentImageService),
	mImageSaver(imageSaver),
	mSavePathProvider(savePathProvider),
	mFileDialogService(fileDialogService),
	mSaveContextMenuAction(new TabContextMenuAction(this)),
	mSaveAsContextMenuAction(new TabContextMenuAction(this)),
	mRenameContextMenuAction(new TabContextMenuAction(this)),
	mOpenDirectoryContextMenuAction(new TabContextMenuAction(this)),
	mCopyPathToClipboardContextMenuAction(new TabContextMenuAction(this)),
	mCopyToClipboardContextMenuAction(new TabContextMenuAction(this)),
	mDeleteImageContextMenuAction(new TabContextMenuAction(this)),
	mContextMenuSeparatorAction(new QAction(this))
{
	connect(mImageAnnotator, &IImageAnnotator::currentTabChanged, mTabStateHandler.data(), &ICaptureTabStateHandler::currentTabChanged);
	connect(mImageAnnotator, &IImageAnnotator::tabMoved, mTabStateHandler.data(), &ICaptureTabStateHandler::tabMoved);
	connect(mImageAnnotator, &IImageAnnotator::imageChanged, mTabStateHandler.data(), &ICaptureTabStateHandler::currentTabContentChanged);
	connect(mTabStateHandler.data(), &ICaptureTabStateHandler::updateTabInfo, mImageAnnotator, &IImageAnnotator::updateTabInfo);

	connect(mImageAnnotator, &IImageAnnotator::imageChanged, this, &MultiCaptureHandler::captureChanged);
	connect(mImageAnnotator, &IImageAnnotator::currentTabChanged, this, &MultiCaptureHandler::captureChanged);
	connect(mImageAnnotator, &IImageAnnotator::tabCloseRequested, this, &MultiCaptureHandler::tabCloseRequested);
	connect(mImageAnnotator, &IImageAnnotator::tabContextMenuOpened, this, &MultiCaptureHandler::updateContextMenuActions);

	connect(mConfig.data(), &IConfig::annotatorConfigChanged, this, &MultiCaptureHandler::annotatorConfigChanged);

	addTabContextMenuActions(iconLoader);

	annotatorConfigChanged();
}

bool MultiCaptureHandler::canClose()
{
	while (mTabStateHandler->count() != 0) {
		int index = mTabStateHandler->currentTabIndex();
		if (!discardChanges(index)) {
			return false;
		}
		removeTab(index);
	}
	return true;
}

bool MultiCaptureHandler::canTakeNew()
{
	return true;
}

bool MultiCaptureHandler::discardChanges(int index)
{
	auto image = mImageAnnotator->imageAt(index);
	auto isUnsaved = !mTabStateHandler->isSaved(index);
	auto pathToSource = mTabStateHandler->path(index);
	auto filename = mTabStateHandler->filename(index);
	CanDiscardOperation operation(
			image,
			isUnsaved,
			pathToSource,
			filename,
			mNotificationService,
			mRecentImageService,
			mMessageBoxService,
			mImageSaver,
			mSavePathProvider,
			mFileDialogService,
			mConfig,
			mParent);
	return operation.execute();
}

void MultiCaptureHandler::removeTab(int currentTabIndex)
{
	mImageAnnotator->removeTab(currentTabIndex);
	mTabStateHandler->tabRemoved(currentTabIndex);
	captureChanged();

	if(mTabStateHandler->count() == 0) {
		mImageAnnotator->hide();
		captureEmpty();
	}
}

bool MultiCaptureHandler::isSaved() const
{
	return mTabStateHandler->isSaved(mTabStateHandler->currentTabIndex());
}

QString MultiCaptureHandler::path() const
{
	return mTabStateHandler->path(mTabStateHandler->currentTabIndex());
}

bool MultiCaptureHandler::isPathValid() const
{
	return mTabStateHandler->isPathValid(mTabStateHandler->currentTabIndex());
}

void MultiCaptureHandler::saveAs()
{
	saveAsTab(mTabStateHandler->currentTabIndex());
}

void MultiCaptureHandler::save()
{
	saveTab(mTabStateHandler->currentTabIndex());
}

void MultiCaptureHandler::rename()
{
	renameTab(mTabStateHandler->currentTabIndex());
}

void MultiCaptureHandler::copy()
{
	copyToClipboardTab(mTabStateHandler->currentTabIndex());
}

void MultiCaptureHandler::copyPath()
{
	copyPathToClipboardTab(mTabStateHandler->currentTabIndex());
}

void MultiCaptureHandler::openDirectory()
{
	openDirectoryTab(mTabStateHandler->currentTabIndex());
}

void MultiCaptureHandler::removeImage()
{
	deleteImageTab(mTabStateHandler->currentTabIndex());
}

void MultiCaptureHandler::saveAt(int index, bool isInstant)
{
	auto image = mImageAnnotator->imageAt(index);
	SaveOperation operation(
			image,
			isInstant,
			mTabStateHandler->path(index),
			mNotificationService,
			mRecentImageService,
			mImageSaver,
			mSavePathProvider,
			mFileDialogService,
			mConfig,
			mParent);
	auto saveResult = operation.execute();
	mTabStateHandler->setSaveState(index, saveResult);
	captureChanged();
}

void MultiCaptureHandler::load(const CaptureDto &capture)
{
	auto path = mPathFromCaptureProvider.pathFrom(capture);
	auto isSaved = PathHelper::isPathValid(path);
	auto filename = mNewCaptureNameProvider.nextName(path);
	auto index = mImageAnnotator->addTab(capture.screenshot, filename, path);
	mTabStateHandler->add(index, filename, path, isSaved);
	if (capture.isCursorValid()) {
		mImageAnnotator->insertImageItem(capture.cursor.position, capture.cursor.image);
	}
}

void MultiCaptureHandler::tabCloseRequested(int index)
{
	if (!discardChanges(index)) {
		return;
	}
	removeTab(index);
}

QImage MultiCaptureHandler::image() const
{
	return mImageAnnotator->image();
}

void MultiCaptureHandler::insertImageItem(const QPointF &pos, const QPixmap &pixmap)
{
	mImageAnnotator->insertImageItem(pos, pixmap);
}

void MultiCaptureHandler::addListener(ICaptureChangeListener *captureChangeListener)
{
	mCaptureChangeListener = captureChangeListener;
}

void MultiCaptureHandler::captureChanged()
{
	if(mCaptureChangeListener != nullptr) {
		mCaptureChangeListener->captureChanged();
	}
}

void MultiCaptureHandler::captureEmpty()
{
	if(mCaptureChangeListener != nullptr) {
		mCaptureChangeListener->captureEmpty();
	}
}

void MultiCaptureHandler::annotatorConfigChanged()
{
	mImageAnnotator->setTabBarAutoHide(mConfig->autoHideTabs());
}

void MultiCaptureHandler::addTabContextMenuActions(const QSharedPointer<IIconLoader> &iconLoader)
{
	mSaveContextMenuAction->setText(tr("Save"));
	mSaveContextMenuAction->setIcon(iconLoader->loadForTheme(QLatin1String("save.svg")));

	mSaveAsContextMenuAction->setText(tr("Save As"));
	mSaveAsContextMenuAction->setIcon(iconLoader->loadForTheme(QLatin1String("saveAs.svg")));

	mRenameContextMenuAction->setText(tr("Rename"));

	mOpenDirectoryContextMenuAction->setText(tr("Open Directory"));

	mCopyToClipboardContextMenuAction->setText(tr("Copy"));
	mCopyToClipboardContextMenuAction->setIcon(iconLoader->loadForTheme(QLatin1String("copy.svg")));

	mCopyPathToClipboardContextMenuAction->setText(tr("Copy Path"));

	mContextMenuSeparatorAction->setSeparator(true);

	mDeleteImageContextMenuAction->setText(tr("Delete"));
	mDeleteImageContextMenuAction->setIcon(iconLoader->loadForTheme(QLatin1String("delete.svg")));

	connect(mSaveContextMenuAction, &TabContextMenuAction::triggered, this, &MultiCaptureHandler::saveTab);
	connect(mSaveAsContextMenuAction, &TabContextMenuAction::triggered, this, &MultiCaptureHandler::saveAsTab);
	connect(mRenameContextMenuAction, &TabContextMenuAction::triggered, this, &MultiCaptureHandler::renameTab);
	connect(mOpenDirectoryContextMenuAction, &TabContextMenuAction::triggered, this, &MultiCaptureHandler::openDirectoryTab);
	connect(mCopyPathToClipboardContextMenuAction, &TabContextMenuAction::triggered, this, &MultiCaptureHandler::copyPathToClipboardTab);
	connect(mCopyToClipboardContextMenuAction, &TabContextMenuAction::triggered, this, &MultiCaptureHandler::copyToClipboardTab);
	connect(mDeleteImageContextMenuAction, &TabContextMenuAction::triggered, this, &MultiCaptureHandler::deleteImageTab);

	auto actions = QList<QAction *>{mSaveContextMenuAction,
									mSaveAsContextMenuAction,
									mRenameContextMenuAction,
									mOpenDirectoryContextMenuAction,
									mCopyToClipboardContextMenuAction,
									mCopyPathToClipboardContextMenuAction,
									mContextMenuSeparatorAction,
									mDeleteImageContextMenuAction
	};
	mImageAnnotator->addTabContextMenuActions(actions);
}

void MultiCaptureHandler::saveAsTab(int index)
{
	saveAt(index, false);
}

void MultiCaptureHandler::saveTab(int index)
{
	saveAt(index, true);
}

void MultiCaptureHandler::renameTab(int index)
{
	RenameOperation operation(mTabStateHandler->path(index), mTabStateHandler->filename(index), mNotificationService, mConfig, mParent);
	auto renameResult = operation.execute();
	if(renameResult.isSuccessful) {
		mTabStateHandler->renameFile(index, renameResult);
		captureChanged();
	}
}

void MultiCaptureHandler::updateContextMenuActions(int index)
{
	auto isPathValid = mTabStateHandler->isPathValid(index);
	mSaveContextMenuAction->setEnabled(!mTabStateHandler->isSaved(index));
	mRenameContextMenuAction->setEnabled(isPathValid);
	mOpenDirectoryContextMenuAction->setEnabled(isPathValid);
	mCopyPathToClipboardContextMenuAction->setEnabled(isPathValid);
	mDeleteImageContextMenuAction->setEnabled(isPathValid);
}

void MultiCaptureHandler::openDirectoryTab(int index)
{
	auto path = mTabStateHandler->path(index);
	mDesktopService->openFile(PathHelper::extractParentDirectory(path));
}

void MultiCaptureHandler::copyToClipboardTab(int index)
{
	auto image = mImageAnnotator->imageAt(index);
	mClipboard->setImage(image);
}

void MultiCaptureHandler::copyPathToClipboardTab(int index)
{
	auto path = mTabStateHandler->path(index);
	mClipboard->setText(path);
}

void MultiCaptureHandler::deleteImageTab(int index)
{
	auto path = mTabStateHandler->path(index);

	DeleteImageOperation operation(path, mFileService.data(), mMessageBoxService.data());

	if(operation.execute()) {
		removeTab(index);
	}
}
