/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_COMMANDLINECAPTUREHANDLER_H
#define KSNIP_COMMANDLINECAPTUREHANDLER_H

#include <QObject>

#include "CommandLineCaptureParameter.h"
#include "src/backend/imageGrabber/IImageGrabber.h"
#include "src/backend/saver/ImageSaver.h"
#include "src/backend/saver/SavePathProvider.h"
#include "src/backend/uploader/UploaderProvider.h"
#include "src/common/dtos/CaptureFromFileDto.h"
#include "src/common/helper/EnumTranslator.h"
#include "src/dependencyInjector/DependencyInjector.h"

class CommandLineCaptureHandler : public QObject
{
	Q_OBJECT

public:
	explicit CommandLineCaptureHandler(DependencyInjector *dependencyInjector);
	~CommandLineCaptureHandler() override = default;
	void captureAndProcessScreenshot(const CommandLineCaptureParameter &parameter);
	QList<CaptureModes> supportedCaptureModes() const;

signals:
	void finished(const CaptureDto &captureDto);
	void canceled();

private:
	QSharedPointer<IImageGrabber> mImageGrabber;
	QSharedPointer<IUploaderProvider> mUploadProvider;
	QString mSavePath;
	bool mIsWithSave;
	bool mIsWithUpload;
	CaptureDto mCurrentCapture;

private slots:
	void processCapture(const CaptureDto &capture);
	void saveCapture(const CaptureDto &capture) const;
	void uploadFinished(const UploadResult &result);
};


#endif //KSNIP_COMMANDLINECAPTUREHANDLER_H
