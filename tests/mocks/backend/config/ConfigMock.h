/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_CONFIGMOCK_H
#define KSNIP_CONFIGMOCK_H

#include <gmock/gmock.h>

#include "src/backend/config/IConfig.h"
#include "src/gui/actions/Action.h"
#include "src/plugins/PluginInfo.h"

class ConfigMock : public IConfig
{
public:
	MOCK_METHOD(bool, rememberPosition, (), (const, override));
	MOCK_METHOD(void, setRememberPosition, (bool enabled), (override));

	MOCK_METHOD(bool, promptSaveBeforeExit, (), (const, override));
	MOCK_METHOD(void, setPromptSaveBeforeExit, (bool enabled), (override));

	MOCK_METHOD(bool, autoCopyToClipboardNewCaptures, (), (const, override));
	MOCK_METHOD(void, setAutoCopyToClipboardNewCaptures, (bool enabled), (override));

	MOCK_METHOD(bool, autoSaveNewCaptures, (), (const, override));
	MOCK_METHOD(void, setAutoSaveNewCaptures, (bool enabled), (override));

	MOCK_METHOD(bool, autoHideDocks, (), (const, override));
	MOCK_METHOD(void, setAutoHideDocks, (bool enabled), (override));

	MOCK_METHOD(bool, autoResizeToContent, (), (const, override));
	MOCK_METHOD(void, setAutoResizeToContent, (bool enabled), (override));

	MOCK_METHOD(int, resizeToContentDelay, (), (const, override));
	MOCK_METHOD(void, setResizeToContentDelay, (int ms), (override));

	MOCK_METHOD(bool, overwriteFile, (), (const, override));
	MOCK_METHOD(void, setOverwriteFile, (bool enabled), (override));

	MOCK_METHOD(bool, useTabs, (), (const, override));
	MOCK_METHOD(void, setUseTabs, (bool enabled), (override));

	MOCK_METHOD(bool, autoHideTabs, (), (const, override));
	MOCK_METHOD(void, setAutoHideTabs, (bool enabled), (override));

	MOCK_METHOD(bool, captureOnStartup, (), (const, override));
	MOCK_METHOD(void, setCaptureOnStartup, (bool enabled), (override));

	MOCK_METHOD(QPoint, windowPosition, (), (const, override));
	MOCK_METHOD(void, setWindowPosition, (const QPoint &position), (override));

	MOCK_METHOD(CaptureModes, captureMode, (), (const, override));
	MOCK_METHOD(void, setCaptureMode, (CaptureModes mode), (override));

	MOCK_METHOD(QString, saveDirectory, (), (const, override));
	MOCK_METHOD(void, setSaveDirectory, (const QString &path), (override));

	MOCK_METHOD(QString, saveFilename, (), (const, override));
	MOCK_METHOD(void, setSaveFilename, (const QString &filename), (override));

	MOCK_METHOD(QString, saveFormat, (), (const, override));
	MOCK_METHOD(void, setSaveFormat, (const QString &format), (override));

	MOCK_METHOD(QString, applicationStyle, (), (const, override));
	MOCK_METHOD(void, setApplicationStyle, (const QString &style), (override));

	MOCK_METHOD(TrayIconDefaultActionMode, defaultTrayIconActionMode, (), (const, override));
	MOCK_METHOD(void, setDefaultTrayIconActionMode, (TrayIconDefaultActionMode mode), (override));

	MOCK_METHOD(CaptureModes, defaultTrayIconCaptureMode, (), (const, override));
	MOCK_METHOD(void, setDefaultTrayIconCaptureMode, (CaptureModes mode), (override));

	MOCK_METHOD(bool, useTrayIcon, (), (const, override));
	MOCK_METHOD(void, setUseTrayIcon, (bool enabled), (override));

	MOCK_METHOD(bool, minimizeToTray, (), (const, override));
	MOCK_METHOD(void, setMinimizeToTray, (bool enabled), (override));

	MOCK_METHOD(bool, closeToTray, (), (const, override));
	MOCK_METHOD(void, setCloseToTray, (bool enabled), (override));

	MOCK_METHOD(bool, trayIconNotificationsEnabled, (), (const, override));
	MOCK_METHOD(void, setTrayIconNotificationsEnabled, (bool enabled), (override));

	MOCK_METHOD(bool, platformSpecificNotificationServiceEnabled, (), (const, override));
	MOCK_METHOD(void, setPlatformSpecificNotificationServiceEnabled, (bool enabled), (override));

	MOCK_METHOD(bool, startMinimizedToTray, (), (const, override));
	MOCK_METHOD(void, setStartMinimizedToTray, (bool enabled), (override));

	MOCK_METHOD(bool, rememberLastSaveDirectory, (), (const, override));
	MOCK_METHOD(void, setRememberLastSaveDirectory, (bool enabled), (override));

	MOCK_METHOD(bool, useSingleInstance, (), (const, override));
	MOCK_METHOD(void, setUseSingleInstance, (bool enabled), (override));

	MOCK_METHOD(SaveQualityMode, saveQualityMode, (), (const, override));
	MOCK_METHOD(void, setSaveQualityMode, (SaveQualityMode mode), (override));

	MOCK_METHOD(int, saveQualityFactor, (), (const, override));
	MOCK_METHOD(void, setSaveQualityFactor, (int factor), (override));

	MOCK_METHOD(bool, isDebugEnabled, (), (const, override));
	MOCK_METHOD(void, setIsDebugEnabled, (bool enabled), (override));

	// Annotator

	MOCK_METHOD(bool, rememberToolSelection, (), (const, override));
	MOCK_METHOD(void, setRememberToolSelection, (bool enabled), (override));

	MOCK_METHOD(bool, switchToSelectToolAfterDrawingItem, (), (const, override));
	MOCK_METHOD(void, setSwitchToSelectToolAfterDrawingItem, (bool enabled), (override));

	MOCK_METHOD(bool, selectItemAfterDrawing, (), (const, override));
	MOCK_METHOD(void, setSelectItemAfterDrawing, (bool enabled), (override));

	MOCK_METHOD(bool, numberToolSeedChangeUpdatesAllItems, (), (const, override));
	MOCK_METHOD(void, setNumberToolSeedChangeUpdatesAllItems, (bool enabled), (override));

	MOCK_METHOD(bool, smoothPathEnabled, (), (const, override));
	MOCK_METHOD(void, setSmoothPathEnabled, (bool enabled), (override));

	MOCK_METHOD(int, smoothFactor, (), (const, override));
	MOCK_METHOD(void, setSmoothFactor, (int factor), (override));

	MOCK_METHOD(bool, rotateWatermarkEnabled, (), (const, override));
	MOCK_METHOD(void, setRotateWatermarkEnabled, (bool enabled), (override));

	MOCK_METHOD(QStringList, stickerPaths, (), (const, override));
	MOCK_METHOD(void, setStickerPaths, (const QStringList &paths), (override));

	MOCK_METHOD(bool, useDefaultSticker, (), (const, override));
	MOCK_METHOD(void, setUseDefaultSticker, (bool enabled), (override));

	MOCK_METHOD(QColor, canvasColor, (), (const, override));
	MOCK_METHOD(void, setCanvasColor, (const QColor &color), (override));

	MOCK_METHOD(bool, isControlsWidgetVisible, (), (const, override));
	MOCK_METHOD(void, setIsControlsWidgetVisible, (bool isVisible), (override));

	// Image Grabber

	MOCK_METHOD(bool, isFreezeImageWhileSnippingEnabledReadOnly, (), (const, override));
	MOCK_METHOD(bool, freezeImageWhileSnippingEnabled, (), (const, override));
	MOCK_METHOD(void, setFreezeImageWhileSnippingEnabled, (bool enabled), (override));

	MOCK_METHOD(bool, captureCursor, (), (const, override));
	MOCK_METHOD(void, setCaptureCursor, (bool enabled), (override));

	MOCK_METHOD(bool, snippingAreaRulersEnabled, (), (const, override));
	MOCK_METHOD(void, setSnippingAreaRulersEnabled, (bool enabled), (override));

	MOCK_METHOD(bool, snippingAreaPositionAndSizeInfoEnabled, (), (const, override));
	MOCK_METHOD(void, setSnippingAreaPositionAndSizeInfoEnabled, (bool enabled), (override));

	MOCK_METHOD(bool, showMainWindowAfterTakingScreenshotEnabled, (), (const, override));
	MOCK_METHOD(void, setShowMainWindowAfterTakingScreenshotEnabled, (bool enabled), (override));

	MOCK_METHOD(bool, isSnippingAreaMagnifyingGlassEnabledReadOnly, (), (const, override));
	MOCK_METHOD(bool, snippingAreaMagnifyingGlassEnabled, (), (const, override));
	MOCK_METHOD(void, setSnippingAreaMagnifyingGlassEnabled, (bool enabled), (override));

	MOCK_METHOD(int, captureDelay, (), (const, override));
	MOCK_METHOD(void, setCaptureDelay, (int delay), (override));

	MOCK_METHOD(int, snippingCursorSize, (), (const, override));
	MOCK_METHOD(void, setSnippingCursorSize, (int size), (override));

	MOCK_METHOD(QColor, snippingCursorColor, (), (const, override));
	MOCK_METHOD(void, setSnippingCursorColor, (const QColor &color), (override));

	MOCK_METHOD(QColor, snippingAdornerColor, (), (const, override));
	MOCK_METHOD(void, setSnippingAdornerColor, (const QColor &color), (override));

	MOCK_METHOD(int, snippingAreaTransparency, (), (const, override));
	MOCK_METHOD(void, setSnippingAreaTransparency, (int transparency), (override));

	MOCK_METHOD(QRect, lastRectArea, (), (const, override));
	MOCK_METHOD(void, setLastRectArea, (const QRect &rectArea), (override));

	MOCK_METHOD(bool, isForceGenericWaylandEnabledReadOnly, (), (const, override));
	MOCK_METHOD(bool, forceGenericWaylandEnabled, (), (const, override));
	MOCK_METHOD(void, setForceGenericWaylandEnabled, (bool enabled), (override));

	MOCK_METHOD(bool, isScaleGenericWaylandScreenshotEnabledReadOnly, (), (const, override));
	MOCK_METHOD(bool, scaleGenericWaylandScreenshotsEnabled, (), (const, override));
	MOCK_METHOD(void, setScaleGenericWaylandScreenshots, (bool enabled), (override));

	MOCK_METHOD(bool, hideMainWindowDuringScreenshot, (), (const, override));
	MOCK_METHOD(void, setHideMainWindowDuringScreenshot, (bool enabled), (override));

	MOCK_METHOD(bool, allowResizingRectSelection, (), (const, override));
	MOCK_METHOD(void, setAllowResizingRectSelection, (bool enabled), (override));

	MOCK_METHOD(bool, showSnippingAreaInfoText, (), (const, override));
	MOCK_METHOD(void, setShowSnippingAreaInfoText, (bool enabled), (override));

	MOCK_METHOD(bool, snippingAreaOffsetEnable, (), (const, override));
	MOCK_METHOD(void, setSnippingAreaOffsetEnable, (bool enabled), (override));

	MOCK_METHOD(QPointF, snippingAreaOffset, (), (const, override));
	MOCK_METHOD(void, setSnippingAreaOffset, (const QPointF &offset), (override));

	MOCK_METHOD(int, implicitCaptureDelay, (), (const, override));
	MOCK_METHOD(void, setImplicitCaptureDelay, (int delay), (override));

	// Uploader

	MOCK_METHOD(bool, confirmBeforeUpload, (), (const, override));
	MOCK_METHOD(void, setConfirmBeforeUpload, (bool enabled), (override));

	MOCK_METHOD(UploaderType, uploaderType, (), (const, override));
	MOCK_METHOD(void, setUploaderType, (UploaderType type), (override));

	// Imgur Uploader

	MOCK_METHOD(QString, imgurUsername, (), (const, override));
	MOCK_METHOD(void, setImgurUsername, (const QString &username), (override));

	MOCK_METHOD(QByteArray, imgurClientId, (), (const, override));
	MOCK_METHOD(void, setImgurClientId, (const QString &clientId), (override));

	MOCK_METHOD(QByteArray, imgurClientSecret, (), (const, override));
	MOCK_METHOD(void, setImgurClientSecret, (const QString &clientSecret), (override));

	MOCK_METHOD(QByteArray, imgurAccessToken, (), (const, override));
	MOCK_METHOD(void, setImgurAccessToken, (const QString &accessToken), (override));

	MOCK_METHOD(QByteArray, imgurRefreshToken, (), (const, override));
	MOCK_METHOD(void, setImgurRefreshToken, (const QString &refreshToken), (override));

	MOCK_METHOD(bool, imgurForceAnonymous, (), (const, override));
	MOCK_METHOD(void, setImgurForceAnonymous, (bool enabled), (override));

	MOCK_METHOD(bool, imgurLinkDirectlyToImage, (), (const, override));
	MOCK_METHOD(void, setImgurLinkDirectlyToImage, (bool enabled), (override));

	MOCK_METHOD(bool, imgurAlwaysCopyToClipboard, (), (const, override));
	MOCK_METHOD(void, setImgurAlwaysCopyToClipboard, (bool enabled), (override));

	MOCK_METHOD(bool, imgurOpenLinkInBrowser, (), (const, override));
	MOCK_METHOD(void, setImgurOpenLinkInBrowser, (bool enabled), (override));

	MOCK_METHOD(QString, imgurUploadTitle, (), (const, override));
	MOCK_METHOD(void, setImgurUploadTitle, (const QString &uploadTitle), (override));

	MOCK_METHOD(QString, imgurUploadDescription, (), (const, override));
	MOCK_METHOD(void, setImgurUploadDescription, (const QString &uploadDescription), (override));

	MOCK_METHOD(QString, imgurBaseUrl, (), (const, override));
	MOCK_METHOD(void, setImgurBaseUrl, (const QString &baseUrl), (override));

	// Script Uploader

	MOCK_METHOD(QString, uploadScriptPath, (), (const, override));
	MOCK_METHOD(void, setUploadScriptPath, (const QString &path), (override));

	MOCK_METHOD(bool, uploadScriptCopyOutputToClipboard, (), (const, override));
	MOCK_METHOD(void, setUploadScriptCopyOutputToClipboard, (bool enabled), (override));

	MOCK_METHOD(QString, uploadScriptCopyOutputFilter, (), (const, override));
	MOCK_METHOD(void, setUploadScriptCopyOutputFilter, (const QString &regex), (override));

	MOCK_METHOD(bool, uploadScriptStopOnStdErr, (), (const, override));
	MOCK_METHOD(void, setUploadScriptStopOnStdErr, (bool enabled), (override));

	// FTP Uploader

	MOCK_METHOD(bool, ftpUploadForceAnonymous, (), (const, override));
	MOCK_METHOD(void, setFtpUploadForceAnonymous, (bool enabled), (override));

	MOCK_METHOD(QString, ftpUploadUrl, (), (const, override));
	MOCK_METHOD(void, setFtpUploadUrl, (const QString &path), (override));

	MOCK_METHOD(QString, ftpUploadUsername, (), (const, override));
	MOCK_METHOD(void, setFtpUploadUsername, (const QString &username), (override));

	MOCK_METHOD(QString, ftpUploadPassword, (), (const, override));
	MOCK_METHOD(void, setFtpUploadPassword, (const QString &password), (override));

	// HotKeys

	MOCK_METHOD(bool, isGlobalHotKeysEnabledReadOnly, (), (const, override));
	MOCK_METHOD(bool, globalHotKeysEnabled, (), (const, override));
	MOCK_METHOD(void, setGlobalHotKeysEnabled, (bool enabled), (override));

	MOCK_METHOD(QKeySequence, rectAreaHotKey, (), (const, override));
	MOCK_METHOD(void, setRectAreaHotKey, (const QKeySequence &keySequence), (override));

	MOCK_METHOD(QKeySequence, lastRectAreaHotKey, (), (const, override));
	MOCK_METHOD(void, setLastRectAreaHotKey, (const QKeySequence &keySequence), (override));

	MOCK_METHOD(QKeySequence, fullScreenHotKey, (), (const, override));
	MOCK_METHOD(void, setFullScreenHotKey, (const QKeySequence &keySequence), (override));

	MOCK_METHOD(QKeySequence, currentScreenHotKey, (), (const, override));
	MOCK_METHOD(void, setCurrentScreenHotKey, (const QKeySequence &keySequence), (override));

	MOCK_METHOD(QKeySequence, activeWindowHotKey, (), (const, override));
	MOCK_METHOD(void, setActiveWindowHotKey, (const QKeySequence &keySequence), (override));

	MOCK_METHOD(QKeySequence, windowUnderCursorHotKey, (), (const, override));
	MOCK_METHOD(void, setWindowUnderCursorHotKey, (const QKeySequence &keySequence), (override));

	MOCK_METHOD(QKeySequence, portalHotKey, (), (const, override));
	MOCK_METHOD(void, setPortalHotKey, (const QKeySequence &keySequence), (override));

	// Actions

	MOCK_METHOD(QList<Action>, actions, (), (override));
	MOCK_METHOD(void, setActions, (const QList<Action> &actions), (override));

	// Plugins

	MOCK_METHOD(QString, pluginPath, (), (const, override));
	MOCK_METHOD(void, setPluginPath, (const QString &path), (override));

	MOCK_METHOD(QList<PluginInfo>, pluginInfos, (), (override));
	MOCK_METHOD(void, setPluginInfos, (const QList<PluginInfo> &pluginInfos), (override));
};

#endif //KSNIP_CONFIGMOCK_H
