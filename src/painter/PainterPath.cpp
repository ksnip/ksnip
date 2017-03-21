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

#include "PainterPath.h"

//
// Public Functions
//

PainterPath::PainterPath(QPointF pos, QPen attributes, bool transparent) : PainterBaseItem(Path, attributes),
    mPath(new QPainterPath),
    mStroker(new QPainterPathStroker),
    mTransparent(transparent)
{
    // Place the path at the right location and draw the first point, which is actually a line just
    // moved one pixel as QT won't draw a line if the point B is equal to point A
    mPath->moveTo(pos);
    mPath->lineTo(pos + QPointF(1, 1));

    //setup the stroker which we use to draw the path
    mStroker->setCapStyle(Qt::RoundCap);
    mStroker->setJoinStyle(Qt::RoundJoin);
    mStroker->setWidth(this->attributes()->width());
}

PainterPath::~PainterPath()
{
    delete mPath;
    delete mStroker;
}

QRectF PainterPath::boundingRect() const
{
    return mStroker->createStroke(*mPath).boundingRect();
}

void PainterPath::addPoint(QPointF pos, bool modifier)
{
    if (mPath->elementAt(mPath->elementCount() - 1).isLineTo() && modifier) {
        prepareGeometryChange();
        mPath->setElementPositionAt(mPath->elementCount() - 1, pos.x(), pos.y());
    } else {
        mPath->lineTo(pos);
    }
    prepareGeometryChange();
}

void PainterPath::moveTo(QPointF newPos)
{
    prepareGeometryChange();
    mPath->translate(newPos - offset() - boundingRect().topLeft());
}

bool PainterPath::containsRect(QPointF topLeft, QSize size) const
{
    return mPath->intersects(QRectF(topLeft.x() - size.width() / 2,
                                    topLeft.y() - size.height() / 2,
                                    size.width(),
                                    size.height()));
}

//
// Private Functions
//

void PainterPath::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget* widget)
{

    if (mTransparent) {
        painter->setCompositionMode(QPainter::CompositionMode_ColorBurn);
        painter->setPen(Qt::NoPen);
    } else {
        painter->setPen(attributes()->color());
    }
    painter->setBrush(attributes()->color());
    painter->drawPath(mStroker->createStroke(*mPath));
}
