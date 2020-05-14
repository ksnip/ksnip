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

#ifndef KSNIP_SINGLEINSTANCEPARAMETERTRANSLATOR_H
#define KSNIP_SINGLEINSTANCEPARAMETERTRANSLATOR_H

#include <QString>
#include <QList>

#include "src/bootstrapper/singleInstance/SingleInstanceParameter.h"
#include "src/common/enum/RunMode.h"

class SingleInstanceParameterTranslator
{
public:
	SingleInstanceParameterTranslator() = default;
	~SingleInstanceParameterTranslator() = default;

	QByteArray translate(const SingleInstanceParameter &parameter) const;
	SingleInstanceParameter translate(const QByteArray &byteArray) const;

private:
	QByteArray getStartParameter() const;
	QByteArray getEditParameters(const QString &path) const;
	QByteArray getCaptureParameters(CaptureModes captureModes, bool save, bool captureCursor, int delay) const;
	QByteArray getSeparator() const;
	QByteArray getPathParameter(const QString &path) const;
	QByteArray getCaptureModeParameter(const CaptureModes &captureModes) const;
	QByteArray getSaveParameter(bool save) const;
	QByteArray getBooleanString(bool value) const;
	QByteArray getCaptureCursorParameter(bool captureCursor) const;
	QByteArray getDelayParameter(int delay) const;
	QByteArray getEditParameter() const;
	QByteArray getCaptureParameter() const;
	CaptureModes getCaptureMode(const QByteArray &captureMode) const;
	bool getBoolean(const QByteArray &value) const;
};


#endif //KSNIP_SINGLEINSTANCEPARAMETERTRANSLATOR_H
