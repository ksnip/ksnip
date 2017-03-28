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
#include <iostream>

KsnipConfig::KsnipConfig(QObject* parent) : QObject(parent)
{

}

//
// Public Functions
//

KsnipConfig* KsnipConfig::instance()
{
    static KsnipConfig instance;
    return &instance;
}

// Application

bool KsnipConfig::saveKsnipPosition() const
{
    return mConfig.value("Application/SaveKsnipPosition", true).toBool();
}

void KsnipConfig::setSaveKsnipPosition(const bool& enabled)
{
    if (saveKsnipPosition() == enabled) {
        return;
    }
    mConfig.setValue("Application/SaveKsnipPosition", enabled);
    mConfig.sync();
}

bool KsnipConfig::promptSaveBeforeExit() const
{
    return mConfig.value("Application/PromptSaveBeforeExit", false).toBool();
}

void KsnipConfig::setPromptSaveBeforeExit(const bool& enabled)
{
    if (promptSaveBeforeExit() == enabled) {
        return;
    }
    mConfig.setValue("Application/PromptSaveBeforeExit", enabled);
    mConfig.sync();
}

bool KsnipConfig::alwaysCopyToClipboard() const
{
    return mConfig.value("Application/AlwaysCopyToClipboard", false).toBool();
}

void KsnipConfig::setAlwaysCopyToClipboard(const bool& enabled)
{
    if (alwaysCopyToClipboard() == enabled) {
        return;
    }
    mConfig.setValue("Application/AlwaysCopyToClipboard", enabled);
    mConfig.sync();
}

bool KsnipConfig::saveKsnipToolSelection() const
{
    return mConfig.value("Application/SaveKsnipToolsSelection", true).toBool();
}

void KsnipConfig::setSaveKsnipToolSelection(const bool& enabled)
{
    if (saveKsnipToolSelection() == enabled) {
        return;
    }
    mConfig.setValue("Application/SaveKsnipToolsSelection", enabled);
    mConfig.sync();
}

QPoint KsnipConfig::windowPosition() const
{
    // If we are not saving the position we return the default and ignore what
    // has been save earlier
    if (!saveKsnipPosition()) {
        return QPoint(200, 200);
    }

    return mConfig.value("MainWindow/Position", QPoint(200, 200)).value<QPoint>();
}

void KsnipConfig::setWindowPosition(const QPoint& position)
{
    if (windowPosition() == position) {
        return;
    }
    mConfig.setValue("MainWindow/Position", position);
    mConfig.sync();
}

PaintArea::PaintMode KsnipConfig::paintMode() const
{
    // If we are not storing the tool selection, always return the pen as default
    if (!saveKsnipToolSelection()) {
        return PaintArea::Pen;
    }

    return PaintArea::PaintMode(mConfig.value("Painter/PaintMode").toInt());
}

void KsnipConfig::setPaintMode(const PaintArea::PaintMode& mode)
{
    if (paintMode() == mode) {
        return;
    }
    mConfig.setValue("Painter/PaintMode", mode);
    mConfig.sync();
}

ImageGrabber::CaptureMode KsnipConfig::captureMode() const
{
    // If we are not storing the tool selection, always return the rect area as default
    if (!saveKsnipToolSelection()) {
        return ImageGrabber::RectArea;
    }

    switch (mConfig.value("ImageGrabber/CaptureMode").toInt()) {
    case ImageGrabber::ActiveWindow:
        return ImageGrabber::ActiveWindow;

    case ImageGrabber::CurrentScreen:
        return ImageGrabber::CurrentScreen;

    case ImageGrabber::FullScreen:
        return ImageGrabber::FullScreen;

    default:
        return ImageGrabber::RectArea;
    }
}

void KsnipConfig::setCaptureMode(const ImageGrabber::CaptureMode& mode)
{
    if (captureMode() == mode) {
        return;
    }
    mConfig.setValue("ImageGrabber/CaptureMode", mode);
    mConfig.sync();
}

QString KsnipConfig::saveDirectory() const
{
    if (!mConfig.value("Application/SaveDirectory", QDir::homePath()).toString().isEmpty()) {
        return mConfig.value("Application/SaveDirectory", QDir::homePath()).toString() + "/";
    } else {
        return QString();
    }
}

void KsnipConfig::setSaveDirectory(const QString& path)
{
    if (saveDirectory() == path) {
        return;
    }
    mConfig.setValue("Application/SaveDirectory", path);
    mConfig.sync();
}

QString KsnipConfig::saveFilename() const
{
    return mConfig.value("Application/SaveFilename", "ksnip_$Y$M$D$").toString();
}

void KsnipConfig::setSaveFilename(const QString& filename)
{
    if (saveFilename() == filename) {
        return;
    }
    mConfig.setValue("Application/SaveFilename", filename);
    mConfig.sync();
}

QString KsnipConfig::saveFormat() const
{
    if (!mConfig.value("Application/SaveFormat", "png").toString().isEmpty()) {
        return "." + mConfig.value("Application/SaveFormat", "png").toString();
    } else {
        return QString();
    }
}

void KsnipConfig::setSaveFormat(const QString& format)
{
    if (saveFormat() == format) {
        return;
    }
    mConfig.setValue("Application/SaveFormat", format);
    mConfig.sync();
}

// Painter

QPen KsnipConfig::pen() const
{
    QPen pen;
    pen.setColor(penColor());
    pen.setWidth(penSize());
    return pen;
}

QColor KsnipConfig::penColor() const
{
    return mConfig.value("Painter/PenColor", QColor("Red")).value<QColor>();
}

void KsnipConfig::setPenColor(const QColor& color)
{
    if (penColor() == color) {
        return;
    }
    mConfig.setValue("Painter/PenColor", color);
    mConfig.sync();
    emit painterUpdated();
}

int KsnipConfig::penSize() const
{
    return mConfig.value("Painter/PenSize", 3).toInt();
}

void KsnipConfig::setPenSize(const int& size)
{
    if (penSize() == size) {
        return;
    }
    mConfig.setValue("Painter/PenSize", size);
    mConfig.sync();
    emit painterUpdated();
}

QPen KsnipConfig::marker() const
{
    QPen marker;
    marker.setColor(markerColor());
    marker.setWidth(markerSize());
    return marker;
}

QColor KsnipConfig::markerColor() const
{
    return mConfig.value("Painter/MarkerColor", QColor("Yellow")).value<QColor>();
}

void KsnipConfig::setMarkerColor(const QColor& color)
{
    if (markerColor() == color) {
        return;
    }
    mConfig.setValue("Painter/MarkerColor", color);
    mConfig.sync();
    emit painterUpdated();
}

int KsnipConfig::markerSize() const
{
    return mConfig.value("Painter/MarkerSize", 20).toInt();
}

void KsnipConfig::setMarkerSize(const int& size)
{
    if (markerSize() == size) {
        return;
    }
    mConfig.setValue("Painter/MarkerSize", size);
    mConfig.sync();
    emit painterUpdated();
}

QPen KsnipConfig::rect() const
{
    QPen rect;
    rect.setColor(rectColor());
    rect.setWidth(rectSize());
    return rect;
}

QColor KsnipConfig::rectColor() const
{
    return mConfig.value("Painter/RectColor", QColor("Blue")).value<QColor>();
}

void KsnipConfig::setRectColor(const QColor& color)
{
    if (rectColor() == color) {
        return;
    }
    mConfig.setValue("Painter/RectColor", color);
    mConfig.sync();
    emit painterUpdated();
}

int KsnipConfig::rectSize() const
{
    return mConfig.value("Painter/RectSize", 3).toInt();
}

void KsnipConfig::setRectSize(const int& size)
{
    if (rectSize() == size) {
        return;
    }
    mConfig.setValue("Painter/RectSize", size);
    mConfig.sync();
    emit painterUpdated();
}

bool KsnipConfig::rectFill() const
{
    return mConfig.value("Painter/RectFill", false).toBool();
}

void KsnipConfig::setRectFill(const bool& fill)
{
    if (rectFill() == fill) {
        return;
    }
    mConfig.setValue("Painter/RectFill", fill);
    mConfig.sync();
    emit painterUpdated();
}

QPen KsnipConfig::ellipse() const
{
    QPen ellipse;
    ellipse.setColor(ellipseColor());
    ellipse.setWidth(ellipseSize());
    return ellipse;
}

QColor KsnipConfig::ellipseColor() const
{
    return mConfig.value("Painter/EllipseColor", QColor("Blue")).value<QColor>();
}

void KsnipConfig::setEllipseColor(const QColor& color)
{
    if (ellipseColor() == color) {
        return;
    }
    mConfig.setValue("Painter/EllipseColor", color);
    mConfig.sync();
    emit painterUpdated();
}

int KsnipConfig::ellipseSize() const
{
    return mConfig.value("Painter/EllipseSize", 3).toInt();
}

void KsnipConfig::setEllipseSize(const int& size)
{
    if (ellipseSize() == size) {
        return;
    }
    mConfig.setValue("Painter/EllipseSize", size);
    mConfig.sync();
    emit painterUpdated();
}

bool KsnipConfig::ellipseFill() const
{
    return mConfig.value("Painter/EllipseFill", false).toBool();
}

void KsnipConfig::setEllipseFill(const bool& fill)
{
    if (ellipseFill() == fill) {
        return;
    }
    mConfig.setValue("Painter/EllipseFill", fill);
    mConfig.sync();
    emit painterUpdated();
}

QPen KsnipConfig::text() const
{
    QPen text;
    text.setColor(textColor());
    text.setWidth(textSize());
    return text;
}

QColor KsnipConfig::textColor() const
{
    return mConfig.value("Painter/TextColor", QColor("Black")).value<QColor>();
}

void KsnipConfig::setTextColor(const QColor& color)
{
    if (textColor() == color) {
        return;
    }
    mConfig.setValue("Painter/TextColor", color);
    mConfig.sync();
    emit painterUpdated();
}

int KsnipConfig::textSize() const
{
    return textFont().pointSize();
}

void KsnipConfig::setTextSize(const int& size)
{
    if (textSize() == size) {
        return;
    }
    QFont font = textFont();
    font.setPointSize(size);

    mConfig.setValue("Painter/TextFont", font);
    mConfig.sync();
    emit painterUpdated();
}

bool KsnipConfig::textBold() const
{
    return textFont().bold();
}

void KsnipConfig::setTextBold(const bool& bold)
{
    if (textBold() == bold) {
        return;
    }
    QFont font = textFont();
    font.setBold(bold);

    mConfig.setValue("Painter/TextFont", font);
    mConfig.sync();
    emit painterUpdated();
}

bool KsnipConfig::textItalic() const
{
    return textFont().italic();
}

void KsnipConfig::setTextItalic(const bool& italic)
{
    if (textItalic() == italic) {
        return;
    }
    QFont font = textFont();
    font.setItalic(italic);

    mConfig.setValue("Painter/TextFont", font);
    mConfig.sync();
    emit painterUpdated();
}

bool KsnipConfig::textUnderline() const
{
    return textFont().underline();
}

void KsnipConfig::setTextUnderline(const bool& underline)
{
    if (textUnderline() == underline) {
        return;
    }
    QFont font = textFont();
    font.setUnderline(underline);

    mConfig.setValue("Painter/TextFont", font);
    mConfig.sync();
    emit painterUpdated();
}

QFont KsnipConfig::textFont() const
{
    return mConfig.value("Painter/TextFont", QFont("Arial", 12)).value<QFont>();
}

void KsnipConfig::setTextFont(const QFont& font)
{
    if (textFont().family() == font.family()) {
        return;
    }
    QFont tmpfont = textFont();
    tmpfont.setFamily(font.family());

    mConfig.setValue("Painter/TextFont", tmpfont);
    mConfig.sync();
    emit painterUpdated();
}

int KsnipConfig::eraseSize() const
{
    return mConfig.value("Painter/EraseSize", 5).toInt();
}

void KsnipConfig::setEraseSize(const int& size)
{
    if (eraseSize() == size) {
        return;
    }
    mConfig.setValue("Painter/EraseSize", size);
    mConfig.sync();
    emit painterUpdated();
}

bool KsnipConfig::smoothPath() const
{
    return mConfig.value("Painter/SmoothPath", true).toBool();
}

void KsnipConfig::setSmoothPath(const bool& enabled)
{
    if (smoothPath() == enabled) {
        return;
    }

    mConfig.setValue("Painter/SmoothPath", enabled);
    mConfig.sync();
}

int KsnipConfig::smoothFactor() const
{
    return mConfig.value("Painter/SmoothPathFactor", 7).toInt();
}

void KsnipConfig::setSmoothFactor(const int& factor)
{
    if (smoothFactor() == factor) {
        return;
    }

    mConfig.setValue("Painter/SmoothPathFactor", factor);
    mConfig.sync();
}

// Image Grabber

bool KsnipConfig::captureMouse() const
{
    return mConfig.value("ImageGrabber/CaptureMouse", false).toBool();
}

void KsnipConfig::setCaptureMouse(bool enabled)
{
    if (captureMouse() == enabled) {
        return;
    }
    mConfig.setValue("ImageGrabber/CaptureMouse", enabled);
    mConfig.sync();
}

int KsnipConfig::captureDelay() const
{
    return mConfig.value("ImageGrabber/CaptureDelay", 300).toInt() ;
}

void KsnipConfig::setCaptureDelay(int delay)
{
    if (captureDelay() == delay) {
        return;
    }
    mConfig.setValue("ImageGrabber/CaptureDelay", delay);
    mConfig.sync();
    emit captureDelayUpdated(delay);
}

// Imgur Uploader

QString KsnipConfig::imgurUsername() const
{
    return mConfig.value("Imgur/Username", "").toString();
}

void KsnipConfig::setImgurUsername(QString username)
{
    if (imgurUsername() == username) {
        return;
    }
    mConfig.setValue("Imgur/Username", username);
    mConfig.sync();
}

QByteArray KsnipConfig::imgurClientId() const
{
    return mConfig.value("Imgur/ClientId", "").toByteArray();
}

void KsnipConfig::setImgurClientId(QString clientId)
{
    if (imgurClientId() == clientId) {
        return;
    }
    mConfig.setValue("Imgur/ClientId", clientId);
    mConfig.sync();
}

QByteArray KsnipConfig::imgurClientSecret() const
{
    return mConfig.value("Imgur/ClientSecret", "").toByteArray();
}

void KsnipConfig::setImgurClientSecret(QString clientSecret)
{
    if (imgurClientSecret() == clientSecret) {
        return;
    }
    mConfig.setValue("Imgur/ClientSecret", clientSecret);
    mConfig.sync();
}

QByteArray KsnipConfig::imgurAccessToken() const
{
    return mConfig.value("Imgur/AccessToken", "").toByteArray();
}

void KsnipConfig::setImgurAccessToken(QString accessToken)
{
    if (imgurAccessToken() == accessToken) {
        return;
    }
    mConfig.setValue("Imgur/AccessToken", accessToken);
    mConfig.sync();
}

QByteArray KsnipConfig::imgurRefreshToken() const
{
    return mConfig.value("Imgur/RefreshToken", "").toByteArray();
}

void KsnipConfig::setImgurRefreshToken(QString refreshToken)
{
    if (imgurRefreshToken() == refreshToken) {
        return;
    }
    mConfig.setValue("Imgur/RefreshToken", refreshToken);
    mConfig.sync();
}

bool KsnipConfig::imgurForceAnonymous() const
{
    return mConfig.value("Imgur/ForceAnonymous", false).toBool();
}

void KsnipConfig::setImgurForceAnonymous(bool enabled)
{
    if (imgurForceAnonymous() == enabled) {
        return;
    }
    mConfig.setValue("Imgur/ForceAnonymous", enabled);
    mConfig.sync();
}

bool KsnipConfig::imgurOpenLinkDirectlyToImage() const
{
    return mConfig.value("Imgur/OpenLinkDirectlyToImage", false).toBool();
}

void KsnipConfig::setImgurOpenLinkDirectlyToImage(bool enabled)
{
    if (imgurOpenLinkDirectlyToImage() == enabled) {
        return;
    }
    mConfig.setValue("Imgur/OpenLinkDirectlyToImage", enabled);
    mConfig.sync();
}

bool KsnipConfig::imgurAlwaysCopyToClipboard() const
{
    return mConfig.value("Imgur/AlwaysCopyToClipboard", false).toBool();
}

void KsnipConfig::setImgurAlwaysCopyToClipboard(bool enabled)
{
    if (imgurAlwaysCopyToClipboard() == enabled) {
        return;
    }
    mConfig.setValue("Imgur/AlwaysCopyToClipboard", enabled);
    mConfig.sync();
}
