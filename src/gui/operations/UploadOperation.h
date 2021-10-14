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

#ifndef KSNIP_UPLOADOPERATION_H
#define KSNIP_UPLOADOPERATION_H

#include <QCoreApplication>
#include <QImage>
#include <QSharedPointer>

#include <utility>

#include "src/backend/uploader/IUploader.h"
#include "src/backend/config/IConfig.h"
#include "src/gui/messageBoxService/IMessageBoxService.h"
#include "src/common/helper/PathHelper.h"

class UploadOperation : public QObject
{
	Q_OBJECT
public:
	UploadOperation(
			QImage image,
			const QSharedPointer<IUploader> &uploader,
			const QSharedPointer<IConfig> &config,
			const QSharedPointer<IMessageBoxService> &messageBoxService);
	~UploadOperation() override = default;
	bool execute();

private:
	QImage mImage;
	QSharedPointer<IConfig> mConfig;
	QSharedPointer<IUploader> mUploader;
	QSharedPointer<IMessageBoxService> mMessageBoxService;

	bool proceedWithUpload() const;
	bool askIfCanProceedWithUpload() const;
};

#endif //KSNIP_UPLOADOPERATION_H
