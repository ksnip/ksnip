/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_CAPTUREUPLOADER_H
#define KSNIP_CAPTUREUPLOADER_H

#include <QImage>

#include "src/backend/ImgurUploader.h"
#include "src/backend/KsnipConfig.h"

class CaptureUploader : public QObject
{
public:
    explicit CaptureUploader();
    ~CaptureUploader();

    void upload(const QImage &image);

signals:
    void finished(const QString &url) const;
    void error(const QString &error) const;

private:
    ImgurUploader *mImgurUploader;
    KsnipConfig *mConfig;
    QImage mImage;

private slots:
    void imgurUploadFinished(QString message);
    void imgurError(const QString &message);
    void imgurTokenUpdated(const QString &accessToken, const QString &refreshTocken, const QString &username);
    void imgurTokenRefresh();
};

#endif //KSNIP_CAPTUREUPLOADER_H
