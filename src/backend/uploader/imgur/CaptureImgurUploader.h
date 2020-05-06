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

#ifndef KSNIP_CAPTUREIMGURUPLOADER_H
#define KSNIP_CAPTUREIMGURUPLOADER_H

#include <QImage>

#include "ImgurWrapper.h"
#include "ImgurResponseLogger.h"
#include "src/backend/uploader/UploadResult.h"
#include "backend/config/KsnipConfigProvider.h"

class CaptureImgurUploader : public QObject
{
Q_OBJECT
public:
    explicit CaptureImgurUploader();
    ~CaptureImgurUploader() override;

    void upload(const QImage &image);

signals:
    void finished(const QString &url) const;
    void error(const QString &error) const;

private:
    ImgurWrapper *mImgurWrapper;
    ImgurResponseLogger *mImgurResponseLogger;
    KsnipConfig *mConfig;
    QImage mImage;

private slots:
    void imgurUploadFinished(const UploadResponse &response);
    void imgurError(const QString &message);
    void imgurTokenUpdated(const QString &accessToken, const QString &refreshToken, const QString &username);
    void imgurTokenRefresh();
};

#endif //KSNIP_CAPTUREIMGURUPLOADER_H
