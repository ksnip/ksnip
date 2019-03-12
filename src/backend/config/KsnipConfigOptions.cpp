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

#include "KsnipConfigOptions.h"

QString KsnipConfigOptions::savePositionString()
{
	return applicationSectionString() + QStringLiteral("SavePosition");
}

QString KsnipConfigOptions::promptSaveBeforeExitString()
{
	return applicationSectionString() + QStringLiteral("PromptSaveBeforeExit");
}

QString KsnipConfigOptions::alwaysCopyToClipboardString()
{
	return applicationSectionString() + QStringLiteral("AlwaysCopyToClipboard");
}

QString KsnipConfigOptions::saveToolSelectionString()
{
	return applicationSectionString() + QStringLiteral("SaveToolsSelection");
}

QString KsnipConfigOptions::captureOnStartupString()
{
	return applicationSectionString() + QStringLiteral("CaptureOnStartup");
}

QString KsnipConfigOptions::freezeImageWhileSnippingEnabledString()
{
	return imageGrabberSectionString() + QStringLiteral("FreezeImageWhileSnippingEnabled");
}

QString KsnipConfigOptions::positionString()
{
	return mainWindowSectionString() + QStringLiteral("Position");
}

QString KsnipConfigOptions::captureModeString()
{
	return imageGrabberSectionString() + QStringLiteral("CaptureMode");
}

QString KsnipConfigOptions::saveDirectoryString()
{
	return applicationSectionString() + QStringLiteral("SaveDirectory");
}

QString KsnipConfigOptions::saveFilenameString()
{
	return applicationSectionString() + QStringLiteral("SaveFilename");
}

QString KsnipConfigOptions::saveFormatString()
{
	return applicationSectionString() + QStringLiteral("SaveFormat");
}

QString KsnipConfigOptions::useInstantSaveString()
{
	return applicationSectionString() + QStringLiteral("UseInstantSave");
}

QString KsnipConfigOptions::applicationStyleString()
{
	return applicationSectionString() + QStringLiteral("ApplicationStyle");
}

QString KsnipConfigOptions::textFontString()
{
	return annotatorSectionString() + QStringLiteral("TextFont");
}

QString KsnipConfigOptions::numberFontString()
{
	return annotatorSectionString() + QStringLiteral("NumberFont");
}

QString KsnipConfigOptions::itemShadowEnabledString()
{
	return annotatorSectionString() + QStringLiteral("ItemShadowEnabled");
}

QString KsnipConfigOptions::smoothPathEnabledString()
{
	return annotatorSectionString() + QStringLiteral("SmoothPathEnabled");
}

QString KsnipConfigOptions::smoothPathFactorString()
{
	return annotatorSectionString() + QStringLiteral("SmoothPathFactor");
}

QString KsnipConfigOptions::captureCursorString()
{
	return imageGrabberSectionString() + QStringLiteral("CaptureCursor");
}

QString KsnipConfigOptions::snippingAreaRulersEnabledString()
{
	return imageGrabberSectionString() + QStringLiteral("SnippingAreaRulersEnabled");
}

QString KsnipConfigOptions::snippingAreaPositionAndSizeInfoEnabledString()
{
	return imageGrabberSectionString() + QStringLiteral("SnippingAreaPositionAndSizeInfoEnabled");
}

QString KsnipConfigOptions::snippingAreaMagnifyingGlassEnabledString()
{
	return imageGrabberSectionString() + QStringLiteral("SnippingAreaMagnifyingGlassEnabled");
}

QString KsnipConfigOptions::captureDelayString()
{
	return imageGrabberSectionString() + QStringLiteral("CaptureDelay");
}

QString KsnipConfigOptions::snippingCursorSizeString()
{
	return imageGrabberSectionString() + QStringLiteral("SnippingCursorSize");
}

QString KsnipConfigOptions::snippingCursorColorString()
{
	return imageGrabberSectionString() + QStringLiteral("SnippingCursorColor");
}

QString KsnipConfigOptions::imgurUsernameString()
{
	return imgurSectionString() + QStringLiteral("Username");
}

QString KsnipConfigOptions::imgurClientIdString()
{
	return imgurSectionString() + QStringLiteral("ClientId");
}

QString KsnipConfigOptions::imgurClientSecretString()
{
	return imgurSectionString() + QStringLiteral("ClientSecret");
}

QString KsnipConfigOptions::imgurAccessTokenString()
{
	return imgurSectionString() + QStringLiteral("AccessToken");
}

QString KsnipConfigOptions::imgurRefreshTokenString()
{
	return imgurSectionString() + QStringLiteral("RefreshToken");
}

QString KsnipConfigOptions::imgurForceAnonymousString()
{
	return imgurSectionString() + QStringLiteral("ForceAnonymous");
}

QString KsnipConfigOptions::imgurOpenLinkDirectlyToImageString()
{
	return imgurSectionString() + QStringLiteral("OpenLinkDirectlyToImage");
}

QString KsnipConfigOptions::imgurAlwaysCopyToClipboardString()
{
	return imgurSectionString() + QStringLiteral("AlwaysCopyToClipboard");
}

QString KsnipConfigOptions::imgurConfirmBeforeUploadString()
{
	return imgurSectionString() + QStringLiteral("ConfirmBeforeUpload");
}

QString KsnipConfigOptions::applicationSectionString()
{
	return QStringLiteral("Application/");;
}

QString KsnipConfigOptions::imageGrabberSectionString()
{
	return QStringLiteral("ImageGrabber/");
}

QString KsnipConfigOptions::annotatorSectionString()
{
	return QStringLiteral("Painter/");
}

QString KsnipConfigOptions::imgurSectionString()
{
	return QStringLiteral("Imgur/");
}

QString KsnipConfigOptions::mainWindowSectionString()
{
	return QStringLiteral("MainWindow/");
}
