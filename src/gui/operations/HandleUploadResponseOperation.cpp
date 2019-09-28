/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "HandleUploadResponseOperation.h"

HandleUploadResponseOperation::HandleUploadResponseOperation(const QString &response, TrayIcon *trayIcon) : QObject(nullptr)
{
	mResponse = response;
	mTrayIcon = trayIcon;
	mConfig = KsnipConfig::instance();
	mClipboard = QApplication::clipboard();
}

bool HandleUploadResponseOperation::execute()
{
	auto url = formatUrl(mResponse);

	openInBrowser(url);

	copyToClipboard(url);

	notifyAboutUpload(url);

	return true;
}

void HandleUploadResponseOperation::notifyAboutUpload(const QUrl &url) const
{
	NotifyOperation operation(mTrayIcon, tr("Upload Successful"), tr("Uploaded to") + QStringLiteral(" ") + url.toString(), NotificationTypes::Information);
	operation.execute();
}

void HandleUploadResponseOperation::openInBrowser(const QUrl &url) const
{
	if(mConfig->imgurOpenLinkInBrowser()) {
		QDesktopServices::openUrl(url);
	}
}

QUrl HandleUploadResponseOperation::formatUrl(QString &response) const
{
	if (!mConfig->imgurOpenLinkDirectlyToImage()) {
		response = response.remove(QStringLiteral(".png"));
	}
	return response;
}

void HandleUploadResponseOperation::copyToClipboard(const QUrl &url) const
{
	if (mConfig->imgurAlwaysCopyToClipboard()) {
		mClipboard->setText(url.toString());
	}
}
