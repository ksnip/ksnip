/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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
 */

#ifndef KSNIP_ENUMTRANSLATOR_H
#define KSNIP_ENUMTRANSLATOR_H

#include <QObject>
#include <QMap>

#include "src/common/enum/CaptureModes.h"
#include "src/common/enum/UploadStatus.h"
#include "src/common/enum/PluginType.h"

class EnumTranslator : public QObject
{
Q_OBJECT
public:
	static EnumTranslator *instance();

	QString toTranslatedString(CaptureModes captureMode) const;
	QString toString(UploadStatus uploadStatus) const;
	QString toString(PluginType pluginType) const;

private:
	QMap<CaptureModes, QString> mCaptureModeMap;
	QMap<UploadStatus, QString> mUploadStatusMap;
	QMap<PluginType, QString> mPluginTypeMap;

	EnumTranslator();
	void mapCaptureModeEnum();
	void mapUploadStatusEnum();
	void mapPluginTypeEnum();
};

#endif //KSNIP_ENUMTRANSLATOR_H
