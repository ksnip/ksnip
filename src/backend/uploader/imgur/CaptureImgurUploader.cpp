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

#include "CaptureImgurUploader.h"

CaptureImgurUploader::CaptureImgurUploader()
{
	mImgurWrapper = new ImgurWrapper();
    mImgurResponseLogger = new ImgurResponseLogger();
    mConfig = KsnipConfigProvider::instance();

    connect(mImgurWrapper, &ImgurWrapper::uploadFinished, this, &CaptureImgurUploader::imgurUploadFinished);
    connect(mImgurWrapper, &ImgurWrapper::error, this, &CaptureImgurUploader::imgurError);
    connect(mImgurWrapper, &ImgurWrapper::tokenUpdated, this, &CaptureImgurUploader::imgurTokenUpdated);
    connect(mImgurWrapper, &ImgurWrapper::tokenRefreshRequired, this, &CaptureImgurUploader::imgurTokenRefresh);
}

CaptureImgurUploader::~CaptureImgurUploader()
{
    delete mImgurWrapper;
    delete mImgurResponseLogger;
}

void CaptureImgurUploader::upload(const QImage &image)
{
    mImage = image;

    if (!mConfig->imgurForceAnonymous() && !mConfig->imgurAccessToken().isEmpty()) {
        mImgurWrapper->startUpload(mImage, mConfig->imgurAccessToken());
    } else {
        mImgurWrapper->startUpload(mImage);
    }
}

void CaptureImgurUploader::imgurUploadFinished(const UploadResponse &response)
{
    qInfo("%s", qPrintable(tr("Upload to imgur.com finished!")));
    emit finished(response.link());

    mImgurResponseLogger->log(response);

    mImage = QImage();
}

void CaptureImgurUploader::imgurError(const QString &message)
{
    qCritical("MainWindow: Imgur uploader returned error: '%s'", qPrintable(message));
    emit error(message);
}

void CaptureImgurUploader::imgurTokenUpdated(const QString &accessToken, const QString &refreshToken, const QString &username)
{
    mConfig->setImgurAccessToken(accessToken.toUtf8());
    mConfig->setImgurRefreshToken(refreshToken.toUtf8());
    mConfig->setImgurUsername(username);

    qInfo("%s", qPrintable(tr("Received new token, trying upload again…")));
    upload(mImage);
}

void CaptureImgurUploader::imgurTokenRefresh()
{
    mImgurWrapper->refreshToken(mConfig->imgurRefreshToken(), mConfig->imgurClientId(), mConfig->imgurClientSecret());
    qInfo("%s", qPrintable(tr("Imgur token has expired, requesting new token…")));
}
