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

#ifndef KSNIP_IMGURUPLOADER_H
#define KSNIP_IMGURUPLOADER_H

#include <QImage>

#include "IImgurUploader.h"
#include "ImgurWrapper.h"
#include "ImgurResponseLogger.h"
#include "src/backend/uploader/IUploader.h"
#include "src/backend/uploader/UploadResult.h"
#include "src/backend/config/IConfig.h"
#include "src/common/constants/DefaultValues.h"

class ImgurUploader : public IImgurUploader
{
Q_OBJECT
public:
    explicit ImgurUploader(const QSharedPointer<IConfig> &config);
    ~ImgurUploader() override;

    void upload(const QImage &image) override;
	UploaderType type() const override;

private:
	QSharedPointer<IConfig> mConfig;
	ImgurWrapper *mImgurWrapper;
    ImgurResponseLogger *mImgurResponseLogger;
    QImage mImage;

private slots:
    void imgurUploadFinished(const ImgurResponse &response);
    void imgurError(const QString &message);
    void imgurTokenUpdated(const QString &accessToken, const QString &refreshToken, const QString &username);
    void imgurTokenRefresh();
	QString formatResponseUrl(const ImgurResponse &response) const;
};

#endif //KSNIP_IMGURUPLOADER_H
