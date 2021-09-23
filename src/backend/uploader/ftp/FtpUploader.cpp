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

#include "FtpUploader.h"

FtpUploader::FtpUploader(const QSharedPointer<IConfig> &config, const QSharedPointer<ILogger> &logger) :
	mConfig(config),
	mLogger(logger),
	mReply(nullptr)
{

}

void FtpUploader::upload(const QImage &image)
{
	// Convert the image into a byteArray
	auto imageByteArray = getImageAsByteArray(image);

	auto url = getUploadUrl();

	mLogger->log(QString("FTP upload started to %1").arg(url.toString(QUrl::RemoveUserInfo)));

	mReply = mNetworkAccessManager.put(QNetworkRequest(url), imageByteArray);
	connect(mReply, &QNetworkReply::uploadProgress, this, &FtpUploader::uploadProgress);
	connect(mReply, &QNetworkReply::finished, this, &FtpUploader::uploadDone);
}

QByteArray FtpUploader::getImageAsByteArray(const QImage &image)
{
	QByteArray imageByteArray;
	QBuffer buffer(&imageByteArray);
	image.save(&buffer, "PNG");
	return imageByteArray;
}

QUrl FtpUploader::getUploadUrl() const
{
	QUrl url(mConfig->ftpUploadUrl() + QLatin1String("/") + getFilename());

	if(mConfig->ftpUploadForceAnonymous()) {
		mLogger->log(QLatin1String("Enforcing anonymous FTP upload."));
	} else {
		url.setUserName(mConfig->ftpUploadUsername());
		url.setPassword(mConfig->ftpUploadPassword());
	}

	return url.adjusted(QUrl::NormalizePathSegments);
}

QString FtpUploader::getFilename()
{
	return QLatin1String("ksnip_") + QDateTime::currentDateTime().toString("yyyy-MM-ddTHH:mm:ss");
}

UploaderType FtpUploader::type() const
{
	return UploaderType::Ftp;
}

void FtpUploader::uploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
	mLogger->log(QString("Uploaded %1 of %2 bytes.").arg(QString::number(bytesSent), QString::number(bytesTotal)));
}

void FtpUploader::uploadDone()
{
	mLogger->log(QLatin1String("FTP uploaded finished with status %1."), mReply->error());

	emit finished(UploadResult(mapErrorTypeToStatus(mReply->error()), type()));

	mReply->deleteLater();
}

UploadStatus FtpUploader::mapErrorTypeToStatus(QNetworkReply::NetworkError errorType)
{
	switch (errorType) {
		case QNetworkReply::NetworkError::NoError:
			return UploadStatus::NoError;
		case QNetworkReply::NetworkError::TimeoutError:
			return UploadStatus::TimedOut;
		case QNetworkReply::NetworkError::ConnectionRefusedError:
		case QNetworkReply::NetworkError::RemoteHostClosedError:
		case QNetworkReply::NetworkError::HostNotFoundError:
		case QNetworkReply::NetworkError::TemporaryNetworkFailureError:
		case QNetworkReply::NetworkError::ServiceUnavailableError:
			return UploadStatus::ConnectionError;
		case QNetworkReply::NetworkError::ContentOperationNotPermittedError:
		case QNetworkReply::NetworkError::ContentAccessDenied:
		case QNetworkReply::NetworkError::AuthenticationRequiredError:
			return UploadStatus::PermissionError;
		default:
			return UploadStatus::UnknownError;
	}
}
