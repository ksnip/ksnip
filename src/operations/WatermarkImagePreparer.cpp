/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#include "WatermarkImagePreparer.h"

WatermarkImagePreparer::WatermarkImagePreparer()
{
	mOpacity = 0.15;
}

QPixmap WatermarkImagePreparer::prepare(const QPixmap &image, const QSize &availableSpace) const
{
	auto finishedWatermarkImage = getPreparedWatermarkImage(image);
	return fitWatermarkIntoCapture(finishedWatermarkImage, availableSpace);
}

QPixmap WatermarkImagePreparer::getPreparedWatermarkImage(const QPixmap &watermarkImage) const
{
	QTransform transform;
	transform.rotate(45);
	auto rotatedWatermarkImage = watermarkImage.transformed(transform);

	QPixmap transparentWatermark(rotatedWatermarkImage.size());
	transparentWatermark.fill(Qt::transparent);
	QPainter painter(&transparentWatermark);
	painter.setOpacity(mOpacity);
	painter.drawPixmap(0, 0, rotatedWatermarkImage);
	return transparentWatermark;
}

QPixmap &WatermarkImagePreparer::fitWatermarkIntoCapture(QPixmap &finishedWatermarkImage, const QSize &availableSpace) const
{
	auto widthRatio = (qreal) availableSpace.width() / (qreal) finishedWatermarkImage.size().width();
	auto heightRatio = (qreal) availableSpace.height() / (qreal) finishedWatermarkImage.size().height();
	if (widthRatio < 1 || heightRatio < 1) {
		auto minRatio = qMin(widthRatio, heightRatio);
		QTransform transform;
		transform.scale(minRatio, minRatio);
		finishedWatermarkImage = finishedWatermarkImage.transformed(transform);
	}
	return finishedWatermarkImage;
}
