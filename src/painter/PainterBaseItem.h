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

#ifndef PAINTERBASEITEM_H
#define PAINTERBASEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPen>

class PainterBaseItem :  public QGraphicsItem
{
public:
    enum {
        Type = UserType + 1
    };

    enum PaintItemShape {
        Path,
        Rect,
        Circle,
        Text
    };

public:
    PainterBaseItem(PaintItemShape shape, QPen attributes);
    ~PainterBaseItem();
    virtual int type() const;
    virtual QRectF boundingRect() const = 0;
    virtual void addPoint(QPointF pos, bool modifier = 0) = 0;
    virtual void moveTo(QPointF newPos) = 0;
    virtual bool containsRect(QPointF topLeft, QSize size) const = 0;
    virtual bool isValid() const;
    virtual QPointF position() const;
    virtual QPen *attributes() const;
    virtual PaintItemShape ItemShape() const;
    virtual QPointF offset() const;
    virtual void setOffset(QPointF offset);
    virtual void setJoinStyle(Qt::PenJoinStyle join);
    virtual void setCapStyle(Qt::PenCapStyle cap);
    virtual void setOutlineStyle(Qt::PenStyle penStyle);
    virtual void setOutlineWidth(int width);
    virtual void setOutlineColor(QColor color);

private:
    PaintItemShape  mItemType;
    QPen           *mAttributes;
    QPointF         mOffset;

};

#endif // PAINTERBASEITEM_H
