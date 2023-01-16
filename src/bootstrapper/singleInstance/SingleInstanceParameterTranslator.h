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

class SingleInstanceParameterTranslator
{
public:
	SingleInstanceParameterTranslator() = default;
	~SingleInstanceParameterTranslator() = default;

	QByteArray translate(const SingleInstanceParameter &parameter) const;
	SingleInstanceParameter translate(const QByteArray &byteArray) const;

private:
	static QByteArray getStartParameter();
	static QByteArray getEditPathParameters(const QString &path);
	static QByteArray getEditImageParameters(const QByteArray &image);
	static QByteArray getCaptureParameters(CaptureModes captureModes, bool save, const QString &savePath, bool captureCursor, int delay);
	static QByteArray getSeparator();
	static QByteArray getPathParameter(const QString &path);
	static QByteArray getCaptureModeParameter(const CaptureModes &captureModes);
	static QByteArray getBooleanString(bool value);
	static QByteArray getCaptureCursorParameter(bool captureCursor);
	static QByteArray getDelayParameter(int delay);
	static QByteArray getEditPathParameter();
	static QByteArray getEditImageParameter();
	static QByteArray getCaptureParameter();
	static CaptureModes getCaptureMode(const QByteArray &captureMode);
	static bool getBoolean(const QByteArray &value);
};

#endif //KSNIP_SINGLEINSTANCEPARAMETERTRANSLATOR_H
