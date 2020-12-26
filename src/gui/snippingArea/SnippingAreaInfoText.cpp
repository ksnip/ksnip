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

#include "SnippingAreaInfoText.h"

SnippingAreaInfoText::SnippingAreaInfoText(QObject *parent) :
	QObject(parent),
	mRectPen(new QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)),
	mRectBrush(new QBrush(QColor(255, 255, 255, 160))),
	mBaseInfoTextRect(new QRect(30, 30, 500, 100)),
	mIsActive(false),
	mIsResizingDefault(false)
{
	updateInfoText();
}

SnippingAreaInfoText::~SnippingAreaInfoText()
{
	delete mRectPen;
	delete mRectBrush;
	delete mBaseInfoTextRect;
}

void SnippingAreaInfoText::updateInfoText()
{
	auto selectRect = tr("Click and Drag to select a rectangular area or press ESC to quit.");
	auto resizeAfterSelection = tr("Hold CTRL pressed to resize selection after selecting.");
	auto dontResizeAfterSelection = tr("Hold CTRL pressed to prevent resizing after selecting.");
	auto cancelAfterTimeout = tr("Operation will be canceled after 60 sec when no selection made.");
	auto infoTextCanBeDisabled = tr("This message can be disabled via settings.");
	auto newLine = QLatin1String("\n");
	if(mIsResizingDefault) {
		mInfoText = selectRect + newLine + dontResizeAfterSelection + newLine + cancelAfterTimeout + newLine + infoTextCanBeDisabled;
	} else {
		mInfoText = selectRect + newLine + resizeAfterSelection + newLine + cancelAfterTimeout + newLine + infoTextCanBeDisabled;
	}
}

void SnippingAreaInfoText::paint(QPainter *painter)
{
	if(mIsActive) {
		auto fontMetric = painter->fontMetrics();
		auto textRect = fontMetric.boundingRect(*mBaseInfoTextRect, Qt::TextWordWrap, mInfoText);
		auto boundingRect = textRect.adjusted(-10, -10, 10, 10);

		if(boundingRect.contains(mCurrentMousePos)) {
			auto newPos = mSnippingAreaGeometry.bottomRight().toPoint();
			textRect.moveBottomRight(newPos - QPoint(40, 40));
			boundingRect.moveBottomRight(newPos - QPoint(30, 30));
		}

		painter->setBrush(*mRectBrush);
		painter->setPen(*mRectPen);
		painter->drawRect(boundingRect);
		painter->drawText(textRect, mInfoText);
	}
}

void SnippingAreaInfoText::handleMouseMove(const QPoint &pos)
{
	mCurrentMousePos = pos;
}

void SnippingAreaInfoText::activate(const QRectF &snippingAreaGeometry, bool isResizingDefault)
{
	mIsActive = true;
	mIsResizingDefault = isResizingDefault;
	mSnippingAreaGeometry = snippingAreaGeometry;
	updateInfoText();
}

void SnippingAreaInfoText::deactivate()
{
	mIsActive = false;
}
