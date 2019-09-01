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
#include <QPen>
#include <QFont>
#include <QSettings>

#include "KsnipConfigOptions.h"
#include "src/common/enum/CaptureModes.h"
#include "common/helper/PathHelper.h"

class KsnipConfig : public QObject
{
    Q_OBJECT

public:
    static KsnipConfig *instance();

    // Application

	bool savePosition() const;
	void setSavePosition(bool enabled);

    bool promptSaveBeforeExit() const;
    void setPromptSaveBeforeExit(bool enabled);

    bool alwaysCopyToClipboard() const;
    void setAlwaysCopyToClipboard(bool enabled);

	bool saveToolSelection() const;
	void setSaveToolSelection(bool enabled);

    bool captureOnStartup() const;
    void setCaptureOnStartup(bool enabled);

    QPoint windowPosition() const;
    void setWindowPosition(const QPoint &position);

    CaptureModes captureMode() const;
    void setCaptureMode(CaptureModes mode);

    QString saveDirectory() const;
    void setSaveDirectory(const QString &path);

    QString saveFilename() const;
    void setSaveFilename(const QString &filename);

    QString saveFormat() const;
    void setSaveFormat(const QString &format);

    bool useInstantSave() const;
    void setUseInstantSave(bool enabled);

	QString applicationStyle() const;
	void setApplicationStyle(QString style);

    bool textBold() const;
    void setTextBold(bool bold);
    bool textItalic() const;
    void setTextItalic(bool italic);
    bool textUnderline() const;
    void setTextUnderline(bool underline);
    QFont textFont() const;
    void setTextFont(const QFont &font);

    QFont numberFont() const;
    void setNumberFont(const QFont &font);

    bool itemShadowEnabled() const;
    void setItemShadowEnabled(bool enabled);

    bool smoothPathEnabled() const;
    void setSmoothPathEnabled(bool enabled);

    int smoothFactor() const;
    void setSmoothFactor(int factor);

    // Image Grabber

	bool freezeImageWhileSnippingEnabled() const;
	void setFreezeImageWhileSnippingEnabled(bool enabled);

    bool captureCursor() const;
    void setCaptureCursor(bool enabled);

	bool snippingAreaRulersEnabled() const;
	void setSnippingAreaRulersEnabled(bool enabled);

	bool snippingAreaPositionAndSizeInfoEnabled() const;
	void setSnippingAreaPositionAndSizeInfoEnabled(bool enabled);

	bool snippingAreaMagnifyingGlassEnabled() const;
	void setSnippingAreaMagnifyingGlassEnabled(bool enabled);

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

    bool imgurConfirmBeforeUpload() const;
    void setImgurConfirmBeforeUpload(bool enabled);

signals:
    void painterUpdated() const;
	void toolConfigChanged() const;

private:
    QSettings mConfig;

	KsnipConfig() = default;

	void saveValue(const QString &key, const QVariant &value);
	QVariant loadValue(const QString &key, const QVariant &defaultValue = QVariant()) const;
};

#endif // KSNIPCONFIG_H
