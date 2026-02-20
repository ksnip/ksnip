/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software override; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation override; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY override; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program override; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef KSNIP_CONFIG_H
#define KSNIP_CONFIG_H

#include <QPoint>
#include <QPen>
#include <QFont>
#include <QKeySequence>
#include <QSettings>

#include "IConfig.h"
#include "ConfigOptions.h"
#include "src/common/helper/PathHelper.h"
#include "src/common/constants/DefaultValues.h"
#include "src/common/provider/directoryPathProvider/IDirectoryPathProvider.h"
#include "src/plugins/PluginInfo.h"
#include "src/gui/actions/Action.h"

class Config : public IConfig
{
	Q_OBJECT
public:
	explicit Config(const QSharedPointer<IDirectoryPathProvider> &directoryPathProvider);
	~Config() override = default;

	// Application

	bool rememberPosition() const override;
	void setRememberPosition(bool enabled) override;

	bool promptSaveBeforeExit() const override;
	void setPromptSaveBeforeExit(bool enabled) override;

	bool autoCopyToClipboardNewCaptures() const override;
	void setAutoCopyToClipboardNewCaptures(bool enabled) override;

	bool autoSaveNewCaptures() const override;
	void setAutoSaveNewCaptures(bool enabled) override;

	bool autoHideDocks() const override;
	void setAutoHideDocks(bool enabled) override;

	bool autoResizeToContent() const override;
	void setAutoResizeToContent(bool enabled) override;

	int resizeToContentDelay() const override;
	void setResizeToContentDelay(int ms) override;

	bool overwriteFile() const override;
	void setOverwriteFile(bool enabled) override;

	bool useTabs() const override;
	void setUseTabs(bool enabled) override;

	bool autoHideTabs() const override;
	void setAutoHideTabs(bool enabled) override;

	bool captureOnStartup() const override;
	void setCaptureOnStartup(bool enabled) override;

	QPoint windowPosition() const override;
	void setWindowPosition(const QPoint &position) override;

	CaptureModes captureMode() const override;
	void setCaptureMode(CaptureModes mode) override;

	QString saveDirectory() const override;
	void setSaveDirectory(const QString &path) override;

	QString saveFilename() const override;
	void setSaveFilename(const QString &filename) override;

	QString saveFormat() const override;
	void setSaveFormat(const QString &format) override;

	QString applicationStyle() const override;
	void setApplicationStyle(const QString &style) override;

	TrayIconDefaultActionMode defaultTrayIconActionMode() const override;
	void setDefaultTrayIconActionMode(TrayIconDefaultActionMode mode) override;

	CaptureModes defaultTrayIconCaptureMode() const override;
	void setDefaultTrayIconCaptureMode(CaptureModes mode) override;

	bool useTrayIcon() const override;
	void setUseTrayIcon(bool enabled) override;

	bool useCustomTrayIconImage() const override;
	void setCustomTrayIconImage(bool enabled) override;
	QString customTrayIconImageFile() const override;
	void setCustomTrayIconImageFile(const QString &filename) override;

	bool minimizeToTray() const override;
	void setMinimizeToTray(bool enabled) override;

	bool closeToTray() const override;
	void setCloseToTray(bool enabled) override;

	bool trayIconNotificationsEnabled() const override;
	void setTrayIconNotificationsEnabled(bool enabled) override;

	bool platformSpecificNotificationServiceEnabled() const override;
	void setPlatformSpecificNotificationServiceEnabled(bool enabled) override;

	bool startMinimizedToTray() const override;
	void setStartMinimizedToTray(bool enabled) override;

	bool rememberLastSaveDirectory() const override;
	void setRememberLastSaveDirectory(bool enabled) override;

	bool useSingleInstance() const override;
	void setUseSingleInstance(bool enabled) override;

	SaveQualityMode saveQualityMode() const override;
	void setSaveQualityMode(SaveQualityMode mode) override;

	int saveQualityFactor() const override;
	void setSaveQualityFactor(int factor) override;

	bool isDebugEnabled() const override;
	void setIsDebugEnabled(bool enabled) override;

    QString tempDirectory() const override;
    void setTempDirectory(const QString &path) override;

	// Annotator

	bool rememberToolSelection() const override;
	void setRememberToolSelection(bool enabled) override;

	bool switchToSelectToolAfterDrawingItem() const override;
	void setSwitchToSelectToolAfterDrawingItem(bool enabled) override;

	bool selectItemAfterDrawing() const override;
	void setSelectItemAfterDrawing(bool enabled) override;

	bool numberToolSeedChangeUpdatesAllItems() const override;
	void setNumberToolSeedChangeUpdatesAllItems(bool enabled) override;

	bool smoothPathEnabled() const override;
	void setSmoothPathEnabled(bool enabled) override;

	int smoothFactor() const override;
	void setSmoothFactor(int factor) override;

	bool rotateWatermarkEnabled() const override;
	void setRotateWatermarkEnabled(bool enabled) override;

	QStringList stickerPaths() const override;
	void setStickerPaths(const QStringList &paths) override;

	bool useDefaultSticker() const override;
	void setUseDefaultSticker(bool enabled) override;

	QColor canvasColor() const override;
	void setCanvasColor(const QColor &color) override;

	bool isControlsWidgetVisible() const override;
	void setIsControlsWidgetVisible(bool isVisible) override;

	// Image Grabber

	bool isFreezeImageWhileSnippingEnabledReadOnly() const override;
	bool freezeImageWhileSnippingEnabled() const override;
	void setFreezeImageWhileSnippingEnabled(bool enabled) override;

	bool captureCursor() const override;
	void setCaptureCursor(bool enabled) override;

	bool snippingAreaRulersEnabled() const override;
	void setSnippingAreaRulersEnabled(bool enabled) override;

	bool snippingAreaPositionAndSizeInfoEnabled() const override;
	void setSnippingAreaPositionAndSizeInfoEnabled(bool enabled) override;

	bool showMainWindowAfterTakingScreenshotEnabled() const override;
	void setShowMainWindowAfterTakingScreenshotEnabled(bool enabled) override;

	bool isSnippingAreaMagnifyingGlassEnabledReadOnly() const override;
	bool snippingAreaMagnifyingGlassEnabled() const override;
	void setSnippingAreaMagnifyingGlassEnabled(bool enabled) override;

	int captureDelay() const override;
	void setCaptureDelay(int delay) override;

	int snippingCursorSize() const override;
	void setSnippingCursorSize(int size) override;

	QColor snippingCursorColor() const override;
	void setSnippingCursorColor(const QColor &color) override;

	QColor snippingAdornerColor() const override;
	void setSnippingAdornerColor(const QColor &color) override;

	int snippingAreaTransparency() const override;
	void setSnippingAreaTransparency(int transparency) override;

	QRect lastRectArea() const override;
	void setLastRectArea(const QRect &rectArea) override;

	bool isForceGenericWaylandEnabledReadOnly() const override;
	bool forceGenericWaylandEnabled() const override;
	void setForceGenericWaylandEnabled(bool enabled) override;

	bool isScaleGenericWaylandScreenshotEnabledReadOnly() const override;
	bool scaleGenericWaylandScreenshotsEnabled() const override;
	void setScaleGenericWaylandScreenshots(bool enabled) override;

	bool hideMainWindowDuringScreenshot() const override;
	void setHideMainWindowDuringScreenshot(bool enabled) override;

	bool allowResizingRectSelection() const override;
	void setAllowResizingRectSelection(bool enabled) override;

	bool showSnippingAreaInfoText() const override;
	void setShowSnippingAreaInfoText(bool enabled) override;

	bool snippingAreaOffsetEnable() const override;
	void setSnippingAreaOffsetEnable(bool enabled) override;

	QPointF snippingAreaOffset() const override;
	void setSnippingAreaOffset(const QPointF &offset) override;

	int implicitCaptureDelay() const override;
	void setImplicitCaptureDelay(int delay) override;

	// Uploader

	bool confirmBeforeUpload() const override;
	void setConfirmBeforeUpload(bool enabled) override;

	UploaderType uploaderType() const override;
	void setUploaderType(UploaderType type) override;

	// Imgur Uploader

	QString imgurUsername() const override;
	void setImgurUsername(const QString &username) override;

	QByteArray imgurClientId() const override;
	void setImgurClientId(const QString &clientId) override;

	QByteArray imgurClientSecret() const override;
	void setImgurClientSecret(const QString &clientSecret) override;

	QByteArray imgurAccessToken() const override;
	void setImgurAccessToken(const QString &accessToken) override;

	QByteArray imgurRefreshToken() const override;
	void setImgurRefreshToken(const QString &refreshToken) override;

	bool imgurForceAnonymous() const override;
	void setImgurForceAnonymous(bool enabled) override;

	bool imgurLinkDirectlyToImage() const override;
	void setImgurLinkDirectlyToImage(bool enabled) override;

	bool imgurAlwaysCopyToClipboard() const override;
	void setImgurAlwaysCopyToClipboard(bool enabled) override;

	bool imgurOpenLinkInBrowser() const override;
	void setImgurOpenLinkInBrowser(bool enabled) override;

	QString imgurUploadTitle() const override;
	void setImgurUploadTitle(const QString &uploadTitle) override;

	QString imgurUploadDescription() const override;
	void setImgurUploadDescription(const QString &uploadDescription) override;

	QString imgurBaseUrl() const override;
	void setImgurBaseUrl(const QString &baseUrl) override;

	// Script Uploader

	QString uploadScriptPath() const override;
	void setUploadScriptPath(const QString &path) override;

	bool uploadScriptCopyOutputToClipboard() const override;
	void setUploadScriptCopyOutputToClipboard(bool enabled) override;

	QString uploadScriptCopyOutputFilter() const override;
	void setUploadScriptCopyOutputFilter(const QString &regex) override;

	bool uploadScriptStopOnStdErr() const override;
	void setUploadScriptStopOnStdErr(bool enabled) override;

	// FTP Uploader

	bool ftpUploadForceAnonymous() const override;
	void setFtpUploadForceAnonymous(bool enabled) override;

	QString ftpUploadUrl() const override;
	void setFtpUploadUrl(const QString &path) override;

	QString ftpUploadUsername() const override;
	void setFtpUploadUsername(const QString &username) override;

	QString ftpUploadPassword() const override;
	void setFtpUploadPassword(const QString &password) override;

	// HotKeys

	bool isGlobalHotKeysEnabledReadOnly() const override;
	bool globalHotKeysEnabled() const override;
	void setGlobalHotKeysEnabled(bool enabled) override;

	QKeySequence rectAreaHotKey() const override;
	void setRectAreaHotKey(const QKeySequence &keySequence) override;

	QKeySequence lastRectAreaHotKey() const override;
	void setLastRectAreaHotKey(const QKeySequence &keySequence) override;

	QKeySequence fullScreenHotKey() const override;
	void setFullScreenHotKey(const QKeySequence &keySequence) override;

	QKeySequence currentScreenHotKey() const override;
	void setCurrentScreenHotKey(const QKeySequence &keySequence) override;

	QKeySequence activeWindowHotKey() const override;
	void setActiveWindowHotKey(const QKeySequence &keySequence) override;

	QKeySequence windowUnderCursorHotKey() const override;
	void setWindowUnderCursorHotKey(const QKeySequence &keySequence) override;

	QKeySequence portalHotKey() const override;
	void setPortalHotKey(const QKeySequence &keySequence) override;

	// Actions

	QList<Action> actions() override;
	void setActions(const QList<Action> &actions) override;

	// Plugins

	QString pluginPath() const override;
	void setPluginPath(const QString &path) override;

	QList<PluginInfo> pluginInfos() override;
	void setPluginInfos(const QList<PluginInfo> &pluginInfos) override;

	bool customPluginSearchPathEnabled() const override;
	void setCustomPluginSearchPathEnabled(bool enabled) override;

private:
	QSettings mConfig;
	const QSharedPointer<IDirectoryPathProvider> mDirectoryPathProvider;

	void saveValue(const QString &key, const QVariant &value);
	QVariant loadValue(const QString &key, const QVariant &defaultValue = QVariant()) const;
};

#endif // KSNIP_CONFIG_H
