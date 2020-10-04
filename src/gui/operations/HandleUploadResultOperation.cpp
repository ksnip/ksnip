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

#include "HandleUploadResultOperation.h"

HandleUploadResultOperation::HandleUploadResultOperation(const UploadResult &result, TrayIcon *trayIcon) :
	mUploadResult(result),
	mTrayIcon(trayIcon),
	mConfig(KsnipConfigProvider::instance()),
	mClipboard(QApplication::clipboard())
{
}

bool HandleUploadResultOperation::execute()
{
	switch (mUploadResult.type) {
		case UploaderType::Imgur:
			handleImgurResult();
			break;
		case UploaderType::Script:
			handleScriptResult();
			break;
	}

	return mUploadResult.status == UploadStatus::NoError;
}

void HandleUploadResultOperation::handleImgurResult()
{
	if(mUploadResult.status == UploadStatus::NoError) {
		if (mConfig->imgurOpenLinkInBrowser()) {
			OpenUrl(mUploadResult.content);
		}

		if (mConfig->imgurAlwaysCopyToClipboard()) {
			copyToClipboard(mUploadResult.content);
		}

		notifyImgurSuccessfulUpload(mUploadResult.content);
	} else {
		handleUploadError();
	}
}

void HandleUploadResultOperation::handleScriptResult()
{
	if(mUploadResult.status == UploadStatus::NoError) {
		if (mConfig->uploadScriptCopyOutputToClipboard()) {
			copyToClipboard(mUploadResult.content);
		}

		notifyScriptSuccessfulUpload();
	} else {
		handleUploadError();
	}
}

void HandleUploadResultOperation::notifyScriptSuccessfulUpload() const
{
	NotifyOperation operation(mTrayIcon, tr("Upload Successful"), tr("Upload script ") + mConfig->uploadScriptPath() + tr(" finished successfully."), NotificationTypes::Information);
	operation.execute();
}

void HandleUploadResultOperation::notifyImgurSuccessfulUpload(const QString &url) const
{
	NotifyOperation operation(mTrayIcon, tr("Upload Successful"), tr("Uploaded to") + QLatin1Literal(" ") + url, url, NotificationTypes::Information);
	operation.execute();
}

void HandleUploadResultOperation::copyToClipboard(const QString &url) const
{
	mClipboard->setText(url);
}


void HandleUploadResultOperation::OpenUrl(const QString &url) const
{
	QDesktopServices::openUrl(url);
}

void HandleUploadResultOperation::handleUploadError()
{
	switch (mUploadResult.status) {

		case UploadStatus::NoError:
			// Nothing to report all good
			break;
		case UploadStatus::UnableToSaveTemporaryImage:
			notifyFailedUpload(tr("Unable to save temporary image for upload."));
			break;
		case UploadStatus::FailedToStart:
			notifyFailedUpload(tr("Unable to start process, check path and permissions."));
			break;
		case UploadStatus::Crashed:
			notifyFailedUpload(tr("Process crashed"));
			break;
		case UploadStatus::Timedout:
			notifyFailedUpload(tr("Process timed out."));
			break;
		case UploadStatus::ReadError:
			notifyFailedUpload(tr("Process read error."));
			break;
		case UploadStatus::WriteError:
			notifyFailedUpload(tr("Process write error."));
			break;
		case UploadStatus::WebError:
			notifyFailedUpload(tr("Web error, check console output."));
			break;
		case UploadStatus::UnknownError:
			notifyFailedUpload(tr("Unknown process error."));
			break;
		case UploadStatus::ScriptWroteToStdErr:
			notifyFailedUpload(tr("Script wrote to StdErr."));
			break;
	}
}

void HandleUploadResultOperation::notifyFailedUpload(const QString &message) const
{
	NotifyOperation operation(mTrayIcon, tr("Upload Failed"), message, NotificationTypes::Warning);
	operation.execute();
}

