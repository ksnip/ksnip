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

#include "SnippingAreaAdorner.h"

SnippingAreaAdorner::SnippingAreaAdorner()
{
	setRulersEnabled(false);
	setPositionAndSizeInfoEnabled(false);
}

void SnippingAreaAdorner::setRulersEnabled(bool enabled)
{
	mRulerEnabled = enabled;
}

void SnippingAreaAdorner::setPositionAndSizeInfoEnabled(bool enabled)
{
	mPositionAndSizeInfoEnabled = enabled;
}

void SnippingAreaAdorner::setMagnifyingGlassEnabled(bool enabled)
{
	mMagnifyingGlassEnabled = enabled;
}

void SnippingAreaAdorner::setIsMouseDown(bool isDown)
{
	mMouseIsDown = isDown;
}

void SnippingAreaAdorner::setBackgroundImage(const QPixmap *background)
{
	mMagnifyingGlass.setBackgroundImage(background);
}

void SnippingAreaAdorner::update(const QPoint &mousePosition, const QRect &screenRect, const QRect &captureRect)
{
	if (mRulerEnabled && !mMouseIsDown) {
		mRulers.update(mousePosition, screenRect);
	}

	if (mPositionAndSizeInfoEnabled) {
		if (mMouseIsDown) {
			mSizeInfo.update(captureRect);
		} else {
			mPositionInfo.update(mousePosition);
		}
	}

	if (mMagnifyingGlassEnabled) {
		mMagnifyingGlass.update(mousePosition, screenRect);
	}
}

void SnippingAreaAdorner::paint(QPainter *painter, const QColor &adornerColor, const QColor &cursorColor)
{
	if (mRulerEnabled && !mMouseIsDown) {
		mRulers.paint(painter, adornerColor);
	}

	if (mPositionAndSizeInfoEnabled) {
		if (mMouseIsDown) {
			mSizeInfo.paint(painter, adornerColor);
		} else {
			mPositionInfo.paint(painter, adornerColor);
		}
	}

	if (mMagnifyingGlassEnabled) {
		mMagnifyingGlass.paint(painter, cursorColor);
	}
}
