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

#include "PainterArrow.h"

PainterArrow::PainterArrow(const QPointF& pos, const QPen& attributes) :
    PainterLine(pos, attributes)
{
    mScale = attributes.width();
    mArrowHeadLength = 20 * mScale;
    mArrowHeadWidth = 10 * mScale;
    mArrowHeadMid = 17 * mScale;
}

PainterArrow::PainterArrow(const PainterArrow& other) : PainterLine(other)
{
    this->mScale = other.mScale;
    this->mArrowHeadLength = other.mArrowHeadLength;
    this->mArrowHeadWidth = other.mArrowHeadWidth;
    this->mArrowHeadMid = other.mArrowHeadMid;
    this->mArrow = other.mArrow;
}

QRectF PainterArrow::boundingRect() const
{
    return mArrow.boundingRect().normalized();
}

void PainterArrow::addPoint(const QPointF& pos, bool modifier)
{
    PainterLine::addPoint(pos, modifier);
    updateArrow();
}

void PainterArrow::moveTo(const QPointF& newPos)
{
    PainterLine::moveTo(newPos);
    updateArrow();
}

void PainterArrow::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (isLineToShort()) {
        return;
    }

    painter->setPen(attributes().color());
    painter->setBrush(attributes().color());
    painter->drawPolygon(mArrow);

    paintDecoration(painter);
}

bool PainterArrow::isLineToShort() const
{
    return mLine->length() < (mArrowHeadMid);
}

void PainterArrow::updateArrow()
{
    auto tmpArrow = createArrow();
    mArrow = positionAndRotateArrow(tmpArrow);
}


QPolygonF PainterArrow::createArrow() const
{
    QPointF p0(0, 0);
    QPointF p1(-mArrowHeadLength, mArrowHeadWidth);
    QPointF p2(-mArrowHeadMid, mScale);
    QPointF p3(-mLine->length(), mScale);
    QPointF p4(-mLine->length(), -mScale);
    QPointF p5(-mArrowHeadMid, -mScale);
    QPointF p6(-mArrowHeadLength,-mArrowHeadWidth);

    QPolygonF arrow;
    arrow << p0 << p1 << p2 << p3 << p4 << p5 << p6;
    return arrow;
}

QPolygonF PainterArrow::positionAndRotateArrow(const QPolygonF& arrowHead) const
{
    auto endX = mLine->p2().x();
    auto endY = mLine->p2().y();
    auto angle = -mLine->angle();
    return QTransform().translate(endX, endY).rotate(angle).map(arrowHead);
}
