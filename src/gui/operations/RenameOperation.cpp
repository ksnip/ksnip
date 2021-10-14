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

RenameOperation::RenameOperation(
		const QString &pathToImageSource,
		const QString &imageFilename,
		const QSharedPointer<INotificationService> &notificationService,
		const QSharedPointer<IConfig> &config,
		QWidget *parent) :
	mParent(parent),
	mPathToImageSource(pathToImageSource),
	mImageFilename(imageFilename),
	mNotificationService(notificationService),
	mConfig(config)
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
		NotifyOperation operation(
				tr("Image Renamed"),
				tr("Successfully renamed image to ") + newFilename,
				NotificationTypes::Information,
				mNotificationService,
				mConfig);
		operation.execute();
	} else {
		NotifyOperation operation(
				tr("Image Rename Failed"),
				tr("Failed to rename image to ") + newFilename,
				NotificationTypes::Warning,
				mNotificationService,
				mConfig);
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
	return {};
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
