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
			return getEditParameters(parameter.imagePath);
		case SingleInstanceStartupModes::Capture:
			return getCaptureParameters(parameter.captureMode, parameter.save, parameter.captureCursor, parameter.delay);
		default:
			return getStartParameter();
	}
}

SingleInstanceParameter SingleInstanceParameterTranslator::translate(const QByteArray &byteArray) const
{
	auto parameters = byteArray.split(getSeparator()[0]);

	if(parameters.empty()) {
		qCritical("Startup mode must be provided.");
		return SingleInstanceParameter();
	}

	auto startupMode = parameters[0];
	if (startupMode == getEditParameter() && parameters.count() == 2) {
		return SingleInstanceParameter(parameters[1]);
	} else if (startupMode == getCaptureParameter() && parameters.count() == 5){
		auto captureMode = getCaptureMode(parameters[1]);
		auto save = getBoolean(parameters[2]);
		auto captureCursor = getBoolean(parameters[3]);
		auto delay = parameters[4].toInt();
		return SingleInstanceParameter(captureMode, save, captureCursor, delay);
	} else {
		return SingleInstanceParameter();
	}
}

CaptureModes SingleInstanceParameterTranslator::getCaptureMode(const QByteArray &captureMode) const
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

QByteArray SingleInstanceParameterTranslator::getStartParameter() const
{
	return QByteArray("start");
}

QByteArray SingleInstanceParameterTranslator::getEditParameters(const QString &path) const
{
	return getEditParameter() + getSeparator() + getPathParameter(path);
}

QByteArray SingleInstanceParameterTranslator::getEditParameter() const
{ 
	return QByteArray("edit"); 
}

QByteArray SingleInstanceParameterTranslator::getCaptureParameters(CaptureModes captureModes, bool save, bool captureCursor, int delay) const
{
	return getCaptureParameter() +
		getSeparator() + getCaptureModeParameter(captureModes) +
		getSeparator() + getSaveParameter(save) +
		getSeparator() + getCaptureCursorParameter(captureCursor) +
		getSeparator() + getDelayParameter(delay);
}

QByteArray SingleInstanceParameterTranslator::getCaptureParameter() const
{ 
	return QByteArray("capture"); 
}

QByteArray SingleInstanceParameterTranslator::getSaveParameter(bool save) const
{
	return getBooleanString(save);
}

QByteArray SingleInstanceParameterTranslator::getCaptureModeParameter(const CaptureModes &captureModes) const
{
	switch (captureModes) {
		case CaptureModes::LastRectArea:
			return QByteArray("lastRectArea");
		case CaptureModes::FullScreen:
			return QByteArray("fullScreen");
		case CaptureModes::CurrentScreen:
			return QByteArray("currentScreen");
		case CaptureModes::ActiveWindow:
			return QByteArray("activeWindow");
		case CaptureModes::WindowUnderCursor:
			return QByteArray("windowUnderCursor");
        case CaptureModes::Portal:
            return QByteArray("portal");
		default:
			return QByteArray("rectArea");
	}
}

QByteArray SingleInstanceParameterTranslator::getSeparator() const
{
	return QByteArray(";");
}

QByteArray SingleInstanceParameterTranslator::getPathParameter(const QString &path) const
{
	return path.toLatin1();
}

QByteArray SingleInstanceParameterTranslator::getBooleanString(bool value) const
{
	return value ? QByteArray("true") : QByteArray("false");
}

QByteArray SingleInstanceParameterTranslator::getCaptureCursorParameter(bool captureCursor) const
{
	return getBooleanString(captureCursor);
}

QByteArray SingleInstanceParameterTranslator::getDelayParameter(int delay) const
{
	return QString::number(delay).toLatin1();
}

bool SingleInstanceParameterTranslator::getBoolean(const QByteArray &value) const
{
	return value == QByteArray("true");
}

