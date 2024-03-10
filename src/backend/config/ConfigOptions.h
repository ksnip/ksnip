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

#ifndef KSNIP_CONFIGOPTIONS_H
#define KSNIP_CONFIGOPTIONS_H

#include <QString>

class ConfigOptions
{
public:
	static QString rememberPositionString();
	static QString promptSaveBeforeExitString();
	static QString autoCopyToClipboardNewCapturesString();
	static QString autoSaveNewCapturesString();
	static QString rememberToolSelectionString();
	static QString switchToSelectToolAfterDrawingItemString();
	static QString selectItemAfterDrawingString();
	static QString numberToolSeedChangeUpdatesAllItemsString();
	static QString useTabsString();
	static QString autoHideTabsString();
	static QString captureOnStartupString();
	static QString freezeImageWhileSnippingEnabledString();
	static QString positionString();
	static QString autoHideDocksString();
	static QString autoResizeToContentString();
	static QString resizeToContentDelayString();
	static QString overwriteFileEnabledString();
	static QString captureModeString();
	static QString saveQualityModeString();
	static QString saveQualityFactorString();
	static QString isDebugEnabledString();
	static QString tempDirectoryString();
	static QString saveDirectoryString();
	static QString saveFilenameString();
	static QString saveFormatString();
	static QString applicationStyleString();
	static QString trayIconDefaultActionModeString();
	static QString trayIconDefaultCaptureModeString();
	static QString useTrayIconString();
	static QString useCustomTrayIconImageString();
	static QString customTrayIconImageFileString();
	static QString minimizeToTrayString();
	static QString closeToTrayString();
	static QString trayIconNotificationsEnabledString();
	static QString platformSpecificNotificationServiceEnabledString();
	static QString startMinimizedToTrayString();
	static QString rememberLastSaveDirectoryString();
	static QString useSingleInstanceString();
	static QString hideMainWindowDuringScreenshotString();
	static QString allowResizingRectSelectionString();
	static QString showSnippingAreaInfoTextString();
	static QString snippingAreaOffsetEnableString();
	static QString snippingAreaOffsetString();
	static QString implicitCaptureDelayString();
	static QString smoothPathEnabledString();
	static QString smoothPathFactorString();
	static QString rotateWatermarkEnabledString();
	static QString stickerPathsString();
	static QString useDefaultStickerString();
	static QString isControlsWidgetVisibleString();
	static QString captureCursorString();
	static QString snippingAreaRulersEnabledString();
	static QString snippingAreaPositionAndSizeInfoEnabledString();
	static QString snippingAreaMagnifyingGlassEnabledString();
	static QString showMainWindowAfterTakingScreenshotEnabledString();
	static QString captureDelayString();
	static QString snippingCursorSizeString();
	static QString snippingCursorColorString();
	static QString snippingAdornerColorString();
	static QString snippingAreaTransparencyString();
	static QString lastRectAreaString();
	static QString forceGenericWaylandEnabledString();
	static QString scaleWaylandScreenshotsEnabledString();
	static QString imgurUsernameString();
	static QString imgurClientIdString();
	static QString imgurClientSecretString();
	static QString imgurAccessTokenString();
	static QString imgurRefreshTokenString();
	static QString imgurForceAnonymousString();
	static QString imgurLinkDirectlyToImageString();
	static QString imgurOpenLinkInBrowserString();
	static QString imgurUploadTitleString();
	static QString imgurUploadDescriptionString();
	static QString imgurAlwaysCopyToClipboardString();
	static QString imgurBaseUrlString();
	static QString uploadScriptPathString();
	static QString confirmBeforeUploadString();
	static QString uploadScriptCopyOutputToClipboardString();
	static QString uploadScriptStopOnStdErrString();
	static QString uploadScriptCopyOutputFilterString();
	static QString ftpUploadForceAnonymousString();
	static QString ftpUploadUrlString();
	static QString ftpUploadUsernameString();
	static QString ftpUploadPasswordString();
	static QString globalHotKeysEnabledString();
	static QString rectAreaHotKeyString();
	static QString lastRectAreaHotKeyString();
	static QString fullScreenHotKeyString();
	static QString currentScreenHotKeyString();
	static QString activeWindowHotKeyString();
	static QString windowUnderCursorHotKeyString();
	static QString portalHotKeyString();
	static QString uploaderTypeString();
	static QString canvasColorString();
	static QString actionsString();
	static QString actionNameString();
	static QString actionShortcutString();
	static QString actionShortcutIsGlobalString();
	static QString actionIsCaptureEnabledString();
	static QString actionIncludeCursorString();
	static QString actionCaptureDelayString();
	static QString actionCaptureModeString();
	static QString actionIsPinImageEnabledString();
	static QString actionIsUploadEnabledString();
	static QString actionIsOpenDirectoryEnabledString();
	static QString actionIsCopyToClipboardEnabledString();
	static QString actionIsSaveEnabledString();
	static QString actionIsHideMainWindowEnabledString();
	static QString pluginPathString();
	static QString customPluginSearchPathEnabledString();
	static QString pluginInfosString();
	static QString pluginInfoPathString();
	static QString pluginInfoTypeString();
	static QString pluginInfoVersionString();

private:
	static QString applicationSectionString();
	static QString imageGrabberSectionString();
	static QString annotatorSectionString();
	static QString uploaderSectionString();
	static QString imgurSectionString();
	static QString uploadScriptSectionString();
	static QString ftpUploadSectionString();
	static QString hotKeysSectionString();
	static QString mainWindowSectionString();
	static QString saveSectionString();
	static QString pluginsSectionString();
	static QString snippingAreaSectionString();
};

#endif //KSNIP_CONFIGOPTIONS_H
