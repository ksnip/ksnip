/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "SingleInstanceParameterTranslator.h"

QByteArray SingleInstanceParameterTranslator::translate(const SingleInstanceParameter &parameter) const
{
	switch (parameter.startupMode) {
		case SingleInstanceStartupModes::Edit:
            if(parameter.isImageAsByteArraySet()) {
                return getEditImageParameters(parameter.imageAsByteArray);
            } else {
                return getEditPathParameters(parameter.imagePath);
            }
		case SingleInstanceStartupModes::Capture:
			return getCaptureParameters(parameter.captureMode, parameter.save, parameter.savePath, parameter.captureCursor, parameter.delay);
		default:
			return getStartParameter();
	}
}

SingleInstanceParameter SingleInstanceParameterTranslator::translate(const QByteArray &byteArray) const
{
	auto parameters = byteArray.split(getSeparator()[0]);

	if(parameters.empty()) {
		qCritical("Startup mode must be provided.");
		return {};
	}

	auto startupMode = parameters[0];
	if (startupMode == getEditPathParameter() && parameters.count() == 2) {
        auto pathToImage = QString(parameters[1]);
        return SingleInstanceParameter(pathToImage);
    } else if (startupMode == getEditImageParameter() && parameters.count() == 2) {
        auto imageAsByteArray = QByteArray::fromBase64(parameters[1]);
        return SingleInstanceParameter(imageAsByteArray);
	} else if (startupMode == getCaptureParameter() && parameters.count() == 6){
		auto captureMode = getCaptureMode(parameters[1]);
		auto save = getBoolean(parameters[2]);
		auto savePath = getPathParameter(parameters[3]);
		auto captureCursor = getBoolean(parameters[4]);
		auto delay = parameters[5].toInt();
		return SingleInstanceParameter(captureMode, save, savePath, captureCursor, delay);
	} else {
		return {};
	}
}

CaptureModes SingleInstanceParameterTranslator::getCaptureMode(const QByteArray &captureMode)
{
	if (captureMode == QByteArray("rectArea")) {
		return CaptureModes::RectArea;
	} else if (captureMode == QByteArray("lastRectArea")) {
		return CaptureModes::LastRectArea;
	} else if (captureMode == QByteArray("fullScreen")) {
		return CaptureModes::FullScreen;
	} else if (captureMode == QByteArray("currentScreen")) {
		return CaptureModes::CurrentScreen;
	} else if (captureMode == QByteArray("activeWindow")) {
		return CaptureModes::ActiveWindow;
	} else if (captureMode == QByteArray("portal")) {
        return CaptureModes::Portal;
    } else {
		return CaptureModes::WindowUnderCursor;
	}
}

QByteArray SingleInstanceParameterTranslator::getStartParameter()
{
	return {"start"};
}

QByteArray SingleInstanceParameterTranslator::getEditPathParameters(const QString &path)
{
	return getEditPathParameter() + getSeparator() + getPathParameter(path);
}

QByteArray SingleInstanceParameterTranslator::getEditImageParameters(const QByteArray &image)
{
    return getEditImageParameter() + getSeparator() + image;
}

QByteArray SingleInstanceParameterTranslator::getEditPathParameter()
{ 
	return {"edit-path"};
}

QByteArray SingleInstanceParameterTranslator::getEditImageParameter()
{
    return {"edit-image"};
}

QByteArray SingleInstanceParameterTranslator::getCaptureParameters(CaptureModes captureModes, bool save, const QString &savePath, bool captureCursor, int delay)
{
	return getCaptureParameter() +
		getSeparator() + getCaptureModeParameter(captureModes) +
		getSeparator() + getBooleanString(save) +
		getSeparator() + getPathParameter(savePath) +
		getSeparator() + getCaptureCursorParameter(captureCursor) +
		getSeparator() + getDelayParameter(delay);
}

QByteArray SingleInstanceParameterTranslator::getCaptureParameter()
{ 
	return {"capture"};
}

QByteArray SingleInstanceParameterTranslator::getCaptureModeParameter(const CaptureModes &captureModes)
{
	switch (captureModes) {
		case CaptureModes::LastRectArea:
			return {"lastRectArea"};
		case CaptureModes::FullScreen:
			return {"fullScreen"};
		case CaptureModes::CurrentScreen:
			return {"currentScreen"};
		case CaptureModes::ActiveWindow:
			return {"activeWindow"};
		case CaptureModes::WindowUnderCursor:
			return {"windowUnderCursor"};
        case CaptureModes::Portal:
            return {"portal"};
		default:
			return {"rectArea"};
	}
}

QByteArray SingleInstanceParameterTranslator::getSeparator()
{
	return {";"};
}

QByteArray SingleInstanceParameterTranslator::getPathParameter(const QString &path)
{
	return path.toLatin1();
}

QByteArray SingleInstanceParameterTranslator::getBooleanString(bool value)
{
	return value ? QByteArray("true") : QByteArray("false");
}

QByteArray SingleInstanceParameterTranslator::getCaptureCursorParameter(bool captureCursor)
{
	return getBooleanString(captureCursor);
}

QByteArray SingleInstanceParameterTranslator::getDelayParameter(int delay)
{
	return QString::number(delay).toLatin1();
}

bool SingleInstanceParameterTranslator::getBoolean(const QByteArray &value)
{
	return value == QByteArray("true");
}

