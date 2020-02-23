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
#include <QKeySequence>
#include <QSettings>

#include "KsnipConfigOptions.h"
#include "src/common/enum/CaptureModes.h"
#include "common/helper/PathHelper.h"

class KsnipConfig : public QObject
{
    Q_OBJECT
public:
	KsnipConfig() = default;

    // Application

	virtual bool savePosition() const;
	virtual void setSavePosition(bool enabled);

	virtual bool promptSaveBeforeExit() const;
	virtual void setPromptSaveBeforeExit(bool enabled);

	virtual bool alwaysCopyToClipboard() const;
	virtual void setAlwaysCopyToClipboard(bool enabled);

	virtual bool saveToolSelection() const;
	virtual void setSaveToolSelection(bool enabled);

	virtual bool captureOnStartup() const;
	virtual void setCaptureOnStartup(bool enabled);

	virtual QPoint windowPosition() const;
	virtual void setWindowPosition(const QPoint &position);

	virtual CaptureModes captureMode() const;
	virtual void setCaptureMode(CaptureModes mode);

	virtual QString saveDirectory() const;
	virtual void setSaveDirectory(const QString &path);

	virtual QString saveFilename() const;
	virtual void setSaveFilename(const QString &filename);

	virtual QString saveFormat() const;
	virtual void setSaveFormat(const QString &format);

	virtual bool useInstantSave() const;
	virtual void setUseInstantSave(bool enabled);

	virtual QString applicationStyle() const;
	virtual void setApplicationStyle(QString style);

	virtual bool useTrayIcon() const;
	virtual void setUseTrayIcon(bool enabled);

	virtual bool minimizeToTray() const;
	virtual void setMinimizeToTray(bool enabled);

	virtual bool closeToTray() const;
	virtual void setCloseToTray(bool enabled);

	virtual bool startMinimizedToTray() const;
	virtual void setStartMinimizedToTray(bool enabled);

	// Annotator

	virtual bool textBold() const;
	virtual void setTextBold(bool bold);

	virtual bool textItalic() const;
	virtual void setTextItalic(bool italic);

	virtual bool textUnderline() const;
	virtual void setTextUnderline(bool underline);

	virtual QFont textFont() const;
	virtual void setTextFont(const QFont &font);

	virtual QFont numberFont() const;
	virtual void setNumberFont(const QFont &font);

	virtual bool itemShadowEnabled() const;
	virtual void setItemShadowEnabled(bool enabled);

	virtual bool smoothPathEnabled() const;
	virtual void setSmoothPathEnabled(bool enabled);

	virtual int smoothFactor() const;
	virtual void setSmoothFactor(int factor);

	virtual bool rotateWatermarkEnabled() const;
	virtual void setRotateWatermarkEnabled(bool enabled);

    // Image Grabber

    virtual bool isFreezeImageWhileSnippingEnabledReadOnly() const;
	virtual bool freezeImageWhileSnippingEnabled() const;
	virtual void setFreezeImageWhileSnippingEnabled(bool enabled);

	virtual bool captureCursor() const;
	virtual void setCaptureCursor(bool enabled);

	virtual bool snippingAreaRulersEnabled() const;
	virtual void setSnippingAreaRulersEnabled(bool enabled);

	virtual bool snippingAreaPositionAndSizeInfoEnabled() const;
	virtual void setSnippingAreaPositionAndSizeInfoEnabled(bool enabled);

	virtual bool isSnippingAreaMagnifyingGlassEnabledReadOnly() const;
	virtual bool snippingAreaMagnifyingGlassEnabled() const;
	virtual void setSnippingAreaMagnifyingGlassEnabled(bool enabled);

	virtual int captureDelay() const;
	virtual void setCaptureDelay(int delay);

	virtual int snippingCursorSize() const;
	virtual void setSnippingCursorSize(int size);

	virtual QColor snippingCursorColor() const;
	virtual void setSnippingCursorColor(const QColor &color);

	virtual QRect lastRectArea() const;
	virtual void setLastRectArea(const QRect &rectArea);

    // Imgur Uploader

	virtual QString imgurUsername() const;
	virtual void setImgurUsername(const QString &username);

	virtual QByteArray imgurClientId() const;
	virtual void setImgurClientId(const QString &clientId);

	virtual QByteArray imgurClientSecret() const;
	virtual void setImgurClientSecret(const QString &clientSecret);

	virtual QByteArray imgurAccessToken() const;
	virtual void setImgurAccessToken(const QString &accessToken);

	virtual QByteArray imgurRefreshToken() const;
	virtual void setImgurRefreshToken(const QString &refreshToken);

	virtual bool imgurForceAnonymous() const;
	virtual void setImgurForceAnonymous(bool enabled);

	virtual bool imgurLinkDirectlyToImage() const;
	virtual void setImgurLinkDirectlyToImage(bool enabled);

	virtual bool imgurAlwaysCopyToClipboard() const;
	virtual void setImgurAlwaysCopyToClipboard(bool enabled);

	virtual bool imgurConfirmBeforeUpload() const;
	virtual void setImgurConfirmBeforeUpload(bool enabled);

	virtual bool imgurOpenLinkInBrowser() const;
	virtual void setImgurOpenLinkInBrowser(bool enabled);

	// HotKeys

	virtual bool isGlobalHotKeysEnabledReadOnly() const;
	virtual bool globalHotKeysEnabled() const;
	virtual void setGlobalHotKeysEnabled(bool enabled);

	virtual QKeySequence rectAreaHotKey() const;
	virtual void setRectAreaHotKey(const QKeySequence &keySequence);

	virtual QKeySequence lastRectAreaHotKey() const;
	virtual void setLastRectAreaHotKey(const QKeySequence &keySequence);

	virtual QKeySequence fullScreenHotKey() const;
	virtual void setFullScreenHotKey(const QKeySequence &keySequence);

	virtual QKeySequence currentScreenHotKey() const;
	virtual void setCurrentScreenHotKey(const QKeySequence &keySequence);

	virtual QKeySequence activeWindowHotKey() const;
	virtual void setActiveWindowHotKey(const QKeySequence &keySequence);

	virtual QKeySequence windowUnderCursorHotKey() const;
	virtual void setWindowUnderCursorHotKey(const QKeySequence &keySequence);

signals:
    void painterUpdated() const;
	void toolConfigChanged() const;
	void hotKeysChanged() const;

private:
    QSettings mConfig;

	void saveValue(const QString &key, const QVariant &value);
	QVariant loadValue(const QString &key, const QVariant &defaultValue = QVariant()) const;
};

#endif // KSNIPCONFIG_H
