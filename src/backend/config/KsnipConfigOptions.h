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

#ifndef KSNIP_KSNIPCONFIGOPTIONS_H
#define KSNIP_KSNIPCONFIGOPTIONS_H

#include <QString>

class KsnipConfigOptions
{
public:
	static QString rememberPositionString();
	static QString promptSaveBeforeExitString();
	static QString autoCopyToClipboardNewCapturesString();
	static QString autoSaveNewCapturesString();
	static QString rememberToolSelectionString();
	static QString switchToSelectToolAfterDrawingItemString();
	static QString numberToolSeedChangeUpdatesAllItemsString();
	static QString useTabsString();
	static QString autoHideTabsString();
	static QString captureOnStartupString();
	static QString freezeImageWhileSnippingEnabledString();
	static QString positionString();
	static QString autoHideDocksString();
	static QString captureModeString();
	static QString saveQualityModeString();
	static QString saveQualityFactorString();
	static QString saveDirectoryString();
	static QString saveFilenameString();
	static QString saveFormatString();
	static QString applicationStyleString();
	static QString trayIconDefaultActionModeString();
	static QString trayIconDefaultCaptureModeString();
	static QString useTrayIconString();
	static QString minimizeToTrayString();
	static QString closeToTrayString();
	static QString trayIconNotificationsEnabledString();
	static QString startMinimizedToTrayString();
	static QString rememberLastSaveDirectoryString();
	static QString useSingleInstanceString();
	static QString hideMainWindowDuringScreenshotString();
	static QString allowResizingRectSelectionString();
	static QString showSnippingAreaInfoTextString();
	static QString textFontString();
	static QString numberFontString();
	static QString itemShadowEnabledString();
	static QString smoothPathEnabledString();
	static QString smoothPathFactorString();
	static QString rotateWatermarkEnabledString();
	static QString stickerPathsString();
	static QString useDefaultStickerString();
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
	static QString imgurAlwaysCopyToClipboardString();
	static QString imgurBaseUrlString();
	static QString uploadScriptPathString();
	static QString confirmBeforeUploadString();
	static QString uploadScriptCopyOutputToClipboardString();
	static QString uploadScriptStopOnStdErrString();
	static QString uploadScriptCopyOutputFilterString();
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

private:
	static QString applicationSectionString();
	static QString imageGrabberSectionString();
	static QString annotatorSectionString();
	static QString uploaderSectionString();
	static QString imgurSectionString();
	static QString uploadScriptSectionString();
	static QString hotKeysSectionString();
	static QString mainWindowSectionString();
	static QString saveSectionString();
};

#endif //KSNIP_KSNIPCONFIGOPTIONS_H
