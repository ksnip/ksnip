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

#ifndef KSNIP_SNIPPINGAREAADORNER_H
#define KSNIP_SNIPPINGAREAADORNER_H

#include <QPainter>

#include "AdornerMagnifyingGlass.h"
#include "AdornerRulers.h"
#include "AdornerPositionInfo.h"
#include "AdornerSizeInfo.h"
#include "src/common/helper/MathHelper.h"

class SnippingAreaAdorner
{
public:
	explicit SnippingAreaAdorner();
	~SnippingAreaAdorner() = default;
	void setRulersEnabled(bool enabled);
	void setPositionAndSizeInfoEnabled(bool enabled);
	void setMagnifyingGlassEnabled(bool enabled);
	void setMouseDown(bool isDown);
	void setBackgroundImage(const QPixmap *background);
	void update(const QPoint &mousePosition, const QRect &screenRect, const QRect &captureRect);
	void draw(QPainter &painter);

private:
	bool mRulerEnabled;
	bool mPositionAndSizeInfoEnabled;
	bool mMagnifyingGlassEnabled;
	bool mMouseIsDown;
	AdornerSizeInfo mSizeInfo;
	AdornerPositionInfo mPositionInfo;
	AdornerRulers mRulers;
	AdornerMagnifyingGlass mMagnifyingGlass;
};

#endif //KSNIP_SNIPPINGAREAADORNER_H
