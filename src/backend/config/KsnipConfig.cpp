/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#include "KsnipConfig.h"

KsnipConfig* KsnipConfig::instance()
{
    static KsnipConfig instance;
    return &instance;
}

// Application

bool KsnipConfig::savePosition() const
{
	return loadValue(KsnipConfigOptions::savePositionString(), true).toBool();
}

void KsnipConfig::setSavePosition(bool enabled)
{
	if (savePosition() == enabled) {
        return;
    }
	saveValue(KsnipConfigOptions::savePositionString(), enabled);
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

bool KsnipConfig::alwaysCopyToClipboard() const
{
	return loadValue(KsnipConfigOptions::alwaysCopyToClipboardString(), false).toBool();
}

void KsnipConfig::setAlwaysCopyToClipboard(bool  enabled)
{
    if (alwaysCopyToClipboard() == enabled) {
        return;
    }
	saveValue(KsnipConfigOptions::alwaysCopyToClipboardString(), enabled);
}

bool KsnipConfig::saveToolSelection() const
{
	return loadValue(KsnipConfigOptions::saveToolSelectionString(), true).toBool();
}

void KsnipConfig::setSaveToolSelection(bool enabled)
{
	if (saveToolSelection() == enabled) {
        return;
    }
	saveValue(KsnipConfigOptions::saveToolSelectionString(), enabled);
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
	if (!savePosition()) {
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
	if (!saveToolSelection()) {
        return CaptureModes::RectArea;
    }

	auto modeEnumAsInt = loadValue(KsnipConfigOptions::captureModeString()).toInt();
    return static_cast<CaptureModes>(modeEnumAsInt);
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
	auto saveDirectoryString = loadValue(KsnipConfigOptions::saveDirectoryString(), QDir::homePath()).toString();
	if (!saveDirectoryString.isEmpty()) {
		return saveDirectoryString + QStringLiteral("/");
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
	auto defaultFilename = QStringLiteral("ksnip_$Y$M$D-$T");
	return loadValue(KsnipConfigOptions::saveFilenameString(), defaultFilename).toString();
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
	auto defaultFormat = QStringLiteral("png");
	auto saveFormatString = loadValue(KsnipConfigOptions::saveFormatString(), defaultFormat).toString();
	if (!saveFormatString.isEmpty()) {
		return QStringLiteral(".") + saveFormatString;
    } else {
		return {};
    }
}

void KsnipConfig::setSaveFormat(const QString& format)
{
    if (saveFormat() == format) {
        return;
    }
	saveValue(KsnipConfigOptions::saveFormatString(), format);
}

bool KsnipConfig::useInstantSave() const
{
	return loadValue(KsnipConfigOptions::useInstantSaveString(), false).toBool();
}

void KsnipConfig::setUseInstantSave(const bool enabled)
{
    if (useInstantSave() == enabled) {
        return;
    }
	saveValue(KsnipConfigOptions::useInstantSaveString(), enabled);
}

QString KsnipConfig::applicationStyle() const
{
	auto defaultStyle = QStringLiteral("Fusion");
	return loadValue(KsnipConfigOptions::applicationStyleString(), defaultStyle).toString();
}

void KsnipConfig::setApplicationStyle(QString style)
{
    if (applicationStyle() == style) {
        return;
    }
	saveValue(KsnipConfigOptions::applicationStyleString(), style);
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
    emit painterUpdated();
	emit toolConfigChanged();
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
    emit painterUpdated();
	emit toolConfigChanged();
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
    emit painterUpdated();
	emit toolConfigChanged();
}

QFont KsnipConfig::textFont() const
{
	auto defaultFont = QFont(QStringLiteral("Arial"), 12);
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
    emit painterUpdated();
	emit toolConfigChanged();
}

QFont KsnipConfig::numberFont() const
{
	auto defaultFont = QFont(QStringLiteral("Comic Sans MS"), 30, QFont::Bold);
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
    emit painterUpdated();
	emit toolConfigChanged();
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
	emit toolConfigChanged();
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
	emit toolConfigChanged();
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
	emit toolConfigChanged();
}

// Image Grabber

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

// Imgur Uploader

QString KsnipConfig::imgurUsername() const
{
	auto defaultUsername = QStringLiteral("");
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
	auto defaultClientId = QStringLiteral("");
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
	auto defaultClientSecret = QStringLiteral("");
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
	auto defaultAccessToken = QStringLiteral("");
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
	auto defaultRefreshToken = QStringLiteral("");
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

bool KsnipConfig::imgurOpenLinkDirectlyToImage() const
{
	return loadValue(KsnipConfigOptions::imgurOpenLinkDirectlyToImageString(), false).toBool();
}

void KsnipConfig::setImgurOpenLinkDirectlyToImage(bool  enabled)
{
    if (imgurOpenLinkDirectlyToImage() == enabled) {
        return;
    }
	saveValue(KsnipConfigOptions::imgurOpenLinkDirectlyToImageString(), enabled);
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

bool KsnipConfig::imgurConfirmBeforeUpload() const
{
	return loadValue(KsnipConfigOptions::imgurConfirmBeforeUploadString(), true).toBool();
}

void KsnipConfig::setImgurConfirmBeforeUpload(bool enabled)
{
    if (imgurConfirmBeforeUpload() == enabled) {
        return;
    }
	saveValue(KsnipConfigOptions::imgurConfirmBeforeUploadString(), enabled);
}

void KsnipConfig::saveValue(const QString &key, const QVariant &value)
{
	mConfig.setValue(key, value);
	mConfig.sync();
}

QVariant KsnipConfig::loadValue(const QString &key, const QVariant &defaultValue) const
{
	return mConfig.value(key, defaultValue);
}
