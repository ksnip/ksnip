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

#ifndef KSNIP_UPLOADHANDLER_H
#define KSNIP_UPLOADHANDLER_H

#include <QSharedPointer>
#include <QMap>

#include "IUploadHandler.h"
#include "src/backend/uploader/imgur/IImgurUploader.h"
#include "src/backend/uploader/script/IScriptUploader.h"
#include "src/backend/uploader/ftp/IFtpUploader.h"
#include "src/backend/config/IConfig.h"

class UploadHandler : public IUploadHandler
{
public:
	explicit UploadHandler(
			const QSharedPointer<IConfig> &config,
			const QSharedPointer<IFtpUploader> &ftpUploader,
			const QSharedPointer<IScriptUploader> &scriptUploader,
			const QSharedPointer<IImgurUploader> &imgurUploader);
	~UploadHandler() override = default;
	void upload(const QImage &image) override;
	UploaderType type() const override;

private:
	QSharedPointer<IConfig> mConfig;
	QMap<UploaderType, QSharedPointer<IUploader>> mTypeToUploaderMap;

	void insertUploader(const QSharedPointer<IUploader> &uploader);
};

#endif //KSNIP_UPLOADHANDLER_H
