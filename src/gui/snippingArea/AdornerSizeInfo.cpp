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

#include "AdornerSizeInfo.h"

AdornerSizeInfo::AdornerSizeInfo()
{
	mFontMetric = new QFontMetrics(mFont);
	mSizeInfoPen = new QPen(Qt::red, 1);
}

AdornerSizeInfo::~AdornerSizeInfo()
{
	delete mFontMetric;
	delete mSizeInfoPen;
}

void AdornerSizeInfo::update(const QRect &captureRect)
{
	updateWidthInfo(captureRect);
	updateHeightInfo(captureRect);
	updateSizeInfoText(captureRect);
}

void AdornerSizeInfo::draw(QPainter &painter)
{
	painter.setBrush(Qt::NoBrush);
	painter.setPen(*mSizeInfoPen);
	painter.drawPath(mWidthInfo);
	painter.drawPath(mHeightInfo);
	painter.drawText(mWidthTextPosition, mWidthInfoText);
	painter.drawText(mHeightTextPosition, mHeightInfoText);
}

void AdornerSizeInfo::updateWidthInfo(const QRect &captureRect)
{
	auto topLeft = captureRect.topLeft();
	auto topRight = captureRect.topRight();
	auto offsetLine = QPoint(0, 10);
	auto offsetBorderBottom = QPoint(0, 7);
	auto offsetBorderTop = QPoint(0, 13);

	QPainterPath newPath(topLeft - offsetBorderBottom);
	newPath.lineTo(topLeft - offsetBorderTop);
	newPath.lineTo(topLeft - offsetLine);
	newPath.lineTo(topRight - offsetLine);
	newPath.lineTo(topRight - offsetBorderTop);
	newPath.lineTo(topRight - offsetBorderBottom);
	mWidthInfo.swap(newPath);
}

void AdornerSizeInfo::updateHeightInfo(const QRect &captureRect)
{
	auto topLeft = captureRect.topLeft();
	auto bottomLeft = captureRect.bottomLeft();
	auto offsetLine = QPoint(10, 0);
	auto offsetBorderLeft = QPoint(7, 0);
	auto offsetBorderRight = QPoint(13, 0);

	QPainterPath newPath(topLeft - offsetBorderLeft);
	newPath.lineTo(topLeft - offsetBorderRight);
	newPath.lineTo(topLeft - offsetLine);
	newPath.lineTo(bottomLeft - offsetLine);
	newPath.lineTo(bottomLeft - offsetBorderRight);
	newPath.lineTo(bottomLeft - offsetBorderLeft);
	mHeightInfo.swap(newPath);
}

void AdornerSizeInfo::updateSizeInfoText(const QRect &captureRect)
{
	auto textOffset = 13;
	mWidthInfoText = QString::number(captureRect.width());
	mHeightInfoText = QString::number(captureRect.height());
	auto widthTextBoundingRect = mFontMetric->boundingRect(mWidthInfoText);
	auto heightTextBoundingRect = mFontMetric->boundingRect(mHeightInfoText);
	mWidthTextPosition.setX(captureRect.center().x() - widthTextBoundingRect.width() / 2);
	mWidthTextPosition.setY(captureRect.top() - textOffset);
	mHeightTextPosition.setX(captureRect.left() - textOffset - heightTextBoundingRect.width());
	mHeightTextPosition.setY(captureRect.center().y() + heightTextBoundingRect.height() / 2);
}
