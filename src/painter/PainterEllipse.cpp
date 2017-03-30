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

#include "PainterEllipse.h"
#include <cmath>

namespace
{

float smallesLenght(float lenght1, float lenght2)
{
    float l = (std::abs(lenght1) < std::abs(lenght2)) ? std::abs(lenght1) : std::abs(lenght2);
    return (lenght1 < 0) ? -l : l;
}

}

//
// Public Functions
//

PainterEllipse::PainterEllipse(QPointF pos, QPen attributes, bool filled) :
    PainterBaseItem(Rect, attributes),
    mFilled(filled)
{
    mRect.moveTo(pos);
}

QRectF PainterEllipse::boundingRect() const
{
    qreal w = attributes()->widthF();
    return mRect.normalized().adjusted(-w / 2, -w / 2, w, w);
}

void PainterEllipse::addPoint(QPointF pos, bool modifier)
{
    mRect.setBottomRight(pos);
    if (modifier) {
        mRect.setHeight(smallesLenght(mRect.height(), mRect.width()));
        mRect.setWidth(smallesLenght(mRect.width(), mRect.height()));
    }
    prepareGeometryChange();
}

void PainterEllipse::moveTo(QPointF newPos)
{
    mRect.translate(newPos - offset() - boundingRect().topLeft());
    prepareGeometryChange();
}

bool PainterEllipse::containsRect(QPointF topLeft, QSize size) const
{
    if (mFilled) {
        QRegion r(mRect.toRect(), QRegion::Ellipse);
        return r.intersects(QRect(topLeft.x() - size.width() / 2,
                                  topLeft.y() - size.height() / 2,
                                  size.width(),
                                  size.height()));
    } else {
        // When the rect is not filled, do not allow grabbing the empty space.
        // TODO Improve this function, could be eventually more efficient.
        QRegion r1(mRect.normalized().toRect(), QRegion::Ellipse);
        QRegion r2(mRect.normalized().adjusted((attributes()->width()),
                                               (attributes()->width()),
                                               -(attributes()->width()),
                                               -(attributes()->width())).toRect(), QRegion::Ellipse);

        return r1.subtract(r2).contains(QRect(topLeft.x() - size.width() / 2,
                                              topLeft.y() - size.height() / 2,
                                              size.width(),
                                              size.height()));
    }
}

//
// Private Functions
//

void PainterEllipse::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (mFilled) {
        painter->setBrush(attributes()->color());
    }
    painter->setPen(*attributes());
    painter->drawEllipse(mRect.normalized());
}
