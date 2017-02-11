/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#include "PaintStroke.h"

PaintStroke::PaintStroke(QPointF startingPoint, QPen attributes, bool isTransparent) :
    QGraphicsItem(),
    mPath(new QPainterPath),
    mAttributes(new QPen(attributes)),
    mStroker(new QPainterPathStroker)
{
    mIsTransparent = isTransparent;

    // Place the path at the right location and draw the first point, which is actually a line just
    // moved one pixel as QT won't draw a line if the point B is equal to point A
    mPath->moveTo(startingPoint);
    mPath->lineTo(startingPoint + QPointF(1, 1));

    //setup the stroker which we use to draw the path
    mStroker->setCapStyle(Qt::RoundCap);
    mStroker->setJoinStyle(Qt::RoundJoin);
    mStroker->setWidth(mAttributes->width());
}

//
// Public Functions
//

QRectF PaintStroke::boundingRect() const
{
    return mStroker->createStroke(*mPath).boundingRect();
}

int PaintStroke::type() const
{
    return Type;
}

void PaintStroke::lineTo(QPointF pos)
{
    prepareGeometryChange();
    mPath->lineTo(pos);
}

/*
 * Moves last point of the path to new location, can be used to draw
 * straight lines.
 */
void PaintStroke::lastLineTo(QPointF pos)
{
    if (mPath->elementAt(mPath->elementCount() - 1).isLineTo()) {
        prepareGeometryChange();
        mPath->setElementPositionAt(mPath->elementCount() - 1, pos.x(), pos.y());
    } else {
        lineTo(pos);
    }
}

/*
 *  Build a small rect at the provided point location and check if it  intersects with the path.
 *  This is used to detect overlapping, for features like removing/erasing the path or moving it.
 *  The provided short is used to draw a rectangle against which we check if there is as a collision
 */
bool PaintStroke::isUnderLocation(QPointF pos, short rectSize)
{
    return mPath->intersects(QRectF(pos.x() - rectSize / 2,
                                    pos.y() - rectSize / 2,
                                    rectSize,
                                    rectSize));
}

/*
 * Moves the path to the provided position. The path position is calculated for the top left corner.
 * Offset is not calculated, it should be already included.
 */
void PaintStroke::setPos(QPointF pos)
{
    mPath->translate(pos - boundingRect().topLeft());
    prepareGeometryChange();
}

//
// Private Functions
//
void PaintStroke::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget* widget)
{
    if (mIsTransparent) {
        painter->setCompositionMode(QPainter::CompositionMode_ColorBurn);
        painter->setPen(Qt::NoPen);
    } else {
        painter->setPen(mAttributes->color());
    }

    painter->setBrush(mAttributes->color());
    painter->drawPath(mStroker->createStroke(*mPath));
}
