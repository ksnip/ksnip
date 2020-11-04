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

#include "RenameOperation.h"

RenameOperation::RenameOperation(QWidget *parent, const QString &pathToImageSource, const QString &imageFilename, IToastService *toastService) :
    mParent(parent),
    mPathToImageSource(pathToImageSource),
    mImageFilename(imageFilename),
    mToastService(toastService)
{
}

SaveResultDto RenameOperation::execute()
{
	const auto newFilename = getNewFilename();
	if (newFilename.isEmpty()) {
		return SaveResultDto(false, mPathToImageSource);
	}

	const bool renameOk = rename(newFilename);

	if (renameOk) {
		NotifyOperation operation(mToastService, tr("Image Renamed"),
								  "Successfully renamed image to " + newFilename,
								  NotificationTypes::Information);
		operation.execute();
		return SaveResultDto(true, mPathToImageSource);
	} else {
		NotifyOperation operation(mToastService, tr("Image Rename Failed"),
								  "Failed to rename image to " + newFilename,
								  NotificationTypes::Warning);
		operation.execute();
		return SaveResultDto(false, mPathToImageSource);
	}
}

QString RenameOperation::getNewFilename() const
{
	bool ok;
	QString newFilename = QInputDialog::getText(mParent, tr("Rename image"),
												tr("New filename:"), QLineEdit::Normal,
												mImageFilename, &ok);

	return (ok ? newFilename : "");
}

bool RenameOperation::rename(const QString &newFilename)
{
	QFile file(mPathToImageSource);
	const bool renameOk = file.rename(newFilename);
	if (renameOk) {
		mPathToImageSource = QFileInfo(file).absoluteFilePath();
	}
	return renameOk;
}
