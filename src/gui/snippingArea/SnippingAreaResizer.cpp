/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "SnippingAreaResizer.h"

SnippingAreaResizer::SnippingAreaResizer(KsnipConfig *config, QObject *parent) :
	QObject(parent),
	mConfig(config),
	mIsActive(false),
	mIsGrabbed(false),
	mGrabbedHandleIndex(-1),
	mControlPressed(false),
	mAltPressed(false)
{

	const auto width = 15;
	mHandles.append(QRectF(0, 0, width, width));
	mHandles.append(QRectF(0, 0, width, width));
	mHandles.append(QRectF(0, 0, width, width));
	mHandles.append(QRectF(0, 0, width, width));
	mHandles.append(QRectF(0, 0, width, width));
	mHandles.append(QRectF(0, 0, width, width));
	mHandles.append(QRectF(0, 0, width, width));
	mHandles.append(QRectF(0, 0, width, width));
}

void SnippingAreaResizer::activate(const QRectF &rect, const QPointF &pos)
{
	mIsActive = true;
	mCurrentRect = rect;
	mColor = mConfig->snippingAdornerColor();
	updateHandlePositions();
	updateCursor(pos.toPoint());
}

void SnippingAreaResizer::deactivate()
{
	mIsActive = false;
	mIsGrabbed = false;
	mGrabbedHandleIndex = -1;
}

void SnippingAreaResizer::paint(QPainter *painter)
{
	if(mIsActive) {
		painter->setRenderHint(QPainter::Antialiasing);
		painter->setBrush(Qt::NoBrush);
		painter->setPen(QPen(mColor, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
		painter->drawRect(mCurrentRect);
		painter->setBrush(mColor);
		for(const auto handle : mHandles) {
			painter->drawEllipse(handle);
		}
	}
}

bool SnippingAreaResizer::isActive() const
{
	return mIsActive;
}

void SnippingAreaResizer::handleMousePress(QMouseEvent *event)
{
	if(mIsActive) {
		auto pos = event->pos();
		for(const auto handle : mHandles) {
			if(handle.contains(pos)) {
				mIsGrabbed = true;
				mGrabOffset = pos - handle.center();
				mGrabbedHandleIndex = mHandles.indexOf(handle);
				break;
			}
		}

		if(!mIsGrabbed && mCurrentRect.contains(pos)) {
			mIsGrabbed = true;
			mGrabOffset = pos - mCurrentRect.topLeft();
		}
	}
}

void SnippingAreaResizer::handleMouseRelease(QMouseEvent *event)
{
	Q_UNUSED(event)

	if(mIsActive && mIsGrabbed) {
		mIsGrabbed = false;
		mGrabOffset = {};
		mGrabbedHandleIndex = -1;
	}
}

void SnippingAreaResizer::handleMouseMove(QMouseEvent *event)
{
	if (mIsActive) {
		if (mIsGrabbed) {
			updateCurrentRect(event->pos());
		} else {
			updateCursor(event->pos());
		}
	}
}

void SnippingAreaResizer::handleKeyPress(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Control) {
		mControlPressed = true;
	} else if (event->key() == Qt::Key_Alt) {
		mAltPressed = true;
	}

	if (mIsActive) {
		arrowKeyPressed(event);
		notifyRectChanged();
	}
}

void SnippingAreaResizer::arrowKeyPressed(const QKeyEvent *event)
{
	if (event->key() == Qt::Key_Up) {
		arrowUpPressed();
	} else if (event->key() == Qt::Key_Down) {
		arrowDownPressed();
	} else if (event->key() == Qt::Key_Left) {
		arrowLeftPressed();
	} else if (event->key() == Qt::Key_Right) {
		arrowRightPressed();
	}
}

void SnippingAreaResizer::handleKeyRelease(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Control) {
		mControlPressed = false;
	} else if(event->key() == Qt::Key_Alt) {
		mAltPressed = false;
	}
}

void SnippingAreaResizer::updateCursor(const QPoint &pos)
{
	if (mHandles[1].contains(pos) || mHandles[5].contains(pos)) {
		emit cursorChanged(Qt::SizeVerCursor);
	} else if (mHandles[3].contains(pos) || mHandles[7].contains(pos)) {
		emit cursorChanged(Qt::SizeHorCursor);
	} else if (mHandles[0].contains(pos) || mHandles[2].contains(pos) || mHandles[4].contains(pos) || mHandles[6].contains(pos) || mCurrentRect.contains(pos)) {
		emit cursorChanged(Qt::SizeAllCursor);
	} else {
		emit cursorChanged(Qt::ArrowCursor);
	}
}

void SnippingAreaResizer::updateCurrentRect(const QPoint &point)
{
	if(mGrabbedHandleIndex == -1){
		mCurrentRect.moveTo(point - mGrabOffset);
	} else if(mGrabbedHandleIndex == 0){
		mCurrentRect.setTopLeft(point - mGrabOffset);
	} else if(mGrabbedHandleIndex == 1){
		mCurrentRect.setTop((point - mGrabOffset).y());
	} else if(mGrabbedHandleIndex == 2){
		mCurrentRect.setTopRight(point - mGrabOffset);
	} else if(mGrabbedHandleIndex == 3){
		mCurrentRect.setRight((point - mGrabOffset).x());
	} else if(mGrabbedHandleIndex == 4){
		mCurrentRect.setBottomRight(point - mGrabOffset);
	} else if(mGrabbedHandleIndex == 5){
		mCurrentRect.setBottom((point - mGrabOffset).y());
	} else if(mGrabbedHandleIndex == 6){
		mCurrentRect.setBottomLeft(point - mGrabOffset);
	} else if(mGrabbedHandleIndex == 7){
		mCurrentRect.setLeft((point - mGrabOffset).x());
	}

	notifyRectChanged();
}

void SnippingAreaResizer::notifyRectChanged()
{
	updateHandlePositions();
	emit rectChanged(mCurrentRect.normalized());
}

void SnippingAreaResizer::updateHandlePositions()
{
	mHandles[0].moveCenter(RectHelper::topLeft(mCurrentRect));
	mHandles[1].moveCenter(RectHelper::top(mCurrentRect));
	mHandles[2].moveCenter(RectHelper::topRight(mCurrentRect));
	mHandles[3].moveCenter(RectHelper::right(mCurrentRect));
	mHandles[4].moveCenter(RectHelper::bottomRight(mCurrentRect));
	mHandles[5].moveCenter(RectHelper::bottom(mCurrentRect));
	mHandles[6].moveCenter(RectHelper::bottomLeft(mCurrentRect));
	mHandles[7].moveCenter(RectHelper::left(mCurrentRect));
}

void SnippingAreaResizer::arrowRightPressed()
{
	if (mControlPressed) {
		mCurrentRect.setLeft(mCurrentRect.left() + 1);
	} else if (mAltPressed) {
		mCurrentRect.setRight(mCurrentRect.right() + 1);
	} else {
		mCurrentRect.moveRight(mCurrentRect.right() + 1);
	}
}

void SnippingAreaResizer::arrowLeftPressed()
{
	if (mControlPressed) {
		mCurrentRect.setLeft(mCurrentRect.left() - 1);
	} else if (mAltPressed) {
		mCurrentRect.setRight(mCurrentRect.right() - 1);
	} else {
		mCurrentRect.moveLeft(mCurrentRect.left() - 1);
	}
}

void SnippingAreaResizer::arrowDownPressed()
{
	if (mControlPressed) {
		mCurrentRect.setTop(mCurrentRect.top() + 1);
	} else if (mAltPressed) {
		mCurrentRect.setBottom(mCurrentRect.bottom() + 1);
	} else {
		mCurrentRect.moveBottom(mCurrentRect.bottom() + 1);
	}
}

void SnippingAreaResizer::arrowUpPressed()
{
	if (mControlPressed) {
		mCurrentRect.setTop(mCurrentRect.top() - 1);
	} else if (mAltPressed) {
		mCurrentRect.setBottom(mCurrentRect.bottom() - 1);
	} else {
		mCurrentRect.moveTop(mCurrentRect.top() - 1);
	}
}
