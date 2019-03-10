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

#include "AdornerMagnifyingGlass.h"

AdornerMagnifyingGlass::AdornerMagnifyingGlass()
{
	mOffsetToMouse = QPoint(20, 20);
	mScaleFactor = QSize(600, 600);
	mVisibleRect.setWidth(200);
	mVisibleRect.setHeight(200);
	mCrossHairPen = new QPen(Qt::red, 6);
}

AdornerMagnifyingGlass::~AdornerMagnifyingGlass()
{
	delete mCrossHairPen;
}

void AdornerMagnifyingGlass::update(const QPoint &mousePosition, const QPixmap *background)
{
	updatePosition(mousePosition, background);
	updateImage(mousePosition, background);

	updateCrossHair();
}

void AdornerMagnifyingGlass::draw(QPainter &painter)
{
	painter.setBrush(Qt::NoBrush);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setClipRegion(QRegion(mVisibleRect, QRegion::Ellipse));
	painter.drawPixmap(mVisibleRect, mZoomedAndCenterImage);

	painter.setPen(*mCrossHairPen);
	painter.drawLine(mCrossHairTop);
	painter.drawLine(mCrossHairBottom);
	painter.drawLine(mCrossHairLeft);
	painter.drawLine(mCrossHairRight);
}

void AdornerMagnifyingGlass::updatePosition(const QPoint &mousePosition, const QPixmap *background)
{
	if (isPositionTopLeftFromMouse(mousePosition, background)) {
		mVisibleRect.moveBottomRight(mousePosition);
	} else if (isPositionBottomLeftFromMouse(mousePosition, background)) {
		mVisibleRect.moveTopRight(mousePosition);
	} else if (isPositionTopRightFromMouse(mousePosition, background)) {
		mVisibleRect.moveBottomLeft(mousePosition);
	} else {
		mVisibleRect.moveTopLeft(mousePosition + mOffsetToMouse);
	}
}

void AdornerMagnifyingGlass::updateImage(const QPoint &mousePosition, const QPixmap *background)
{
	QRect positionAroundMouse(0, 0, 100, 100);
	positionAroundMouse.moveCenter(mousePosition);

	auto zoomedInImage = background->copy(positionAroundMouse).scaled(mScaleFactor);
	QRect rectForFinalCut(mVisibleRect);
	rectForFinalCut.moveCenter(zoomedInImage.rect().center());
	mZoomedAndCenterImage = zoomedInImage.copy(rectForFinalCut);
}

void AdornerMagnifyingGlass::updateCrossHair()
{
	auto outerOffset = 20;
	auto innerOffset = 15;
	mCrossHairTop.setLine(mVisibleRect.center().x(), mVisibleRect.top() + outerOffset, mVisibleRect.center().x(), mVisibleRect.center().y() - innerOffset);
	mCrossHairBottom.setLine(mVisibleRect.center().x(), mVisibleRect.bottom() - outerOffset, mVisibleRect.center().x(), mVisibleRect.center().y() + innerOffset);
	mCrossHairLeft.setLine(mVisibleRect.left() + outerOffset, mVisibleRect.center().y(), mVisibleRect.center().x() - innerOffset, mVisibleRect.center().y());
	mCrossHairRight.setLine(mVisibleRect.right() - outerOffset, mVisibleRect.center().y(), mVisibleRect.center().x() + innerOffset, mVisibleRect.center().y());
}

bool AdornerMagnifyingGlass::isPositionTopRightFromMouse(const QPoint &mousePosition, const QPixmap *background) const
{
	return mousePosition.x() + mVisibleRect.width() < background->width() && mousePosition.y() + mVisibleRect.height() > background->height();
}

bool AdornerMagnifyingGlass::isPositionBottomLeftFromMouse(const QPoint &mousePosition, const QPixmap *background) const
{
	return mousePosition.x() + mVisibleRect.width() > background->width() && mousePosition.y() + mVisibleRect.height() < background->height();
}

bool AdornerMagnifyingGlass::isPositionTopLeftFromMouse(const QPoint &mousePosition, const QPixmap *background) const
{
	return mousePosition.x() + mVisibleRect.width() > background->width() && mousePosition.y() + mVisibleRect.height() > background->height();
}
