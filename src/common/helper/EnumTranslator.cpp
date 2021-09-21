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

#include "EnumTranslator.h"

EnumTranslator *EnumTranslator::instance()
{
	static EnumTranslator instance;
	return &instance;
}

QString EnumTranslator::toTranslatedString(CaptureModes captureMode) const
{
	Q_ASSERT(mCaptureModeMap.contains(captureMode));
	return mCaptureModeMap.value(captureMode);
}

QString EnumTranslator::toString(UploadStatus uploadStatus) const
{
	Q_ASSERT(mUploadStatusMap.contains(uploadStatus));
	return mUploadStatusMap.value(uploadStatus);
}

EnumTranslator::EnumTranslator()
{
	mapCaptureModeEnum();
	mapUploadStatusEnum();
}

void EnumTranslator::mapUploadStatusEnum()
{
	mUploadStatusMap[UploadStatus::NoError] = QLatin1String("No Error");
	mUploadStatusMap[UploadStatus::ConnectionError] = QLatin1String("Connection Error");
	mUploadStatusMap[UploadStatus::PermissionError] = QLatin1String("Permission Error");
	mUploadStatusMap[UploadStatus::TimedOut] = QLatin1String("Timed Out");
	mUploadStatusMap[UploadStatus::Crashed] = QLatin1String("Crashed");
	mUploadStatusMap[UploadStatus::FailedToStart] = QLatin1String("Failed To Start");
	mUploadStatusMap[UploadStatus::ReadError] = QLatin1String("Read Error");
	mUploadStatusMap[UploadStatus::ScriptWroteToStdErr] = QLatin1String("Script Wrote To StdErr");
	mUploadStatusMap[UploadStatus::UnableToSaveTemporaryImage] = QLatin1String("Unable To Save Temporary Image");
	mUploadStatusMap[UploadStatus::UnknownError] = QLatin1String("Unknown Error");
	mUploadStatusMap[UploadStatus::WebError] = QLatin1String("Web Error");
	mUploadStatusMap[UploadStatus::WriteError] = QLatin1String("Write Error");
}

void EnumTranslator::mapCaptureModeEnum()
{
	mCaptureModeMap[CaptureModes::RectArea] = tr("Rectangular Area");
	mCaptureModeMap[CaptureModes::LastRectArea] = tr("Last Rectangular Area");
	mCaptureModeMap[CaptureModes::FullScreen] = tr("Full Screen (All Monitors)");
	mCaptureModeMap[CaptureModes::CurrentScreen] = tr("Current Screen");
	mCaptureModeMap[CaptureModes::ActiveWindow] = tr("Active Window");
	mCaptureModeMap[CaptureModes::WindowUnderCursor] = tr("Window Under Cursor");
	mCaptureModeMap[CaptureModes::Portal] = tr("Screenshot Portal");
}
