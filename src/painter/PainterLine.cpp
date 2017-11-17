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
    PainterBaseItem(Line, attributes),
    mLine(new QLineF)
{
    mLine->setP1(pos);
    mLine->setP2(pos + QPointF(1,1));
}

QRectF PainterLine::boundingRect() const
{
    auto offset = attributes().width();
    return QRectF(mLine->p1(), mLine->p2()).normalized().adjusted(-offset, -offset, offset, offset);
}

void PainterLine::addPoint(const QPointF& pos, bool modifier)
{
    prepareGeometryChange();
    mLine->setP2(pos);
}

void PainterLine::moveTo(const QPointF& newPos)
{
    prepareGeometryChange();
    mLine->translate(newPos - offset() - boundingRect().topLeft());
}

bool PainterLine::containsRect(const QPointF& topLeft, const QSize& size) const
{
    return boundingRect().intersects(QRectF(topLeft, size));
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
