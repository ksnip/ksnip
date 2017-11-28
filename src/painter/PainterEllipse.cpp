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

PainterEllipse::PainterEllipse(const QPointF& pos, const QPen& attributes, bool filled) :
    PainterRect(pos, attributes, filled)
{
}

PainterEllipse::PainterEllipse(const PainterEllipse& other) : PainterRect(other)
{
}

bool PainterEllipse::containsRect(const QPointF& topLeft, const QSize& size) const
{
    if (mFilled) {
        QRegion r(mRect.normalized().toRect(), QRegion::Ellipse);
        return r.contains(QRect(topLeft.x() - size.width() / 2,
                                topLeft.y() - size.height() / 2,
                                size.width(),
                                size.height()));
    } else {
        // When the rect is not filled, do not allow grabbing the empty space.
        // TODO Improve this function, could be eventually more efficient.
        QRegion r1(mRect.normalized().toRect(), QRegion::Ellipse);
        auto w = attributes().width();
        QRegion r2(mRect.normalized().adjusted(w, w, -w, -w).toRect(), QRegion::Ellipse);

        return r1.subtracted(r2).contains(QRect(topLeft.x() - size.width() / 2,
                                                topLeft.y() - size.height() / 2,
                                                size.width(),
                                                size.height()));
    }
}

void PainterEllipse::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (mFilled) {
        painter->setBrush(attributes().color());
    }

    painter->setPen(attributes());
    painter->drawEllipse(mRect.normalized());

    paintDecoration(painter);
}
