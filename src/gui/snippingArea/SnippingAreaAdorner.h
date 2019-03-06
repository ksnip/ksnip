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

#ifndef KSNIP_SNIPPINGAREAADORNER_H
#define KSNIP_SNIPPINGAREAADORNER_H

#include <QPainter>

#include "src/common/helper/MathHelper.h"

class SnippingAreaAdorner
{
public:
	explicit SnippingAreaAdorner();
	~SnippingAreaAdorner();
	void setRulerEnabled(bool enabled);
	void setCursorInfoEnabled(bool enabled);
	void setMouseDown(bool isDown);
	void update(const QPoint &mousePosition, const QRect &screenRect, const QRect &captureRect);
	void draw(QPainter &painter);

private:
	bool mRulerEnabled;
	bool mCursorInfoEnabled;
	bool mMouseIsDown;
	QFont mFont;
	QFontMetrics *mFontMetric;
	QPen *mRulerPen;
	QPen *mSizeInfoPen;
	QPen *mCursorInfoPen;
	QLine mBottomLine;
	QLine mTopLine;
	QLine mLeftLine;
	QLine mRightLine;
	QPainterPath mWidthInfo;
	QPainterPath mHeightInfo;
	QPoint mWidthTextPosition;
	QPoint mHeightTextPosition;
	QString mWidthInfoText;
	QString mHeightInfoText;
	QRect mCursorInfoBox;
	QRect mCursorInfoTextRect;
	QString mCursorInfoText;

	void updateRulers(const QPoint &mousePosition, const QRect &screenRect);
	void updateCursorInfo(const QPoint &mousePosition);
	void updateSizeInfo(const QRect &captureRect);
	void drawRulers(QPainter &painter);
	void drawSizeInfo(QPainter &painter);
	void drawCursorInfo(QPainter &painter);
	void updateWidthInfo(const QRect &captureRect);
	void updateHeightInfo(const QRect &captureRect);
	void updateSizeInfoText(const QRect &captureRect);
};

#endif //KSNIP_SNIPPINGAREAADORNER_H
