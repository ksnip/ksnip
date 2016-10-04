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
#include "PaintArea.h"

PaintArea::PaintArea() : QGraphicsScene(),
    mPen( new QPen ),
    mCursor( NULL ),
    mMarker( new QPen )
{
    mCurrentPaintStroke = NULL;
    mCurrentPaintMode = Pen;
    mIsSnapping = false;
}

//
// Public Functions
//

/*
 * Load new captured image and add it to the scene and set the scene size to the size of the loaded
 * image.
 */
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

void PaintArea::setPaintMode( PaintMode paintMode )
{
    mCurrentPaintMode = paintMode;
    setCursorForPaintArea();
}

PaintArea::PaintMode PaintArea::getPaintMode()
{
    return mCurrentPaintMode;
}

/*
 * In order to export the scene as Image we must use a QPainter to draw all scene items to a new
 * image which we can the export.
 */
QImage PaintArea::exportAsImage()
{
    QImage image( sceneRect().size().toSize(), QImage::Format_ARGB32 );
    image.fill( Qt::transparent );

    QPainter painter( &image );
    painter.setRenderHint( QPainter::Antialiasing );
    render( &painter );
    return image;
}

void PaintArea::setPenProperties( QColor color, int width )
{
    mPen->setColor( color );
    mPen->setWidth( width );
    setCursorForPaintArea();
}

QPen PaintArea::getPenProperties()
{
    return *mPen;
}

void PaintArea::setMarkerProperties( QColor color, int width )
{
    mMarker->setColor( color );
    mMarker->setWidth( width );
    setCursorForPaintArea();
}

QPen PaintArea::getMarkerProperties()
{
    return *mMarker;
}

//
// Protected Functions
//

void PaintArea::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
    if ( event->button() != Qt::LeftButton ) {
        return;
    }

    if ( mCurrentPaintMode == Erase ) {
        erasePaintStroke( event->scenePos() );
    }
    else {
        addNewPaintStroke( event->scenePos() );
    }

    QGraphicsScene::mousePressEvent( event );
}

void PaintArea::mouseMoveEvent( QGraphicsSceneMouseEvent *event )
{
    if ( event->buttons() != Qt::LeftButton ) {
        return;
    }

    if ( mCurrentPaintMode == Erase ) {
        erasePaintStroke( event->scenePos() );
    }
    else {
        addToCurrentPaintStroke( event->scenePos() );
    }

    QGraphicsScene::mouseMoveEvent( event );
}

void PaintArea::mouseReleaseEvent( QGraphicsSceneMouseEvent *event )
{
    if ( event->button() == Qt::LeftButton ) {
        mCurrentPaintStroke = NULL;

        // Inform the MainWindow that something was drawn on the image so the user should be able to
        // save again.
        emit imageChanged();
    }

    QGraphicsScene::mouseReleaseEvent( event );
}

void PaintArea::keyPressEvent( QKeyEvent *event )
{
    if ( event->key() == Qt::Key_Shift ) {
        mIsSnapping = true;
    }

    QGraphicsScene::keyPressEvent( event );
}

void PaintArea::keyReleaseEvent( QKeyEvent *event )
{
    if ( event->key() == Qt::Key_Shift ) {
        mIsSnapping = false;
    }

    QGraphicsScene::keyReleaseEvent( event );
}

//
// Private Functions
//
void PaintArea::addNewPaintStroke( QPointF mousePosition )
{
    if ( mCurrentPaintMode == Pen ) {
        mCurrentPaintStroke = new PaintStroke( mousePosition, *mPen );
    }
    else {
        mCurrentPaintStroke = new PaintStroke( mousePosition, *mMarker, true );
    }

    addItem( mCurrentPaintStroke );
}

void PaintArea::addToCurrentPaintStroke( QPointF mousePosistion )
{
    if ( mCurrentPaintStroke == NULL ) {
        qCritical( "PaintArea::addToCurrentPaintStroke: Unable to add point to path, \
        current path set to NULL" );
        return;
    }

    if ( mIsSnapping ) {
        mCurrentPaintStroke->lastLineTo( mousePosistion );
    }
    else {
        mCurrentPaintStroke->lineTo( mousePosistion );
    }

    mCurrentPaintStroke->lineTo( mousePosistion );
}

bool PaintArea::erasePaintStroke( QPointF mousePosition )
{
    PaintStroke *item = NULL;

    for ( int i = 0 ; i < items().count() ; i++ ) {
        item = qgraphicsitem_cast<PaintStroke *> ( items().at( i ) );

        if ( item && item->isUnderLocation( mousePosition ) ) {
            removeItem( items().at( i ) );
            return true;
        }
    }

    return false;
}

/*
 * Set the mouse cursor on all views that show this scene to a specif cursor that represents the
 * currently selected paint tool
 */
void PaintArea::setCursorForPaintArea()
{
    if ( mCursor != NULL )
        delete mCursor;

    mCursor = getCursor();

    for ( int i = 0; i < views().length(); i++ ) {
        views().at( i )->setCursor( *mCursor );
    }
}

/*
 * Returns a new custom cursor based on currently selected paint tool
 */
CustomCursor *PaintArea::getCursor()
{
    switch ( mCurrentPaintMode ) {
    case Pen:
        return new CustomCursor( CustomCursor::Circle, mPen->color(), mPen->width() );
        break;

    case Marker:
        return new CustomCursor( CustomCursor::Circle, mMarker->color(), mMarker->width() );
        break;

    case Erase:
        return new CustomCursor( CustomCursor::Rect, QColor( "white" ), 6 );
        break;
    }
}