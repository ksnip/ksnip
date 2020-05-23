/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#include "ImgurUploader.h"

ImgurUploader::ImgurUploader() :
	mConfig(KsnipConfigProvider::instance()),
	mImgurWrapper(new ImgurWrapper(mConfig->imgurBaseUrl(), nullptr)),
	mImgurResponseLogger(new ImgurResponseLogger)

{
    connect(mImgurWrapper, &ImgurWrapper::uploadFinished, this, &ImgurUploader::imgurUploadFinished);
    connect(mImgurWrapper, &ImgurWrapper::error, this, &ImgurUploader::imgurError);
    connect(mImgurWrapper, &ImgurWrapper::tokenUpdated, this, &ImgurUploader::imgurTokenUpdated);
    connect(mImgurWrapper, &ImgurWrapper::tokenRefreshRequired, this, &ImgurUploader::imgurTokenRefresh);
}

UploaderType ImgurUploader::type() const
{
	return UploaderType::Imgur;
}

ImgurUploader::~ImgurUploader()
{
    delete mImgurWrapper;
    delete mImgurResponseLogger;
}

void ImgurUploader::upload(const QImage &image)
{
    mImage = image;

    if (!mConfig->imgurForceAnonymous() && !mConfig->imgurAccessToken().isEmpty()) {
        mImgurWrapper->startUpload(mImage, mConfig->imgurAccessToken());
    } else {
        mImgurWrapper->startUpload(mImage);
    }
}

void ImgurUploader::imgurUploadFinished(const ImgurResponse &response)
{
    qInfo("%s", qPrintable(tr("Upload to imgur.com finished!")));
    mImgurResponseLogger->log(response);

	auto url = formatResponseUrl(response);

	emit finished(UploadResult(UploadStatus::NoError, type(), url));
}

QString ImgurUploader::formatResponseUrl(const ImgurResponse &response) const
{
	if (!mConfig->imgurLinkDirectlyToImage()) {
		return response.link().remove(QStringLiteral(".png"));
	}
	return response.link();
}

void ImgurUploader::imgurError(const QString &message)
{
    qCritical("MainWindow: Imgur uploader returned error: '%s'", qPrintable(message));
	emit finished(UploadResult(UploadStatus::NoError, type(), message));
}

void ImgurUploader::imgurTokenUpdated(const QString &accessToken, const QString &refreshToken, const QString &username)
{
    mConfig->setImgurAccessToken(accessToken.toUtf8());
    mConfig->setImgurRefreshToken(refreshToken.toUtf8());
    mConfig->setImgurUsername(username);

    qInfo("%s", qPrintable(tr("Received new token, trying upload again…")));
    upload(mImage);
}

void ImgurUploader::imgurTokenRefresh()
{
    mImgurWrapper->refreshToken(mConfig->imgurRefreshToken(), mConfig->imgurClientId(), mConfig->imgurClientSecret());
    qInfo("%s", qPrintable(tr("Imgur token has expired, requesting new token…")));
}
