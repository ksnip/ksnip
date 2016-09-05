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
#include <QtGui>

#include "PaintArea.h"

PaintArea::PaintArea() : QGraphicsScene()
{
    mCurrentPaintStroke = NULL;
    mCurrentPaintMode = Pen;
    mIsSnapping = false;

    mPen.setWidth( 3 );
    mPen.setColor( Qt::red );

    mMarker.setWidth( 20 );
    mMarker.setColor( QColor( 255, 255, 0, 255 ) );
}

void PaintArea::loadCapture( QPixmap pixmap )
{
    clear();
    addPixmap( pixmap );
    setSceneRect( 0, 0, pixmap.width(), pixmap.height() );
}

QSize PaintArea::getAreaSize()
{
    return sceneRect().size().toSize();
}

void PaintArea::setScribbleMode( PaintMode scribbleMode )
{
    mCurrentPaintMode = scribbleMode;
}

PaintArea::PaintMode PaintArea::getPaintMode()
{
    return mCurrentPaintMode;
}

QImage PaintArea::exportAsImage()
{
    QImage image( sceneRect().size().toSize(), QImage::Format_ARGB32 ); 
    image.fill( Qt::transparent );                                           

    QPainter painter( &image );
    painter.setRenderHint(QPainter::Antialiasing);
    render( &painter );
    return image;
}

void PaintArea::mousePressEvent( QGraphicsSceneMouseEvent* event )
{
    if ( event->button() != Qt::LeftButton )
        return;
        
    emit imageChanged();
    
    if ( mCurrentPaintMode == Erase )
        erasePaintStroke( event->scenePos() );
    else
        addNewPaintStroke( event->scenePos() );
        
    QGraphicsScene::mousePressEvent( event );
}

void PaintArea::mouseMoveEvent( QGraphicsSceneMouseEvent* event )
{
    if ( event->buttons() != Qt::LeftButton )
        return;

    if ( mCurrentPaintMode == Erase )
        erasePaintStroke( event->scenePos() );
    else
        addToCurrentPaintStroke( event->scenePos() );

    QGraphicsScene::mouseMoveEvent( event );
}

void PaintArea::mouseReleaseEvent( QGraphicsSceneMouseEvent* event )
{
    if ( event->button() != Qt::LeftButton )
        mCurrentPaintStroke = NULL;

    QGraphicsScene::mouseReleaseEvent( event );
}

void PaintArea::keyPressEvent( QKeyEvent* event )
{
    if ( event->key() == Qt::Key_Shift )
        mIsSnapping = true;

    QGraphicsScene::keyPressEvent( event );
}

void PaintArea::keyReleaseEvent( QKeyEvent* event )
{
    if ( event->key() == Qt::Key_Shift )
        mIsSnapping = false;

    QGraphicsScene::keyReleaseEvent( event );
}

void PaintArea::addNewPaintStroke( QPointF mousePosition )
{
    if ( mCurrentPaintMode == Pen )
        mCurrentPaintStroke = new PaintStroke( mousePosition, mPen );
    else
        mCurrentPaintStroke = new PaintStroke( mousePosition, mMarker, true );
    
    addItem( mCurrentPaintStroke );
}

void PaintArea::addToCurrentPaintStroke( QPointF mousePosistion )
{
    if ( mCurrentPaintStroke == NULL )
    {
        qCritical( "PaintArea::addToCurrentPaintStroke: Unable to add point to path, current path set to NULL" );
        return;
    }

    if ( mIsSnapping )
        mCurrentPaintStroke->lastLineTo( mousePosistion );
    else
        mCurrentPaintStroke->lineTo( mousePosistion );

    mCurrentPaintStroke->lineTo( mousePosistion );
}

bool PaintArea::erasePaintStroke( QPointF mousePosition )
{
    PaintStroke *item = NULL;

    for ( int i = 0 ; i < items().count() ; i++ )
    {
        item = qgraphicsitem_cast<PaintStroke*>( items().at( i ) );
        if ( item && item->isUnderLocation( mousePosition ) )
        {
            removeItem( items().at( i ) );
            return true;
        }
    }
    return false;
}