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

CanDiscardOperation::CanDiscardOperation(QWidget *parent, QImage image, bool isUnsaved, QString pathToImageSource, QString filename, IToastService *toastService, IRecentImageService *recentImageService) :
	mParent(parent),
	mImage(std::move(image)),
	mIsUnsaved(isUnsaved),
	mPathToImageSource(std::move(pathToImageSource)),
	mFilename(std::move(filename)),
	mConfig(KsnipConfigProvider::instance()),
	mToastService(toastService),
	mMessageBoxService(new MessageBoxService),
	mRecentImageService(recentImageService)
{

}

CanDiscardOperation::~CanDiscardOperation()
{
	delete mMessageBoxService;
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
	SaveOperation operation(mParent, mImage, true, mPathToImageSource, mToastService, mRecentImageService);
	return operation.execute().isSuccessful;
}

MessageBoxResponse CanDiscardOperation::getSaveBeforeDiscard() const
{
	auto quote = mFilename.isEmpty() ? QString() : QLatin1String("\"");
	return mMessageBoxService->yesNoCancel(tr("Warning - ") + QApplication::applicationName(),
										  tr("The capture %1%2%3 has been modified.\nDo you want to save it?").arg(quote).arg(mFilename).arg(quote));
}
