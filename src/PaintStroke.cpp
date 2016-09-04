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

#include "PaintStroke.h"

PaintStroke::PaintStroke( QPointF startingPoint, QPen attributes, bool isTransparent ) : QGraphicsItem()
{
    mPath.moveTo( startingPoint );
    mAttributes = attributes;
    mIsTransparent = isTransparent;

    mStroker.setCapStyle( Qt::RoundCap );
    mStroker.setJoinStyle( Qt::RoundJoin );
    mStroker.setWidth( mAttributes.width() );
}

QRectF PaintStroke::boundingRect() const
{
    return mStroker.createStroke( mPath ).boundingRect();
}

int PaintStroke::type() const
{
    return Type;
}

void PaintStroke::lineTo( QPointF p )
{
    prepareGeometryChange();
    mPath.lineTo( p );
}

/*
 * Moves last point of the path to new location, can be used to draw
 * straight lines.
 */
void PaintStroke::lastLineTo( QPointF p )
{
    if ( mPath.elementAt( mPath.elementCount() - 1 ).isLineTo() )
    {
        prepareGeometryChange();
        mPath.setElementPositionAt( mPath.elementCount() - 1, p.x(), p.y() );
    }
    else
    {
        lineTo( p );
    }
}

bool PaintStroke::isUnderLocation( QPointF p )
{
    // Build a small rect at the provided point location and check if it 
    // intersects with the path.
    return mPath.intersects(QRectF(p.x() - 2, p.y() - 2, 4, 4));
}

void PaintStroke::paint( QPainter* painter, const QStyleOptionGraphicsItem* , QWidget* )
{
    if ( mIsTransparent )
    {
        painter->setCompositionMode( QPainter::CompositionMode_ColorBurn );
    }
    painter->setPen( mAttributes.color() );
    painter->setBrush( mAttributes.color() );
    painter->drawPath( mStroker.createStroke( mPath ) );
}









