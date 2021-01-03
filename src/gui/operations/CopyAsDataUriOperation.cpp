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

#include "CopyAsDataUriOperation.h"

CopyAsDataUriOperation::CopyAsDataUriOperation(QImage image, IClipboard *clipboard, IToastService *toastService) :
	mImage(std::move(image)),
	mClipboard(clipboard),
	mToastService(toastService)
{
}

bool CopyAsDataUriOperation::execute()
{
	QByteArray byteArray;

	QBuffer buffer(&byteArray);
	buffer.open(QIODevice::WriteOnly);
	auto saved = mImage.save(&buffer, "PNG");
	buffer.close();

	if (saved) {
		QByteArray output = "data:image/png;base64,";
		output.append(byteArray.toBase64());
		mClipboard->setText(output);
		notifySuccess();
	} else {
		notifyFailure();
	}

	return saved;
}

void CopyAsDataUriOperation::notifyFailure() const
{
	auto title = tr("Failed to copy to clipboard");
	auto message = tr("Failed to copy to clipboard as base64 encoded image.");
	notify(title, message, NotificationTypes::Warning);
}

void CopyAsDataUriOperation::notifySuccess() const
{
	auto title = tr("Copied to clipboard");
	auto message = tr("Copied to clipboard as base64 encoded image.");
	notify(title, message, NotificationTypes::Information);
}

void CopyAsDataUriOperation::notify(const QString &title, const QString &message, NotificationTypes type) const
{
	NotifyOperation operation(mToastService, title, message, type);
	operation.execute();
}
