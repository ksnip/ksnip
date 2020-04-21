/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#include "CustomCursor.h"

CustomCursor::CustomCursor() : QCursor()
{
}

CustomCursor::CustomCursor(const QColor &color, int size) : QCursor(createCrossPixmap(color, size))
{
}

QPixmap CustomCursor::createCrossPixmap(const QColor& color, int size) const
{
    auto pixmap = createEmptyPixmap();
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine));
    painter.drawPoint(16, 16);
    painter.setPen(QPen(color, size, Qt::SolidLine));
    painter.drawLine(16, 12, 16, 0);
    painter.drawLine(16, 20, 16, 32);
    painter.drawLine(12, 16, 0, 16);
    painter.drawLine(20, 16, 32, 16);
    return pixmap;
}

QPixmap CustomCursor::createEmptyPixmap() const
{
    QPixmap pixmap(QSize(32, 32));
    pixmap.fill(Qt::transparent);
    return pixmap;
}
