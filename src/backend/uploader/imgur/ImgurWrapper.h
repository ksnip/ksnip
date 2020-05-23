/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#ifndef KSNIP_IMGURWRAPPER_H
#define KSNIP_IMGURWRAPPER_H

#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QDomDocument>
#include <QImage>
#include <QBuffer>

#include "ImgurResponse.h"

class ImgurWrapper : public QObject
{
    Q_OBJECT
public:
    explicit ImgurWrapper(const QString &imgurUrl, QObject *parent);
    void startUpload(const QImage &image, const QByteArray &accessToken = nullptr) const;
    void getAccessToken(const QByteArray &pin, const QByteArray &clientId, const QByteArray &clientSecret) const;
    void refreshToken(const QByteArray &refreshToken, const QByteArray &clientId, const QByteArray &clientSecret) const;
    QUrl pinRequestUrl(const QString &clientId) const;

signals:
    void uploadFinished(const ImgurResponse &response) const;
    void error(const QString &message) const;
    void tokenUpdated(const QString &accessToken, const QString &refreshToken, const QString &username) const;
    void tokenRefreshRequired() const;

private:
    QNetworkAccessManager *mAccessManager;
    QByteArray mClientId;
    QString mBaseImgutUrl;

    void handleDataResponse(const QDomElement &element) const;
    void handleTokenResponse(const QDomElement &element) const;

private slots:
    void handleReply(QNetworkReply *reply);
};

#endif // KSNIP_IMGURWRAPPER_H
