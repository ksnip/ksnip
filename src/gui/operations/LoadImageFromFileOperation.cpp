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

#include "LoadImageFromFileOperation.h"

LoadImageFromFileOperation::LoadImageFromFileOperation(IImageProcessor *imageProcessor, const QString &path, IToastService *toastService, IServiceLocator *serviceLocator) :
	mImageProcessor(imageProcessor),
	mPath(path),
	mToastService(toastService),
	mRecentImageService(serviceLocator->recentImageService()),
	mFileService(serviceLocator->fileService())
{

}

bool LoadImageFromFileOperation::execute()
{
	auto pixmap = mFileService->openPixmap(mPath);
	if(pixmap.isNull()) {
		notifyAboutInvalidPath();
		return false;
	} else {
		mRecentImageService->storeImagePath(mPath);
		CaptureFromFileDto captureDto(pixmap, mPath);
		mImageProcessor->processImage(captureDto);
		return true;
	}
}

void LoadImageFromFileOperation::notifyAboutInvalidPath() const
{
	auto title = tr("Unable to open image");
	auto message = tr("Unable to open image from path %1").arg(mPath);
	NotifyOperation operation(mToastService, title, message, NotificationTypes::Warning);
	operation.execute();
}

