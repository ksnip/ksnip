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

#include "src/backend/imageGrabber/AbstractImageGrabber.h"
#include "src/backend/saver/ImageSaver.h"
#include "src/backend/saver/SavePathProvider.h"
#include "src/backend/imageGrabber/ImageGrabberFactory.h"
#include "src/common/dtos/CaptureFromFileDto.h"

class CommandLineCaptureHandler : public QObject
{
	Q_OBJECT

public:
	explicit CommandLineCaptureHandler();
	~CommandLineCaptureHandler() override;

	void captureScreenshot(CaptureModes captureMode, bool captureCursor, int delay);
	void captureScreenshotAndSave(CaptureModes captureMode, bool captureCursor, int delay, const QString &savePath);
	QList<CaptureModes> supportedCaptureModes() const;

signals:
	void finished(const CaptureDto &captureDto);
	void canceled();

private:
	AbstractImageGrabber *mImageGrabber;
	QString mSavePath;
	bool mIsWithSaveImage;

private slots:
	void processCapture(const CaptureDto &capture);
	void savecapture(const CaptureDto &capture) const;
};


#endif //KSNIP_COMMANDLINECAPTUREHANDLER_H
