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

#include "UploadHandler.h"

UploadHandler::UploadHandler(
		const QSharedPointer<IConfig> &config,
		const QSharedPointer<IFtpUploader> &ftpUploader,
		const QSharedPointer<IScriptUploader> &scriptUploader,
		const QSharedPointer<IImgurUploader> &imgurUploader) :
	mConfig(config)
{
	insertUploader(imgurUploader);
	insertUploader(scriptUploader);
	insertUploader(ftpUploader);
}

void UploadHandler::upload(const QImage &image)
{
	mTypeToUploaderMap[type()]->upload(image);
}

UploaderType UploadHandler::type() const
{
	return mConfig->uploaderType();
}

void UploadHandler::insertUploader(const QSharedPointer<IUploader> &uploader)
{
	mTypeToUploaderMap[uploader->type()] = uploader;
	connect(uploader.data(), &IUploader::finished, this, &IUploader::finished);
}
