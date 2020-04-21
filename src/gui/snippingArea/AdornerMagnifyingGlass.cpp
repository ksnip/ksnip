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

#include "AdornerMagnifyingGlass.h"

AdornerMagnifyingGlass::AdornerMagnifyingGlass()
{
	mOffsetToMouse = QPoint(20, 20);
	mScaleFactor = QSize(600, 600);
	mVisibleRect.setWidth(200);
	mVisibleRect.setHeight(200);
	mZoomInAreaSize = QSize(100, 100);
	mBackgroundOffset = QPoint(50,50);
	mCrossHairPen = new QPen(Qt::red, 6);
}

AdornerMagnifyingGlass::~AdornerMagnifyingGlass()
{
	delete mCrossHairPen;
}

void AdornerMagnifyingGlass::update(const QPoint &mousePosition, const QRect &screenRect)
{
	if (mBackgroundWithMargine.isNull()) {
		return;
	}

	updatePosition(mousePosition, screenRect);
	updateImage(mousePosition);
	updateCrossHair();
}

void AdornerMagnifyingGlass::draw(QPainter &painter)
{
	if (mBackgroundWithMargine.isNull()) {
		return;
	}

	painter.setBrush(Qt::NoBrush);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setClipRegion(QRegion(mVisibleRect, QRegion::Ellipse));
	painter.drawPixmap(mVisibleRect, mImage);

	painter.setPen(*mCrossHairPen);
	painter.drawLine(mCrossHairTop);
	painter.drawLine(mCrossHairBottom);
	painter.drawLine(mCrossHairLeft);
	painter.drawLine(mCrossHairRight);
}

void AdornerMagnifyingGlass::setBackgroundImage(const QPixmap *background)
{
	if (background == nullptr) {
		mBackgroundWithMargine = QPixmap();
	} else {
		mBackgroundWithMargine = createBackgroundWithMagine(background);
	}
}

void AdornerMagnifyingGlass::updatePosition(const QPoint &mousePosition, const QRect &screenRect)
{
	if (isPositionTopLeftFromMouse(mousePosition, screenRect)) {
		mVisibleRect.moveBottomRight(mousePosition);
	} else if (isPositionBottomLeftFromMouse(mousePosition, screenRect)) {
		mVisibleRect.moveTopRight(mousePosition);
	} else if (isPositionTopRightFromMouse(mousePosition, screenRect)) {
		mVisibleRect.moveBottomLeft(mousePosition);
	} else {
		mVisibleRect.moveTopLeft(mousePosition + mOffsetToMouse);
	}
}

void AdornerMagnifyingGlass::updateImage(const QPoint &mousePosition)
{
	QRect positionAroundMouse(QPoint(), mZoomInAreaSize);
	positionAroundMouse.moveCenter(mousePosition + mBackgroundOffset);

	auto zoomedInImage = mBackgroundWithMargine.copy(positionAroundMouse).scaled(mScaleFactor);
	QRect rectForFinalCut(mVisibleRect);
	rectForFinalCut.moveCenter(zoomedInImage.rect().center());
	mImage = zoomedInImage.copy(rectForFinalCut);
}

QPixmap AdornerMagnifyingGlass::createBackgroundWithMagine(const QPixmap *background) const
{
	QPixmap backgroundWithMargine(background->size() + mZoomInAreaSize);
	backgroundWithMargine.fill(Qt::black);
	QPainter painter(&backgroundWithMargine);
	painter.drawPixmap(mBackgroundOffset, *background);
	return backgroundWithMargine;
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

bool AdornerMagnifyingGlass::isPositionTopRightFromMouse(const QPoint &mousePosition, const QRect &screenRect) const
{
	return mousePosition.x() + mVisibleRect.width() < screenRect.width() && mousePosition.y() + mVisibleRect.height() > screenRect.height();
}

bool AdornerMagnifyingGlass::isPositionBottomLeftFromMouse(const QPoint &mousePosition, const QRect &screenRect) const
{
	return mousePosition.x() + mVisibleRect.width() > screenRect.width() && mousePosition.y() + mVisibleRect.height() < screenRect.height();
}

bool AdornerMagnifyingGlass::isPositionTopLeftFromMouse(const QPoint &mousePosition, const QRect &screenRect) const
{
	return mousePosition.x() + mVisibleRect.width() > screenRect.width() && mousePosition.y() + mVisibleRect.height() > screenRect.height();
}
