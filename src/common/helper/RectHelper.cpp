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

#include "RectHelper.h"

QPointF RectHelper::topLeft(const QRectF &rect)
{
	return rect.topLeft();
}

QPointF RectHelper::top(const QRectF &rect)
{
	return { rect.center().x(), rect.top() };
}

QPointF RectHelper::topRight(const QRectF &rect)
{
	return rect.topRight();
}

QPointF RectHelper::right(const QRectF &rect)
{
	return { rect.right(), rect.center().y() };
}

QPointF RectHelper::bottomRight(const QRectF &rect)
{
	return rect.bottomRight();
}

QPointF RectHelper::bottom(const QRectF &rect)
{
	return { rect.center().x(), rect.bottom() };
}

QPointF RectHelper::bottomLeft(const QRectF &rect)
{
	return rect.bottomLeft();
}

QPointF RectHelper::left(const QRectF &rect)
{
	return { rect.left(), rect.center().y() };
}
