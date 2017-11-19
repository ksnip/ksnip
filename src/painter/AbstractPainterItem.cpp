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

#include "AbstractPainterItem.h"

int AbstractPainterItem::mOrder = 1;

//
// Public Methods
//
AbstractPainterItem::AbstractPainterItem(const QPen& attributes)
{
    mAttributes = attributes;
    mSelectAttr.setColor(Qt::red);
    mSelectAttr.setStyle(Qt::DotLine);

    setZValue(mOrder++);
}

AbstractPainterItem::~AbstractPainterItem()
{
    mOrder--;
}

int AbstractPainterItem::type() const
{
    return Type;
}

void AbstractPainterItem::addPoint(const QPointF& pos, bool modifier)
{
}

bool AbstractPainterItem::isValid() const
{
    return true;
}

/*
 * Returns the item position within local space, same as top left of the
 * bounding rect.
 */
QPointF AbstractPainterItem::position() const
{
    return boundingRect().topLeft();
}

const QPen& AbstractPainterItem::attributes() const
{
    return mAttributes;
}

/*
 * Setting offset will affect all future move operations as it will move the new
 * position by the amount of offset. Setting the offset via setOffset(QPointF)
 * to a zero value disables the offset.
 */
QPointF AbstractPainterItem::offset() const
{
    return mOffset;
}

void AbstractPainterItem::setOffset(const QPointF& offset)
{
    mOffset = offset;
}

void AbstractPainterItem::setJoinStyle(Qt::PenJoinStyle join)
{
    mAttributes.setJoinStyle(join);
}

void AbstractPainterItem::setCapStyle(Qt::PenCapStyle cap)
{
    mAttributes.setCapStyle(cap);
}

void AbstractPainterItem::setOutlineStyle(Qt::PenStyle penStyle)
{
    mAttributes.setStyle(penStyle);
}

void AbstractPainterItem::setOutlineWidth(int width)
{
    mAttributes.setWidth(width);
}

void AbstractPainterItem::setOutlineColor(const QColor& color)
{
    mAttributes.setColor(color);
}

bool AbstractPainterItem::selectable() const
{
    return flags().testFlag(QGraphicsItem::ItemIsSelectable);
}

void AbstractPainterItem::setSelectable(bool enabled)
{
    if (selectable() == enabled) {
        return;
    }
    setFlag(QGraphicsItem::ItemIsSelectable, enabled);
}

const QPen& AbstractPainterItem::selectColor() const
{
    return mSelectAttr;
}

/*
 * Returns highest item order, the zValue of the top most item.
 */
int AbstractPainterItem::order()
{
    return mOrder;
}

void AbstractPainterItem::resetOrder()
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
void AbstractPainterItem::paintDecoration(QPainter* painter)
{
    if (isSelected()) {
        painter->setPen(selectColor());
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }
}
