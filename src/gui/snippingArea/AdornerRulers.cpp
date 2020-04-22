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

#include "AdornerRulers.h"

AdornerRulers::AdornerRulers()
{
	mPen = new QPen(Qt::red, 1, Qt::DotLine, Qt::SquareCap, Qt::MiterJoin);
}

AdornerRulers::~AdornerRulers()
{
	delete mPen;
}

void AdornerRulers::update(const QPoint &mousePosition, const QRect &screenRect)
{
	int offset = 4;
	mTopLine.setLine(mousePosition.x(), mousePosition.y() - offset, mousePosition.x(), screenRect.top());
	mRightLine.setLine(mousePosition.x() + offset, mousePosition.y(), screenRect.right(), mousePosition.y());
	mBottomLine.setLine(mousePosition.x(), mousePosition.y() + offset, mousePosition.x(), screenRect.bottom());
	mLeftLine.setLine(mousePosition.x() - offset, mousePosition.y(), screenRect.left(), mousePosition.y());
}

void AdornerRulers::draw(QPainter &painter)
{
	painter.setPen(*mPen);
	painter.drawLine(mTopLine);
	painter.drawLine(mRightLine);
	painter.drawLine(mBottomLine);
	painter.drawLine(mLeftLine);
}
