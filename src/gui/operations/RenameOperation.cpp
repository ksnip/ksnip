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

RenameResultDto RenameOperation::execute()
{
	auto newFilename = getNewFilename();
	if (newFilename.isNull() || newFilename.isEmpty()) {
		return RenameResultDto(false, mPathToImageSource);
	}

	auto renameSuccessful = rename(newFilename);

	if (renameSuccessful) {
		NotifyOperation operation(mToastService,
							tr("Image Renamed"),
							tr("Successfully renamed image to ") + newFilename,
							NotificationTypes::Information);
		operation.execute();
	} else {
		NotifyOperation operation(mToastService,
							tr("Image Rename Failed"),
							tr("Failed to rename image to ") + newFilename,
							NotificationTypes::Warning);
		operation.execute();
	}

	return RenameResultDto(renameSuccessful, mPathToImageSource);
}

QString RenameOperation::getNewFilename() const
{
	QInputDialog dialog;

	dialog.setInputMode(QInputDialog::TextInput);
	dialog.setWindowTitle(tr("Rename image"));
	dialog.setLabelText(tr("New filename:"));
	dialog.setTextEchoMode(QLineEdit::Normal);
	dialog.setTextValue(mImageFilename);
	dialog.resize(270, 0);

	if (QDialog::Accepted == dialog.exec()) {
		return dialog.textValue();
	}
	return QString();
}

bool RenameOperation::rename(const QString &newFilename)
{
	auto oldFilename = PathHelper::extractFilename(mPathToImageSource);
	auto newPathToImageSource = mPathToImageSource;
	newPathToImageSource.replace(oldFilename, newFilename);

	QFile file(mPathToImageSource);
	auto renameSuccessful = file.rename(newPathToImageSource);
	if (renameSuccessful) {
		mPathToImageSource = newPathToImageSource;
	}
	return renameSuccessful;
}
