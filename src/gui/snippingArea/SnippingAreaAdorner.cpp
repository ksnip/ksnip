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
	mFontMetric = new QFontMetrics(mFont);
	mRulerPen = new QPen(Qt::red, 1, Qt::DotLine, Qt::SquareCap, Qt::MiterJoin);
	mCursorInfoPen = new QPen(Qt::red, 1);
	mSizeInfoPen = new QPen(Qt::red, 1);
}

SnippingAreaAdorner::~SnippingAreaAdorner()
{
	delete mFontMetric;
	delete mRulerPen;
	delete mSizeInfoPen;
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
		updateRulers(mousePosition, screenRect);
	}

	if (mCursorInfoEnabled) {
		if (mMouseIsDown) {
			updateSizeInfo(captureRect);
		} else {
			updateCursorInfo(mousePosition);
		}
	}

	if(background != nullptr) {
		mMagnifyingGlass.update(mousePosition, background);
	}
}

void SnippingAreaAdorner::draw(QPainter &painter)
{
	if (mRulerEnabled && !mMouseIsDown) {
		drawRulers(painter);
	}

	if (mCursorInfoEnabled) {
		if (mMouseIsDown) {
			drawSizeInfo(painter);
		} else {
			drawCursorInfo(painter);
		}
	}
	mMagnifyingGlass.draw(painter);
}

void SnippingAreaAdorner::updateRulers(const QPoint &mousePosition, const QRect &screenRect)
{
	int offset = 4;
	mTopLine.setLine(mousePosition.x(), mousePosition.y() - offset, mousePosition.x(), screenRect.top());
	mRightLine.setLine(mousePosition.x() + offset, mousePosition.y(), screenRect.right(), mousePosition.y());
	mBottomLine.setLine(mousePosition.x(), mousePosition.y() + offset, mousePosition.x(), screenRect.bottom());
	mLeftLine.setLine(mousePosition.x() - offset, mousePosition.y(), screenRect.left(), mousePosition.y());
}

void SnippingAreaAdorner::updateCursorInfo(const QPoint &mousePosition)
{
	QPoint textOffset(10, 8);
	auto pos = mousePosition;
	mCursorInfoText = QString::number(pos.x()) + QStringLiteral(", ") + QString::number(pos.y());
	mCursorInfoBox = mFontMetric->boundingRect(mCursorInfoText);
	mCursorInfoBox.moveTopLeft(pos + textOffset);
	mCursorInfoTextRect = mCursorInfoBox;
	mCursorInfoBox.adjust(0, 0, 7, 4);
	mCursorInfoTextRect.adjust(-3, 0, 5, 0);
}

void SnippingAreaAdorner::updateSizeInfo(const QRect &captureRect)
{
	updateWidthInfo(captureRect);
	updateHeightInfo(captureRect);
	updateSizeInfoText(captureRect);
}

void SnippingAreaAdorner::drawRulers(QPainter &painter)
{
	painter.setPen(*mRulerPen);
	painter.drawLine(mTopLine);
	painter.drawLine(mRightLine);
	painter.drawLine(mBottomLine);
	painter.drawLine(mLeftLine);
}

void SnippingAreaAdorner::drawSizeInfo(QPainter &painter)
{
	painter.setBrush(Qt::NoBrush);
	painter.setPen(*mSizeInfoPen);
	painter.drawPath(mWidthInfo);
	painter.drawPath(mHeightInfo);
	painter.drawText(mWidthTextPosition, mWidthInfoText);
	painter.drawText(mHeightTextPosition, mHeightInfoText);
}

void SnippingAreaAdorner::drawCursorInfo(QPainter &painter)
{
	painter.setPen(*mCursorInfoPen);
	painter.setBrush(QColor(0, 0, 0, 200));

	painter.drawRoundedRect(mCursorInfoTextRect, 2, 2);
	painter.drawText(mCursorInfoBox, mCursorInfoText);
}

void SnippingAreaAdorner::updateSizeInfoText(const QRect &captureRect)
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

void SnippingAreaAdorner::updateHeightInfo(const QRect &captureRect)
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

void SnippingAreaAdorner::updateWidthInfo(const QRect &captureRect)
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
