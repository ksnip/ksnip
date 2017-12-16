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
            return createCrossPixmap(color, size);
    }
}

QPixmap CustomCursor::createCrossPixmap(const QColor& color, int size) const
{
    auto pixmap = createEmptyPixmap();
    QPainter painter(&pixmap);
    painter.setPen(QPen(QColor("red"), 1, Qt::SolidLine));
    painter.drawPoint(16, 16);
    painter.setPen(QPen(color, size, Qt::SolidLine));
    painter.drawLine(16, 12, 16, 0);
    painter.drawLine(16, 20, 16, 32);
    painter.drawLine(12, 16, 0, 16);
    painter.drawLine(20, 16, 32, 16);
    return pixmap;
}

QPixmap CustomCursor::createCirclePixmap(const QColor& color, int size) const
{
    auto pixmap = createEmptyPixmap();
    auto pixmapCenter = getPixmapCenter(pixmap);
    QPainter painter(&pixmap);
    painter.setBrush(color);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen("white");
    auto radius = (size + painter.pen().width()) / 2;
    painter.drawEllipse(pixmapCenter, radius, radius);
    return pixmap;
}

QPixmap CustomCursor::createRectPixmap(const QColor& color, int size) const
{
    auto pixmap = createEmptyPixmap();
    auto pixmapCenter = getPixmapCenter(pixmap);
    QPainter painter(&pixmap);
    painter.setBrush(color);
    painter.setPen(Qt::NoPen);
    painter.drawRect(pixmapCenter.x() - size / 2, pixmapCenter.y() - size / 2, size, size);
    return pixmap;
}

QPixmap CustomCursor::createEmptyPixmap() const
{
    QPixmap pixmap(QSize(32, 32));
    pixmap.fill(Qt::transparent);
    return pixmap;
}

QPoint CustomCursor::getPixmapCenter(const QPixmap& pixmap) const
{
    return QPoint(pixmap.width() / 2, pixmap.height() / 2);
}
