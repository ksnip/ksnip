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

#include "CustomCursor.h"

CustomCursor::CustomCursor() : QCursor()
{
}

CustomCursor::CustomCursor(CursorShape shape, const QColor& color, int size) :
    QCursor(getPixmapForShape(shape, color, size))
{
}

QPixmap CustomCursor::getPixmapForShape(CursorShape shape, const QColor& color, int size) const
{
    switch(shape) {
        case Circle:
            return createCirclePixmap(color, size);
        case Rect:
            return createRectPixmap(color, size);
        case Cross:
            return createCrossPixmap(QColor(93,91,89));
    }
}

QPixmap CustomCursor::createCrossPixmap(const QColor& color) const
{
    auto pixmap = createEmptyPixmap(20);
    QPainter painter(&pixmap);
    painter.setPen(QPen(color, 2, Qt::SolidLine));
    painter.drawLine(4, 13, 24, 13);
    painter.drawLine(13, 4, 13, 24);
    painter.setPen(QPen(QColor("red"), 2, Qt::SolidLine));
    painter.drawPoint(13,13);
    return pixmap;
}

QPixmap CustomCursor::createCirclePixmap(const QColor& color, int size) const
{
    auto pixmap = createEmptyPixmap(size);
    QPainter painter(&pixmap);
    painter.setBrush(color);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen("white");
    painter.drawEllipse(0, 0, size + 1, size + 1);
    return pixmap;
}

QPixmap CustomCursor::createRectPixmap(const QColor& color, int size) const
{
    auto pixmap = createEmptyPixmap(size);
    QPainter painter(&pixmap);
    painter.setBrush(color);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, size, size);
    return pixmap;
}

QPixmap CustomCursor::createEmptyPixmap(int size) const
{
    QPixmap pixmap(QSize(size + 2, size + 2));
    pixmap.fill(Qt::transparent);
    return pixmap;
}

