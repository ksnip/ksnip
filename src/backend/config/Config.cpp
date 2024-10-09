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

#include "Config.h"

Config::Config(const QSharedPointer<IDirectoryPathProvider> &directoryPathProvider) :
		mDirectoryPathProvider(directoryPathProvider)
{

}

// Application

bool Config::rememberPosition() const
{
	return loadValue(ConfigOptions::rememberPositionString(), true).toBool();
}

void Config::setRememberPosition(bool enabled)
{
	if (rememberPosition() == enabled) {
		return;
	}
	saveValue(ConfigOptions::rememberPositionString(), enabled);
}

bool Config::promptSaveBeforeExit() const
{
	return loadValue(ConfigOptions::promptSaveBeforeExitString(), true).toBool();
}

void Config::setPromptSaveBeforeExit(bool  enabled)
{
	if (promptSaveBeforeExit() == enabled) {
		return;
	}
	saveValue(ConfigOptions::promptSaveBeforeExitString(), enabled);
}

bool Config::autoCopyToClipboardNewCaptures() const
{
	return loadValue(ConfigOptions::autoCopyToClipboardNewCapturesString(), false).toBool();
}

void Config::setAutoCopyToClipboardNewCaptures(bool  enabled)
{
	if (autoCopyToClipboardNewCaptures() == enabled) {
		return;
	}
	saveValue(ConfigOptions::autoCopyToClipboardNewCapturesString(), enabled);
}

bool Config::autoSaveNewCaptures() const
{
	return loadValue(ConfigOptions::autoSaveNewCapturesString(), false).toBool();
}

void Config::setAutoSaveNewCaptures(bool  enabled)
{
	if (autoSaveNewCaptures() == enabled) {
		return;
	}
	saveValue(ConfigOptions::autoSaveNewCapturesString(), enabled);
}

bool Config::autoHideDocks() const
{
	return loadValue(ConfigOptions::autoHideDocksString(), false).toBool();
}

void Config::setAutoHideDocks(bool enabled)
{
	if (autoHideDocks() == enabled) {
		return;
	}
	saveValue(ConfigOptions::autoHideDocksString(), enabled);
}

bool Config::autoResizeToContent() const
{
	return loadValue(ConfigOptions::autoResizeToContentString(), true).toBool();
}

void Config::setAutoResizeToContent(bool enabled)
{
	if (autoResizeToContent() == enabled) {
		return;
	}
	saveValue(ConfigOptions::autoResizeToContentString(), enabled);
}

int Config::resizeToContentDelay() const
{
	return loadValue(ConfigOptions::resizeToContentDelayString(), 10).toInt();
}

void Config::setResizeToContentDelay(int ms)
{
	if (resizeToContentDelay() == ms) {
		return;
	}
	saveValue(ConfigOptions::resizeToContentDelayString(), ms);
}

bool Config::overwriteFile() const
{
	return loadValue(ConfigOptions::overwriteFileEnabledString(), false).toBool();
}

void Config::setOverwriteFile(bool enabled)
{
	if (overwriteFile() == enabled) {
		return;
	}
	saveValue(ConfigOptions::overwriteFileEnabledString(), enabled);
}

bool Config::useTabs() const
{
	return loadValue(ConfigOptions::useTabsString(), true).toBool();
}

void Config::setUseTabs(bool enabled)
{
	if (useTabs() == enabled) {
		return;
	}
	saveValue(ConfigOptions::useTabsString(), enabled);
	emit annotatorConfigChanged();
}

bool Config::autoHideTabs() const
{
	return loadValue(ConfigOptions::autoHideTabsString(), false).toBool();
}

void Config::setAutoHideTabs(bool enabled)
{
	if (autoHideTabs() == enabled) {
		return;
	}
	saveValue(ConfigOptions::autoHideTabsString(), enabled);
	emit annotatorConfigChanged();
}

bool Config::captureOnStartup() const
{
	return loadValue(ConfigOptions::captureOnStartupString(), false).toBool();
}

void Config::setCaptureOnStartup(bool enabled)
{
	if (captureOnStartup() == enabled) {
		return;
	}
	saveValue(ConfigOptions::captureOnStartupString(), enabled);
}

QPoint Config::windowPosition() const
{
	// If we are not saving the position we return the default and ignore what
	// has been save earlier
	if (!rememberPosition()) {
		return { 200, 200 };
	}

	auto defaultPosition = QPoint(200, 200);
	return loadValue(ConfigOptions::positionString(), defaultPosition).value<QPoint>();
}

void Config::setWindowPosition(const QPoint& position)
{
	if (windowPosition() == position) {
		return;
	}
	saveValue(ConfigOptions::positionString(), position);
}

CaptureModes Config::captureMode() const
{
	// If we are not storing the tool selection, always return the rect area as default
	if (!rememberToolSelection()) {
		return CaptureModes::RectArea;
	}

	return loadValue(ConfigOptions::captureModeString(), (int)CaptureModes::RectArea).value<CaptureModes>();
}

void Config::setCaptureMode(CaptureModes mode)
{
	if (captureMode() == mode) {
		return;
	}
	saveValue(ConfigOptions::captureModeString(), static_cast<int>(mode));
}

QString Config::saveDirectory() const
{
	auto saveDirectoryString = loadValue(ConfigOptions::saveDirectoryString(), mDirectoryPathProvider->home()).toString();
	if (!saveDirectoryString.isEmpty()) {
		return saveDirectoryString + QLatin1String("/");
	} else {
		return {};
	}
}

void Config::setSaveDirectory(const QString& path)
{
	if (saveDirectory() == path) {
		return;
	}
	saveValue(ConfigOptions::saveDirectoryString(), path);
}

QString Config::saveFilename() const
{
	auto defaultFilename = QLatin1String("ksnip_$Y$M$D-$T");
	auto filename = loadValue(ConfigOptions::saveFilenameString(), defaultFilename).toString();
	if (filename.isEmpty() || filename.isNull()) {
		filename = defaultFilename;
	}

	return filename;
}

void Config::setSaveFilename(const QString& filename)
{
	if (saveFilename() == filename) {
		return;
	}
	saveValue(ConfigOptions::saveFilenameString(), filename);
}

QString Config::saveFormat() const
{
	auto defaultFormat = QLatin1String("png");
	auto format = loadValue(ConfigOptions::saveFormatString(), defaultFormat).toString();
	if (format.isEmpty() || format.isNull()) {
		format = defaultFormat;
	}

	return format;
}

void Config::setSaveFormat(const QString& format)
{
	if (saveFormat() == format) {
		return;
	}
	saveValue(ConfigOptions::saveFormatString(), format);
}

QString Config::applicationStyle() const
{
	auto defaultStyle = QLatin1String("Fusion");
	return loadValue(ConfigOptions::applicationStyleString(), defaultStyle).toString();
}

void Config::setApplicationStyle(const QString &style)
{
	if (applicationStyle() == style) {
		return;
	}
	saveValue(ConfigOptions::applicationStyleString(), style);
}

TrayIconDefaultActionMode Config::defaultTrayIconActionMode() const
{
	return loadValue(ConfigOptions::trayIconDefaultActionModeString(), (int)TrayIconDefaultActionMode::ShowEditor).value<TrayIconDefaultActionMode>();
}

void Config::setDefaultTrayIconActionMode(TrayIconDefaultActionMode mode)
{
	if (defaultTrayIconActionMode() == mode) {
		return;
	}
	saveValue(ConfigOptions::trayIconDefaultActionModeString(), static_cast<int>(mode));
}

CaptureModes Config::defaultTrayIconCaptureMode() const
{
	return loadValue(ConfigOptions::trayIconDefaultCaptureModeString(), (int)CaptureModes::RectArea).value<CaptureModes>();
}

void Config::setDefaultTrayIconCaptureMode(CaptureModes mode)
{
	if (defaultTrayIconCaptureMode() == mode) {
		return;
	}
	saveValue(ConfigOptions::trayIconDefaultCaptureModeString(), static_cast<int>(mode));
}

bool Config::useTrayIcon() const
{
	return loadValue(ConfigOptions::useTrayIconString(), true).toBool();
}

void Config::setUseTrayIcon(bool enabled)
{
	if (useTrayIcon() == enabled) {
		return;
	}
	saveValue(ConfigOptions::useTrayIconString(), enabled);
}

bool Config::useCustomTrayIconImage() const
{
	return loadValue(ConfigOptions::useCustomTrayIconImageString(), false).toBool();
}

void Config::setCustomTrayIconImage(bool enabled)
{
	if (useCustomTrayIconImage() == enabled) {
		return;
	}
	saveValue(ConfigOptions::useCustomTrayIconImageString(), enabled);
}

QString Config::customTrayIconImageFile() const
{
	return loadValue(ConfigOptions::customTrayIconImageFileString(), "").toString();
}

void Config::setCustomTrayIconImageFile(const QString& filepath)
{
	if(customTrayIconImageFile() == filepath) {
		return;
	}

	saveValue(ConfigOptions::customTrayIconImageFileString(), filepath);
}

bool Config::minimizeToTray() const
{
	return loadValue(ConfigOptions::minimizeToTrayString(), true).toBool();
}

void Config::setMinimizeToTray(bool enabled)
{
	if (minimizeToTray() == enabled) {
		return;
	}
	saveValue(ConfigOptions::minimizeToTrayString(), enabled);
}

bool Config::closeToTray() const
{
	return loadValue(ConfigOptions::closeToTrayString(), true).toBool();
}

void Config::setCloseToTray(bool enabled)
{
	if (closeToTray() == enabled) {
		return;
	}
	saveValue(ConfigOptions::closeToTrayString(), enabled);
}

bool Config::trayIconNotificationsEnabled() const
{
	return loadValue(ConfigOptions::trayIconNotificationsEnabledString(), true).toBool();
}

void Config::setTrayIconNotificationsEnabled(bool enabled)
{
	if (trayIconNotificationsEnabled() == enabled) {
		return;
	}
	saveValue(ConfigOptions::trayIconNotificationsEnabledString(), enabled);
}

bool Config::platformSpecificNotificationServiceEnabled() const
{
	return loadValue(ConfigOptions::platformSpecificNotificationServiceEnabledString(), true).toBool();
}

void Config::setPlatformSpecificNotificationServiceEnabled(bool enabled)
{
	if (platformSpecificNotificationServiceEnabled() == enabled) {
		return;
	}
	saveValue(ConfigOptions::platformSpecificNotificationServiceEnabledString(), enabled);
}

bool Config::startMinimizedToTray() const
{
	return loadValue(ConfigOptions::startMinimizedToTrayString(), false).toBool();
}

void Config::setStartMinimizedToTray(bool enabled)
{
	if (startMinimizedToTray() == enabled) {
		return;
	}
	saveValue(ConfigOptions::startMinimizedToTrayString(), enabled);
}

bool Config::rememberLastSaveDirectory() const
{
	return loadValue(ConfigOptions::rememberLastSaveDirectoryString(), false).toBool();
}

void Config::setRememberLastSaveDirectory(bool enabled)
{
	if (rememberLastSaveDirectory() == enabled) {
		return;
	}
	saveValue(ConfigOptions::rememberLastSaveDirectoryString(), enabled);
}

bool Config::useSingleInstance() const
{
	return loadValue(ConfigOptions::useSingleInstanceString(), true).toBool();
}

void Config::setUseSingleInstance(bool enabled)
{
	if (useSingleInstance() == enabled) {
		return;
	}
	saveValue(ConfigOptions::useSingleInstanceString(), enabled);
}

bool Config::hideMainWindowDuringScreenshot() const
{
	return loadValue(ConfigOptions::hideMainWindowDuringScreenshotString(), true).toBool();
}

void Config::setHideMainWindowDuringScreenshot(bool enabled)
{
	if (hideMainWindowDuringScreenshot() == enabled) {
		return;
	}
	saveValue(ConfigOptions::hideMainWindowDuringScreenshotString(), enabled);
}

bool Config::allowResizingRectSelection() const
{
	return loadValue(ConfigOptions::allowResizingRectSelectionString(), false).toBool();
}

void Config::setAllowResizingRectSelection(bool enabled)
{
	if (allowResizingRectSelection() == enabled) {
		return;
	}
	saveValue(ConfigOptions::allowResizingRectSelectionString(), enabled);
}

bool Config::showSnippingAreaInfoText() const
{
	return loadValue(ConfigOptions::showSnippingAreaInfoTextString(), true).toBool();
}

void Config::setShowSnippingAreaInfoText(bool enabled)
{
	if (showSnippingAreaInfoText() == enabled) {
		return;
	}
	saveValue(ConfigOptions::showSnippingAreaInfoTextString(), enabled);
}

bool Config::snippingAreaOffsetEnable() const
{
	return loadValue(ConfigOptions::snippingAreaOffsetEnableString(), false).toBool();
}

void Config::setSnippingAreaOffsetEnable(bool enabled)
{
	if (snippingAreaOffsetEnable() == enabled) {
		return;
	}
	saveValue(ConfigOptions::snippingAreaOffsetEnableString(), enabled);

	emit snippingAreaChangedChanged();
}

QPointF Config::snippingAreaOffset() const
{
	return loadValue(ConfigOptions::snippingAreaOffsetString(), QPointF(0, 0)).value<QPointF>();
}

void Config::setSnippingAreaOffset(const QPointF &offset)
{
	if (snippingAreaOffset() == offset) {
		return;
	}
	saveValue(ConfigOptions::snippingAreaOffsetString(), offset);

	emit snippingAreaChangedChanged();
}

int Config::implicitCaptureDelay() const
{
	return loadValue(ConfigOptions::implicitCaptureDelayString(), 200).value<int>();
}

void Config::setImplicitCaptureDelay(int delay)
{
	if (implicitCaptureDelay() == delay) {
		return;
	}
	saveValue(ConfigOptions::implicitCaptureDelayString(), delay);

	emit delayChanged();
}

SaveQualityMode Config::saveQualityMode() const
{
	return loadValue(ConfigOptions::saveQualityModeString(), (int)SaveQualityMode::Default).value<SaveQualityMode>();
}

void Config::setSaveQualityMode(SaveQualityMode mode)
{
	if (saveQualityMode() == mode) {
		return;
	}

	saveValue(ConfigOptions::saveQualityModeString(), static_cast<int>(mode));
}

int Config::saveQualityFactor() const
{
	return loadValue(ConfigOptions::saveQualityFactorString(), 50).toInt();
}

void Config::setSaveQualityFactor(int factor)
{
	if (saveQualityFactor() == factor) {
		return;
	}

	saveValue(ConfigOptions::saveQualityFactorString(), factor);
}

bool Config::isDebugEnabled() const
{
	return loadValue(ConfigOptions::isDebugEnabledString(), false).toBool();
}

void Config::setIsDebugEnabled(bool enabled)
{
	if (isDebugEnabled() == enabled) {
		return;
	}

	saveValue(ConfigOptions::isDebugEnabledString(), enabled);
}

QString Config::tempDirectory() const
{
    return loadValue(ConfigOptions::tempDirectoryString(), QDir::tempPath()).toString();
}

void Config::setTempDirectory(const QString& path)
{
    if (tempDirectory() == path) {
        return;
    }
    saveValue(ConfigOptions::tempDirectoryString(), path);
}

// Annotator

bool Config::rememberToolSelection() const
{
	return loadValue(ConfigOptions::rememberToolSelectionString(), true).toBool();
}

void Config::setRememberToolSelection(bool enabled)
{
	if (rememberToolSelection() == enabled) {
		return;
	}
	saveValue(ConfigOptions::rememberToolSelectionString(), enabled);
}

bool Config::switchToSelectToolAfterDrawingItem() const
{
	return loadValue(ConfigOptions::switchToSelectToolAfterDrawingItemString(), false).toBool();
}

void Config::setSwitchToSelectToolAfterDrawingItem(bool enabled)
{
	if (switchToSelectToolAfterDrawingItem() == enabled) {
		return;
	}
	saveValue(ConfigOptions::switchToSelectToolAfterDrawingItemString(), enabled);
	emit annotatorConfigChanged();
}

bool Config::selectItemAfterDrawing() const
{
	return loadValue(ConfigOptions::selectItemAfterDrawingString(), true).toBool();
}

void Config::setSelectItemAfterDrawing(bool enabled)
{
	if (selectItemAfterDrawing() == enabled) {
		return;
	}
	saveValue(ConfigOptions::selectItemAfterDrawingString(), enabled);
	emit annotatorConfigChanged();
}

bool Config::numberToolSeedChangeUpdatesAllItems() const
{
	return loadValue(ConfigOptions::numberToolSeedChangeUpdatesAllItemsString(), true).toBool();
}

void Config::setNumberToolSeedChangeUpdatesAllItems(bool enabled)
{
	if (numberToolSeedChangeUpdatesAllItems() == enabled) {
		return;
	}
	saveValue(ConfigOptions::numberToolSeedChangeUpdatesAllItemsString(), enabled);
	emit annotatorConfigChanged();
}

bool Config::smoothPathEnabled() const
{
	return loadValue(ConfigOptions::smoothPathEnabledString(), true).toBool();
}

void Config::setSmoothPathEnabled(bool  enabled)
{
	if (smoothPathEnabled() == enabled) {
		return;
	}

	saveValue(ConfigOptions::smoothPathEnabledString(), enabled);
	emit annotatorConfigChanged();
}

int Config::smoothFactor() const
{
	return loadValue(ConfigOptions::smoothPathFactorString(), 7).toInt();
}

void Config::setSmoothFactor(int  factor)
{
	if (smoothFactor() == factor) {
		return;
	}

	saveValue(ConfigOptions::smoothPathFactorString(), factor);
	emit annotatorConfigChanged();
}

bool Config::rotateWatermarkEnabled() const
{
	return loadValue(ConfigOptions::rotateWatermarkEnabledString(), true).toBool();
}

void Config::setRotateWatermarkEnabled(bool enabled)
{
	if (rotateWatermarkEnabled() == enabled) {
		return;
	}

	saveValue(ConfigOptions::rotateWatermarkEnabledString(), enabled);
}

QStringList Config::stickerPaths() const
{
	return loadValue(ConfigOptions::stickerPathsString(), QVariant::fromValue(QStringList())).value<QStringList>();
}

void Config::setStickerPaths(const QStringList &paths)
{
	if (stickerPaths() == paths) {
		return;
	}

	saveValue(ConfigOptions::stickerPathsString(), QVariant::fromValue(paths));
	emit annotatorConfigChanged();
}

bool Config::useDefaultSticker() const
{
	return loadValue(ConfigOptions::useDefaultStickerString(), true).toBool();
}

void Config::setUseDefaultSticker(bool enabled)
{
	if (useDefaultSticker() == enabled) {
		return;
	}

	saveValue(ConfigOptions::useDefaultStickerString(), enabled);
	emit annotatorConfigChanged();
}

QColor Config::canvasColor() const
{
	return loadValue(ConfigOptions::canvasColorString(), QColor(Qt::white)).value<QColor>();
}

void Config::setCanvasColor(const QColor &color)
{
	if (canvasColor() == color) {
		return;
	}

	saveValue(ConfigOptions::canvasColorString(), color);
	emit annotatorConfigChanged();
}

bool Config::isControlsWidgetVisible() const
{
	return loadValue(ConfigOptions::isControlsWidgetVisibleString(), false).toBool();
}

void Config::setIsControlsWidgetVisible(bool isVisible)
{
	if (isControlsWidgetVisible() == isVisible) {
		return;
	}

	saveValue(ConfigOptions::isControlsWidgetVisibleString(), isVisible);
	emit annotatorConfigChanged();
}

// Image Grabber

bool Config::isFreezeImageWhileSnippingEnabledReadOnly() const
{
	return false;
}

bool Config::freezeImageWhileSnippingEnabled() const
{
	return loadValue(ConfigOptions::freezeImageWhileSnippingEnabledString(), true).toBool();
}

void Config::setFreezeImageWhileSnippingEnabled(bool enabled)
{
	if (freezeImageWhileSnippingEnabled() == enabled) {
		return;
	}
	saveValue(ConfigOptions::freezeImageWhileSnippingEnabledString(), enabled);
}

bool Config::captureCursor() const
{
	return loadValue(ConfigOptions::captureCursorString(), true).toBool();
}

void Config::setCaptureCursor(bool  enabled)
{
	if (captureCursor() == enabled) {
		return;
	}
	saveValue(ConfigOptions::captureCursorString(), enabled);
}

bool Config::snippingAreaRulersEnabled() const
{
	return loadValue(ConfigOptions::snippingAreaRulersEnabledString(), true).toBool();
}

void Config::setSnippingAreaRulersEnabled(bool enabled)
{
	if (snippingAreaRulersEnabled() == enabled) {
		return;
	}
	saveValue(ConfigOptions::snippingAreaRulersEnabledString(), enabled);
}

bool Config::snippingAreaPositionAndSizeInfoEnabled() const
{
	return loadValue(ConfigOptions::snippingAreaPositionAndSizeInfoEnabledString(), true).toBool();
}

void Config::setSnippingAreaPositionAndSizeInfoEnabled(bool enabled)
{
	if (snippingAreaPositionAndSizeInfoEnabled() == enabled) {
		return;
	}
	saveValue(ConfigOptions::snippingAreaPositionAndSizeInfoEnabledString(), enabled);
}

bool Config::showMainWindowAfterTakingScreenshotEnabled() const
{
	return loadValue(ConfigOptions::showMainWindowAfterTakingScreenshotEnabledString(), true).toBool();
}

void Config::setShowMainWindowAfterTakingScreenshotEnabled(bool enabled)
{
	if (showMainWindowAfterTakingScreenshotEnabled() == enabled) {
		return;
	}
	saveValue(ConfigOptions::showMainWindowAfterTakingScreenshotEnabledString(), enabled);
}

bool Config::isSnippingAreaMagnifyingGlassEnabledReadOnly() const
{
	return false;
}

bool Config::snippingAreaMagnifyingGlassEnabled() const
{
	return loadValue(ConfigOptions::snippingAreaMagnifyingGlassEnabledString(), true).toBool();
}

void Config::setSnippingAreaMagnifyingGlassEnabled(bool enabled)
{
	if (snippingAreaMagnifyingGlassEnabled() == enabled) {
		return;
	}
	saveValue(ConfigOptions::snippingAreaMagnifyingGlassEnabledString(), enabled);
}

int Config::captureDelay() const
{
	return loadValue(ConfigOptions::captureDelayString(), 0).toInt();
}

void Config::setCaptureDelay(int delay)
{
	if (captureDelay() == delay) {
		return;
	}
	saveValue(ConfigOptions::captureDelayString(), delay);
}

int Config::snippingCursorSize() const
{
	return loadValue(ConfigOptions::snippingCursorSizeString(), 1).toInt();
}

void Config::setSnippingCursorSize(int size)
{
	if (snippingCursorSize() == size) {
		return;
	}
	saveValue(ConfigOptions::snippingCursorSizeString(), size);
}

QColor Config::snippingCursorColor() const
{
	auto defaultColor = QColor(27, 20, 77);
	return loadValue(ConfigOptions::snippingCursorColorString(), defaultColor).value<QColor>();
}

void Config::setSnippingCursorColor(const QColor& color)
{
	if (snippingCursorColor() == color) {
		return;
	}
	saveValue(ConfigOptions::snippingCursorColorString(), color);
}

QColor Config::snippingAdornerColor() const
{
	return loadValue(ConfigOptions::snippingAdornerColorString(), QColor(Qt::red)).value<QColor>();
}

void Config::setSnippingAdornerColor(const QColor& color)
{
	if (snippingAdornerColor() == color) {
		return;
	}
	saveValue(ConfigOptions::snippingAdornerColorString(), color);
}

int Config::snippingAreaTransparency() const
{
	return loadValue(ConfigOptions::snippingAreaTransparencyString(), 150).value<int>();
}

void Config::setSnippingAreaTransparency(int transparency)
{
	if (snippingAreaTransparency() == transparency) {
		return;
	}
	saveValue(ConfigOptions::snippingAreaTransparencyString(), transparency);
}

QRect Config::lastRectArea() const
{
	return loadValue(ConfigOptions::lastRectAreaString(), QRect()).value<QRect>();
}

void Config::setLastRectArea(const QRect &rectArea)
{
	if (lastRectArea() == rectArea) {
		return;
	}
	saveValue(ConfigOptions::lastRectAreaString(), rectArea);
}

bool Config::isForceGenericWaylandEnabledReadOnly() const
{
	return true;
}

bool Config::forceGenericWaylandEnabled() const
{
	return loadValue(ConfigOptions::forceGenericWaylandEnabledString(), false).toBool();
}

void Config::setForceGenericWaylandEnabled(bool enabled)
{
	if (forceGenericWaylandEnabled() == enabled) {
		return;
	}
	saveValue(ConfigOptions::forceGenericWaylandEnabledString(), enabled);
}

bool Config::isScaleGenericWaylandScreenshotEnabledReadOnly() const
{
	return true;
}

bool Config::scaleGenericWaylandScreenshotsEnabled() const
{
	return loadValue(ConfigOptions::scaleWaylandScreenshotsEnabledString(), false).toBool();
}

void Config::setScaleGenericWaylandScreenshots(bool enabled)
{
	if (scaleGenericWaylandScreenshotsEnabled() == enabled) {
		return;
	}
	saveValue(ConfigOptions::scaleWaylandScreenshotsEnabledString(), enabled);
}

// Uploader

bool Config::confirmBeforeUpload() const
{
	return loadValue(ConfigOptions::confirmBeforeUploadString(), true).toBool();
}

void Config::setConfirmBeforeUpload(bool enabled)
{
	if (confirmBeforeUpload() == enabled) {
		return;
	}
	saveValue(ConfigOptions::confirmBeforeUploadString(), enabled);
}

UploaderType Config::uploaderType() const
{
	return loadValue(ConfigOptions::uploaderTypeString(), static_cast<int>(UploaderType::Imgur)).value<UploaderType >();
}

void Config::setUploaderType(UploaderType type)
{
	if (uploaderType() == type) {
		return;
	}
	saveValue(ConfigOptions::uploaderTypeString(), static_cast<int>(type));
}

// Imgur Uploader

QString Config::imgurUsername() const
{
	auto defaultUsername = QLatin1String("");
	return loadValue(ConfigOptions::imgurUsernameString(), defaultUsername).toString();
}

void Config::setImgurUsername(const QString& username)
{
	if (imgurUsername() == username) {
		return;
	}
	saveValue(ConfigOptions::imgurUsernameString(), username);
}

QByteArray Config::imgurClientId() const
{
	auto defaultClientId = QLatin1String("");
	return loadValue(ConfigOptions::imgurClientIdString(), defaultClientId).toByteArray();
}

void Config::setImgurClientId(const QString& clientId)
{
	if (imgurClientId() == clientId) {
		return;
	}
	saveValue(ConfigOptions::imgurClientIdString(), clientId);
}

QByteArray Config::imgurClientSecret() const
{
	auto defaultClientSecret = QLatin1String("");
	return loadValue(ConfigOptions::imgurClientSecretString(), defaultClientSecret).toByteArray();
}

void Config::setImgurClientSecret(const QString& clientSecret)
{
	if (imgurClientSecret() == clientSecret) {
		return;
	}
	saveValue(ConfigOptions::imgurClientSecretString(), clientSecret);
}

QByteArray Config::imgurAccessToken() const
{
	auto defaultAccessToken = QLatin1String("");
	return loadValue(ConfigOptions::imgurAccessTokenString(), defaultAccessToken).toByteArray();
}

void Config::setImgurAccessToken(const QString& accessToken)
{
	if (imgurAccessToken() == accessToken) {
		return;
	}
	saveValue(ConfigOptions::imgurAccessTokenString(), accessToken);
}

QByteArray Config::imgurRefreshToken() const
{
	auto defaultRefreshToken = QLatin1String("");
	return loadValue(ConfigOptions::imgurRefreshTokenString(), defaultRefreshToken).toByteArray();
}

void Config::setImgurRefreshToken(const QString& refreshToken)
{
	if (imgurRefreshToken() == refreshToken) {
		return;
	}
	saveValue(ConfigOptions::imgurRefreshTokenString(), refreshToken);
}

bool Config::imgurForceAnonymous() const
{
	return loadValue(ConfigOptions::imgurForceAnonymousString(), false).toBool();
}

void Config::setImgurForceAnonymous(bool  enabled)
{
	if (imgurForceAnonymous() == enabled) {
		return;
	}
	saveValue(ConfigOptions::imgurForceAnonymousString(), enabled);
}

bool Config::imgurLinkDirectlyToImage() const
{
	return loadValue(ConfigOptions::imgurLinkDirectlyToImageString(), false).toBool();
}

void Config::setImgurLinkDirectlyToImage(bool  enabled)
{
	if (imgurLinkDirectlyToImage() == enabled) {
		return;
	}
	saveValue(ConfigOptions::imgurLinkDirectlyToImageString(), enabled);
}

bool Config::imgurAlwaysCopyToClipboard() const
{
	return loadValue(ConfigOptions::imgurAlwaysCopyToClipboardString(), false).toBool();
}

void Config::setImgurAlwaysCopyToClipboard(bool  enabled)
{
	if (imgurAlwaysCopyToClipboard() == enabled) {
		return;
	}
	saveValue(ConfigOptions::imgurAlwaysCopyToClipboardString(), enabled);
}

bool Config::imgurOpenLinkInBrowser() const
{
	return loadValue(ConfigOptions::imgurOpenLinkInBrowserString(), true).toBool();
}

void Config::setImgurOpenLinkInBrowser(bool enabled)
{
	if (imgurOpenLinkInBrowser() == enabled) {
		return;
	}
	saveValue(ConfigOptions::imgurOpenLinkInBrowserString(), enabled);
}

QString Config::imgurUploadTitle() const
{
	return loadValue(ConfigOptions::imgurUploadTitleString(), DefaultValues::ImgurUploadTitle).toString();
}

void Config::setImgurUploadTitle(const QString &uploadTitle)
{
	if (imgurUploadTitle() == uploadTitle) {
		return;
	}
	saveValue(ConfigOptions::imgurUploadTitleString(), uploadTitle);
}

QString Config::imgurUploadDescription() const
{
	return loadValue(ConfigOptions::imgurUploadDescriptionString(), DefaultValues::ImgurUploadDescription).toString();
}

void Config::setImgurUploadDescription(const QString &uploadDescription)
{
	if (imgurUploadDescription() == uploadDescription) {
		return;
	}
	saveValue(ConfigOptions::imgurUploadDescriptionString(), uploadDescription);
}

QString Config::imgurBaseUrl() const
{
	return loadValue(ConfigOptions::imgurBaseUrlString(), DefaultValues::ImgurBaseUrl).toString();
}

void Config::setImgurBaseUrl(const QString &baseUrl)
{
	if (imgurBaseUrl() == baseUrl) {
		return;
	}
	saveValue(ConfigOptions::imgurBaseUrlString(), baseUrl);
}

// Script Uploader

QString Config::uploadScriptPath() const
{
	return loadValue(ConfigOptions::uploadScriptPathString(), QString()).toString();
}

void Config::setUploadScriptPath(const QString &path)
{
	if (uploadScriptPath() == path) {
		return;
	}
	saveValue(ConfigOptions::uploadScriptPathString(), path);
}

bool Config::uploadScriptCopyOutputToClipboard() const
{
	return loadValue(ConfigOptions::uploadScriptCopyOutputToClipboardString(), false).toBool();
}

void Config::setUploadScriptCopyOutputToClipboard(bool enabled)
{
	if (uploadScriptCopyOutputToClipboard() == enabled) {
		return;
	}
	saveValue(ConfigOptions::uploadScriptCopyOutputToClipboardString(), enabled);
}

QString Config::uploadScriptCopyOutputFilter() const
{
	return loadValue(ConfigOptions::uploadScriptCopyOutputFilterString(), QString()).toString();
}

void Config::setUploadScriptCopyOutputFilter(const QString &regex)
{
	if (uploadScriptCopyOutputFilter() == regex) {
		return;
	}
	saveValue(ConfigOptions::uploadScriptCopyOutputFilterString(), regex);
}

bool Config::uploadScriptStopOnStdErr() const
{
	return loadValue(ConfigOptions::uploadScriptStopOnStdErrString(), true).toBool();
}

void Config::setUploadScriptStopOnStdErr(bool enabled)
{
	if (uploadScriptStopOnStdErr() == enabled) {
		return;
	}
	saveValue(ConfigOptions::uploadScriptStopOnStdErrString(), enabled);
}

// FTP Uploader

bool Config::ftpUploadForceAnonymous() const
{
	return loadValue(ConfigOptions::ftpUploadForceAnonymousString(), false).toBool();
}

void Config::setFtpUploadForceAnonymous(bool enabled)
{
	if (ftpUploadForceAnonymous() == enabled) {
		return;
	}
	saveValue(ConfigOptions::ftpUploadForceAnonymousString(), enabled);
}

QString Config::ftpUploadUrl() const
{
	return loadValue(ConfigOptions::ftpUploadUrlString(), QString()).toString();
}

void Config::setFtpUploadUrl(const QString &path)
{
	if (ftpUploadUrl() == path) {
		return;
	}
	saveValue(ConfigOptions::ftpUploadUrlString(), path);
}

QString Config::ftpUploadUsername() const
{
	return loadValue(ConfigOptions::ftpUploadUsernameString(), QString()).toString();
}

void Config::setFtpUploadUsername(const QString &username)
{
	if (ftpUploadUsername() == username) {
		return;
	}
	saveValue(ConfigOptions::ftpUploadUsernameString(), username);
}

QString Config::ftpUploadPassword() const
{
	return loadValue(ConfigOptions::ftpUploadPasswordString(), QString()).toString();
}

void Config::setFtpUploadPassword(const QString &password)
{
	if (ftpUploadPassword() == password) {
		return;
	}
	saveValue(ConfigOptions::ftpUploadPasswordString(), password);
}

// HotKeys

bool Config::isGlobalHotKeysEnabledReadOnly() const
{
	return false;
}

bool Config::globalHotKeysEnabled() const
{
	return loadValue(ConfigOptions::globalHotKeysEnabledString(), true).toBool();
}

void Config::setGlobalHotKeysEnabled(bool enabled)
{
	if (globalHotKeysEnabled() == enabled) {
		return;
	}
	saveValue(ConfigOptions::globalHotKeysEnabledString(), enabled);
	emit hotKeysChanged();
}

QKeySequence Config::rectAreaHotKey() const
{
	return loadValue(ConfigOptions::rectAreaHotKeyString(), QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_R)).value<QKeySequence>();
}

void Config::setRectAreaHotKey(const QKeySequence &keySequence)
{
	if (rectAreaHotKey() == keySequence) {
		return;
	}
	saveValue(ConfigOptions::rectAreaHotKeyString(), keySequence);
	emit hotKeysChanged();
}


QKeySequence Config::lastRectAreaHotKey() const
{
	return loadValue(ConfigOptions::lastRectAreaHotKeyString(), QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_L)).value<QKeySequence>();
}

void Config::setLastRectAreaHotKey(const QKeySequence &keySequence)
{
	if (lastRectAreaHotKey() == keySequence) {
		return;
	}
	saveValue(ConfigOptions::lastRectAreaHotKeyString(), keySequence);
	emit hotKeysChanged();
}

QKeySequence Config::fullScreenHotKey() const
{
	return loadValue(ConfigOptions::fullScreenHotKeyString(), QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_F)).value<QKeySequence>();
}

void Config::setFullScreenHotKey(const QKeySequence &keySequence)
{
	if (fullScreenHotKey() == keySequence) {
		return;
	}
	saveValue(ConfigOptions::fullScreenHotKeyString(), keySequence);
	emit hotKeysChanged();
}

QKeySequence Config::currentScreenHotKey() const
{
	return loadValue(ConfigOptions::currentScreenHotKeyString(), QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_C)).value<QKeySequence>();
}

void Config::setCurrentScreenHotKey(const QKeySequence &keySequence)
{
	if (currentScreenHotKey() == keySequence) {
		return;
	}
	saveValue(ConfigOptions::currentScreenHotKeyString(), keySequence);
	emit hotKeysChanged();
}

QKeySequence Config::activeWindowHotKey() const
{
	return loadValue(ConfigOptions::activeWindowHotKeyString(), QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_A)).value<QKeySequence>();
}

void Config::setActiveWindowHotKey(const QKeySequence &keySequence)
{
	if (activeWindowHotKey() == keySequence) {
		return;
	}
	saveValue(ConfigOptions::activeWindowHotKeyString(), keySequence);
	emit hotKeysChanged();
}

QKeySequence Config::windowUnderCursorHotKey() const
{
	return loadValue(ConfigOptions::windowUnderCursorHotKeyString(), QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_U)).value<QKeySequence>();
}

void Config::setWindowUnderCursorHotKey(const QKeySequence &keySequence)
{
	if (windowUnderCursorHotKey() == keySequence) {
		return;
	}
	saveValue(ConfigOptions::windowUnderCursorHotKeyString(), keySequence);
	emit hotKeysChanged();
}

QKeySequence Config::portalHotKey() const
{
	return loadValue(ConfigOptions::portalHotKeyString(), QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_T)).value<QKeySequence>();
}

void Config::setPortalHotKey(const QKeySequence &keySequence)
{
	if (portalHotKey() == keySequence) {
		return;
	}
	saveValue(ConfigOptions::portalHotKeyString(), keySequence);
	emit hotKeysChanged();
}

// Actions

QList<Action> Config::actions()
{
	QList<Action> actions;
	auto count = mConfig.beginReadArray(ConfigOptions::actionsString());
	for (auto index = 0; index < count; index++) {
		mConfig.setArrayIndex(index);
		Action action;
		action.setName(mConfig.value(ConfigOptions::actionNameString()).toString());
		action.setShortcut(mConfig.value(ConfigOptions::actionShortcutString()).value<QKeySequence>());
		action.setIsGlobalShortcut(mConfig.value(ConfigOptions::actionShortcutIsGlobalString(), true).value<bool>());
		action.setIsCaptureEnabled(mConfig.value(ConfigOptions::actionIsCaptureEnabledString()).toBool());
		action.setIncludeCursor(mConfig.value(ConfigOptions::actionIncludeCursorString()).toBool());
		action.setCaptureDelay(mConfig.value(ConfigOptions::actionCaptureDelayString()).toInt());
		action.setCaptureMode(mConfig.value(ConfigOptions::actionCaptureModeString()).value<CaptureModes>());
		action.setIsPinImageEnabled(mConfig.value(ConfigOptions::actionIsPinImageEnabledString()).toBool());
		action.setIsUploadEnabled(mConfig.value(ConfigOptions::actionIsUploadEnabledString()).toBool());
		action.setIsOpenDirectoryEnabled(mConfig.value(ConfigOptions::actionIsOpenDirectoryEnabledString()).toBool());
		action.setIsCopyToClipboardEnabled(mConfig.value(ConfigOptions::actionIsCopyToClipboardEnabledString()).toBool());
		action.setIsSaveEnabled(mConfig.value(ConfigOptions::actionIsSaveEnabledString()).toBool());
		action.setIsHideMainWindowEnabled(mConfig.value(ConfigOptions::actionIsHideMainWindowEnabledString()).toBool());
		actions.append(action);
	}
	mConfig.endArray();
	return actions;
}

void Config::setActions(const QList<Action> &actions)
{
	auto savedActions = this->actions();

	if(savedActions == actions) {
		return;
	}

	mConfig.remove(ConfigOptions::actionsString());

	auto count = actions.count();
	mConfig.beginWriteArray(ConfigOptions::actionsString());
	for (auto index = 0; index < count; ++index) {
		const auto& action = actions.at(index);
		mConfig.setArrayIndex(index);
		mConfig.setValue(ConfigOptions::actionNameString(), action.name());
		mConfig.setValue(ConfigOptions::actionShortcutString(), action.shortcut());
		mConfig.setValue(ConfigOptions::actionShortcutIsGlobalString(), action.isGlobalShortcut());
		mConfig.setValue(ConfigOptions::actionIsCaptureEnabledString(), action.isCaptureEnabled());
		mConfig.setValue(ConfigOptions::actionIncludeCursorString(), action.includeCursor());
		mConfig.setValue(ConfigOptions::actionCaptureDelayString(), action.captureDelay());
		mConfig.setValue(ConfigOptions::actionCaptureModeString(), static_cast<int>(action.captureMode()));
		mConfig.setValue(ConfigOptions::actionIsPinImageEnabledString(), action.isPinImageEnabled());
		mConfig.setValue(ConfigOptions::actionIsUploadEnabledString(), action.isUploadEnabled());
		mConfig.setValue(ConfigOptions::actionIsOpenDirectoryEnabledString(), action.isOpenDirectoryEnabled());
		mConfig.setValue(ConfigOptions::actionIsCopyToClipboardEnabledString(), action.isCopyToClipboardEnabled());
		mConfig.setValue(ConfigOptions::actionIsSaveEnabledString(), action.isSaveEnabled());
		mConfig.setValue(ConfigOptions::actionIsHideMainWindowEnabledString(), action.isHideMainWindowEnabled());
	}
	mConfig.endArray();

	emit actionsChanged();
	emit hotKeysChanged();
}

QString Config::pluginPath() const
{
	return loadValue(ConfigOptions::pluginPathString()).toString();
}

void Config::setPluginPath(const QString &path)
{
	if (pluginPath() == path) {
		return;
	}
	saveValue(ConfigOptions::pluginPathString(), path);
}

QList<PluginInfo> Config::pluginInfos()
{
	QList<PluginInfo> pluginInfos;
	auto count = mConfig.beginReadArray(ConfigOptions::pluginInfosString());
	for (auto index = 0; index < count; index++) {
		mConfig.setArrayIndex(index);
		auto path = mConfig.value(ConfigOptions::pluginInfoPathString()).toString();
		auto type = mConfig.value(ConfigOptions::pluginInfoTypeString()).value<PluginType>();
		auto version = mConfig.value(ConfigOptions::pluginInfoVersionString()).toString();
		PluginInfo pluginInfo(type, version, path);
		pluginInfos.append(pluginInfo);
	}
	mConfig.endArray();
	return pluginInfos;
}

void Config::setPluginInfos(const QList<PluginInfo> &pluginInfos)
{
	auto savedPluginInfos = this->pluginInfos();
	if(savedPluginInfos == pluginInfos) {
		return;
	}

	mConfig.remove(ConfigOptions::pluginInfosString());

	auto count = pluginInfos.count();
	mConfig.beginWriteArray(ConfigOptions::pluginInfosString());
	for (auto index = 0; index < count; ++index) {
		const auto& pluginInfo = pluginInfos.at(index);
		mConfig.setArrayIndex(index);
		mConfig.setValue(ConfigOptions::pluginInfoPathString(), pluginInfo.path());
		mConfig.setValue(ConfigOptions::pluginInfoTypeString(), static_cast<int>(pluginInfo.type()));
		mConfig.setValue(ConfigOptions::pluginInfoVersionString(), pluginInfo.version());
	}
	mConfig.endArray();
	emit pluginsChanged();
}

bool Config::customPluginSearchPathEnabled() const
{
	return loadValue(ConfigOptions::customPluginSearchPathEnabledString(), false).toBool();
}

void Config::setCustomPluginSearchPathEnabled(bool enabled)
{
	if (customPluginSearchPathEnabled() == enabled) {
		return;
	}
	saveValue(ConfigOptions::customPluginSearchPathEnabledString(), enabled);
}

// Misc

void Config::saveValue(const QString &key, const QVariant &value)
{
	mConfig.setValue(key, value);
	mConfig.sync();
}

QVariant Config::loadValue(const QString &key, const QVariant &defaultValue) const
{
	return mConfig.value(key, defaultValue);
}
