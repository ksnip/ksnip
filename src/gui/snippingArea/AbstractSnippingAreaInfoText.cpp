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

#include "AbstractSnippingAreaInfoText.h"

AbstractSnippingAreaInfoText::AbstractSnippingAreaInfoText(QObject *parent):
	QObject(parent),
	mRectPen(new QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)),
	mRectBrush(new QBrush(QColor(255, 255, 255, 160))),
	mBaseInfoTextRect(new QRect(30, 30, 500, 100)),
	mIsActive(false)
{
}

AbstractSnippingAreaInfoText::~AbstractSnippingAreaInfoText()
{
	delete mRectPen;
	delete mRectBrush;
	delete mBaseInfoTextRect;
}

void AbstractSnippingAreaInfoText::paint(QPainter *painter)
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

void AbstractSnippingAreaInfoText::handleMouseMove(const QPoint &pos)
{
	mCurrentMousePos = pos;
}

void AbstractSnippingAreaInfoText::activate(const QRectF &snippingAreaGeometry)
{
	mIsActive = true;
	mSnippingAreaGeometry = snippingAreaGeometry;
	updateInfoText();
}

void AbstractSnippingAreaInfoText::deactivate()
{
	mIsActive = false;
}

void AbstractSnippingAreaInfoText::setInfoText(const QStringList &infoTextLines)
{
	auto newLine = QLatin1String("\n");
	mInfoText = QString();
	for (int i = 0; i < infoTextLines.length(); ++i) {
		mInfoText += infoTextLines[i];
		if(i < infoTextLines.length() - 1){
			mInfoText += newLine;
		}
	}
}
