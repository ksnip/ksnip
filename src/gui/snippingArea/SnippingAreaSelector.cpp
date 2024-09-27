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

#include "SnippingAreaSelector.h"

SnippingAreaSelector::SnippingAreaSelector(const QSharedPointer<IConfig> &config, QObject *parent) :
	QObject(parent),
	mIsActive(false),
	mConfig(config),
	mIsMouseDown(false),
	mMouseCursor()
{

}

void SnippingAreaSelector::activate(const QRectF &snippingAreaGeometry, const QPointF &pos)
{
	setupAdorner();
	mIsActive = true;
	mSnippingAreaGeometry = snippingAreaGeometry;
	mAdornerColor = mConfig->snippingAdornerColor();
	mCursorColor = mConfig->snippingCursorColor();
	updateCurrentRect({}, pos);
	updateAdorner(pos);
	emit cursorChanged(CustomCursor(mConfig->snippingCursorColor(), mConfig->snippingCursorSize()));
}

void SnippingAreaSelector::deactivate()
{
	mIsActive = false;
	mIsMouseDown = false;
	mMouseDownPos = {};
}

void SnippingAreaSelector::paint(QPainter *painter)
{
	if(mIsActive) {
		mAdorner.paint(painter, mAdornerColor, mCursorColor);

		painter->setClipping(false);
		painter->setRenderHint(QPainter::Antialiasing, false);

		painter->setPen(mAdornerColor);
		painter->drawRect(mCurrentRect);
	}
}

void SnippingAreaSelector::setBackgroundImage(const QPixmap *background)
{
	mAdorner.setBackgroundImage(background);
}

bool SnippingAreaSelector::isActive() const
{
	return mIsActive;
}

void SnippingAreaSelector::handleMousePress(const QPointF &pos)
{
	if(mIsActive) {
		mMouseDownPos = pos;
		setIsMouseDown(true);
		rectChanged(QRectF(mMouseDownPos, mMouseDownPos));
	}
}

void SnippingAreaSelector::handleMouseRelease()
{
	if(mIsActive) {
		setIsMouseDown(false);
	}
}

void SnippingAreaSelector::handleMouseMove(const QPointF &pos)
{
	if(mIsActive) {
		if(mIsMouseDown) {
			const auto rect = QRectF(mMouseDownPos, pos).normalized();
			updateCurrentRect(rect, pos);
		}

		updateAdorner(pos);
	}
}

void SnippingAreaSelector::handleKeyPress(QKeyEvent *event)
{
	if (mIsActive) {
		// Get the current mouse cursor position and move it.
		// This triggers the mouse move event
		const QPoint mouseCursorPosition = mMouseCursor.pos();
		switch (event->key()) {
		case Qt::Key_Up:
			mMouseCursor.setPos(mouseCursorPosition + QPoint(0, -1));
			break;
		case Qt::Key_Down:
			mMouseCursor.setPos(mouseCursorPosition + QPoint(0, 1));
			break;
		case Qt::Key_Left:
			mMouseCursor.setPos(mouseCursorPosition + QPoint(-1, 0));
			break;
		case Qt::Key_Right:
			mMouseCursor.setPos(mouseCursorPosition + QPoint(1, 0));
			break;
		}
	}
}

void SnippingAreaSelector::updateAdorner(const QPointF &pos)
{
	mAdorner.update(pos.toPoint(), mSnippingAreaGeometry.toRect(), mCurrentRect.toRect());
}

void SnippingAreaSelector::updateCurrentRect(const QRectF &rect, const QPointF &pos)
{
	mCurrentRect = rect;
	emit rectChanged(rect);
}

void SnippingAreaSelector::setupAdorner()
{
	auto magnifyingGlassEnabled = mConfig->snippingAreaMagnifyingGlassEnabled();
	auto freezeImageWhileSnippingEnabled = mConfig->freezeImageWhileSnippingEnabled();
	mAdorner.setRulersEnabled(mConfig->snippingAreaRulersEnabled());
	mAdorner.setPositionAndSizeInfoEnabled(mConfig->snippingAreaPositionAndSizeInfoEnabled());
	mAdorner.setMagnifyingGlassEnabled(magnifyingGlassEnabled && freezeImageWhileSnippingEnabled);
}

void SnippingAreaSelector::setIsMouseDown(bool isMouseDown)
{
	mIsMouseDown = isMouseDown;
	mAdorner.setIsMouseDown(isMouseDown);
}
