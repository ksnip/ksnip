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

CanDiscardOperation::CanDiscardOperation(QWidget *parent, const QImage &image, bool isUnsaved, const QString &pathToImageSource, const QString &filename, IToastService *toastService) :
	mParent(parent),
	mImage(image),
	mIsUnsaved(isUnsaved),
	mPathToImageSource(pathToImageSource),
	mFilename(filename),
	mConfig(KsnipConfigProvider::instance()),
	mToastService(toastService)
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
	SaveOperation operation(mParent, mImage, true, mPathToImageSource, mToastService);
	return operation.execute().isSuccessful;
}

MessageBoxResponse CanDiscardOperation::getSaveBeforeDiscard() const
{
	auto quote = mFilename.isEmpty() ? QString() : QStringLiteral("\"");
	return MessageBoxHelper::yesNoCancel(tr("Warning - ") + QApplication::applicationName(),
		                                 tr("The capture %1%2%3 has been modified.\nDo you want to save it?").arg(quote).arg(mFilename).arg(quote));
}
