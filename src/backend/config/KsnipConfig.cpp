/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#include "KsnipConfig.h"

// Application

bool KsnipConfig::rememberPosition() const
{
	return loadValue(KsnipConfigOptions::rememberPositionString(), true).toBool();
}

void KsnipConfig::setRememberPosition(bool enabled)
{
	if (rememberPosition() == enabled) {
        return;
    }
	saveValue(KsnipConfigOptions::rememberPositionString(), enabled);
}

bool KsnipConfig::promptSaveBeforeExit() const
{
	return loadValue(KsnipConfigOptions::promptSaveBeforeExitString(), true).toBool();
}

void KsnipConfig::setPromptSaveBeforeExit(bool  enabled)
{
    if (promptSaveBeforeExit() == enabled) {
        return;
    }
	saveValue(KsnipConfigOptions::promptSaveBeforeExitString(), enabled);
}

bool KsnipConfig::autoCopyToClipboardNewCaptures() const
{
	return loadValue(KsnipConfigOptions::autoCopyToClipboardNewCapturesString(), false).toBool();
}

void KsnipConfig::setAutoCopyToClipboardNewCaptures(bool  enabled)
{
    if (autoCopyToClipboardNewCaptures() == enabled) {
        return;
    }
	saveValue(KsnipConfigOptions::autoCopyToClipboardNewCapturesString(), enabled);
}

bool KsnipConfig::autoSaveNewCaptures() const
{
	return loadValue(KsnipConfigOptions::autoSaveNewCapturesString(), false).toBool();
}

void KsnipConfig::setAutoSaveNewCaptures(bool  enabled)
{
	if (autoSaveNewCaptures() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::autoSaveNewCapturesString(), enabled);
}

bool KsnipConfig::autoHideDocks() const
{
	return loadValue(KsnipConfigOptions::autoHideDocksString(), false).toBool();
}

void KsnipConfig::setAutoHideDocks(bool enabled)
{
	if (autoHideDocks() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::autoHideDocksString(), enabled);
}

bool KsnipConfig::useTabs() const
{
	return loadValue(KsnipConfigOptions::useTabsString(), true).toBool();
}

void KsnipConfig::setUseTabs(bool enabled)
{
	if (useTabs() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::useTabsString(), enabled);
	emit annotatorConfigChanged();
}

bool KsnipConfig::autoHideTabs() const
{
	return loadValue(KsnipConfigOptions::autoHideTabsString(), false).toBool();
}

void KsnipConfig::setAutoHideTabs(bool enabled)
{
	if (autoHideTabs() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::autoHideTabsString(), enabled);
	emit annotatorConfigChanged();
}

bool KsnipConfig::captureOnStartup() const
{
	return loadValue(KsnipConfigOptions::captureOnStartupString(), false).toBool();
}

void KsnipConfig::setCaptureOnStartup(bool enabled)
{
    if (captureOnStartup() == enabled) {
        return;
    }
	saveValue(KsnipConfigOptions::captureOnStartupString(), enabled);
}

QPoint KsnipConfig::windowPosition() const
{
	// If we are not saving the position we return the default and ignore what
    // has been save earlier
	if (!rememberPosition()) {
	    return { 200, 200 };
    }

	auto defaultPosition = QPoint(200, 200);
	return loadValue(KsnipConfigOptions::positionString(), defaultPosition).value<QPoint>();
}

void KsnipConfig::setWindowPosition(const QPoint& position)
{
    if (windowPosition() == position) {
        return;
    }
	saveValue(KsnipConfigOptions::positionString(), position);
}

CaptureModes KsnipConfig::captureMode() const
{
    // If we are not storing the tool selection, always return the rect area as default
	if (!rememberToolSelection()) {
        return CaptureModes::RectArea;
    }

	return loadValue(KsnipConfigOptions::captureModeString(), (int)CaptureModes::RectArea).value<CaptureModes>();
}

void KsnipConfig::setCaptureMode(CaptureModes mode)
{
    if (captureMode() == mode) {
        return;
    }
	saveValue(KsnipConfigOptions::captureModeString(), static_cast<int>(mode));
}

QString KsnipConfig::saveDirectory() const
{
	auto saveDirectoryString = loadValue(KsnipConfigOptions::saveDirectoryString(), DirectoryPathProvider::home()).toString();
	if (!saveDirectoryString.isEmpty()) {
		return saveDirectoryString + QLatin1String("/");
    } else {
		return {};
    }
}

void KsnipConfig::setSaveDirectory(const QString& path)
{
    if (saveDirectory() == path) {
        return;
    }
	saveValue(KsnipConfigOptions::saveDirectoryString(), path);
}

QString KsnipConfig::saveFilename() const
{
	auto defaultFilename = QLatin1String("ksnip_$Y$M$D-$T");
	auto filename = loadValue(KsnipConfigOptions::saveFilenameString(), defaultFilename).toString();
	if (filename.isEmpty() || filename.isNull()) {
		filename = defaultFilename;
	}

	return filename;
}

void KsnipConfig::setSaveFilename(const QString& filename)
{
    if (saveFilename() == filename) {
        return;
    }
	saveValue(KsnipConfigOptions::saveFilenameString(), filename);
}

QString KsnipConfig::saveFormat() const
{
	auto defaultFormat = QLatin1String("png");
	auto format = loadValue(KsnipConfigOptions::saveFormatString(), defaultFormat).toString();
	if (format.isEmpty() || format.isNull()) {
		format = defaultFormat;
    }

	return format;
}

void KsnipConfig::setSaveFormat(const QString& format)
{
    if (saveFormat() == format) {
        return;
    }
	saveValue(KsnipConfigOptions::saveFormatString(), format);
}

QString KsnipConfig::applicationStyle() const
{
	auto defaultStyle = QLatin1String("Fusion");
	return loadValue(KsnipConfigOptions::applicationStyleString(), defaultStyle).toString();
}

void KsnipConfig::setApplicationStyle(const QString &style)
{
    if (applicationStyle() == style) {
        return;
    }
	saveValue(KsnipConfigOptions::applicationStyleString(), style);
}

TrayIconDefaultActionMode KsnipConfig::defaultTrayIconActionMode() const
{
	return loadValue(KsnipConfigOptions::trayIconDefaultActionModeString(), (int)TrayIconDefaultActionMode::ShowEditor).value<TrayIconDefaultActionMode>();
}

void KsnipConfig::setDefaultTrayIconActionMode(TrayIconDefaultActionMode mode)
{
	if (defaultTrayIconActionMode() == mode) {
		return;
	}
	saveValue(KsnipConfigOptions::trayIconDefaultActionModeString(), static_cast<int>(mode));
}

CaptureModes KsnipConfig::defaultTrayIconCaptureMode() const
{
	return loadValue(KsnipConfigOptions::trayIconDefaultCaptureModeString(), (int)CaptureModes::RectArea).value<CaptureModes>();
}

void KsnipConfig::setDefaultTrayIconCaptureMode(CaptureModes mode)
{
	if (defaultTrayIconCaptureMode() == mode) {
		return;
	}
	saveValue(KsnipConfigOptions::trayIconDefaultCaptureModeString(), static_cast<int>(mode));
}

bool KsnipConfig::useTrayIcon() const
{
	return loadValue(KsnipConfigOptions::useTrayIconString(), true).toBool();
}

void KsnipConfig::setUseTrayIcon(bool enabled)
{
	if (useTrayIcon() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::useTrayIconString(), enabled);
}

bool KsnipConfig::minimizeToTray() const
{
	return loadValue(KsnipConfigOptions::minimizeToTrayString(), true).toBool();
}

void KsnipConfig::setMinimizeToTray(bool enabled)
{
	if (minimizeToTray() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::minimizeToTrayString(), enabled);
}

bool KsnipConfig::closeToTray() const
{
	return loadValue(KsnipConfigOptions::closeToTrayString(), true).toBool();
}

void KsnipConfig::setCloseToTray(bool enabled)
{
	if (closeToTray() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::closeToTrayString(), enabled);
}

bool KsnipConfig::trayIconNotificationsEnabled() const
{
	return loadValue(KsnipConfigOptions::trayIconNotificationsEnabledString(), true).toBool();
}

void KsnipConfig::setTrayIconNotificationsEnabled(bool enabled)
{
	if (trayIconNotificationsEnabled() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::trayIconNotificationsEnabledString(), enabled);
}

bool KsnipConfig::startMinimizedToTray() const
{
	return loadValue(KsnipConfigOptions::startMinimizedToTrayString(), false).toBool();
}

void KsnipConfig::setStartMinimizedToTray(bool enabled)
{
	if (startMinimizedToTray() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::startMinimizedToTrayString(), enabled);
}

bool KsnipConfig::rememberLastSaveDirectory() const
{
	return loadValue(KsnipConfigOptions::rememberLastSaveDirectoryString(), false).toBool();
}

void KsnipConfig::setRememberLastSaveDirectory(bool enabled)
{
	if (rememberLastSaveDirectory() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::rememberLastSaveDirectoryString(), enabled);
}

bool KsnipConfig::useSingleInstance() const
{
	return loadValue(KsnipConfigOptions::useSingleInstanceString(), true).toBool();
}

void KsnipConfig::setUseSingleInstance(bool enabled)
{
	if (useSingleInstance() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::useSingleInstanceString(), enabled);
}

bool KsnipConfig::hideMainWindowDuringScreenshot() const
{
	return loadValue(KsnipConfigOptions::hideMainWindowDuringScreenshotString(), true).toBool();
}

void KsnipConfig::setHideMainWindowDuringScreenshot(bool enabled)
{
	if (hideMainWindowDuringScreenshot() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::hideMainWindowDuringScreenshotString(), enabled);
}

bool KsnipConfig::allowResizingRectSelection() const
{
	return loadValue(KsnipConfigOptions::allowResizingRectSelectionString(), false).toBool();
}

void KsnipConfig::setAllowResizingRectSelection(bool enabled)
{
	if (allowResizingRectSelection() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::allowResizingRectSelectionString(), enabled);
}

bool KsnipConfig::showSnippingAreaInfoText() const
{
	return loadValue(KsnipConfigOptions::showSnippingAreaInfoTextString(), true).toBool();
}

void KsnipConfig::setShowSnippingAreaInfoText(bool enabled)
{
	if (showSnippingAreaInfoText() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::showSnippingAreaInfoTextString(), enabled);
}

SaveQualityMode KsnipConfig::saveQualityMode() const
{
	return loadValue(KsnipConfigOptions::saveQualityModeString(), (int)SaveQualityMode::Default).value<SaveQualityMode>();
}

void KsnipConfig::setSaveQualityMode(SaveQualityMode mode)
{
	if (saveQualityMode() == mode) {
		return;
	}

	saveValue(KsnipConfigOptions::saveQualityModeString(), static_cast<int>(mode));
}

int KsnipConfig::saveQualityFactor() const
{
	return loadValue(KsnipConfigOptions::saveQualityFactorString(), 50).toInt();
}

void KsnipConfig::setSaveQualityFactor(int factor)
{
	if (saveQualityFactor() == factor) {
		return;
	}

	saveValue(KsnipConfigOptions::saveQualityFactorString(), factor);
}

// Annotator

bool KsnipConfig::rememberToolSelection() const
{
	return loadValue(KsnipConfigOptions::rememberToolSelectionString(), true).toBool();
}

void KsnipConfig::setRememberToolSelection(bool enabled)
{
	if (rememberToolSelection() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::rememberToolSelectionString(), enabled);
}

bool KsnipConfig::switchToSelectToolAfterDrawingItem() const
{
	return loadValue(KsnipConfigOptions::switchToSelectToolAfterDrawingItemString(), false).toBool();
}

void KsnipConfig::setSwitchToSelectToolAfterDrawingItem(bool enabled)
{
	if (switchToSelectToolAfterDrawingItem() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::switchToSelectToolAfterDrawingItemString(), enabled);
	emit annotatorConfigChanged();
}

bool KsnipConfig::numberToolSeedChangeUpdatesAllItems() const
{
	return loadValue(KsnipConfigOptions::numberToolSeedChangeUpdatesAllItemsString(), true).toBool();
}

void KsnipConfig::setNumberToolSeedChangeUpdatesAllItems(bool enabled)
{
	if (numberToolSeedChangeUpdatesAllItems() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::numberToolSeedChangeUpdatesAllItemsString(), enabled);
	emit annotatorConfigChanged();
}

bool KsnipConfig::textBold() const
{
    return textFont().bold();
}

void KsnipConfig::setTextBold(bool  bold)
{
    if (textBold() == bold) {
        return;
    }
    auto font = textFont();
    font.setBold(bold);

	saveValue(KsnipConfigOptions::textFontString(), font);
	emit annotatorConfigChanged();
}

bool KsnipConfig::textItalic() const
{
    return textFont().italic();
}

void KsnipConfig::setTextItalic(bool  italic)
{
    if (textItalic() == italic) {
        return;
    }
    auto font = textFont();
    font.setItalic(italic);

	saveValue(KsnipConfigOptions::textFontString(), font);
	emit annotatorConfigChanged();
}

bool KsnipConfig::textUnderline() const
{
    return textFont().underline();
}

void KsnipConfig::setTextUnderline(bool  underline)
{
    if (textUnderline() == underline) {
        return;
    }
    auto font = textFont();
    font.setUnderline(underline);

	saveValue(KsnipConfigOptions::textFontString(), font);
	emit annotatorConfigChanged();
}

QFont KsnipConfig::textFont() const
{
	auto defaultFont = QFont(QLatin1String("Arial"), 12);
	return loadValue(KsnipConfigOptions::textFontString(), defaultFont).value<QFont>();
}

void KsnipConfig::setTextFont(const QFont& font)
{
    if (textFont().family() == font.family()) {
        return;
    }
    auto tmpFont = textFont();
    tmpFont.setFamily(font.family());

	saveValue(KsnipConfigOptions::textFontString(), tmpFont);
	emit annotatorConfigChanged();
}

QFont KsnipConfig::numberFont() const
{
	auto defaultFont = QFont(QLatin1String("Arial"), 30, QFont::Bold);
	return loadValue(KsnipConfigOptions::numberFontString(), defaultFont).value<QFont>();
}

void KsnipConfig::setNumberFont(const QFont& font)
{
    if (numberFont().family() == font.family()) {
        return;
    }
    auto tmpFont = numberFont();
    tmpFont.setFamily(font.family());
    tmpFont.setBold(true);

	saveValue(KsnipConfigOptions::numberFontString(), tmpFont);
	emit annotatorConfigChanged();
}

bool KsnipConfig::itemShadowEnabled() const
{
	return loadValue(KsnipConfigOptions::itemShadowEnabledString(), true).toBool();
}

void KsnipConfig::setItemShadowEnabled(bool enabled)
{
    if (itemShadowEnabled() == enabled) {
        return;
    }

	saveValue(KsnipConfigOptions::itemShadowEnabledString(), enabled);
	emit annotatorConfigChanged();
}

bool KsnipConfig::smoothPathEnabled() const
{
	return loadValue(KsnipConfigOptions::smoothPathEnabledString(), true).toBool();
}

void KsnipConfig::setSmoothPathEnabled(bool  enabled)
{
    if (smoothPathEnabled() == enabled) {
        return;
    }

	saveValue(KsnipConfigOptions::smoothPathEnabledString(), enabled);
	emit annotatorConfigChanged();
}

int KsnipConfig::smoothFactor() const
{
	return loadValue(KsnipConfigOptions::smoothPathFactorString(), 7).toInt();
}

void KsnipConfig::setSmoothFactor(int  factor)
{
    if (smoothFactor() == factor) {
        return;
    }

	saveValue(KsnipConfigOptions::smoothPathFactorString(), factor);
	emit annotatorConfigChanged();
}

bool KsnipConfig::rotateWatermarkEnabled() const
{
	return loadValue(KsnipConfigOptions::rotateWatermarkEnabledString(), true).toBool();
}

void KsnipConfig::setRotateWatermarkEnabled(bool enabled)
{
	if (rotateWatermarkEnabled() == enabled) {
		return;
	}

	saveValue(KsnipConfigOptions::rotateWatermarkEnabledString(), enabled);
}

QStringList KsnipConfig::stickerPaths() const
{
	return loadValue(KsnipConfigOptions::stickerPathsString(), QVariant::fromValue(QStringList())).value<QStringList>();
}

void KsnipConfig::setStickerPaths(const QStringList &paths)
{
	if (stickerPaths() == paths) {
		return;
	}

	saveValue(KsnipConfigOptions::stickerPathsString(), QVariant::fromValue(paths));
	emit annotatorConfigChanged();
}

bool KsnipConfig::useDefaultSticker() const
{
	return loadValue(KsnipConfigOptions::useDefaultStickerString(), true).toBool();
}

void KsnipConfig::setUseDefaultSticker(bool enabled)
{
	if (useDefaultSticker() == enabled) {
		return;
	}

	saveValue(KsnipConfigOptions::useDefaultStickerString(), enabled);
	emit annotatorConfigChanged();
}

QColor KsnipConfig::canvasColor() const
{
	return loadValue(KsnipConfigOptions::canvasColorString(), QColor(Qt::white)).value<QColor>();
}

void KsnipConfig::setCanvasColor(const QColor &color)
{
	if (canvasColor() == color) {
		return;
	}

	saveValue(KsnipConfigOptions::canvasColorString(), color);
	emit annotatorConfigChanged();
}

// Image Grabber

bool KsnipConfig::isFreezeImageWhileSnippingEnabledReadOnly() const
{
	return false;
}

bool KsnipConfig::freezeImageWhileSnippingEnabled() const
{
	return loadValue(KsnipConfigOptions::freezeImageWhileSnippingEnabledString(), true).toBool();
}

void KsnipConfig::setFreezeImageWhileSnippingEnabled(bool enabled)
{
	if (freezeImageWhileSnippingEnabled() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::freezeImageWhileSnippingEnabledString(), enabled);
}

bool KsnipConfig::captureCursor() const
{
	return loadValue(KsnipConfigOptions::captureCursorString(), true).toBool();
}

void KsnipConfig::setCaptureCursor(bool  enabled)
{
    if (captureCursor() == enabled) {
        return;
    }
	saveValue(KsnipConfigOptions::captureCursorString(), enabled);
}

bool KsnipConfig::snippingAreaRulersEnabled() const
{
	return loadValue(KsnipConfigOptions::snippingAreaRulersEnabledString(), true).toBool();
}

void KsnipConfig::setSnippingAreaRulersEnabled(bool enabled)
{
	if (snippingAreaRulersEnabled() == enabled) {
        return;
    }
	saveValue(KsnipConfigOptions::snippingAreaRulersEnabledString(), enabled);
}

bool KsnipConfig::snippingAreaPositionAndSizeInfoEnabled() const
{
	return loadValue(KsnipConfigOptions::snippingAreaPositionAndSizeInfoEnabledString(), true).toBool();
}

void KsnipConfig::setSnippingAreaPositionAndSizeInfoEnabled(bool enabled)
{
	if (snippingAreaPositionAndSizeInfoEnabled() == enabled) {
        return;
    }
	saveValue(KsnipConfigOptions::snippingAreaPositionAndSizeInfoEnabledString(), enabled);
}

bool KsnipConfig::showMainWindowAfterTakingScreenshotEnabled() const
{
	return loadValue(KsnipConfigOptions::showMainWindowAfterTakingScreenshotEnabledString(), true).toBool();
}

void KsnipConfig::setShowMainWindowAfterTakingScreenshotEnabled(bool enabled)
{
	if (showMainWindowAfterTakingScreenshotEnabled() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::showMainWindowAfterTakingScreenshotEnabledString(), enabled);
}

bool KsnipConfig::isSnippingAreaMagnifyingGlassEnabledReadOnly() const
{
	return false;
}

bool KsnipConfig::snippingAreaMagnifyingGlassEnabled() const
{
	return loadValue(KsnipConfigOptions::snippingAreaMagnifyingGlassEnabledString(), true).toBool();
}

void KsnipConfig::setSnippingAreaMagnifyingGlassEnabled(bool enabled)
{
	if (snippingAreaMagnifyingGlassEnabled() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::snippingAreaMagnifyingGlassEnabledString(), enabled);
}

int KsnipConfig::captureDelay() const
{
	return loadValue(KsnipConfigOptions::captureDelayString(), 0).toInt();
}

void KsnipConfig::setCaptureDelay(int delay)
{
    if (captureDelay() == delay) {
        return;
    }
	saveValue(KsnipConfigOptions::captureDelayString(), delay);
}

int KsnipConfig::snippingCursorSize() const
{
	return loadValue(KsnipConfigOptions::snippingCursorSizeString(), 1).toInt();
}

void KsnipConfig::setSnippingCursorSize(int size)
{
    if (snippingCursorSize() == size) {
        return;
    }
	saveValue(KsnipConfigOptions::snippingCursorSizeString(), size);
}

QColor KsnipConfig::snippingCursorColor() const
{
	auto defaultColor = QColor(27, 20, 77);
	return loadValue(KsnipConfigOptions::snippingCursorColorString(), defaultColor).value<QColor>();
}

void KsnipConfig::setSnippingCursorColor(const QColor& color)
{
    if (snippingCursorColor() == color) {
        return;
    }
	saveValue(KsnipConfigOptions::snippingCursorColorString(), color);
}

QColor KsnipConfig::snippingAdornerColor() const
{
	return loadValue(KsnipConfigOptions::snippingAdornerColorString(), QColor(Qt::red)).value<QColor>();
}

void KsnipConfig::setSnippingAdornerColor(const QColor& color)
{
	if (snippingAdornerColor() == color) {
		return;
	}
	saveValue(KsnipConfigOptions::snippingAdornerColorString(), color);
}

int KsnipConfig::snippingAreaTransparency() const
{
	return loadValue(KsnipConfigOptions::snippingAreaTransparencyString(), 150).value<int>();
}

void KsnipConfig::setSnippingAreaTransparency(int transparency)
{
	if (snippingAreaTransparency() == transparency) {
		return;
	}
	saveValue(KsnipConfigOptions::snippingAreaTransparencyString(), transparency);
}

QRect KsnipConfig::lastRectArea() const
{
	return loadValue(KsnipConfigOptions::lastRectAreaString(), QRect()).value<QRect>();
}

void KsnipConfig::setLastRectArea(const QRect &rectArea)
{
	if (lastRectArea() == rectArea) {
		return;
	}
	saveValue(KsnipConfigOptions::lastRectAreaString(), rectArea);
}

bool KsnipConfig::isForceGenericWaylandEnabledReadOnly() const
{
    return true;
}

bool KsnipConfig::forceGenericWaylandEnabled() const
{
    return loadValue(KsnipConfigOptions::forceGenericWaylandEnabledString(), false).toBool();
}

void KsnipConfig::setForceGenericWaylandEnabled(bool enabled)
{
    if (forceGenericWaylandEnabled() == enabled) {
        return;
    }
    saveValue(KsnipConfigOptions::forceGenericWaylandEnabledString(), enabled);
}

bool KsnipConfig::isScaleGenericWaylandScreenshotEnabledReadOnly() const
{
    return true;
}

bool KsnipConfig::scaleGenericWaylandScreenshotsEnabled() const
{
    return loadValue(KsnipConfigOptions::scaleWaylandScreenshotsEnabledString(), false).toBool();
}

void KsnipConfig::setScaleGenericWaylandScreenshots(bool enabled)
{
    if (scaleGenericWaylandScreenshotsEnabled() == enabled) {
        return;
    }
    saveValue(KsnipConfigOptions::scaleWaylandScreenshotsEnabledString(), enabled);
}

// Uploader

bool KsnipConfig::confirmBeforeUpload() const
{
	return loadValue(KsnipConfigOptions::confirmBeforeUploadString(), true).toBool();
}

void KsnipConfig::setConfirmBeforeUpload(bool enabled)
{
	if (confirmBeforeUpload() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::confirmBeforeUploadString(), enabled);
}

UploaderType KsnipConfig::uploaderType() const
{
	return loadValue(KsnipConfigOptions::uploaderTypeString(), static_cast<int>(UploaderType::Imgur)).value<UploaderType >();
}

void KsnipConfig::setUploaderType(UploaderType type)
{
	if (uploaderType() == type) {
		return;
	}
	saveValue(KsnipConfigOptions::uploaderTypeString(), static_cast<int>(type));
}

// Imgur Uploader

QString KsnipConfig::imgurUsername() const
{
	auto defaultUsername = QLatin1String("");
	return loadValue(KsnipConfigOptions::imgurUsernameString(), defaultUsername).toString();
}

void KsnipConfig::setImgurUsername(const QString& username)
{
    if (imgurUsername() == username) {
        return;
    }
	saveValue(KsnipConfigOptions::imgurUsernameString(), username);
}

QByteArray KsnipConfig::imgurClientId() const
{
	auto defaultClientId = QLatin1String("");
	return loadValue(KsnipConfigOptions::imgurClientIdString(), defaultClientId).toByteArray();
}

void KsnipConfig::setImgurClientId(const QString& clientId)
{
    if (imgurClientId() == clientId) {
        return;
    }
	saveValue(KsnipConfigOptions::imgurClientIdString(), clientId);
}

QByteArray KsnipConfig::imgurClientSecret() const
{
	auto defaultClientSecret = QLatin1String("");
	return loadValue(KsnipConfigOptions::imgurClientSecretString(), defaultClientSecret).toByteArray();
}

void KsnipConfig::setImgurClientSecret(const QString& clientSecret)
{
    if (imgurClientSecret() == clientSecret) {
        return;
    }
	saveValue(KsnipConfigOptions::imgurClientSecretString(), clientSecret);
}

QByteArray KsnipConfig::imgurAccessToken() const
{
	auto defaultAccessToken = QLatin1String("");
	return loadValue(KsnipConfigOptions::imgurAccessTokenString(), defaultAccessToken).toByteArray();
}

void KsnipConfig::setImgurAccessToken(const QString& accessToken)
{
    if (imgurAccessToken() == accessToken) {
        return;
    }
	saveValue(KsnipConfigOptions::imgurAccessTokenString(), accessToken);
}

QByteArray KsnipConfig::imgurRefreshToken() const
{
	auto defaultRefreshToken = QLatin1String("");
	return loadValue(KsnipConfigOptions::imgurRefreshTokenString(), defaultRefreshToken).toByteArray();
}

void KsnipConfig::setImgurRefreshToken(const QString& refreshToken)
{
    if (imgurRefreshToken() == refreshToken) {
        return;
    }
	saveValue(KsnipConfigOptions::imgurRefreshTokenString(), refreshToken);
}

bool KsnipConfig::imgurForceAnonymous() const
{
	return loadValue(KsnipConfigOptions::imgurForceAnonymousString(), false).toBool();
}

void KsnipConfig::setImgurForceAnonymous(bool  enabled)
{
    if (imgurForceAnonymous() == enabled) {
        return;
    }
	saveValue(KsnipConfigOptions::imgurForceAnonymousString(), enabled);
}

bool KsnipConfig::imgurLinkDirectlyToImage() const
{
	return loadValue(KsnipConfigOptions::imgurLinkDirectlyToImageString(), false).toBool();
}

void KsnipConfig::setImgurLinkDirectlyToImage(bool  enabled)
{
    if (imgurLinkDirectlyToImage() == enabled) {
        return;
    }
	saveValue(KsnipConfigOptions::imgurLinkDirectlyToImageString(), enabled);
}

bool KsnipConfig::imgurAlwaysCopyToClipboard() const
{
	return loadValue(KsnipConfigOptions::imgurAlwaysCopyToClipboardString(), false).toBool();
}

void KsnipConfig::setImgurAlwaysCopyToClipboard(bool  enabled)
{
    if (imgurAlwaysCopyToClipboard() == enabled) {
        return;
    }
	saveValue(KsnipConfigOptions::imgurAlwaysCopyToClipboardString(), enabled);
}

bool KsnipConfig::imgurOpenLinkInBrowser() const
{
	return loadValue(KsnipConfigOptions::imgurOpenLinkInBrowserString(), true).toBool();
}

void KsnipConfig::setImgurOpenLinkInBrowser(bool enabled)
{
	if (imgurOpenLinkInBrowser() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::imgurOpenLinkInBrowserString(), enabled);
}

QString KsnipConfig::imgurBaseUrl() const
{
	return loadValue(KsnipConfigOptions::imgurBaseUrlString(), DefaultValues::ImgurBaseUrl).toString();
}

void KsnipConfig::setImgurBaseUrl(const QString &baseUrl)
{
	if (imgurBaseUrl() == baseUrl) {
		return;
	}
	saveValue(KsnipConfigOptions::imgurBaseUrlString(), baseUrl);
}

// Script Uploader

QString KsnipConfig::uploadScriptPath() const
{
	return loadValue(KsnipConfigOptions::uploadScriptPathString(), QString()).toString();
}

void KsnipConfig::setUploadScriptPath(const QString &path)
{
	if (uploadScriptPath() == path) {
		return;
	}
	saveValue(KsnipConfigOptions::uploadScriptPathString(), path);
}

bool KsnipConfig::uploadScriptCopyOutputToClipboard() const
{
	return loadValue(KsnipConfigOptions::uploadScriptCopyOutputToClipboardString(), false).toBool();
}

void KsnipConfig::setUploadScriptCopyOutputToClipboard(bool enabled)
{
	if (uploadScriptCopyOutputToClipboard() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::uploadScriptCopyOutputToClipboardString(), enabled);
}

QString KsnipConfig::uploadScriptCopyOutputFilter() const
{
	return loadValue(KsnipConfigOptions::uploadScriptCopyOutputFilterString(), QString()).toString();
}

void KsnipConfig::setUploadScriptCopyOutputFilter(const QString &regex)
{
	if (uploadScriptCopyOutputFilter() == regex) {
		return;
	}
	saveValue(KsnipConfigOptions::uploadScriptCopyOutputFilterString(), regex);
}

bool KsnipConfig::uploadScriptStopOnStdErr() const
{
	return loadValue(KsnipConfigOptions::uploadScriptStopOnStdErrString(), true).toBool();
}

void KsnipConfig::setUploadScriptStopOnStdErr(bool enabled)
{
	if (uploadScriptStopOnStdErr() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::uploadScriptStopOnStdErrString(), enabled);
}

// HotKeys

bool KsnipConfig::isGlobalHotKeysEnabledReadOnly() const
{
	return false;
}

bool KsnipConfig::globalHotKeysEnabled() const
{
	return loadValue(KsnipConfigOptions::globalHotKeysEnabledString(), true).toBool();
}

void KsnipConfig::setGlobalHotKeysEnabled(bool enabled)
{
	if (globalHotKeysEnabled() == enabled) {
		return;
	}
	saveValue(KsnipConfigOptions::globalHotKeysEnabledString(), enabled);
	emit hotKeysChanged();
}

QKeySequence KsnipConfig::rectAreaHotKey() const
{
	return loadValue(KsnipConfigOptions::rectAreaHotKeyString(), QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_R)).value<QKeySequence>();
}

void KsnipConfig::setRectAreaHotKey(const QKeySequence &keySequence)
{
	if (rectAreaHotKey() == keySequence) {
		return;
	}
	saveValue(KsnipConfigOptions::rectAreaHotKeyString(), keySequence);
	emit hotKeysChanged();
}


QKeySequence KsnipConfig::lastRectAreaHotKey() const
{
	return loadValue(KsnipConfigOptions::lastRectAreaHotKeyString(), QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_L)).value<QKeySequence>();
}

void KsnipConfig::setLastRectAreaHotKey(const QKeySequence &keySequence)
{
	if (lastRectAreaHotKey() == keySequence) {
		return;
	}
	saveValue(KsnipConfigOptions::lastRectAreaHotKeyString(), keySequence);
	emit hotKeysChanged();
}

QKeySequence KsnipConfig::fullScreenHotKey() const
{
	return loadValue(KsnipConfigOptions::fullScreenHotKeyString(), QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_F)).value<QKeySequence>();
}

void KsnipConfig::setFullScreenHotKey(const QKeySequence &keySequence)
{
	if (fullScreenHotKey() == keySequence) {
		return;
	}
	saveValue(KsnipConfigOptions::fullScreenHotKeyString(), keySequence);
	emit hotKeysChanged();
}

QKeySequence KsnipConfig::currentScreenHotKey() const
{
	return loadValue(KsnipConfigOptions::currentScreenHotKeyString(), QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_C)).value<QKeySequence>();
}

void KsnipConfig::setCurrentScreenHotKey(const QKeySequence &keySequence)
{
	if (currentScreenHotKey() == keySequence) {
		return;
	}
	saveValue(KsnipConfigOptions::currentScreenHotKeyString(), keySequence);
	emit hotKeysChanged();
}

QKeySequence KsnipConfig::activeWindowHotKey() const
{
	return loadValue(KsnipConfigOptions::activeWindowHotKeyString(), QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_A)).value<QKeySequence>();
}

void KsnipConfig::setActiveWindowHotKey(const QKeySequence &keySequence)
{
	if (activeWindowHotKey() == keySequence) {
		return;
	}
	saveValue(KsnipConfigOptions::activeWindowHotKeyString(), keySequence);
	emit hotKeysChanged();
}

QKeySequence KsnipConfig::windowUnderCursorHotKey() const
{
	return loadValue(KsnipConfigOptions::windowUnderCursorHotKeyString(), QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_U)).value<QKeySequence>();
}

void KsnipConfig::setWindowUnderCursorHotKey(const QKeySequence &keySequence)
{
	if (windowUnderCursorHotKey() == keySequence) {
		return;
	}
	saveValue(KsnipConfigOptions::windowUnderCursorHotKeyString(), keySequence);
	emit hotKeysChanged();
}

QKeySequence KsnipConfig::portalHotKey() const
{
    return loadValue(KsnipConfigOptions::portalHotKeyString(), QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_T)).value<QKeySequence>();
}

void KsnipConfig::setPortalHotKey(const QKeySequence &keySequence)
{
    if (portalHotKey() == keySequence) {
        return;
    }
    saveValue(KsnipConfigOptions::portalHotKeyString(), keySequence);
    emit hotKeysChanged();
}

// Misc

void KsnipConfig::saveValue(const QString &key, const QVariant &value)
{
	mConfig.setValue(key, value);
	mConfig.sync();
}

QVariant KsnipConfig::loadValue(const QString &key, const QVariant &defaultValue) const
{
	return mConfig.value(key, defaultValue);
}
