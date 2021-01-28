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

#include "KsnipConfigOptions.h"

QString KsnipConfigOptions::rememberPositionString()
{
	return applicationSectionString() + QLatin1String("SavePosition");
}

QString KsnipConfigOptions::promptSaveBeforeExitString()
{
	return applicationSectionString() + QLatin1String("PromptSaveBeforeExit");
}

QString KsnipConfigOptions::autoCopyToClipboardNewCapturesString()
{
	return applicationSectionString() + QLatin1String("AutoCopyToClipboardNewCaptures");
}

QString KsnipConfigOptions::autoSaveNewCapturesString()
{
	return applicationSectionString() + QLatin1String("AutoSaveNewCaptures");
}

QString KsnipConfigOptions::rememberToolSelectionString()
{
	return annotatorSectionString() + QLatin1String("SaveToolsSelection");
}

QString KsnipConfigOptions::switchToSelectToolAfterDrawingItemString()
{
	return annotatorSectionString() + QLatin1String("SwitchToSelectToolAfterDrawingItem");
}

QString KsnipConfigOptions::numberToolSeedChangeUpdatesAllItemsString()
{
	return annotatorSectionString() + QLatin1String("NumberToolSeedChangeUpdatesAllItems");
}

QString KsnipConfigOptions::useTabsString()
{
	return applicationSectionString() + QLatin1String("UseTabs");
}

QString KsnipConfigOptions::autoHideTabsString()
{
	return applicationSectionString() + QLatin1String("AutoHideTabs");
}

QString KsnipConfigOptions::captureOnStartupString()
{
	return applicationSectionString() + QLatin1String("CaptureOnStartup");
}

QString KsnipConfigOptions::autoHideDocksString()
{
	return applicationSectionString() + QLatin1String("AutoHideDocks");
}

QString KsnipConfigOptions::freezeImageWhileSnippingEnabledString()
{
	return imageGrabberSectionString() + QLatin1String("FreezeImageWhileSnippingEnabled");
}

QString KsnipConfigOptions::positionString()
{
	return mainWindowSectionString() + QLatin1String("Position");
}

QString KsnipConfigOptions::captureModeString()
{
	return imageGrabberSectionString() + QLatin1String("CaptureMode");
}

QString KsnipConfigOptions::saveQualityModeString()
{
	return saveSectionString() + QLatin1String("SaveQualityMode");
}

QString KsnipConfigOptions::saveQualityFactorString()
{
	return saveSectionString() + QLatin1String("SaveQualityFactor");
}

QString KsnipConfigOptions::saveDirectoryString()
{
	return applicationSectionString() + QLatin1String("SaveDirectory");
}

QString KsnipConfigOptions::saveFilenameString()
{
	return applicationSectionString() + QLatin1String("SaveFilename");
}

QString KsnipConfigOptions::saveFormatString()
{
	return applicationSectionString() + QLatin1String("SaveFormat");
}

QString KsnipConfigOptions::applicationStyleString()
{
	return applicationSectionString() + QLatin1String("ApplicationStyle");
}

QString KsnipConfigOptions::trayIconDefaultActionModeString()
{
	return applicationSectionString() + QLatin1String("TrayIconDefaultActionMode");
}

QString KsnipConfigOptions::trayIconDefaultCaptureModeString()
{
	return applicationSectionString() + QLatin1String("TrayIconDefaultCaptureMode");
}

QString KsnipConfigOptions::useTrayIconString()
{
	return applicationSectionString() + QLatin1String("UseTrayIcon");
}

QString KsnipConfigOptions::minimizeToTrayString()
{
	return applicationSectionString() + QLatin1String("MinimizeToTray");
}

QString KsnipConfigOptions::closeToTrayString()
{
	return applicationSectionString() + QLatin1String("CloseToTray");
}

QString KsnipConfigOptions::trayIconNotificationsEnabledString()
{
	return applicationSectionString() + QLatin1String("TrayIconNotificationsEnabled");
}

QString KsnipConfigOptions::startMinimizedToTrayString()
{
	return applicationSectionString() + QLatin1String("StartMinimizedToTray");
}

QString KsnipConfigOptions::rememberLastSaveDirectoryString()
{
	return applicationSectionString() + QLatin1String("RememberLastSaveDirectory");
}

QString KsnipConfigOptions::useSingleInstanceString()
{
	return applicationSectionString() + QLatin1String("UseSingleInstanceString");
}

QString KsnipConfigOptions::hideMainWindowDuringScreenshotString()
{
	return applicationSectionString() + QLatin1String("HideMainWindowDuringScreenshot");
}

QString KsnipConfigOptions::allowResizingRectSelectionString()
{
	return applicationSectionString() + QLatin1String("AllowResizingRectSelection");
}

QString KsnipConfigOptions::showSnippingAreaInfoTextString()
{
	return applicationSectionString() + QLatin1String("ShowSnippingAreaInfoText");
}

QString KsnipConfigOptions::textFontString()
{
	return annotatorSectionString() + QLatin1String("TextFont");
}

QString KsnipConfigOptions::numberFontString()
{
	return annotatorSectionString() + QLatin1String("NumberFont");
}

QString KsnipConfigOptions::itemShadowEnabledString()
{
	return annotatorSectionString() + QLatin1String("ItemShadowEnabled");
}

QString KsnipConfigOptions::smoothPathEnabledString()
{
	return annotatorSectionString() + QLatin1String("SmoothPathEnabled");
}

QString KsnipConfigOptions::smoothPathFactorString()
{
	return annotatorSectionString() + QLatin1String("SmoothPathFactor");
}

QString KsnipConfigOptions::rotateWatermarkEnabledString()
{
	return annotatorSectionString() + QLatin1String("RotateWatermark");
}

QString KsnipConfigOptions::stickerPathsString()
{
	return annotatorSectionString() + QLatin1String("StickerPaths");
}

QString KsnipConfigOptions::useDefaultStickerString()
{
	return annotatorSectionString() + QLatin1String("UseDefaultSticker");
}

QString KsnipConfigOptions::captureCursorString()
{
	return imageGrabberSectionString() + QLatin1String("CaptureCursor");
}

QString KsnipConfigOptions::snippingAreaRulersEnabledString()
{
	return imageGrabberSectionString() + QLatin1String("SnippingAreaRulersEnabled");
}

QString KsnipConfigOptions::snippingAreaPositionAndSizeInfoEnabledString()
{
	return imageGrabberSectionString() + QLatin1String("SnippingAreaPositionAndSizeInfoEnabled");
}

QString KsnipConfigOptions::snippingAreaMagnifyingGlassEnabledString()
{
	return imageGrabberSectionString() + QLatin1String("SnippingAreaMagnifyingGlassEnabled");
}

QString KsnipConfigOptions::showMainWindowAfterTakingScreenshotEnabledString()
{
	return imageGrabberSectionString() + QLatin1String("ShowMainWindowAfterTakingScreenshotEnabled");
}

QString KsnipConfigOptions::captureDelayString()
{
	return imageGrabberSectionString() + QLatin1String("CaptureDelay");
}

QString KsnipConfigOptions::snippingCursorSizeString()
{
	return imageGrabberSectionString() + QLatin1String("SnippingCursorSize");
}

QString KsnipConfigOptions::snippingCursorColorString()
{
	return imageGrabberSectionString() + QLatin1String("SnippingCursorColor");
}

QString KsnipConfigOptions::snippingAdornerColorString()
{
	return imageGrabberSectionString() + QLatin1String("SnippingAdornerColor");
}

QString KsnipConfigOptions::snippingAreaTransparencyString()
{
	return imageGrabberSectionString() + QLatin1String("SnippingAreaTransparency");
}

QString KsnipConfigOptions::lastRectAreaString()
{
	return imageGrabberSectionString() + QLatin1String("LastRectArea");
}

QString KsnipConfigOptions::forceGenericWaylandEnabledString()
{
    return imageGrabberSectionString() + QLatin1String("ForceGenericWaylandEnabled");
}

QString KsnipConfigOptions::scaleWaylandScreenshotsEnabledString()
{
    return imageGrabberSectionString() + QLatin1String("ScaleGenericWaylandScreenshotsEnabledString");
}

QString KsnipConfigOptions::imgurUsernameString()
{
	return imgurSectionString() + QLatin1String("Username");
}

QString KsnipConfigOptions::imgurClientIdString()
{
	return imgurSectionString() + QLatin1String("ClientId");
}

QString KsnipConfigOptions::imgurClientSecretString()
{
	return imgurSectionString() + QLatin1String("ClientSecret");
}

QString KsnipConfigOptions::imgurAccessTokenString()
{
	return imgurSectionString() + QLatin1String("AccessToken");
}

QString KsnipConfigOptions::imgurRefreshTokenString()
{
	return imgurSectionString() + QLatin1String("RefreshToken");
}

QString KsnipConfigOptions::imgurForceAnonymousString()
{
	return imgurSectionString() + QLatin1String("ForceAnonymous");
}

QString KsnipConfigOptions::imgurLinkDirectlyToImageString()
{
	return imgurSectionString() + QLatin1String("OpenLinkDirectlyToImage");
}

QString KsnipConfigOptions::imgurOpenLinkInBrowserString()
{
	return imgurSectionString() + QLatin1String("OpenLinkInBrowser");
}

QString KsnipConfigOptions::imgurAlwaysCopyToClipboardString()
{
	return imgurSectionString() + QLatin1String("AlwaysCopyToClipboard");
}

QString KsnipConfigOptions::imgurBaseUrlString()
{
	return imgurSectionString() + QLatin1String("BaseUrl");
}

QString KsnipConfigOptions::uploadScriptPathString()
{
	return uploadScriptSectionString() + QLatin1String("UploadScriptPath");
}

QString KsnipConfigOptions::confirmBeforeUploadString()
{
	return uploaderSectionString() + QLatin1String("ConfirmBeforeUpload");
}

QString KsnipConfigOptions::uploaderTypeString()
{
	return uploaderSectionString() + QLatin1String("UploaderType");
}

QString KsnipConfigOptions::canvasColorString()
{
	return annotatorSectionString() + QLatin1String("CanvasColor");
}

QString KsnipConfigOptions::uploadScriptCopyOutputToClipboardString()
{
	return uploadScriptSectionString() + QLatin1String("CopyOutputToClipboard");
}

QString KsnipConfigOptions::uploadScriptStopOnStdErrString()
{
	return uploadScriptSectionString() + QLatin1String("UploadScriptStoOnStdErr");
}

QString KsnipConfigOptions::uploadScriptCopyOutputFilterString()
{
	return uploadScriptSectionString() + QLatin1String("CopyOutputFilter");
}

QString KsnipConfigOptions::globalHotKeysEnabledString()
{
	return hotKeysSectionString() + QLatin1String("GlobalHotKeysEnabled");
}

QString KsnipConfigOptions::rectAreaHotKeyString()
{
	return hotKeysSectionString() + QLatin1String("RectAreaHotKey");
}

QString KsnipConfigOptions::lastRectAreaHotKeyString()
{
	return hotKeysSectionString() + QLatin1String("LastRectAreaHotKey");
}

QString KsnipConfigOptions::fullScreenHotKeyString()
{
	return hotKeysSectionString() + QLatin1String("FullScreenHotKey");
}

QString KsnipConfigOptions::currentScreenHotKeyString()
{
	return hotKeysSectionString() + QLatin1String("CurrentScreenHotKey");
}

QString KsnipConfigOptions::activeWindowHotKeyString()
{
	return hotKeysSectionString() + QLatin1String("ActiveWindowHotKey");
}

QString KsnipConfigOptions::windowUnderCursorHotKeyString()
{
	return hotKeysSectionString() + QLatin1String("WindowUnderCursorHotKey");
}

QString KsnipConfigOptions::portalHotKeyString()
{
    return hotKeysSectionString() + QLatin1String("PortalHotKey");
}

QString KsnipConfigOptions::applicationSectionString()
{
	return QLatin1String("Application/");;
}

QString KsnipConfigOptions::imageGrabberSectionString()
{
	return QLatin1String("ImageGrabber/");
}

QString KsnipConfigOptions::annotatorSectionString()
{
	return QLatin1String("Painter/");
}

QString KsnipConfigOptions::uploaderSectionString()
{
	return QLatin1String("Uploader/");
}

QString KsnipConfigOptions::imgurSectionString()
{
	return QLatin1String("Imgur/");
}

QString KsnipConfigOptions::uploadScriptSectionString()
{
	return QLatin1String("UploadScript/");
}

QString KsnipConfigOptions::hotKeysSectionString()
{
	return QLatin1String("HotKeys/");
}

QString KsnipConfigOptions::mainWindowSectionString()
{
	return QLatin1String("MainWindow/");
}

QString KsnipConfigOptions::saveSectionString()
{
	return QLatin1String("Save/");
}
