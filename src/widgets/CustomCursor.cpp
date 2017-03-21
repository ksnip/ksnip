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

CustomCursor::CustomCursor(const CursorShape &shape, const QColor &color, const int &size) :
    QCursor(createPixmap(shape, color, size))
{
}

CustomCursor::CustomCursor(const CursorShape &shape, const QColor &color) : QCursor(createPixmap(shape, color))
{

}

//
// Private Functions
//

/*
 * Create a custom pixmap based on provided enum, color and shape, drawing either
 * a colored circle or rectangle.
 */
QPixmap CustomCursor::createPixmap(const CursorShape &shape, const QColor &color, const int &size) const
{
    QPixmap pixmap(QSize(size + 2, size + 2));
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);

    painter.setBrush(color);

    if (shape == Circle) {
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen("white");
        painter.drawEllipse(0, 0, size + 1, size + 1);
    } else { // if rect, probably eraser
        painter.setPen(Qt::NoPen);
        painter.drawRect(0, 0, size, size);
    }

    return pixmap;
}

/*
 * Create custom pixmap with a cross, eventually more shapes can be added later on
 */
QPixmap CustomCursor::createPixmap(const CursorShape &shape, const QColor &color) const
{
    QColor c = color;
    if (!c.isValid()) {
        c.setRgb(93, 91, 89);
    }

    QPixmap pixmap(QSize(22, 22));
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);

    if (shape == Cross) {
        painter.setPen(QPen(c, 2, Qt::SolidLine));
        painter.drawLine(4, 13, 24, 13);
        painter.drawLine(13, 4, 13, 24);
    }

    return pixmap;
}
