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

#ifndef KSNIP_SCRIPTUPLOADER_H
#define KSNIP_SCRIPTUPLOADER_H

#include <QProcess>
#include <QRegularExpression>

#include "src/backend/uploader/IUploader.h"
#include "src/backend/config/KsnipConfigProvider.h"
#include "src/common/enum/UploadStatus.h"

class ScriptUploader : public QObject, public IUploader
{
	Q_OBJECT
public:
	ScriptUploader();
	~ScriptUploader() override = default;
	void upload(const QImage &image) override;
	UploaderType type() const override;

signals:
	void finished(const UploadResult &result) override;

private:
	KsnipConfig * mConfig;
	QProcess mProcessHandler;
	QString mPathToTmpImage;

private slots:
	void scriptFinished(int exitCode, QProcess::ExitStatus exitStatus);
	void errorOccurred(QProcess::ProcessError error);
	bool saveImageLocally(const QImage &image);
	void cleanup();
	QString parseOutput(const QString &output) const;
	void writeToConsole(const QString &output) const;
	UploadStatus mapErrorTypeToStatus(QProcess::ProcessError errorType) const;
	void handleSuccess();
	void handleError(const UploadStatus &status, const QString &stdErrOutput);
};

#endif //KSNIP_SCRIPTUPLOADER_H
