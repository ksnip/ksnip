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

#include "PainterLine.h"

PainterLine::PainterLine(const QPointF& pos, const QPen& attributes) :
    AbstractPainterItem(attributes),
    mLine(new QLineF)
{
    mLine->setP1(pos);
    mLine->setP2(pos + QPointF(1,1));
}

PainterLine::PainterLine(const PainterLine& other) : AbstractPainterItem(other)
{
    mLine = new QLineF(*other.mLine);
}

PainterLine::~PainterLine()
{
    delete mLine;
}

void PainterLine::addPoint(const QPointF& pos, bool modifier)
{
    prepareGeometryChange();
    mLine->setP2(pos);
    if (modifier) {
        auto newAngle = MathHelper::roundAngleTo(mLine->angle(), 45);
        mLine->setAngle(newAngle);
    }
    updateShape();
}

void PainterLine::moveTo(const QPointF& newPos)
{
    prepareGeometryChange();
    mLine->translate(newPos - offset() - boundingRect().topLeft());
    updateShape();
}

void PainterLine::updateShape()
{
    QPainterPath path(mLine->p1());
    path.lineTo(mLine->p2());
    changeShape(path);
}

void PainterLine::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    auto pen = attributes();
    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);
    painter->setBrush(attributes().color());
    painter->drawLine(*mLine);

    paintDecoration(painter);
}
