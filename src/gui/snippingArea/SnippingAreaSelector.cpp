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

SnippingAreaSelector::SnippingAreaSelector(KsnipConfig *config, QObject *parent) :
	QObject(parent),
	mIsActive(false),
	mConfig(config),
	mCursorFactory(new CursorFactory),
	mIsMouseDown(false)
{

}

SnippingAreaSelector::~SnippingAreaSelector()
{
	delete mCursorFactory;
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
	emit cursorChanged(mCursorFactory->createSnippingCursor());
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

void SnippingAreaSelector::handleMousePress(QMouseEvent *event)
{
	if(mIsActive) {
		mMouseDownPos = event->pos();
		setIsMouseDown(true);
		rectChanged(QRectF(mMouseDownPos, mMouseDownPos));
	}
}

void SnippingAreaSelector::handleMouseRelease(QMouseEvent *event)
{
	Q_UNUSED(event)

	if(mIsActive) {
		setIsMouseDown(false);
	}
}

void SnippingAreaSelector::handleMouseMove(QMouseEvent *event)
{
	if(mIsActive) {
		const auto pos = event->pos();

		if(mIsMouseDown) {
			const auto rect = QRectF(mMouseDownPos, pos).normalized();
			updateCurrentRect(rect, pos);
		}

		updateAdorner(pos);
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
