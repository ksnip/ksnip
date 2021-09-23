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

#ifndef KSNIP_UPLOADERPROVIDER_H
#define KSNIP_UPLOADERPROVIDER_H

#include <QObject>
#include <QSharedPointer>

#include "IUploaderProvider.h"
#include "src/backend/uploader/imgur/IImgurUploader.h"
#include "src/backend/uploader/script/IScriptUploader.h"
#include "src/backend/uploader/ftp/IFtpUploader.h"
#include "src/backend/config/IConfig.h"

class UploaderProvider : public IUploaderProvider
{
	Q_OBJECT
public:
	explicit UploaderProvider(
			const QSharedPointer<IConfig> &config,
			const QSharedPointer<IFtpUploader> &ftpUploader,
			const QSharedPointer<IScriptUploader> &scriptUploader,
			const QSharedPointer<IImgurUploader> &imgurUploader);
	~UploaderProvider() override = default;
	IUploader* get() override;

private:
	QSharedPointer<IConfig> mConfig;
	QSharedPointer<IImgurUploader> mImgurUploader;
	QSharedPointer<IScriptUploader> mScriptUploader;
	QSharedPointer<IFtpUploader> mFtpUploader;

	void connectSignals(IUploader *uploader);
};

#endif //KSNIP_UPLOADERPROVIDER_H
