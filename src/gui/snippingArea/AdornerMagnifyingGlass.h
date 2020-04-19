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

#ifndef KSNIP_ADORNERMAGNIFYINGGLASS_H
#define KSNIP_ADORNERMAGNIFYINGGLASS_H

#include <QPainter>

class AdornerMagnifyingGlass
{
public:
	explicit AdornerMagnifyingGlass();
	~AdornerMagnifyingGlass();
	void update(const QPoint &mousePosition, const QRect &screenRect);
	void draw(QPainter &painter);
	void setBackgroundImage(const QPixmap *background);

private:
	QPixmap mBackgroundWithMargine;
	QPixmap mImage;
	QRect mVisibleRect;
	QPoint mOffsetToMouse;
	QSize mScaleFactor;
	QSize mZoomInAreaSize;
	QPoint mBackgroundOffset;
	QLine mCrossHairTop;
	QLine mCrossHairBottom;
	QLine mCrossHairLeft;
	QLine mCrossHairRight;
	QPen *mCrossHairPen;

	void updateImage(const QPoint &mousePosition);
	void updateCrossHair();
	bool isPositionTopLeftFromMouse(const QPoint &mousePosition, const QRect &screenRect) const;
	bool isPositionBottomLeftFromMouse(const QPoint &mousePosition, const QRect &screenRect) const;
	bool isPositionTopRightFromMouse(const QPoint &mousePosition, const QRect &screenRect) const;
	void updatePosition(const QPoint &mousePosition, const QRect &screenRect);
	QPixmap createBackgroundWithMagine(const QPixmap *background) const;
};

#endif //KSNIP_ADORNERMAGNIFYINGGLASS_H
