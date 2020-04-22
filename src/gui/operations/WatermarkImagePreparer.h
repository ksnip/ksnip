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

#ifndef KSNIP_WATERMARKIMAGEPREPARER_H
#define KSNIP_WATERMARKIMAGEPREPARER_H

#include <QPainter>

class WatermarkImagePreparer
{
public:
	explicit WatermarkImagePreparer();
	~WatermarkImagePreparer() = default;
	QPixmap prepare(const QPixmap &image, const QSize &availableSpace, bool rotated) const;

private:
	qreal mOpacity;

	QPixmap getPreparedWatermarkImage(const QPixmap &watermarkImage, bool rotated) const;
	QPixmap &fitWatermarkIntoCapture(QPixmap &finishedWatermarkImage, const QSize &availableSpace) const;
	QPixmap getRotatedImage(const QPixmap &watermarkImage) const;
};

#endif //KSNIP_WATERMARKIMAGEPREPARER_H
