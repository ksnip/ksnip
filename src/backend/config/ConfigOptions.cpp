/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#include "ConfigOptions.h"

QString ConfigOptions::rememberPositionString()
{
	return applicationSectionString() + QLatin1String("SavePosition");
}

QString ConfigOptions::promptSaveBeforeExitString()
{
	return applicationSectionString() + QLatin1String("PromptSaveBeforeExit");
}

QString ConfigOptions::autoCopyToClipboardNewCapturesString()
{
	return applicationSectionString() + QLatin1String("AutoCopyToClipboardNewCaptures");
}

QString ConfigOptions::autoSaveNewCapturesString()
{
	return applicationSectionString() + QLatin1String("AutoSaveNewCaptures");
}

QString ConfigOptions::rememberToolSelectionString()
{
	return annotatorSectionString() + QLatin1String("SaveToolsSelection");
}

QString ConfigOptions::switchToSelectToolAfterDrawingItemString()
{
	return annotatorSectionString() + QLatin1String("SwitchToSelectToolAfterDrawingItem");
}

QString ConfigOptions::selectItemAfterDrawingString()
{
	return annotatorSectionString() + QLatin1String("SelectItemAfterDrawing");
}

QString ConfigOptions::numberToolSeedChangeUpdatesAllItemsString()
{
	return annotatorSectionString() + QLatin1String("NumberToolSeedChangeUpdatesAllItems");
}

QString ConfigOptions::useTabsString()
{
	return applicationSectionString() + QLatin1String("UseTabs");
}

QString ConfigOptions::autoHideTabsString()
{
	return applicationSectionString() + QLatin1String("AutoHideTabs");
}

QString ConfigOptions::captureOnStartupString()
{
	return applicationSectionString() + QLatin1String("CaptureOnStartup");
}

QString ConfigOptions::autoHideDocksString()
{
	return applicationSectionString() + QLatin1String("AutoHideDocks");
}

QString ConfigOptions::autoResizeToContentString()
{
	return applicationSectionString() + QLatin1String("AutoResizeToContent");
}

QString ConfigOptions::resizeToContentDelayString()
{
	return applicationSectionString() + QLatin1String("ResizeToContentDelay");
}

QString ConfigOptions::overwriteFileEnabledString()
{
	return applicationSectionString() + QLatin1String("OverwriteFileEnabled");
}

QString ConfigOptions::freezeImageWhileSnippingEnabledString()
{
	return imageGrabberSectionString() + QLatin1String("FreezeImageWhileSnippingEnabled");
}

QString ConfigOptions::positionString()
{
	return mainWindowSectionString() + QLatin1String("Position");
}

QString ConfigOptions::captureModeString()
{
	return imageGrabberSectionString() + QLatin1String("CaptureMode");
}

QString ConfigOptions::saveQualityModeString()
{
	return saveSectionString() + QLatin1String("SaveQualityMode");
}

QString ConfigOptions::saveQualityFactorString()
{
	return saveSectionString() + QLatin1String("SaveQualityFactor");
}

QString ConfigOptions::isDebugEnabledString()
{
	return applicationSectionString() + QLatin1String("IsDebugEnabled");
}

QString ConfigOptions::tempDirectoryString()
{
	return applicationSectionString() + QLatin1String("TempDirectory");
}

QString ConfigOptions::saveDirectoryString()
{
	return applicationSectionString() + QLatin1String("SaveDirectory");
}

QString ConfigOptions::saveFilenameString()
{
	return applicationSectionString() + QLatin1String("SaveFilename");
}

QString ConfigOptions::saveFormatString()
{
	return applicationSectionString() + QLatin1String("SaveFormat");
}

QString ConfigOptions::applicationStyleString()
{
	return applicationSectionString() + QLatin1String("ApplicationStyle");
}

QString ConfigOptions::trayIconDefaultActionModeString()
{
	return applicationSectionString() + QLatin1String("TrayIconDefaultActionMode");
}

QString ConfigOptions::trayIconDefaultCaptureModeString()
{
	return applicationSectionString() + QLatin1String("TrayIconDefaultCaptureMode");
}

QString ConfigOptions::useTrayIconString()
{
	return applicationSectionString() + QLatin1String("UseTrayIcon");
}

QString ConfigOptions::useCustomTrayIconImageString()
{
	return applicationSectionString() + QLatin1String("UseCustomTrayIconImage");
}

QString ConfigOptions::customTrayIconImageFileString()
{
	return applicationSectionString() + QLatin1String("CustomTrayIconImageFile");
}

QString ConfigOptions::minimizeToTrayString()
{
	return applicationSectionString() + QLatin1String("MinimizeToTray");
}

QString ConfigOptions::closeToTrayString()
{
	return applicationSectionString() + QLatin1String("CloseToTray");
}

QString ConfigOptions::trayIconNotificationsEnabledString()
{
	return applicationSectionString() + QLatin1String("TrayIconNotificationsEnabled");
}

QString ConfigOptions::platformSpecificNotificationServiceEnabledString()
{
	return applicationSectionString() + QLatin1String("PlatformSpecificNotificationServiceEnabled");
}

QString ConfigOptions::startMinimizedToTrayString()
{
	return applicationSectionString() + QLatin1String("StartMinimizedToTray");
}

QString ConfigOptions::rememberLastSaveDirectoryString()
{
	return applicationSectionString() + QLatin1String("RememberLastSaveDirectory");
}

QString ConfigOptions::useSingleInstanceString()
{
	return applicationSectionString() + QLatin1String("UseSingleInstanceString");
}

QString ConfigOptions::hideMainWindowDuringScreenshotString()
{
	return applicationSectionString() + QLatin1String("HideMainWindowDuringScreenshot");
}

QString ConfigOptions::allowResizingRectSelectionString()
{
	return applicationSectionString() + QLatin1String("AllowResizingRectSelection");
}

QString ConfigOptions::showSnippingAreaInfoTextString()
{
	return applicationSectionString() + QLatin1String("ShowSnippingAreaInfoText");
}

QString ConfigOptions::snippingAreaOffsetEnableString()
{
	return snippingAreaSectionString() + QLatin1String("SnippingAreaOffsetEnable");
}

QString ConfigOptions::snippingAreaOffsetString()
{
	return snippingAreaSectionString() + QLatin1String("SnippingAreaOffset");
}

QString ConfigOptions::implicitCaptureDelayString()
{
	return imageGrabberSectionString() + QLatin1String("ImplicitCaptureDelay");
}

QString ConfigOptions::smoothPathEnabledString()
{
	return annotatorSectionString() + QLatin1String("SmoothPathEnabled");
}

QString ConfigOptions::smoothPathFactorString()
{
	return annotatorSectionString() + QLatin1String("SmoothPathFactor");
}

QString ConfigOptions::rotateWatermarkEnabledString()
{
	return annotatorSectionString() + QLatin1String("RotateWatermark");
}

QString ConfigOptions::stickerPathsString()
{
	return annotatorSectionString() + QLatin1String("StickerPaths");
}

QString ConfigOptions::useDefaultStickerString()
{
	return annotatorSectionString() + QLatin1String("UseDefaultSticker");
}

QString ConfigOptions::isControlsWidgetVisibleString()
{
	return annotatorSectionString() + QLatin1String("IsControlsWidgetVisible");
}

QString ConfigOptions::captureCursorString()
{
	return imageGrabberSectionString() + QLatin1String("CaptureCursor");
}

QString ConfigOptions::snippingAreaRulersEnabledString()
{
	return imageGrabberSectionString() + QLatin1String("SnippingAreaRulersEnabled");
}

QString ConfigOptions::snippingAreaPositionAndSizeInfoEnabledString()
{
	return imageGrabberSectionString() + QLatin1String("SnippingAreaPositionAndSizeInfoEnabled");
}

QString ConfigOptions::snippingAreaMagnifyingGlassEnabledString()
{
	return imageGrabberSectionString() + QLatin1String("SnippingAreaMagnifyingGlassEnabled");
}

QString ConfigOptions::showMainWindowAfterTakingScreenshotEnabledString()
{
	return imageGrabberSectionString() + QLatin1String("ShowMainWindowAfterTakingScreenshotEnabled");
}

QString ConfigOptions::captureDelayString()
{
	return imageGrabberSectionString() + QLatin1String("CaptureDelay");
}

QString ConfigOptions::snippingCursorSizeString()
{
	return imageGrabberSectionString() + QLatin1String("SnippingCursorSize");
}

QString ConfigOptions::snippingCursorColorString()
{
	return imageGrabberSectionString() + QLatin1String("SnippingCursorColor");
}

QString ConfigOptions::snippingAdornerColorString()
{
	return imageGrabberSectionString() + QLatin1String("SnippingAdornerColor");
}

QString ConfigOptions::snippingAreaTransparencyString()
{
	return imageGrabberSectionString() + QLatin1String("SnippingAreaTransparency");
}

QString ConfigOptions::lastRectAreaString()
{
	return imageGrabberSectionString() + QLatin1String("LastRectArea");
}

QString ConfigOptions::forceGenericWaylandEnabledString()
{
	return imageGrabberSectionString() + QLatin1String("ForceGenericWaylandEnabled");
}

QString ConfigOptions::scaleWaylandScreenshotsEnabledString()
{
	return imageGrabberSectionString() + QLatin1String("ScaleGenericWaylandScreenshotsEnabledString");
}

QString ConfigOptions::imgurUsernameString()
{
	return imgurSectionString() + QLatin1String("Username");
}

QString ConfigOptions::imgurClientIdString()
{
	return imgurSectionString() + QLatin1String("ClientId");
}

QString ConfigOptions::imgurClientSecretString()
{
	return imgurSectionString() + QLatin1String("ClientSecret");
}

QString ConfigOptions::imgurAccessTokenString()
{
	return imgurSectionString() + QLatin1String("AccessToken");
}

QString ConfigOptions::imgurRefreshTokenString()
{
	return imgurSectionString() + QLatin1String("RefreshToken");
}

QString ConfigOptions::imgurForceAnonymousString()
{
	return imgurSectionString() + QLatin1String("ForceAnonymous");
}

QString ConfigOptions::imgurLinkDirectlyToImageString()
{
	return imgurSectionString() + QLatin1String("OpenLinkDirectlyToImage");
}

QString ConfigOptions::imgurOpenLinkInBrowserString()
{
	return imgurSectionString() + QLatin1String("OpenLinkInBrowser");
}

QString ConfigOptions::imgurUploadTitleString()
{
	return imgurSectionString() + QLatin1String("UploadTitle");
}

QString ConfigOptions::imgurUploadDescriptionString()
{
	return imgurSectionString() + QLatin1String("UploadDescription");
}

QString ConfigOptions::imgurAlwaysCopyToClipboardString()
{
	return imgurSectionString() + QLatin1String("AlwaysCopyToClipboard");
}

QString ConfigOptions::imgurBaseUrlString()
{
	return imgurSectionString() + QLatin1String("BaseUrl");
}

QString ConfigOptions::uploadScriptPathString()
{
	return uploadScriptSectionString() + QLatin1String("UploadScriptPath");
}

QString ConfigOptions::confirmBeforeUploadString()
{
	return uploaderSectionString() + QLatin1String("ConfirmBeforeUpload");
}

QString ConfigOptions::uploaderTypeString()
{
	return uploaderSectionString() + QLatin1String("UploaderType");
}

QString ConfigOptions::canvasColorString()
{
	return annotatorSectionString() + QLatin1String("CanvasColor");
}

QString ConfigOptions::actionsString()
{
	return QLatin1String("Actions");
}

QString ConfigOptions::actionNameString()
{
	return QLatin1String("Name");
}

QString ConfigOptions::actionShortcutString()
{
	return QLatin1String("Shortcut");
}

QString ConfigOptions::actionShortcutIsGlobalString()
{
	return QLatin1String("IsGlobalShortcutString");
}

QString ConfigOptions::actionIsCaptureEnabledString()
{
	return QLatin1String("IsCaptureEnabled");
}

QString ConfigOptions::actionIncludeCursorString()
{
	return QLatin1String("IncludeCursor");
}

QString ConfigOptions::actionCaptureDelayString()
{
	return QLatin1String("CaptureDelay");
}

QString ConfigOptions::actionCaptureModeString()
{
	return QLatin1String("CaptureMode");
}

QString ConfigOptions::actionIsPinImageEnabledString()
{
	return QLatin1String("IsPinImageEnabled");
}

QString ConfigOptions::actionIsUploadEnabledString()
{
	return QLatin1String("IsUploadEnabled");
}

QString ConfigOptions::actionIsOpenDirectoryEnabledString()
{
	return QLatin1String("IsOpenDirectoryEnabled");
}

QString ConfigOptions::actionIsCopyToClipboardEnabledString()
{
	return QLatin1String("IsCopyToClipboardEnabled");
}

QString ConfigOptions::actionIsSaveEnabledString()
{
	return QLatin1String("IsSaveEnabled");
}

QString ConfigOptions::actionIsHideMainWindowEnabledString()
{
	return QLatin1String("IsHideMainWindowEnabled");
}

QString ConfigOptions::pluginPathString()
{
	return pluginsSectionString() + QLatin1String("PluginOcrPath");
}

QString ConfigOptions::customPluginSearchPathEnabledString()
{
	return pluginsSectionString() + QLatin1String("CustomPluginSearchPathEnabled");
}

QString ConfigOptions::pluginInfosString()
{
	return pluginsSectionString() + QLatin1String("PluginInfos");
}

QString ConfigOptions::pluginInfoPathString()
{
	return pluginsSectionString() + QLatin1String("PluginInfoPath");
}

QString ConfigOptions::pluginInfoTypeString()
{
	return pluginsSectionString() + QLatin1String("PluginInfoType");
}

QString ConfigOptions::pluginInfoVersionString()
{
	return pluginsSectionString() + QLatin1String("PluginInfoVersion");
}

QString ConfigOptions::uploadScriptCopyOutputToClipboardString()
{
	return uploadScriptSectionString() + QLatin1String("CopyOutputToClipboard");
}

QString ConfigOptions::uploadScriptStopOnStdErrString()
{
	return uploadScriptSectionString() + QLatin1String("UploadScriptStoOnStdErr");
}

QString ConfigOptions::uploadScriptCopyOutputFilterString()
{
	return uploadScriptSectionString() + QLatin1String("CopyOutputFilter");
}

QString ConfigOptions::ftpUploadForceAnonymousString()
{
	return ftpUploadSectionString() + QLatin1String("ForceAnonymous");
}

QString ConfigOptions::ftpUploadUrlString()
{
	return ftpUploadSectionString() + QLatin1String("Url");
}

QString ConfigOptions::ftpUploadUsernameString()
{
	return ftpUploadSectionString() + QLatin1String("Username");
}

QString ConfigOptions::ftpUploadPasswordString()
{
	return ftpUploadSectionString() + QLatin1String("Password");
}

QString ConfigOptions::globalHotKeysEnabledString()
{
	return hotKeysSectionString() + QLatin1String("GlobalHotKeysEnabled");
}

QString ConfigOptions::rectAreaHotKeyString()
{
	return hotKeysSectionString() + QLatin1String("RectAreaHotKey");
}

QString ConfigOptions::lastRectAreaHotKeyString()
{
	return hotKeysSectionString() + QLatin1String("LastRectAreaHotKey");
}

QString ConfigOptions::fullScreenHotKeyString()
{
	return hotKeysSectionString() + QLatin1String("FullScreenHotKey");
}

QString ConfigOptions::currentScreenHotKeyString()
{
	return hotKeysSectionString() + QLatin1String("CurrentScreenHotKey");
}

QString ConfigOptions::activeWindowHotKeyString()
{
	return hotKeysSectionString() + QLatin1String("ActiveWindowHotKey");
}

QString ConfigOptions::windowUnderCursorHotKeyString()
{
	return hotKeysSectionString() + QLatin1String("WindowUnderCursorHotKey");
}

QString ConfigOptions::portalHotKeyString()
{
	return hotKeysSectionString() + QLatin1String("PortalHotKey");
}

QString ConfigOptions::applicationSectionString()
{
	return QLatin1String("Application/");
}

QString ConfigOptions::imageGrabberSectionString()
{
	return QLatin1String("ImageGrabber/");
}

QString ConfigOptions::annotatorSectionString()
{
	return QLatin1String("Painter/");
}

QString ConfigOptions::uploaderSectionString()
{
	return QLatin1String("Uploader/");
}

QString ConfigOptions::imgurSectionString()
{
	return QLatin1String("Imgur/");
}

QString ConfigOptions::uploadScriptSectionString()
{
	return QLatin1String("UploadScript/");
}

QString ConfigOptions::ftpUploadSectionString()
{
	return QLatin1String("FtpUpload/");
}

QString ConfigOptions::hotKeysSectionString()
{
	return QLatin1String("HotKeys/");
}

QString ConfigOptions::mainWindowSectionString()
{
	return QLatin1String("MainWindow/");
}

QString ConfigOptions::saveSectionString()
{
	return QLatin1String("Save/");
}

QString ConfigOptions::pluginsSectionString()
{
	return QLatin1String("Plugins/");
}

QString ConfigOptions::snippingAreaSectionString()
{
	return QLatin1String("SnippingArea/");
}
