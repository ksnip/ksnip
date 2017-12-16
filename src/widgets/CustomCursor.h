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

#ifndef CUSTOMCURSOR_H
#define CUSTOMCURSOR_H

#include <QCursor>
#include <QPainter>

class CustomCursor : public QCursor
{
public:
    enum CursorShape {
        Rect,
        Circle,
        Cross
    };

public:
    CustomCursor();
    CustomCursor(CursorShape shape, const QColor &color = nullptr, int size = 22);

private:
    QPixmap getPixmapForShape(CursorShape shape, const QColor &color, int size) const;
    QPixmap createCrossPixmap(const QColor &color, int size) const;
    QPixmap createCirclePixmap(const QColor &color, int size) const;
    QPixmap createRectPixmap(const QColor &color, int size) const;
    QPixmap createEmptyPixmap() const;
    QPoint getPixmapCenter(const QPixmap &pixmap) const;
};

#endif // CUSTOMCURSOR_H
