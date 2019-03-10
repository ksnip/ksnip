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

#include "SnippingAreaAdorner.h"

SnippingAreaAdorner::SnippingAreaAdorner()
{
	setRulerEnabled(false);
	setCursorInfoEnabled(false);
}

void SnippingAreaAdorner::setRulerEnabled(bool enabled)
{
	mRulerEnabled = enabled;
}

void SnippingAreaAdorner::setCursorInfoEnabled(bool enabled)
{
	mCursorInfoEnabled = enabled;
}

void SnippingAreaAdorner::setMouseDown(bool isDown)
{
	mMouseIsDown = isDown;
}

void SnippingAreaAdorner::update(const QPoint &mousePosition, const QRect &screenRect, const QRect &captureRect, const QPixmap *background)
{
	if (mRulerEnabled && !mMouseIsDown) {
		mRulers.update(mousePosition, screenRect);
	}

	if (mCursorInfoEnabled) {
		if (mMouseIsDown) {
			mSizeInfo.update(captureRect);
		} else {
			mPositionInfo.update(mousePosition);
		}
	}

	if(background != nullptr) {
		mMagnifyingGlass.update(mousePosition, background);
	}
}

void SnippingAreaAdorner::draw(QPainter &painter)
{
	if (mRulerEnabled && !mMouseIsDown) {
		mRulers.draw(painter);
	}

	if (mCursorInfoEnabled) {
		if (mMouseIsDown) {
			mSizeInfo.draw(painter);
		} else {
			mPositionInfo.draw(painter);
		}
	}
	mMagnifyingGlass.draw(painter);
}
