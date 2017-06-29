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

int PainterBaseItem::mOrder = 1;

//
// Public Methods
//
PainterBaseItem::PainterBaseItem(PaintItemShape shape, const QPen& attributes) :
    mItemType(shape)
{
    mAttributes = attributes;
    mSelectAttr.setColor(Qt::red);
    mSelectAttr.setStyle(Qt::DotLine);

    setZValue(mOrder++);
}

PainterBaseItem::~PainterBaseItem()
{
    mOrder--;
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

const QPen& PainterBaseItem::attributes() const
{
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

const QPen& PainterBaseItem::selectColor() const
{
    return mSelectAttr;
}

/*
 * Returns highest item order, the zValue of the top most item.
 */
int PainterBaseItem::order()
{
    return mOrder;
}

void PainterBaseItem::resetOrder()
{
    mOrder = 1;
}

//
// Protected Methods
//

/*
 * Paints selection decoration to passed painter object. The function checks if
 * the owning item is selected and paints decoration depending on it. If the
 * item is not selected, the function does nothing.
 */
void PainterBaseItem::paintDecoration(QPainter* painter)
{
    if (isSelected()) {
        painter->setPen(selectColor());
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }
}
