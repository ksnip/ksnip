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

#include "src/backend/uploader/IUploader.h"
#include "src/backend/config/KsnipConfigProvider.h"
#include "src/common/helper/MessageBoxHelper.h"

class UploadOperation : public QObject
{
	Q_OBJECT
public:
	UploadOperation(const QImage &image, IUploader *uploader);
	~UploadOperation() override = default;
	bool execute();

private:
	KsnipConfig *mConfig;
	IUploader *mUploader;
	QImage mImage;

	bool proceedWithUpload() const;
	bool getProceedWithUpload() const;
};

#endif //KSNIP_UPLOADOPERATION_H
