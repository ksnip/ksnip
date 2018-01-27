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

#include "PainterRect.h"

PainterRect::PainterRect(const QPointF& pos, const QPen &attributes, bool filled) :
    AbstractPainterItem(attributes),
    mFilled(filled)
{
    mRect.moveTo(pos);
    setJoinStyle(Qt::MiterJoin);
}

PainterRect::PainterRect(const PainterRect& other) : AbstractPainterItem(other)
{
    this->mFilled = other.mFilled;
    this->mRect = other.mRect;
}

QRectF PainterRect::boundingRect() const
{
    qreal width = attributes().widthF();
    return mRect.normalized().adjusted(-width / 2, -width / 2, width, width);
}

void PainterRect::addPoint(const QPointF& pos, bool modifier)
{
    prepareGeometryChange();
    mRect.setBottomRight(pos);
    if (modifier) {
        mRect.setHeight(MathHelper::smallerValue(mRect.height(), mRect.width()));
        mRect.setWidth(MathHelper::smallerValue(mRect.width(), mRect.height()));
    }
}

void PainterRect::moveTo(const QPointF& newPos)
{
    prepareGeometryChange();
    mRect.translate(newPos - offset() - boundingRect().topLeft());
}

bool PainterRect::containsRect(const QPointF& topLeft, const QSize& size) const
{
    QRectF rect(topLeft - QPointF(size.width() / 2, size.height() / 2), size);
    return shape().intersects(rect);
}

QPainterPath PainterRect::shape() const
{
    QPainterPath path;
    if(mFilled) {
        path.addRect(mRect);
    } else {
        QRegion r1(mRect.normalized().toRect());
        auto w = attributes().width();
        QRegion r2(mRect.normalized().adjusted(w, w, -w, -w).toRect());

        path.addRegion(r1.subtracted(r2));
    }
    return path;
}

void PainterRect::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (mFilled) {
        painter->setBrush(attributes().color());
    }
    painter->setPen(attributes());
    painter->drawRect(mRect.normalized());

    paintDecoration(painter);
}
