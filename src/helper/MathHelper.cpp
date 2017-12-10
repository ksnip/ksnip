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

#include "MathHelper.h"

qreal MathHelper::distanceBetweenPoints(const QPointF& point1, const QPointF& point2)
{
    auto horizontalDistance = (point1.x() - point2.x()) * (point1.x() - point2.x());
    auto verticalDistance = (point1.y() - point2.y()) * (point1.y() - point2.y());
    return qSqrt(horizontalDistance + verticalDistance);
}

QPointF MathHelper::getBeginOfRounding(const QPointF& point1, const QPointF& point2)
{
    QPointF startPoint;
    auto rat = 10.0 / distanceBetweenPoints(point1, point2);
    if (rat > 0.5) {
        rat = 0.5;
    }
    startPoint.setX((1.0 - rat) * point1.x() + rat * point2.x());
    startPoint.setY((1.0 - rat) * point1.y() + rat * point2.y());
    return startPoint;
}

QPointF MathHelper::getEndOfRounding(const QPointF& point1, const QPointF& point2)
{
    QPointF endPoint;
    auto rat = 10.0 / distanceBetweenPoints(point1, point2);
    if (rat > 0.5) {
        rat = 0.5;
    }
    endPoint.setX(rat * point1.x() + (1.0 - rat) * point2.x());
    endPoint.setY(rat * point1.y() + (1.0 - rat) * point2.y());
    return endPoint;
}

qreal MathHelper::smallerValue(qreal value1, qreal value2)
{
    qreal l = (qAbs(value1) < qAbs(value2)) ? qAbs(value1) : qAbs(value2);
    return (value1 < 0) ? -l : l;
}

QRect MathHelper::getRectBetweenTwoPoints(const QPoint& point1, const QPoint& point2)
{
    return QRect(point1, point2).normalized();
}

QPoint MathHelper::getLineCenter(const QLine& line)
{
    return (line.p1() + line.p2()) / 2;
}

QPoint MathHelper::getCenterBetweenPoints(const QPoint& p1, const QPoint& p2)
{
    return (p1 + p2) / 2;
}

qreal MathHelper::roundAngleTo(const qreal currentAngle, const int increments)
{
    auto modulo = (int)currentAngle % increments;
    auto requiredRoundup = modulo < increments / 2 ? -modulo : increments - modulo;
    auto newAngle = qFloor(currentAngle + requiredRoundup);
    return newAngle;
}

