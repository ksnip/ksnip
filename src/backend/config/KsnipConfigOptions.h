/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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
 */

#ifndef KSNIP_KSNIPCONFIGOPTIONS_H
#define KSNIP_KSNIPCONFIGOPTIONS_H

#include <QString>

class KsnipConfigOptions
{
public:
	static QString savePositionString();
	static QString promptSaveBeforeExitString();
	static QString alwaysCopyToClipboardString();
	static QString saveToolSelectionString();
	static QString captureOnStartupString();
	static QString freezeImageWhileSnippingEnabledString();
	static QString positionString();
	static QString captureModeString();
	static QString saveDirectoryString();
	static QString saveFilenameString();
	static QString saveFormatString();
	static QString useInstantSaveString();
	static QString applicationStyleString();
	static QString textFontString();
	static QString numberFontString();
	static QString itemShadowEnabledString();
	static QString smoothPathEnabledString();
	static QString smoothPathFactorString();
	static QString captureCursorString();
	static QString snippingAreaRulersEnabledString();
	static QString snippingAreaPositionAndSizeInfoEnabledString();
	static QString snippingAreaMagnifyingGlassEnabledString();
	static QString captureDelayString();
	static QString snippingCursorSizeString();
	static QString snippingCursorColorString();
	static QString imgurUsernameString();
	static QString imgurClientIdString();
	static QString imgurClientSecretString();
	static QString imgurAccessTokenString();
	static QString imgurRefreshTokenString();
	static QString imgurForceAnonymousString();
	static QString imgurOpenLinkDirectlyToImageString();
	static QString imgurAlwaysCopyToClipboardString();
	static QString imgurConfirmBeforeUploadString();

private:
	static QString applicationSectionString();
	static QString imageGrabberSectionString();
	static QString annotatorSectionString();
	static QString imgurSectionString();
	static QString mainWindowSectionString();
};

#endif //KSNIP_KSNIPCONFIGOPTIONS_H
