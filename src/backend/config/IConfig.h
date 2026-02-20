/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software = 0; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation = 0; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY = 0; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program = 0; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KSNIP_ICONFIG_H
#define KSNIP_ICONFIG_H

#include <QObject>

#include "src/common/enum/TrayIconDefaultActionMode.h"
#include "src/common/enum/UploaderType.h"
#include "src/common/enum/SaveQualityMode.h"
#include "src/common/enum/CaptureModes.h"

class Action;
class PluginInfo;

class IConfig : public QObject
{
	Q_OBJECT
public:
	IConfig() = default;
	~IConfig() override = default;

	// Application

	virtual bool rememberPosition() const = 0;
	virtual void setRememberPosition(bool enabled) = 0;

	virtual bool promptSaveBeforeExit() const = 0;
	virtual void setPromptSaveBeforeExit(bool enabled) = 0;

	virtual bool autoCopyToClipboardNewCaptures() const = 0;
	virtual void setAutoCopyToClipboardNewCaptures(bool enabled) = 0;

	virtual bool autoSaveNewCaptures() const = 0;
	virtual void setAutoSaveNewCaptures(bool enabled) = 0;

	virtual bool autoHideDocks() const = 0;
	virtual void setAutoHideDocks(bool enabled) = 0;

	virtual bool autoResizeToContent() const = 0;
	virtual void setAutoResizeToContent(bool enabled) = 0;

	virtual int resizeToContentDelay() const = 0;
	virtual void setResizeToContentDelay(int ms) = 0;

	virtual bool overwriteFile() const = 0;
	virtual void setOverwriteFile(bool enabled) = 0;

	virtual bool useTabs() const = 0;
	virtual void setUseTabs(bool enabled) = 0;

	virtual bool autoHideTabs() const = 0;
	virtual void setAutoHideTabs(bool enabled) = 0;

	virtual bool captureOnStartup() const = 0;
	virtual void setCaptureOnStartup(bool enabled) = 0;

	virtual QPoint windowPosition() const = 0;
	virtual void setWindowPosition(const QPoint &position) = 0;

	virtual CaptureModes captureMode() const = 0;
	virtual void setCaptureMode(CaptureModes mode) = 0;

	virtual QString saveDirectory() const = 0;
	virtual void setSaveDirectory(const QString &path) = 0;

	virtual QString saveFilename() const = 0;
	virtual void setSaveFilename(const QString &filename) = 0;

	virtual QString saveFormat() const = 0;
	virtual void setSaveFormat(const QString &format) = 0;

	virtual QString applicationStyle() const = 0;
	virtual void setApplicationStyle(const QString &style) = 0;

	virtual TrayIconDefaultActionMode defaultTrayIconActionMode() const = 0;
	virtual void setDefaultTrayIconActionMode(TrayIconDefaultActionMode mode) = 0;

	virtual CaptureModes defaultTrayIconCaptureMode() const = 0;
	virtual void setDefaultTrayIconCaptureMode(CaptureModes mode) = 0;

	virtual bool useTrayIcon() const = 0;
	virtual void setUseTrayIcon(bool enabled) = 0;

	virtual bool useCustomTrayIconImage() const = 0;
	virtual void setCustomTrayIconImage(bool enabled) = 0;

	virtual QString customTrayIconImageFile() const = 0;
	virtual void setCustomTrayIconImageFile(const QString &filename) = 0;

	virtual bool minimizeToTray() const = 0;
	virtual void setMinimizeToTray(bool enabled) = 0;

	virtual bool closeToTray() const = 0;
	virtual void setCloseToTray(bool enabled) = 0;

	virtual bool trayIconNotificationsEnabled() const = 0;
	virtual void setTrayIconNotificationsEnabled(bool enabled) = 0;

	virtual bool platformSpecificNotificationServiceEnabled() const = 0;
	virtual void setPlatformSpecificNotificationServiceEnabled(bool enabled) = 0;

	virtual bool startMinimizedToTray() const = 0;
	virtual void setStartMinimizedToTray(bool enabled) = 0;

	virtual bool rememberLastSaveDirectory() const = 0;
	virtual void setRememberLastSaveDirectory(bool enabled) = 0;

	virtual bool useSingleInstance() const = 0;
	virtual void setUseSingleInstance(bool enabled) = 0;

	virtual SaveQualityMode saveQualityMode() const = 0;
	virtual void setSaveQualityMode(SaveQualityMode mode) = 0;

	virtual int saveQualityFactor() const = 0;
	virtual void setSaveQualityFactor(int factor) = 0;

	virtual bool isDebugEnabled() const = 0;
	virtual void setIsDebugEnabled(bool enabled) = 0;

    virtual QString tempDirectory() const = 0;
    virtual void setTempDirectory(const QString &path) = 0;

	// Annotator

	virtual bool rememberToolSelection() const = 0;
	virtual void setRememberToolSelection(bool enabled) = 0;

	virtual bool switchToSelectToolAfterDrawingItem() const = 0;
	virtual void setSwitchToSelectToolAfterDrawingItem(bool enabled) = 0;

	virtual bool selectItemAfterDrawing() const = 0;
	virtual void setSelectItemAfterDrawing(bool enabled) = 0;

	virtual bool numberToolSeedChangeUpdatesAllItems() const = 0;
	virtual void setNumberToolSeedChangeUpdatesAllItems(bool enabled) = 0;

	virtual bool smoothPathEnabled() const = 0;
	virtual void setSmoothPathEnabled(bool enabled) = 0;

	virtual int smoothFactor() const = 0;
	virtual void setSmoothFactor(int factor) = 0;

	virtual bool rotateWatermarkEnabled() const = 0;
	virtual void setRotateWatermarkEnabled(bool enabled) = 0;

	virtual QStringList stickerPaths() const = 0;
	virtual void setStickerPaths(const QStringList &paths) = 0;

	virtual bool useDefaultSticker() const = 0;
	virtual void setUseDefaultSticker(bool enabled) = 0;

	virtual QColor canvasColor() const = 0;
	virtual void setCanvasColor(const QColor &color) = 0;

	virtual bool isControlsWidgetVisible() const = 0;
	virtual void setIsControlsWidgetVisible(bool isVisible) = 0;

	// Image Grabber

	virtual bool isFreezeImageWhileSnippingEnabledReadOnly() const = 0;
	virtual bool freezeImageWhileSnippingEnabled() const = 0;
	virtual void setFreezeImageWhileSnippingEnabled(bool enabled) = 0;

	virtual bool captureCursor() const = 0;
	virtual void setCaptureCursor(bool enabled) = 0;

	virtual bool snippingAreaRulersEnabled() const = 0;
	virtual void setSnippingAreaRulersEnabled(bool enabled) = 0;

	virtual bool snippingAreaPositionAndSizeInfoEnabled() const = 0;
	virtual void setSnippingAreaPositionAndSizeInfoEnabled(bool enabled) = 0;

	virtual bool showMainWindowAfterTakingScreenshotEnabled() const = 0;
	virtual void setShowMainWindowAfterTakingScreenshotEnabled(bool enabled) = 0;

	virtual bool isSnippingAreaMagnifyingGlassEnabledReadOnly() const = 0;
	virtual bool snippingAreaMagnifyingGlassEnabled() const = 0;
	virtual void setSnippingAreaMagnifyingGlassEnabled(bool enabled) = 0;

	virtual int captureDelay() const = 0;
	virtual void setCaptureDelay(int delay) = 0;

	virtual int snippingCursorSize() const = 0;
	virtual void setSnippingCursorSize(int size) = 0;

	virtual QColor snippingCursorColor() const = 0;
	virtual void setSnippingCursorColor(const QColor &color) = 0;

	virtual QColor snippingAdornerColor() const = 0;
	virtual void setSnippingAdornerColor(const QColor &color) = 0;

	virtual int snippingAreaTransparency() const = 0;
	virtual void setSnippingAreaTransparency(int transparency) = 0;

	virtual QRect lastRectArea() const = 0;
	virtual void setLastRectArea(const QRect &rectArea) = 0;

	virtual bool isForceGenericWaylandEnabledReadOnly() const = 0;
	virtual bool forceGenericWaylandEnabled() const = 0;
	virtual void setForceGenericWaylandEnabled(bool enabled) = 0;

	virtual bool isScaleGenericWaylandScreenshotEnabledReadOnly() const = 0;
	virtual bool scaleGenericWaylandScreenshotsEnabled() const = 0;
	virtual void setScaleGenericWaylandScreenshots(bool enabled) = 0;

	virtual bool hideMainWindowDuringScreenshot() const = 0;
	virtual void setHideMainWindowDuringScreenshot(bool enabled) = 0;

	virtual bool allowResizingRectSelection() const = 0;
	virtual void setAllowResizingRectSelection(bool enabled) = 0;

	virtual bool showSnippingAreaInfoText() const = 0;
	virtual void setShowSnippingAreaInfoText(bool enabled) = 0;

	virtual bool snippingAreaOffsetEnable() const = 0;
	virtual void setSnippingAreaOffsetEnable(bool enabled) = 0;

	virtual QPointF snippingAreaOffset() const = 0;
	virtual void setSnippingAreaOffset(const QPointF &offset) = 0;

	virtual int implicitCaptureDelay() const = 0;
	virtual void setImplicitCaptureDelay(int delay) = 0;

	// Uploader

	virtual bool confirmBeforeUpload() const = 0;
	virtual void setConfirmBeforeUpload(bool enabled) = 0;

	virtual UploaderType uploaderType() const = 0;
	virtual void setUploaderType(UploaderType type) = 0;

	// Imgur Uploader

	virtual QString imgurUsername() const = 0;
	virtual void setImgurUsername(const QString &username) = 0;

	virtual QByteArray imgurClientId() const = 0;
	virtual void setImgurClientId(const QString &clientId) = 0;

	virtual QByteArray imgurClientSecret() const = 0;
	virtual void setImgurClientSecret(const QString &clientSecret) = 0;

	virtual QByteArray imgurAccessToken() const = 0;
	virtual void setImgurAccessToken(const QString &accessToken) = 0;

	virtual QByteArray imgurRefreshToken() const = 0;
	virtual void setImgurRefreshToken(const QString &refreshToken) = 0;

	virtual bool imgurForceAnonymous() const = 0;
	virtual void setImgurForceAnonymous(bool enabled) = 0;

	virtual bool imgurLinkDirectlyToImage() const = 0;
	virtual void setImgurLinkDirectlyToImage(bool enabled) = 0;

	virtual bool imgurAlwaysCopyToClipboard() const = 0;
	virtual void setImgurAlwaysCopyToClipboard(bool enabled) = 0;

	virtual bool imgurOpenLinkInBrowser() const = 0;
	virtual void setImgurOpenLinkInBrowser(bool enabled) = 0;

	virtual QString imgurUploadTitle() const = 0;
	virtual void setImgurUploadTitle(const QString &uploadTitle) = 0;

	virtual QString imgurUploadDescription() const = 0;
	virtual void setImgurUploadDescription(const QString &uploadDescription) = 0;

	virtual QString imgurBaseUrl() const = 0;
	virtual void setImgurBaseUrl(const QString &baseUrl) = 0;

	// Script Uploader

	virtual QString uploadScriptPath() const = 0;
	virtual void setUploadScriptPath(const QString &path) = 0;

	virtual bool uploadScriptCopyOutputToClipboard() const = 0;
	virtual void setUploadScriptCopyOutputToClipboard(bool enabled) = 0;

	virtual QString uploadScriptCopyOutputFilter() const = 0;
	virtual void setUploadScriptCopyOutputFilter(const QString &regex) = 0;

	virtual bool uploadScriptStopOnStdErr() const = 0;
	virtual void setUploadScriptStopOnStdErr(bool enabled) = 0;

	// FTP Uploader

	virtual bool ftpUploadForceAnonymous() const = 0;
	virtual void setFtpUploadForceAnonymous(bool enabled) = 0;

	virtual QString ftpUploadUrl() const = 0;
	virtual void setFtpUploadUrl(const QString &path) = 0;

	virtual QString ftpUploadUsername() const = 0;
	virtual void setFtpUploadUsername(const QString &username) = 0;

	virtual QString ftpUploadPassword() const = 0;
	virtual void setFtpUploadPassword(const QString &password) = 0;

	// HotKeys

	virtual bool isGlobalHotKeysEnabledReadOnly() const = 0;
	virtual bool globalHotKeysEnabled() const = 0;
	virtual void setGlobalHotKeysEnabled(bool enabled) = 0;

	virtual QKeySequence rectAreaHotKey() const = 0;
	virtual void setRectAreaHotKey(const QKeySequence &keySequence) = 0;

	virtual QKeySequence lastRectAreaHotKey() const = 0;
	virtual void setLastRectAreaHotKey(const QKeySequence &keySequence) = 0;

	virtual QKeySequence fullScreenHotKey() const = 0;
	virtual void setFullScreenHotKey(const QKeySequence &keySequence) = 0;

	virtual QKeySequence currentScreenHotKey() const = 0;
	virtual void setCurrentScreenHotKey(const QKeySequence &keySequence) = 0;

	virtual QKeySequence activeWindowHotKey() const = 0;
	virtual void setActiveWindowHotKey(const QKeySequence &keySequence) = 0;

	virtual QKeySequence windowUnderCursorHotKey() const = 0;
	virtual void setWindowUnderCursorHotKey(const QKeySequence &keySequence) = 0;

	virtual QKeySequence portalHotKey() const = 0;
	virtual void setPortalHotKey(const QKeySequence &keySequence) = 0;

	// Actions

	virtual QList<Action> actions() = 0;
	virtual void setActions(const QList<Action> &actions) = 0;

	// Plugins

	virtual QString pluginPath() const = 0;
	virtual void setPluginPath(const QString &path) = 0;

	virtual QList<PluginInfo> pluginInfos() = 0;
	virtual void setPluginInfos(const QList<PluginInfo> &pluginInfos) = 0;

	virtual bool customPluginSearchPathEnabled() const = 0;
	virtual void setCustomPluginSearchPathEnabled(bool enabled) = 0;

signals:
	void annotatorConfigChanged() const;
	void hotKeysChanged() const;
	void actionsChanged() const;
	void pluginsChanged() const;
	void snippingAreaChangedChanged() const;
	void delayChanged() const;
};

#endif //KSNIP_ICONFIG_H
