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

#include "AdornerPositionInfo.h"

AdornerPositionInfo::AdornerPositionInfo()
{
	mFontMetric = new QFontMetrics(mFont);
	mPen = new QPen(Qt::red, 1);
}

AdornerPositionInfo::~AdornerPositionInfo()
{
	delete mFontMetric;
	delete mPen;
}

void AdornerPositionInfo::update(const QPoint &mousePosition)
{
	QPoint textOffset(10, 8);
	mText = QString::number(mousePosition.x()) + QStringLiteral(", ") + QString::number(mousePosition.y());
	mBox = mFontMetric->boundingRect(mText);
	mBox.moveTopLeft(mousePosition + textOffset);
	mTextRect = mBox;
	mBox.adjust(0, 0, 7, 4);
	mTextRect.adjust(-3, 0, 5, 0);
}

void AdornerPositionInfo::draw(QPainter &painter)
{
	painter.setPen(*mPen);
	painter.setBrush(QColor(0, 0, 0, 200));

	painter.drawRoundedRect(mTextRect, 2, 2);
	painter.drawText(mBox, mText);
}
