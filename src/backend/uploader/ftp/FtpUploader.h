/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_FTPUPLOADER_H
#define KSNIP_FTPUPLOADER_H

#include <QNetworkAccessManager>
#include <QImage>
#include <QNetworkReply>
#include <QBuffer>
#include <QDateTime>

#include "src/backend/uploader/IUploader.h"
#include "src/backend/config/ConfigProvider.h"
#include "src/logging/LoggerProvider.h"

class FtpUploader : public QObject, public IUploader
{
	Q_OBJECT
public:
	FtpUploader();
	~FtpUploader() override = default;
	void upload(const QImage &image) override;
	UploaderType type() const override;

signals:
	void finished(const UploadResult &result) override;

private:
	Config * mConfig;
	ILogger *mLogger;
	QNetworkAccessManager mNetworkAccessManager;
	QNetworkReply *mReply;

	static UploadStatus mapErrorTypeToStatus(QNetworkReply::NetworkError errorType);
	static QString getFilename();
	static QByteArray getImageAsByteArray(const QImage &image) ;
	QUrl getUploadUrl() const;

private slots:
	void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
	void uploadDone();
};

#endif //KSNIP_FTPUPLOADER_H
