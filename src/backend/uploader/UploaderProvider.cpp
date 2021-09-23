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

#include "UploaderProvider.h"

UploaderProvider::UploaderProvider(
		const QSharedPointer<IConfig> &config,
		const QSharedPointer<IFtpUploader> &ftpUploader,
		const QSharedPointer<IScriptUploader> &scriptUploader,
		const QSharedPointer<IImgurUploader> &imgurUploader) :
	mConfig(config),
	mImgurUploader(imgurUploader),
	mScriptUploader(scriptUploader),
	mFtpUploader(ftpUploader)
{
}

IUploader* UploaderProvider::get()
{
	switch (mConfig->uploaderType()) {
		case UploaderType::Imgur:
			return mImgurUploader.data();
		case UploaderType::Script:
			return mScriptUploader.data();
		case UploaderType::Ftp:
			return mFtpUploader.data();
		default:
			return mImgurUploader.data();
	}
}

void UploaderProvider::connectSignals(IUploader *uploader)
{ 
	connect(dynamic_cast<QObject*>(uploader), SIGNAL(finished(UploadResult)), this, SIGNAL(finished(UploadResult)));
}
