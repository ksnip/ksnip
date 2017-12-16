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
#include <QDirModel>
#include <QPoint>
#include <QSettings>

#include "ImageGrabber.h"
#include "src/helper/StringFormattingHelper.h"
#include "src/painter/PaintModes.h"

class KsnipConfig : public QObject
{
    Q_OBJECT

public:
    KsnipConfig(QObject *parent = 0);

    static KsnipConfig *instance();

    // Application

    bool saveKsnipPosition() const;
    void setSaveKsnipPosition(bool enabled);

    bool promptSaveBeforeExit() const;
    void setPromptSaveBeforeExit(bool enabled);

    bool alwaysCopyToClipboard() const;
    void setAlwaysCopyToClipboard(bool enabled);

    bool saveKsnipToolSelection() const;
    void setSaveKsnipToolSelection(bool enabled);

    bool captureOnStartup() const;
    void setCaptureOnStartup(bool enabled);

    QPoint windowPosition() const;
    void setWindowPosition(const QPoint &position);

    Painter::Modes paintMode() const;
    void setPaintMode(Painter::Modes mode);

    ImageGrabber::CaptureMode captureMode() const;
    void setCaptureMode(ImageGrabber::CaptureMode mode);

    QString saveDirectory() const;
    void setSaveDirectory(const QString &path);

    QString saveFilename() const;
    void setSaveFilename(const QString &filename);

    QString saveFormat() const;
    void setSaveFormat(const QString &format);

    QString savePath(const QString &format = QString()) const;

    // Painter

    QPen pen() const;

    QColor penColor() const;
    void setPenColor(const QColor &color);

    int penSize() const;
    void setPenSize(int size);

    QPen marker() const;

    QColor markerColor() const;
    void setMarkerColor(const QColor &color);

    int markerSize() const;
    void setMarkerSize(int size);

    QPen rect() const;

    QColor rectColor() const;
    void setRectColor(const QColor &color);

    int rectSize() const;
    void setRectSize(int size);

    bool rectFill() const;
    void setRectFill(bool fill);

    QPen ellipse() const;

    QColor ellipseColor() const;
    void setEllipseColor(const QColor &color);

    int ellipseSize() const;
    void setEllipseSize(int size);

    bool ellipseFill() const;
    void setEllipseFill(bool fill);

    QPen line() const;

    QColor lineColor() const;
    void setLineColor(const QColor &color);

    int lineSize() const;
    void setLineSize(int size);

    bool lineFill() const;
    void setLineFill(bool fill);

    QPen arrow() const;

    QColor arrowColor() const;
    void setArrowColor(const QColor &color);

    int arrowSize() const;
    void setArrowSize(int size);

    bool arrowFill() const;
    void setArrowFill(bool fill);

    QPen text() const;

    QColor textColor() const;
    void setTextColor(const QColor &color);

    int textSize() const;
    void setTextSize(int size);

    bool textBold() const;
    void setTextBold(bool bold);

    bool textItalic() const;
    void setTextItalic(bool italic);

    bool textUnderline() const;
    void setTextUnderline(bool underline);

    QFont textFont() const;
    void setTextFont(const QFont &font);

    QPen number() const;

    QColor numberColor() const;
    void setNumberColor(const QColor &color);

    int numberSize() const;
    void setNumberSize(int size);

    QFont numberFont() const;
    void setNumberFont(const QFont &font);

    int eraseSize() const;
    void setEraseSize(int size);

    bool itemShadowEnabled() const;
    void setItemShadowEnabled(bool enabled);

    bool smoothPathEnabled() const;
    void setSmoothPathEnabled(bool enabled);

    int smoothFactor() const;
    void setSmoothFactor(int factor);

    // Image Grabber

    bool captureCursor() const;
    void setCaptureCursor(bool enabled);

    bool cursorRulerEnabled() const;
    void setCursorRulerEnabled(bool enabled);

    bool cursorInfoEnabled() const;
    void setCursorInfoEnabled(bool enabled);

    int captureDelay() const;
    void setCaptureDelay(int delay);

    int snippingCursorSize() const;
    void setSnippingCursorSize(int size);

    QColor snippingCursorColor() const;
    void setSnippingCursorColor(const QColor &color);

    // Imgur Uploader

    QString imgurUsername() const;
    void setImgurUsername(const QString &username);

    QByteArray imgurClientId() const;
    void setImgurClientId(const QString &clientId);

    QByteArray imgurClientSecret() const;
    void setImgurClientSecret(const QString &clientSecret);

    QByteArray imgurAccessToken() const;
    void setImgurAccessToken(const QString &accessToken);

    QByteArray imgurRefreshToken() const;
    void setImgurRefreshToken(const QString &refreshToken);

    bool imgurForceAnonymous() const;
    void setImgurForceAnonymous(bool enabled);

    bool imgurOpenLinkDirectlyToImage() const;
    void setImgurOpenLinkDirectlyToImage(bool enabled);

    bool imgurAlwaysCopyToClipboard() const;
    void setImgurAlwaysCopyToClipboard(bool enabled);

signals:
    void painterUpdated() const;

private:
    QSettings mConfig;
};

#endif // KSNIPCONFIG_H
