/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#include "CanDiscardOperation.h"

CanDiscardOperation::CanDiscardOperation(
		QImage image,
		bool isUnsaved,
		QString pathToImageSource,
		QString filename,
		const QSharedPointer<INotificationService> &notificationService,
		const QSharedPointer<IRecentImageService> &recentImageService,
		const QSharedPointer<IMessageBoxService> &messageBoxService,
		const QSharedPointer<IImageSaver> &imageSaver,
		const QSharedPointer<ISavePathProvider> &savePathProvider,
		const QSharedPointer<IFileDialogService> &fileDialogService,
		const QSharedPointer<IConfig> &config,
		QWidget *parent) :
	mParent(parent),
	mImage(std::move(image)),
	mIsUnsaved(isUnsaved),
	mPathToImageSource(std::move(pathToImageSource)),
	mFilename(std::move(filename)),
	mConfig(config),
	mNotificationService(notificationService),
	mMessageBoxService(messageBoxService),
	mRecentImageService(recentImageService),
	mImageSaver(imageSaver),
	mSavePathProvider(savePathProvider),
	mFileDialogService(fileDialogService)
{

}

bool CanDiscardOperation::execute()
{
	if (mConfig->promptSaveBeforeExit() && mIsUnsaved) {
		auto saveBeforeDiscardResponse = getSaveBeforeDiscard();

		if (saveBeforeDiscardResponse == MessageBoxResponse::Yes) {
			return saveImage();
		} else if (saveBeforeDiscardResponse == MessageBoxResponse::Cancel) {
			return false;
		}
	}

	return true;
}

bool CanDiscardOperation::saveImage() const
{
	SaveOperation operation(
			mImage,
			true,
			mPathToImageSource,
			mNotificationService,
			mRecentImageService,
			mImageSaver,
			mSavePathProvider,
			mFileDialogService,
			mConfig,
			mParent);
	return operation.execute().isSuccessful;
}

MessageBoxResponse CanDiscardOperation::getSaveBeforeDiscard() const
{
	auto quote = mFilename.isEmpty() ? QString() : QLatin1String("\"");
	return mMessageBoxService->yesNoCancel(tr("Warning - ") + QApplication::applicationName(),
										  tr("The capture %1%2%3 has been modified.\nDo you want to save it?").arg(quote, mFilename, quote));
}
