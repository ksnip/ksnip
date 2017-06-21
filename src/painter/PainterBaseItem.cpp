/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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

#include "PainterBaseItem.h"

//
// Public Methods
//
PainterBaseItem::PainterBaseItem(PaintItemShape shape, const QPen& attributes) :
    mItemType(shape)
{
    mAttributes = attributes;
    mSelectColor.setRgb(255, 0, 102); // Color used for painting selected items
}

int PainterBaseItem::type() const
{
    return Type;
}

bool PainterBaseItem::isValid() const
{
    return true;
}

/*
 * Returns the item position within local space, same as top left of the
 * bounding rect.
 */
QPointF PainterBaseItem::position() const
{
    return boundingRect().topLeft();
}

QPen PainterBaseItem::attributes() const
{
    // We check here if the item was selected, in which case we return a
    // specific caller, same for all items that are selected.
    if (isSelected()) {
        QPen p(mAttributes);
        p.setColor(selectColor());
        return p;
    }
    return mAttributes;
}

PainterBaseItem::PaintItemShape PainterBaseItem::ItemShape() const
{
    return mItemType;
}

/*
 * Setting offset will affect all future move operations as it will move the new
 * position by the amount of offset. Setting the offset via setOffset(QPointF)
 * to a zero value disables the offset.
 */
QPointF PainterBaseItem::offset() const
{
    return mOffset;
}

void PainterBaseItem::setOffset(const QPointF& offset)
{
    mOffset = offset;
}

void PainterBaseItem::setJoinStyle(Qt::PenJoinStyle join)
{
    mAttributes.setJoinStyle(join);
}

void PainterBaseItem::setCapStyle(Qt::PenCapStyle cap)
{
    mAttributes.setCapStyle(cap);
}

void PainterBaseItem::setOutlineStyle(Qt::PenStyle penStyle)
{
    mAttributes.setStyle(penStyle);
}

void PainterBaseItem::setOutlineWidth(int width)
{
    mAttributes.setWidth(width);
}

void PainterBaseItem::setOutlineColor(const QColor& color)
{
    mAttributes.setColor(color);
}

bool PainterBaseItem::selectable() const
{
    return flags().testFlag(QGraphicsItem::ItemIsSelectable);
}

void PainterBaseItem::setSelectable(bool enabled)
{
    if (selectable() == enabled) {
        return;
    }
    setFlag(QGraphicsItem::ItemIsSelectable, enabled);
}

QColor PainterBaseItem::selectColor() const
{
    if (mSelectColor == mAttributes.color()) {
        return mSelectColor.darker();
    }
    return mSelectColor;
}
