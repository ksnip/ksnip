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

#include "SingleCaptureHandler.h"

SingleCaptureHandler::SingleCaptureHandler(
		IImageAnnotator *imageAnnotator,
		const QSharedPointer<INotificationService> &notificationService,
		const QSharedPointer<IClipboard> &clipboard,
		const QSharedPointer<IDesktopService> &desktopService,
		const QSharedPointer<IFileService> &fileService,
		const QSharedPointer<IMessageBoxService> &messageBoxService,
		const QSharedPointer<IRecentImageService> &recentImageService,
		const QSharedPointer<IImageSaver> &imageSaver,
		const QSharedPointer<ISavePathProvider> &savePathProvider,
		const QSharedPointer<IFileDialogService> &fileDialogService,
		const QSharedPointer<IConfig> &config,
		QWidget *parent) :
	mImageAnnotator(imageAnnotator),
	mNotificationService(notificationService),
	mClipboard(clipboard),
	mDesktopService(desktopService),
	mFileService(fileService),
	mMessageBoxService(messageBoxService),
	mRecentImageService(recentImageService),
	mImageSaver(imageSaver),
	mSavePathProvider(savePathProvider),
	mFileDialogService(fileDialogService),
	mConfig(config),
	mParent(parent),
	mCaptureChangeListener(nullptr),
	mIsSaved(true)
{
	mImageAnnotator->setTabBarAutoHide(true);

	connect(mImageAnnotator, &IImageAnnotator::imageChanged, this, &SingleCaptureHandler::markUnsaved);
}

bool SingleCaptureHandler::canClose()
{
	return discardChanges();
}

bool SingleCaptureHandler::canTakeNew()
{
	return discardChanges();
}

bool SingleCaptureHandler::isSaved() const
{
	return mIsSaved;
}

QString SingleCaptureHandler::path() const
{
	return mPath;
}

bool SingleCaptureHandler::isPathValid() const
{
	return PathHelper::isPathValid(mPath);
}

void SingleCaptureHandler::saveAs()
{
	innerSave(false);
}

void SingleCaptureHandler::save()
{
	innerSave(true);
}

void SingleCaptureHandler::rename()
{
	RenameOperation operation(mPath, QFileInfo(mPath).fileName(), mNotificationService, mConfig, mParent);
	const auto renameResult = operation.execute();
	if (renameResult.isSuccessful) {
		mPath = renameResult.path;
		captureChanged();
	}
}

void SingleCaptureHandler::copy()
{
	auto image = mImageAnnotator->image();
	mClipboard->setImage(image);
}

void SingleCaptureHandler::copyPath()
{
	mClipboard->setText(mPath);
}

void SingleCaptureHandler::openDirectory()
{
	mDesktopService->openFile(PathHelper::extractParentDirectory(mPath));
}

void SingleCaptureHandler::removeImage()
{
	DeleteImageOperation operation(mPath, mFileService.data(), mMessageBoxService.data());
	if(operation.execute()){
		reset();
	}
}

void SingleCaptureHandler::reset()
{
	mImageAnnotator->hide();
	mPath = QString();
	mIsSaved = true;
	captureEmpty();
	captureChanged();
}

void SingleCaptureHandler::innerSave(bool isInstant)
{
	auto image = mImageAnnotator->image();
	SaveOperation operation(
			image,
			isInstant,
			mPath,
			mNotificationService,
			mRecentImageService,
			mImageSaver,
			mSavePathProvider,
			mFileDialogService,
			mConfig,
			mParent);
	auto saveResult = operation.execute();
	mIsSaved = saveResult.isSuccessful;
	if (mIsSaved) {
		mPath =  saveResult.path;
		captureChanged();
	}
}

void SingleCaptureHandler::load(const CaptureDto &capture)
{
	mPath = mPathFromCaptureProvider.pathFrom(capture);
	mIsSaved = PathHelper::isPathValid(mPath);
	mImageAnnotator->loadImage(capture.screenshot);
	if (capture.isCursorValid()) {
		mImageAnnotator->insertImageItem(capture.cursor.position, capture.cursor.image);
	}
}

QImage SingleCaptureHandler::image() const
{
	return mImageAnnotator->image();
}

void SingleCaptureHandler::insertImageItem(const QPointF &pos, const QPixmap &pixmap)
{
	mImageAnnotator->insertImageItem(pos, pixmap);
}

void SingleCaptureHandler::addListener(ICaptureChangeListener *captureChangeListener)
{
	mCaptureChangeListener = captureChangeListener;
}

bool SingleCaptureHandler::discardChanges()
{
	auto image = mImageAnnotator->image();
	auto filename = PathHelper::extractFilename(mPath);
	CanDiscardOperation operation(
			image,
			!mIsSaved,
			mPath,
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

void SingleCaptureHandler::captureChanged()
{
	if(mCaptureChangeListener != nullptr) {
		mCaptureChangeListener->captureChanged();
	}
}

void SingleCaptureHandler::captureEmpty()
{
	if(mCaptureChangeListener != nullptr) {
		mCaptureChangeListener->captureEmpty();
	}
}

void SingleCaptureHandler::markUnsaved()
{
	mIsSaved = false;
	captureChanged();
}
