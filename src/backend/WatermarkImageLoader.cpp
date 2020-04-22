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

#include "WatermarkImageLoader.h"

WatermarkImageLoader::WatermarkImageLoader()
{
	mImageName = QStringLiteral("watermark_image.png");
	mPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
	mImagePath = mPath + QStringLiteral("/") + mImageName;
}

QPixmap WatermarkImageLoader::load() const
{
	return QPixmap(mImagePath);
}

bool WatermarkImageLoader::save(const QPixmap &image) const
{
	if(image.isNull()) {
		return false;
	}

	createPathIfRequired();
	return image.save(mImagePath);
}

void WatermarkImageLoader::createPathIfRequired() const
{
	QDir qdir;
	qdir.mkpath(mPath);
}
