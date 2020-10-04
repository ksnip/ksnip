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

#include "AddWatermarkOperation.h"

AddWatermarkOperation::AddWatermarkOperation(IImageAnnotator *imageAnnotator) :
	mImageAnnotator(imageAnnotator),
	mConfig(KsnipConfigProvider::instance())
{
}

void AddWatermarkOperation::execute()
{
	auto watermarkImage = mWatermarkImageLoader.load();
	if(watermarkImage.isNull()) {
		NotifyAboutMissingWatermarkImage();
		return;
	}

	auto availableSpace = mImageAnnotator->image().size();
	auto rotated = mConfig->rotateWatermarkEnabled();
	auto finishedWatermarkImage = mImagePreparer.prepare(watermarkImage, availableSpace, rotated);
	auto position = getPositionForWatermark(finishedWatermarkImage, availableSpace);
	mImageAnnotator->insertImageItem(position, finishedWatermarkImage);
}

void AddWatermarkOperation::NotifyAboutMissingWatermarkImage() const
{
	MessageBoxHelper::ok(tr("Watermark Image Required"), tr("Please add a Watermark Image via Options > Settings > Annotator > Update"));
}

QPointF AddWatermarkOperation::getPositionForWatermark(const QPixmap &image, const QSize &availableSpace) const
{
	auto availableWidth = availableSpace.width() - image.rect().width();
	auto availableHeight = availableSpace.height() - image.rect().height();

	qreal x = availableWidth <= 0 ? 0 : rand() % availableWidth;
	qreal y = availableHeight <= 0 ? 0 : rand() % availableHeight;

	return {x, y};
}
