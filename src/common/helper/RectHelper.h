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

#ifndef KSNIP_RECTHELPER_H
#define KSNIP_RECTHELPER_H

#include <QRectF>

class RectHelper
{
public:
	static QPointF topLeft(const QRectF &rect);
	static QPointF top(const QRectF &rect);
	static QPointF topRight(const QRectF &rect);
	static QPointF right(const QRectF &rect);
	static QPointF bottomRight(const QRectF &rect);
	static QPointF bottom(const QRectF &rect);
	static QPointF bottomLeft(const QRectF &rect);
	static QPointF left(const QRectF &rect);

protected:
	RectHelper() = default;
	~RectHelper() = default;
};


#endif //KSNIP_RECTHELPER_H
