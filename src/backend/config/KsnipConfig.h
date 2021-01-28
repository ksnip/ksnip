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

#ifndef KSNIP_KSNIPCONFIG_H
#define KSNIP_KSNIPCONFIG_H

#include <QObject>
#include <QPoint>
#include <QPen>
#include <QFont>
#include <QKeySequence>
#include <QSettings>

#include "KsnipConfigOptions.h"
#include "src/common/enum/CaptureModes.h"
#include "src/common/enum/SaveQualityMode.h"
#include "src/common/enum/UploaderType.h"
#include "src/common/enum/TrayIconDefaultActionMode.h"
#include "src/common/helper/PathHelper.h"
#include "src/common/constants/DefaultValues.h"
#include "src/common/provider/DirectoryPathProvider.h"


class KsnipConfig : public QObject
{
    Q_OBJECT
public:
	KsnipConfig() = default;

    // Application

	virtual bool rememberPosition() const;
	virtual void setRememberPosition(bool enabled);

	virtual bool promptSaveBeforeExit() const;
	virtual void setPromptSaveBeforeExit(bool enabled);

	virtual bool autoCopyToClipboardNewCaptures() const;
	virtual void setAutoCopyToClipboardNewCaptures(bool enabled);

	virtual bool autoSaveNewCaptures() const;
	virtual void setAutoSaveNewCaptures(bool enabled);

	virtual bool autoHideDocks() const;
	virtual void setAutoHideDocks(bool enabled);

	virtual bool useTabs() const;
	virtual void setUseTabs(bool enabled);

	virtual bool autoHideTabs() const;
	virtual void setAutoHideTabs(bool enabled);

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

	virtual QString applicationStyle() const;
	virtual void setApplicationStyle(const QString &style);

	virtual TrayIconDefaultActionMode defaultTrayIconActionMode() const;
	virtual void setDefaultTrayIconActionMode(TrayIconDefaultActionMode mode);

	virtual CaptureModes defaultTrayIconCaptureMode() const;
	virtual void setDefaultTrayIconCaptureMode(CaptureModes mode);

	virtual bool useTrayIcon() const;
	virtual void setUseTrayIcon(bool enabled);

	virtual bool minimizeToTray() const;
	virtual void setMinimizeToTray(bool enabled);

	virtual bool closeToTray() const;
	virtual void setCloseToTray(bool enabled);

	virtual bool trayIconNotificationsEnabled() const;
	virtual void setTrayIconNotificationsEnabled(bool enabled);

	virtual bool startMinimizedToTray() const;
	virtual void setStartMinimizedToTray(bool enabled);

	virtual bool rememberLastSaveDirectory() const;
	virtual void setRememberLastSaveDirectory(bool enabled);

	virtual bool useSingleInstance() const;
	virtual void setUseSingleInstance(bool enabled);

	virtual SaveQualityMode saveQualityMode() const;
	virtual void setSaveQualityMode(SaveQualityMode mode);

	virtual int saveQualityFactor() const;
	virtual void setSaveQualityFactor(int factor);

	// Annotator

	virtual bool rememberToolSelection() const;
	virtual void setRememberToolSelection(bool enabled);

	virtual bool switchToSelectToolAfterDrawingItem() const;
	virtual void setSwitchToSelectToolAfterDrawingItem(bool enabled);

	virtual bool numberToolSeedChangeUpdatesAllItems() const;
	virtual void setNumberToolSeedChangeUpdatesAllItems(bool enabled);

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

	virtual QStringList stickerPaths() const;
	virtual void setStickerPaths(const QStringList &paths);

	virtual bool useDefaultSticker() const;
	virtual void setUseDefaultSticker(bool enabled);

	virtual QColor canvasColor() const;
	virtual void setCanvasColor(const QColor &color);

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

	virtual bool showMainWindowAfterTakingScreenshotEnabled() const;
	virtual void setShowMainWindowAfterTakingScreenshotEnabled(bool enabled);

	virtual bool isSnippingAreaMagnifyingGlassEnabledReadOnly() const;
	virtual bool snippingAreaMagnifyingGlassEnabled() const;
	virtual void setSnippingAreaMagnifyingGlassEnabled(bool enabled);

	virtual int captureDelay() const;
	virtual void setCaptureDelay(int delay);

	virtual int snippingCursorSize() const;
	virtual void setSnippingCursorSize(int size);

	virtual QColor snippingCursorColor() const;
	virtual void setSnippingCursorColor(const QColor &color);

	virtual QColor snippingAdornerColor() const;
	virtual void setSnippingAdornerColor(const QColor &color);

	virtual int snippingAreaTransparency() const;
	virtual void setSnippingAreaTransparency(int transparency);

	virtual QRect lastRectArea() const;
	virtual void setLastRectArea(const QRect &rectArea);

	virtual bool isForceGenericWaylandEnabledReadOnly() const;
	virtual bool forceGenericWaylandEnabled() const;
	virtual void setForceGenericWaylandEnabled(bool enabled);

    virtual bool isScaleGenericWaylandScreenshotEnabledReadOnly() const;
    virtual bool scaleGenericWaylandScreenshotsEnabled() const;
    virtual void setScaleGenericWaylandScreenshots(bool enabled);

	virtual bool hideMainWindowDuringScreenshot() const;
	virtual void setHideMainWindowDuringScreenshot(bool enabled);

	virtual bool allowResizingRectSelection() const;
	virtual void setAllowResizingRectSelection(bool enabled);

	virtual bool showSnippingAreaInfoText() const;
	virtual void setShowSnippingAreaInfoText(bool enabled);

	// Uploader

	virtual bool confirmBeforeUpload() const;
	virtual void setConfirmBeforeUpload(bool enabled);

	virtual UploaderType uploaderType() const;
	virtual void setUploaderType(UploaderType type);

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

	virtual bool imgurOpenLinkInBrowser() const;
	virtual void setImgurOpenLinkInBrowser(bool enabled);

	virtual QString imgurBaseUrl() const;
	virtual void setImgurBaseUrl(const QString &baseUrl);

	// Script Uploader

	virtual QString uploadScriptPath() const;
	virtual void setUploadScriptPath(const QString &path);

	virtual bool uploadScriptCopyOutputToClipboard() const;
	virtual void setUploadScriptCopyOutputToClipboard(bool enabled);

	virtual QString uploadScriptCopyOutputFilter() const;
	virtual void setUploadScriptCopyOutputFilter(const QString &regex);

	virtual bool uploadScriptStopOnStdErr() const;
	virtual void setUploadScriptStopOnStdErr(bool enabled);

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

    virtual QKeySequence portalHotKey() const;
    virtual void setPortalHotKey(const QKeySequence &keySequence);

signals:
	void annotatorConfigChanged() const;
	void hotKeysChanged() const;

private:
    QSettings mConfig;

	void saveValue(const QString &key, const QVariant &value);
	QVariant loadValue(const QString &key, const QVariant &defaultValue = QVariant()) const;
};

#endif // KSNIP_KSNIPCONFIG_H
