/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#ifndef KSNIPCONFIG_H
#define KSNIPCONFIG_H

#include <QObject>
#include <QPoint>
#include <QSettings>

#include "src/painter/PaintArea.h"
#include "ImageGrabber.h"

class KsnipConfig : public QObject
{
    Q_OBJECT

public:
    KsnipConfig(QObject *parent = 0);

    static KsnipConfig *instance();

    // Application

    bool saveKsnipPosition() const;
    void setSaveKsnipPosition(const bool &enabled);

    bool promptSaveBeforeExit() const;
    void setPromptSaveBeforeExit(const bool &enabled);

    bool alwaysCopyToClipboard() const;
    void setAlwaysCopyToClipboard(const bool &enabled);

    bool saveKsnipToolSelection() const;
    void setSaveKsnipToolSelection(const bool &enabled);

    QPoint windowPosition() const;
    void setWindowPosition(const QPoint &position);

    PaintArea::PaintMode paintMode() const;
    void setPaintMode(const PaintArea::PaintMode &mode);

    ImageGrabber::CaptureMode captureMode() const;
    void setCaptureMode(const ImageGrabber::CaptureMode &mode);

    QString saveDirectory() const;
    void setSaveDirectory(const QString &path);

    QString saveFilename() const;
    void setSaveFilename(const QString &filename);

    QString saveFormat() const;
    void setSaveFormat(const QString &format);

    // Painter

    QPen pen() const;

    QColor penColor() const;
    void setPenColor(const QColor &color);

    int penSize() const;
    void setPenSize(const int &size);

    QPen marker() const;

    QColor markerColor() const;
    void setMarkerColor(const QColor &color);

    int markerSize() const;
    void setMarkerSize(const int &size);

    QPen rect() const;

    QColor rectColor() const;
    void setRectColor(const QColor &color);

    int rectSize() const;
    void setRectSize(const int &size);

    bool rectFill() const;
    void setRectFill(const bool &fill);

    QPen ellipse() const;

    QColor ellipseColor() const;
    void setEllipseColor(const QColor &color);

    int ellipseSize() const;
    void setEllipseSize(const int &size);

    bool ellipseFill() const;
    void setEllipseFill(const bool &fill);

    QPen text() const;

    QColor textColor() const;
    void setTextColor(const QColor &color);

    int textSize() const;
    void setTextSize(const int &size);

    bool textBold() const;
    void setTextBold(const bool &bold);

    bool textItalic() const;
    void setTextItalic(const bool &italic);

    bool textUnderline() const;
    void setTextUnderline(const bool &underline);

    QFont textFont() const;
    void setTextFont(const QFont &font);

    int eraseSize() const;
    void setEraseSize(const int &size);

    bool smoothPath() const;
    void setSmoothPath(const bool &enabled);

    int smoothFactor() const;
    void setSmoothFactor(const int &factor);

    // Image Grabber

    bool captureMouse() const;
    void setCaptureMouse(bool enabled);

    int captureDelay() const;
    void setCaptureDelay(int delay);

    // Imgur Uploader

    QString imgurUsername() const;
    void setImgurUsername(QString username);

    QByteArray imgurClientId() const;
    void setImgurClientId(QString clientId);

    QByteArray imgurClientSecret() const;
    void setImgurClientSecret(QString clientSecret);

    QByteArray imgurAccessToken() const;
    void setImgurAccessToken(QString accessToken);

    QByteArray imgurRefreshToken() const;
    void setImgurRefreshToken(QString refreshToken);

    bool imgurForceAnonymous() const;
    void setImgurForceAnonymous(bool enabled);

    bool imgurOpenLinkDirectlyToImage() const;
    void setImgurOpenLinkDirectlyToImage(bool enabled);

    bool imgurAlwaysCopyToClipboard() const;
    void setImgurAlwaysCopyToClipboard(bool enabled);

signals:
    void painterUpdated();
    void captureDelayUpdated(int delay);

private:
    QSettings mConfig;
};

#endif // KSNIPCONFIG_H
