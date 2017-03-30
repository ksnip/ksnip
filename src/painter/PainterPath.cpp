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

/*
 * Credit for the smooth algorithm goes to Bojan Kverh, see his post here:
 * https://www.toptal.com/c-plus-plus/rounded-corners-bezier-curves-qpainter
 */

#include "PainterPath.h"
#include <cmath>

namespace
{
float distance(const QPointF& pt1, const QPointF& pt2)
{
    float hd = (pt1.x() - pt2.x()) * (pt1.x() - pt2.x());
    float vd = (pt1.y() - pt2.y()) * (pt1.y() - pt2.y());
    return std::sqrt(hd + vd);
}

QPointF getLineStart(const QPointF& pt1, const QPointF& pt2)
{
    QPointF pt;
    float rat = 10.0 / distance(pt1, pt2);
    if (rat > 0.5) {
        rat = 0.5;
    }
    pt.setX((1.0 - rat) * pt1.x() + rat * pt2.x());
    pt.setY((1.0 - rat) * pt1.y() + rat * pt2.y());
    return pt;
}

QPointF getLineEnd(const QPointF& pt1, const QPointF& pt2)
{
    QPointF pt;
    float rat = 10.0 / distance(pt1, pt2);
    if (rat > 0.5) {
        rat = 0.5;
    }
    pt.setX(rat * pt1.x() + (1.0 - rat)*pt2.x());
    pt.setY(rat * pt1.y() + (1.0 - rat)*pt2.y());
    return pt;
}

}

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

/*
 * Simple function that smooths out the existing path. The function basically
 * collects all points in a path and skips points that are too close to each
 * other, to close points prevent smoothing out. Then in next step on every
 * point we remove the corner between two lines and replace it with an quadTo
 * Bezier curve. The min factor is used to test the distance between two points,
 * distance below min is ignored and points skipped.
 */
void PainterPath::smoothOut(const float& factor)
{
    QList<QPointF> points;
    QPointF p;
    for (int i = 0; i < mPath->elementCount() - 1; i++) {
        p = QPointF(mPath->elementAt(i).x, mPath->elementAt(i).y);

        // Except for first and last points, check what the distance between two
        // points is and if its less the min, don't add them to the list.
        if (points.count() > 1 && (i < mPath->elementCount() - 2) && (distance(points.last(), p) < factor)) {
            continue;
        }
        points.append(p);
    }

    // Don't proceed if we only have 3 or less points.
    if (points.count() < 3) {
        return;
    }

    QPointF pt1;
    QPointF pt2;
    QPainterPath* path = new QPainterPath();
    for (int i = 0; i < points.count() - 1; i++) {
        pt1 = getLineStart(points[i], points[i + 1]);
        if (i == 0) {
            path->moveTo(pt1);
        } else {
            path->quadTo(points[i], pt1);
        }
        pt2 = getLineEnd(points[i], points[i + 1]);
        path->lineTo(pt2);
    }

    delete mPath;
    mPath = path;
    prepareGeometryChange();
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
