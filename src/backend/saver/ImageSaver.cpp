/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#include "ImageSaver.h"

ImageSaver::ImageSaver() : mConfig(KsnipConfigProvider::instance())
{
}

bool ImageSaver::save(const QImage &image, const QString &path)
{
    ensurePathExists(path);
    auto fullPath = ensureFilenameHasFormat(path);

	auto isSuccessful = image.save(fullPath, nullptr, getSaveQuality());
	if (!isSuccessful) {
		qCritical("Unable to save file '%s'", qPrintable(fullPath));
	}

	return isSuccessful;
}

void ImageSaver::ensurePathExists(const QString &path)
{
	auto directory = PathHelper::extractParentDirectory(path);
	QDir dir(directory);
	if(!dir.exists()) {
		dir.mkpath(QStringLiteral("."));
	}
}

QString ImageSaver::ensureFilenameHasFormat(const QString &path)
{
    auto format = PathHelper::extractFormat(path);
    if(format.isEmpty()) {
        return path + QStringLiteral(".") + mConfig->saveFormat();
    }
    return path;
}

int ImageSaver::getSaveQuality()
{
	auto defaultQualityFactor = -1;
	return mConfig->saveQualityMode() == SaveQualityMode::Default ? defaultQualityFactor : mConfig->saveQualityFactor();
}
