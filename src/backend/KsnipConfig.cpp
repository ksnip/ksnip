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

bool KsnipConfig::saveKsnipPosition() const
{
    return mConfig.value(QStringLiteral("Application/SaveKsnipPosition"), true).toBool();
}

void KsnipConfig::setSaveKsnipPosition(bool  enabled)
{
    if (saveKsnipPosition() == enabled) {
        return;
    }
    mConfig.setValue(QStringLiteral("Application/SaveKsnipPosition"), enabled);
    mConfig.sync();
}

bool KsnipConfig::promptSaveBeforeExit() const
{
    return mConfig.value(QStringLiteral("Application/PromptSaveBeforeExit"), false).toBool();
}

void KsnipConfig::setPromptSaveBeforeExit(bool  enabled)
{
    if (promptSaveBeforeExit() == enabled) {
        return;
    }
    mConfig.setValue(QStringLiteral("Application/PromptSaveBeforeExit"), enabled);
    mConfig.sync();
}

bool KsnipConfig::alwaysCopyToClipboard() const
{
    return mConfig.value(QStringLiteral("Application/AlwaysCopyToClipboard"), false).toBool();
}

void KsnipConfig::setAlwaysCopyToClipboard(bool  enabled)
{
    if (alwaysCopyToClipboard() == enabled) {
        return;
    }
    mConfig.setValue(QStringLiteral("Application/AlwaysCopyToClipboard"), enabled);
    mConfig.sync();
}

bool KsnipConfig::saveKsnipToolSelection() const
{
    return mConfig.value(QStringLiteral("Application/SaveKsnipToolsSelection"), true).toBool();
}

void KsnipConfig::setSaveKsnipToolSelection(bool  enabled)
{
    if (saveKsnipToolSelection() == enabled) {
        return;
    }
    mConfig.setValue(QStringLiteral("Application/SaveKsnipToolsSelection"), enabled);
    mConfig.sync();
}

bool KsnipConfig::captureOnStartup() const
{
    return mConfig.value(QStringLiteral("Application/CaptureOnStartup"), false).toBool();
}

void KsnipConfig::setCaptureOnStartup(bool enabled)
{
    if (captureOnStartup() == enabled) {
        return;
    }
    mConfig.setValue(QStringLiteral("Application/CaptureOnStartup"), enabled);
    mConfig.sync();
}

QPoint KsnipConfig::windowPosition() const
{
    // If we are not saving the position we return the default and ignore what
    // has been save earlier
    if (!saveKsnipPosition()) {
        return QPoint(200, 200);
    }

    return mConfig.value(QStringLiteral("MainWindow/Position"), QPoint(200, 200)).value<QPoint>();
}

void KsnipConfig::setWindowPosition(const QPoint& position)
{
    if (windowPosition() == position) {
        return;
    }
    mConfig.setValue(QStringLiteral("MainWindow/Position"), position);
    mConfig.sync();
}

PaintMode KsnipConfig::paintMode() const
{
    // If we are not storing the tool selection, always return the pen as default
    if (!saveKsnipToolSelection()) {
        return PaintMode::Pen;
    }

    return PaintMode(mConfig.value(QStringLiteral("Painter/PaintMode")).toInt());
}

void KsnipConfig::setPaintMode(PaintMode mode)
{
    if (paintMode() == mode) {
        return;
    }
    mConfig.setValue(QStringLiteral("Painter/PaintMode"), static_cast<int>(mode));
    mConfig.sync();
}

CaptureModes KsnipConfig::captureMode() const
{
    // If we are not storing the tool selection, always return the rect area as default
    if (!saveKsnipToolSelection()) {
        return CaptureModes::RectArea;
    }

    auto modeEnumAsInt = mConfig.value(QStringLiteral("ImageGrabber/CaptureMode")).toInt();
    return static_cast<CaptureModes>(modeEnumAsInt);
}

void KsnipConfig::setCaptureMode(CaptureModes mode)
{
    if (captureMode() == mode) {
        return;
    }
    mConfig.setValue(QStringLiteral("ImageGrabber/CaptureMode"), static_cast<int>(mode));
    mConfig.sync();
}

QString KsnipConfig::saveDirectory() const
{
    if (!mConfig.value(QStringLiteral("Application/SaveDirectory"), QDir::homePath()).toString().isEmpty()) {
        return mConfig.value(QStringLiteral("Application/SaveDirectory"), QDir::homePath()).toString() + QStringLiteral("/");
    } else {
        return QString();
    }
}

void KsnipConfig::setSaveDirectory(const QString& path)
{
    if (saveDirectory() == path) {
        return;
    }
    mConfig.setValue(QStringLiteral("Application/SaveDirectory"), path);
    mConfig.sync();
}

QString KsnipConfig::saveFilename() const
{
    return mConfig.value(QStringLiteral("Application/SaveFilename"), QStringLiteral("ksnip_$Y$M$D-$T")).toString();
}

void KsnipConfig::setSaveFilename(const QString& filename)
{
    if (saveFilename() == filename) {
        return;
    }
    mConfig.setValue(QStringLiteral("Application/SaveFilename"), filename);
    mConfig.sync();
}

QString KsnipConfig::saveFormat() const
{
    if (!mConfig.value(QStringLiteral("Application/SaveFormat"), QStringLiteral("png")).toString().isEmpty()) {
        return QStringLiteral(".") + mConfig.value(QStringLiteral("Application/SaveFormat"), QStringLiteral("png")).toString();
    } else {
        return QString();
    }
}

void KsnipConfig::setSaveFormat(const QString& format)
{
    if (saveFormat() == format) {
        return;
    }
    mConfig.setValue(QStringLiteral("Application/SaveFormat"), format);
    mConfig.sync();
}

bool KsnipConfig::useInstantSave() const
{
    return mConfig.value(QStringLiteral("Application/UseInstantSave"), false).toBool();
}

void KsnipConfig::setUseInstantSave(const bool enabled)
{
    if (useInstantSave() == enabled) {
        return;
    }
    mConfig.setValue(QStringLiteral("Application/UseInstantSave"), enabled);
    mConfig.sync();
}

/*
 * Returns fully formatted save path ready to use. Custom format can be provided
 * to replace the configured format, if not format provided, teh default will be
 * used.
 */
QString KsnipConfig::savePath(const QString& format) const
{
    QString selectedFormat;
    if (format.isNull()) {
        selectedFormat = saveFormat();
    } else {
        selectedFormat = (format.startsWith(QStringLiteral(".")) ? format : QStringLiteral(".") + format);
    }

    auto filename = FilenameFormatter::updateTimeAndDate(saveFilename());
    return FilenameFormatter::makeUniqueFilename(saveDirectory(), filename, selectedFormat);
}

// Painter

int KsnipConfig::toolSize(const PaintMode tool) const
{
    if (tool == PaintMode::Text) {
        return textFont().pointSize();
    }

    return mConfig.value(ConfigNameFormatter::toolSize(tool), 3).value<int>();
}

void KsnipConfig::setToolSize(const PaintMode tool, int size)
{
    if (toolSize(tool) == size) {
        return;
    }

    if (tool == PaintMode::Text) {
        auto font = textFont();
        font.setPointSize(size);
        mConfig.setValue(QStringLiteral("Painter/TextFont"), font);
    } else {
        mConfig.setValue(ConfigNameFormatter::toolSize(tool), size);
    }
    mConfig.sync();
    emit painterUpdated();
}

QColor KsnipConfig::toolColor(const PaintMode tool) const
{
    return mConfig.value(ConfigNameFormatter::toolColor(tool), QColor(Qt::red)).value<QColor>();
}

void KsnipConfig::setToolColor(const PaintMode tool, const QColor &color)
{
    if (toolColor(tool) == color) {
        return;
    }

    mConfig.setValue(ConfigNameFormatter::toolColor(tool), color);
    mConfig.sync();
    emit painterUpdated();
}

bool KsnipConfig::toolFill(PaintMode tool) const
{
    return mConfig.value(ConfigNameFormatter::toolFill(tool), false).value<bool>();
}

void KsnipConfig::setToolFill(PaintMode tool, bool enabled)
{
    if (toolFill(tool) == enabled) {
        return;
    }

    mConfig.setValue(ConfigNameFormatter::toolFill(tool), enabled);
    mConfig.sync();
    emit painterUpdated();
}

QPen KsnipConfig::toolProperties(PaintMode tool) const
{
    QPen pen;
    pen.setColor(toolColor(tool));
    pen.setWidth(toolSize(tool));
    return pen;
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

    mConfig.setValue(QStringLiteral("Painter/TextFont"), font);
    mConfig.sync();
    emit painterUpdated();
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

    mConfig.setValue(QStringLiteral("Painter/TextFont"), font);
    mConfig.sync();
    emit painterUpdated();
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

    mConfig.setValue(QStringLiteral("Painter/TextFont"), font);
    mConfig.sync();
    emit painterUpdated();
}

QFont KsnipConfig::textFont() const
{
    return mConfig.value(QStringLiteral("Painter/TextFont"), QFont(QStringLiteral("Arial"), 12)).value<QFont>();
}

void KsnipConfig::setTextFont(const QFont& font)
{
    if (textFont().family() == font.family()) {
        return;
    }
    auto tmpFont = textFont();
    tmpFont.setFamily(font.family());

    mConfig.setValue(QStringLiteral("Painter/TextFont"), tmpFont);
    mConfig.sync();
    emit painterUpdated();
}

QFont KsnipConfig::numberFont() const
{
    return mConfig.value(QStringLiteral("Painter/NumberFont"), QFont(QStringLiteral("Comic Sans MS"), 30, QFont::Bold)).value<QFont>();
}

void KsnipConfig::setNumberFont(const QFont& font)
{
    if (numberFont().family() == font.family()) {
        return;
    }
    auto tmpFont = numberFont();
    tmpFont.setFamily(font.family());
    tmpFont.setBold(true);

    mConfig.setValue(QStringLiteral("Painter/NumberFont"), tmpFont);
    mConfig.sync();
    emit painterUpdated();
}

bool KsnipConfig::itemShadowEnabled() const
{
    return mConfig.value(QStringLiteral("Painter/ItemShadowEnabled"), true).toBool();
}

void KsnipConfig::setItemShadowEnabled(bool enabled)
{
    if (itemShadowEnabled() == enabled) {
        return;
    }

    mConfig.setValue(QStringLiteral("Painter/ItemShadowEnabled"), enabled);
    mConfig.sync();
}

bool KsnipConfig::smoothPathEnabled() const
{
    return mConfig.value(QStringLiteral("Painter/SmoothPathEnabled"), true).toBool();
}

void KsnipConfig::setSmoothPathEnabled(bool  enabled)
{
    if (smoothPathEnabled() == enabled) {
        return;
    }

    mConfig.setValue(QStringLiteral("Painter/SmoothPathEnabled"), enabled);
    mConfig.sync();
}

int KsnipConfig::smoothFactor() const
{
    return mConfig.value(QStringLiteral("Painter/SmoothPathFactor"), 7).toInt();
}

void KsnipConfig::setSmoothFactor(int  factor)
{
    if (smoothFactor() == factor) {
        return;
    }

    mConfig.setValue(QStringLiteral("Painter/SmoothPathFactor"), factor);
    mConfig.sync();
}

bool KsnipConfig::dynamicCursorSizeEnabled() const
{
    return mConfig.value(QStringLiteral("Painter/DynamicCursorSize"), true).toBool();
}

void KsnipConfig::setDynamicCursorSizeEnabled(bool enabled)
{
    if (dynamicCursorSizeEnabled() == enabled) {
        return;
    }

    mConfig.setValue(QStringLiteral("Painter/DynamicCursorSize"), enabled);
    mConfig.sync();
}

// Image Grabber

bool KsnipConfig::captureCursor() const
{
    return mConfig.value(QStringLiteral("ImageGrabber/CaptureCursor"), true).toBool();
}

void KsnipConfig::setCaptureCursor(bool  enabled)
{
    if (captureCursor() == enabled) {
        return;
    }
    mConfig.setValue(QStringLiteral("ImageGrabber/CaptureCursor"), enabled);
    mConfig.sync();
}

bool KsnipConfig::cursorRulerEnabled() const
{
    return mConfig.value(QStringLiteral("ImageGrabber/CursorRulerEnabled"), true).toBool();
}

void KsnipConfig::setCursorRulerEnabled(bool enabled)
{
    if (cursorRulerEnabled() == enabled) {
        return;
    }
    mConfig.setValue(QStringLiteral("ImageGrabber/CursorRulerEnabled"), enabled);
    mConfig.sync();
}

bool KsnipConfig::cursorInfoEnabled() const
{
    return mConfig.value(QStringLiteral("ImageGrabber/CursorInfoEnabled"), true).toBool();
}

void KsnipConfig::setCursorInfoEnabled(bool enabled)
{
    if (cursorInfoEnabled() == enabled) {
        return;
    }
    mConfig.setValue(QStringLiteral("ImageGrabber/CursorInfoEnabled"), enabled);
    mConfig.sync();
}

int KsnipConfig::captureDelay() const
{
    return mConfig.value(QStringLiteral("ImageGrabber/CaptureDelay"), 0).toInt();
}

void KsnipConfig::setCaptureDelay(int delay)
{
    if (captureDelay() == delay) {
        return;
    }
    mConfig.setValue(QStringLiteral("ImageGrabber/CaptureDelay"), delay);
    mConfig.sync();
}

int KsnipConfig::snippingCursorSize() const
{
    return mConfig.value(QStringLiteral("ImageGrabber/SnippingCursorSize"), 1).toInt();
}

void KsnipConfig::setSnippingCursorSize(int size)
{
    if (snippingCursorSize() == size) {
        return;
    }
    mConfig.setValue(QStringLiteral("ImageGrabber/SnippingCursorSize"), size);
    mConfig.sync();
}

QColor KsnipConfig::snippingCursorColor() const
{
    return mConfig.value(QStringLiteral("ImageGrabber/SnippingCursorColor"), QColor(27,20,77)).value<QColor>();
}

void KsnipConfig::setSnippingCursorColor(const QColor& color)
{
    if (snippingCursorColor() == color) {
        return;
    }
    mConfig.setValue(QStringLiteral("ImageGrabber/SnippingCursorColor"), color);
    mConfig.sync();
}

// Imgur Uploader

QString KsnipConfig::imgurUsername() const
{
    return mConfig.value(QStringLiteral("Imgur/Username"), QStringLiteral("")).toString();
}

void KsnipConfig::setImgurUsername(const QString& username)
{
    if (imgurUsername() == username) {
        return;
    }
    mConfig.setValue(QStringLiteral("Imgur/Username"), username);
    mConfig.sync();
}

QByteArray KsnipConfig::imgurClientId() const
{
    return mConfig.value(QStringLiteral("Imgur/ClientId"), QStringLiteral("")).toByteArray();
}

void KsnipConfig::setImgurClientId(const QString& clientId)
{
    if (imgurClientId() == clientId) {
        return;
    }
    mConfig.setValue(QStringLiteral("Imgur/ClientId"), clientId);
    mConfig.sync();
}

QByteArray KsnipConfig::imgurClientSecret() const
{
    return mConfig.value(QStringLiteral("Imgur/ClientSecret"), QStringLiteral("")).toByteArray();
}

void KsnipConfig::setImgurClientSecret(const QString& clientSecret)
{
    if (imgurClientSecret() == clientSecret) {
        return;
    }
    mConfig.setValue(QStringLiteral("Imgur/ClientSecret"), clientSecret);
    mConfig.sync();
}

QByteArray KsnipConfig::imgurAccessToken() const
{
    return mConfig.value(QStringLiteral("Imgur/AccessToken"), QStringLiteral("")).toByteArray();
}

void KsnipConfig::setImgurAccessToken(const QString& accessToken)
{
    if (imgurAccessToken() == accessToken) {
        return;
    }
    mConfig.setValue(QStringLiteral("Imgur/AccessToken"), accessToken);
    mConfig.sync();
}

QByteArray KsnipConfig::imgurRefreshToken() const
{
    return mConfig.value(QStringLiteral("Imgur/RefreshToken"), QStringLiteral("")).toByteArray();
}

void KsnipConfig::setImgurRefreshToken(const QString& refreshToken)
{
    if (imgurRefreshToken() == refreshToken) {
        return;
    }
    mConfig.setValue(QStringLiteral("Imgur/RefreshToken"), refreshToken);
    mConfig.sync();
}

bool KsnipConfig::imgurForceAnonymous() const
{
    return mConfig.value(QStringLiteral("Imgur/ForceAnonymous"), false).toBool();
}

void KsnipConfig::setImgurForceAnonymous(bool  enabled)
{
    if (imgurForceAnonymous() == enabled) {
        return;
    }
    mConfig.setValue(QStringLiteral("Imgur/ForceAnonymous"), enabled);
    mConfig.sync();
}

bool KsnipConfig::imgurOpenLinkDirectlyToImage() const
{
    return mConfig.value(QStringLiteral("Imgur/OpenLinkDirectlyToImage"), false).toBool();
}

void KsnipConfig::setImgurOpenLinkDirectlyToImage(bool  enabled)
{
    if (imgurOpenLinkDirectlyToImage() == enabled) {
        return;
    }
    mConfig.setValue(QStringLiteral("Imgur/OpenLinkDirectlyToImage"), enabled);
    mConfig.sync();
}

bool KsnipConfig::imgurAlwaysCopyToClipboard() const
{
    return mConfig.value(QStringLiteral("Imgur/AlwaysCopyToClipboard"), false).toBool();
}

void KsnipConfig::setImgurAlwaysCopyToClipboard(bool  enabled)
{
    if (imgurAlwaysCopyToClipboard() == enabled) {
        return;
    }
    mConfig.setValue(QStringLiteral("Imgur/AlwaysCopyToClipboard"), enabled);
    mConfig.sync();
}

bool KsnipConfig::imgurConfirmBeforeUpload() const
{
    return mConfig.value(QStringLiteral("Imgur/ConfirmBeforeUpload"), true).toBool();
}

void KsnipConfig::setImgurConfirmBeforeUpload(bool enabled)
{
    if (imgurConfirmBeforeUpload() == enabled) {
        return;
    }
    mConfig.setValue(QStringLiteral("Imgur/ConfirmBeforeUpload"), enabled);
    mConfig.sync();
}
