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
	return applicationSectionString() + QLatin1Literal("SavePosition");
}

QString KsnipConfigOptions::promptSaveBeforeExitString()
{
	return applicationSectionString() + QLatin1Literal("PromptSaveBeforeExit");
}

QString KsnipConfigOptions::autoCopyToClipboardNewCapturesString()
{
	return applicationSectionString() + QLatin1Literal("AutoCopyToClipboardNewCaptures");
}

QString KsnipConfigOptions::autoSaveNewCapturesString()
{
	return applicationSectionString() + QLatin1Literal("AutoSaveNewCaptures");
}

QString KsnipConfigOptions::rememberToolSelectionString()
{
	return annotatorSectionString() + QLatin1Literal("SaveToolsSelection");
}

QString KsnipConfigOptions::useTabsString()
{
	return applicationSectionString() + QLatin1Literal("UseTabs");
}

QString KsnipConfigOptions::autoHideTabsString()
{
	return applicationSectionString() + QLatin1Literal("AutoHideTabs");
}

QString KsnipConfigOptions::captureOnStartupString()
{
	return applicationSectionString() + QLatin1Literal("CaptureOnStartup");
}

QString KsnipConfigOptions::freezeImageWhileSnippingEnabledString()
{
	return imageGrabberSectionString() + QLatin1Literal("FreezeImageWhileSnippingEnabled");
}

QString KsnipConfigOptions::positionString()
{
	return mainWindowSectionString() + QLatin1Literal("Position");
}

QString KsnipConfigOptions::captureModeString()
{
	return imageGrabberSectionString() + QLatin1Literal("CaptureMode");
}

QString KsnipConfigOptions::saveQualityModeString()
{
	return saveSectionString() + QLatin1Literal("SaveQualityMode");
}

QString KsnipConfigOptions::saveQualityFactorString()
{
	return saveSectionString() + QLatin1Literal("SaveQualityFactor");
}

QString KsnipConfigOptions::saveDirectoryString()
{
	return applicationSectionString() + QLatin1Literal("SaveDirectory");
}

QString KsnipConfigOptions::saveFilenameString()
{
	return applicationSectionString() + QLatin1Literal("SaveFilename");
}

QString KsnipConfigOptions::saveFormatString()
{
	return applicationSectionString() + QLatin1Literal("SaveFormat");
}

QString KsnipConfigOptions::applicationStyleString()
{
	return applicationSectionString() + QLatin1Literal("ApplicationStyle");
}

QString KsnipConfigOptions::useTrayIconString()
{
	return applicationSectionString() + QLatin1Literal("UseTrayIcon");
}

QString KsnipConfigOptions::minimizeToTrayString()
{
	return applicationSectionString() + QLatin1Literal("MinimizeToTray");
}

QString KsnipConfigOptions::closeToTrayString()
{
	return applicationSectionString() + QLatin1Literal("CloseToTray");
}

QString KsnipConfigOptions::startMinimizedToTrayString()
{
	return applicationSectionString() + QLatin1Literal("StartMinimizedToTray");
}

QString KsnipConfigOptions::rememberLastSaveDirectoryString()
{
	return applicationSectionString() + QLatin1Literal("RememberLastSaveDirectory");
}

QString KsnipConfigOptions::useSingleInstanceString()
{
	return applicationSectionString() + QLatin1Literal("UseSingleInstanceString");
}

QString KsnipConfigOptions::hideMainWindowDuringScreenshotString()
{
	return applicationSectionString() + QLatin1Literal("HideMainWindowDuringScreenshotString");
}

QString KsnipConfigOptions::allowResizingRectCaptureString()
{
	return applicationSectionString() + QLatin1Literal("AllowResizingRectCaptureString");
}

QString KsnipConfigOptions::textFontString()
{
	return annotatorSectionString() + QLatin1Literal("TextFont");
}

QString KsnipConfigOptions::numberFontString()
{
	return annotatorSectionString() + QLatin1Literal("NumberFont");
}

QString KsnipConfigOptions::itemShadowEnabledString()
{
	return annotatorSectionString() + QLatin1Literal("ItemShadowEnabled");
}

QString KsnipConfigOptions::smoothPathEnabledString()
{
	return annotatorSectionString() + QLatin1Literal("SmoothPathEnabled");
}

QString KsnipConfigOptions::smoothPathFactorString()
{
	return annotatorSectionString() + QLatin1Literal("SmoothPathFactor");
}

QString KsnipConfigOptions::rotateWatermarkEnabledString()
{
	return annotatorSectionString() + QLatin1Literal("RotateWatermark");
}

QString KsnipConfigOptions::stickerPathsString()
{
	return annotatorSectionString() + QLatin1Literal("StickerPaths");
}

QString KsnipConfigOptions::useDefaultStickerString()
{
	return annotatorSectionString() + QLatin1Literal("UseDefaultSticker");
}

QString KsnipConfigOptions::captureCursorString()
{
	return imageGrabberSectionString() + QLatin1Literal("CaptureCursor");
}

QString KsnipConfigOptions::snippingAreaRulersEnabledString()
{
	return imageGrabberSectionString() + QLatin1Literal("SnippingAreaRulersEnabled");
}

QString KsnipConfigOptions::snippingAreaPositionAndSizeInfoEnabledString()
{
	return imageGrabberSectionString() + QLatin1Literal("SnippingAreaPositionAndSizeInfoEnabled");
}

QString KsnipConfigOptions::snippingAreaMagnifyingGlassEnabledString()
{
	return imageGrabberSectionString() + QLatin1Literal("SnippingAreaMagnifyingGlassEnabled");
}

QString KsnipConfigOptions::captureDelayString()
{
	return imageGrabberSectionString() + QLatin1Literal("CaptureDelay");
}

QString KsnipConfigOptions::snippingCursorSizeString()
{
	return imageGrabberSectionString() + QLatin1Literal("SnippingCursorSize");
}

QString KsnipConfigOptions::snippingCursorColorString()
{
	return imageGrabberSectionString() + QLatin1Literal("SnippingCursorColor");
}

QString KsnipConfigOptions::lastRectAreaString()
{
	return imageGrabberSectionString() + QLatin1Literal("LastRectArea");
}

QString KsnipConfigOptions::forceGenericWaylandEnabledString()
{
    return imageGrabberSectionString() + QLatin1Literal("ForceGenericWaylandEnabled");
}

QString KsnipConfigOptions::scaleWaylandScreenshotsEnabledString()
{
    return imageGrabberSectionString() + QLatin1Literal("ScaleGenericWaylandScreenshotsEnabledString");
}

QString KsnipConfigOptions::imgurUsernameString()
{
	return imgurSectionString() + QLatin1Literal("Username");
}

QString KsnipConfigOptions::imgurClientIdString()
{
	return imgurSectionString() + QLatin1Literal("ClientId");
}

QString KsnipConfigOptions::imgurClientSecretString()
{
	return imgurSectionString() + QLatin1Literal("ClientSecret");
}

QString KsnipConfigOptions::imgurAccessTokenString()
{
	return imgurSectionString() + QLatin1Literal("AccessToken");
}

QString KsnipConfigOptions::imgurRefreshTokenString()
{
	return imgurSectionString() + QLatin1Literal("RefreshToken");
}

QString KsnipConfigOptions::imgurForceAnonymousString()
{
	return imgurSectionString() + QLatin1Literal("ForceAnonymous");
}

QString KsnipConfigOptions::imgurLinkDirectlyToImageString()
{
	return imgurSectionString() + QLatin1Literal("OpenLinkDirectlyToImage");
}

QString KsnipConfigOptions::imgurOpenLinkInBrowserString()
{
	return imgurSectionString() + QLatin1Literal("OpenLinkInBrowser");
}

QString KsnipConfigOptions::imgurAlwaysCopyToClipboardString()
{
	return imgurSectionString() + QLatin1Literal("AlwaysCopyToClipboard");
}

QString KsnipConfigOptions::imgurBaseUrlString()
{
	return imgurSectionString() + QLatin1Literal("BaseUrl");
}

QString KsnipConfigOptions::uploadScriptPathString()
{
	return uploadScriptSectionString() + QLatin1Literal("UploadScriptPath");
}

QString KsnipConfigOptions::confirmBeforeUploadString()
{
	return uploaderSectionString() + QLatin1Literal("ConfirmBeforeUpload");
}

QString KsnipConfigOptions::uploaderTypeString()
{
	return uploaderSectionString() + QLatin1Literal("UploaderType");
}

QString KsnipConfigOptions::uploadScriptCopyOutputToClipboardString()
{
	return uploadScriptSectionString() + QLatin1Literal("CopyOutputToClipboard");
}

QString KsnipConfigOptions::uploadScriptStopOnStdErrString()
{
	return uploadScriptSectionString() + QLatin1Literal("UploadScriptStoOnStdErr");
}

QString KsnipConfigOptions::uploadScriptCopyOutputFilterString()
{
	return uploadScriptSectionString() + QLatin1Literal("CopyOutputFilter");
}

QString KsnipConfigOptions::globalHotKeysEnabledString()
{
	return hotKeysSectionString() + QLatin1Literal("GlobalHotKeysEnabled");
}

QString KsnipConfigOptions::rectAreaHotKeyString()
{
	return hotKeysSectionString() + QLatin1Literal("RectAreaHotKey");
}

QString KsnipConfigOptions::lastRectAreaHotKeyString()
{
	return hotKeysSectionString() + QLatin1Literal("LastRectAreaHotKey");
}

QString KsnipConfigOptions::fullScreenHotKeyString()
{
	return hotKeysSectionString() + QLatin1Literal("FullScreenHotKey");
}

QString KsnipConfigOptions::currentScreenHotKeyString()
{
	return hotKeysSectionString() + QLatin1Literal("CurrentScreenHotKey");
}

QString KsnipConfigOptions::activeWindowHotKeyString()
{
	return hotKeysSectionString() + QLatin1Literal("ActiveWindowHotKey");
}

QString KsnipConfigOptions::windowUnderCursorHotKeyString()
{
	return hotKeysSectionString() + QLatin1Literal("WindowUnderCursorHotKey");
}

QString KsnipConfigOptions::portalHotKeyString()
{
    return hotKeysSectionString() + QLatin1Literal("PortalHotKey");
}

QString KsnipConfigOptions::applicationSectionString()
{
	return QLatin1Literal("Application/");;
}

QString KsnipConfigOptions::imageGrabberSectionString()
{
	return QLatin1Literal("ImageGrabber/");
}

QString KsnipConfigOptions::annotatorSectionString()
{
	return QLatin1Literal("Painter/");
}

QString KsnipConfigOptions::uploaderSectionString()
{
	return QLatin1Literal("Uploader/");
}

QString KsnipConfigOptions::imgurSectionString()
{
	return QLatin1Literal("Imgur/");
}

QString KsnipConfigOptions::uploadScriptSectionString()
{
	return QLatin1Literal("UploadScript/");
}

QString KsnipConfigOptions::hotKeysSectionString()
{
	return QLatin1Literal("HotKeys/");
}

QString KsnipConfigOptions::mainWindowSectionString()
{
	return QLatin1Literal("MainWindow/");
}

QString KsnipConfigOptions::saveSectionString()
{
	return QLatin1Literal("Save/");
}
