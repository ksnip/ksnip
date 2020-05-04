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

#ifndef KSNIP_UPLOADSCRIPTOPERATION_H
#define KSNIP_UPLOADSCRIPTOPERATION_H

#include <QCoreApplication>
#include <QImage>

#include "src/backend/uploader/script/CaptureScriptUploader.h"
#include "src/backend/config/KsnipConfigProvider.h"
#include "src/common/helper/MessageBoxHelper.h"
#include "src/common/helper/PathHelper.h"

class UploadScriptOperation : public QObject
{
	Q_OBJECT
public:
	UploadScriptOperation(const QImage &image, CaptureScriptUploader *uploader);
	~UploadScriptOperation() override = default;
	bool execute();

private:
	KsnipConfig *mConfig;
	CaptureScriptUploader *mUploader;
	QImage mImage;

	bool proceedWithUpload() const;
	bool getProceedWithUpload() const;
	void NotifyAboutMissingScript() const;
};

#endif //KSNIP_UPLOADSCRIPTOPERATION_H
