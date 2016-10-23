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
#include "src/backend/KsnipConfig.h"

PaintArea::PaintArea() : QGraphicsScene(),
    mCursor( cursor() )
{
    mCurrentPaintStroke = NULL;
    mCurrentPaintMode = Pen;
    mIsSnapping = false;

    // Set pixamp to null so we can check if anything was loaded
    mPixmap = NULL;

    // Connect to update signal so that we are informed any time the config changes, we use that to
    // set the correct mouse cursor
    connect( KsnipConfig::instance(), SIGNAL( painterUpdated() ), this, SLOT( setCursor() ) );
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
    mPixmap = addPixmap( pixmap );
    setSceneRect( 0, 0, pixmap.width(), pixmap.height() );
}

// Return scene rect which is the current size of the area
QSize PaintArea::areaSize()
{
    return sceneRect().size().toSize();
}

void PaintArea::setPaintMode( PaintMode paintMode )
{
    mCurrentPaintMode = paintMode;
    setCursor();
}

/*
 * In order to export the scene as Image we must use a QPainter to draw all scene items to a new
 * image which we can the export. If no pixmap has been loaded return a null image.
 */
QImage PaintArea::exportAsImage()
{
    if ( !isValid() ) {
        return QImage();
    }

    QImage image( sceneRect().size().toSize(), QImage::Format_ARGB32 );
    image.fill( Qt::transparent );

    QPainter painter( &image );
    painter.setRenderHint( QPainter::Antialiasing );
    render( &painter );
    return image;
}

void PaintArea::setIsEnabled( bool enabled )
{
    mIsEnabled = enabled;
    setCursor();
}

bool PaintArea::isEnabled()
{
    return mIsEnabled;
}

/*
 * The scene is only valid if a pixmap has been loaded
 */
bool PaintArea::isValid()
{
    if ( mPixmap == NULL ) {
        return false;
    }
    else {
        return true;
    }
}

/*
 * Crop the capture image to the provided rect and set the scene rect appropriately
 */
void PaintArea::crop( QRect rect )
{
    setSceneRect( rect );
    mPixmap->setPixmap( mPixmap->pixmap().copy( rect ) );
    mPixmap->setPos( rect.x(), rect.y() );
}


//
// Protected Functions
//

void PaintArea::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
    if ( event->button() == Qt::LeftButton && mIsEnabled ) {
        switch ( mCurrentPaintMode ) {
        case Erase:
            erasePaintStroke( event->scenePos() );
            break;

        case Move:
            if ( getObjectForMove( event->scenePos() ) ) {
                setCursor();
            }
            break;
            
        case Pen:
        case Marker:
        default:
            addNewPaintStroke( event->scenePos() );
        }
    }

    QGraphicsScene::mousePressEvent( event );
}

void PaintArea::mouseMoveEvent( QGraphicsSceneMouseEvent *event )
{
    if ( event->buttons() == Qt::LeftButton && mIsEnabled ) {
        switch ( mCurrentPaintMode ) {
        case Erase:
            erasePaintStroke( event->scenePos() );
            break;

        case Move:
            moveObject( event->scenePos() );
            break;

        case Pen:
        case Marker:
        default:
            addToCurrentPaintStroke( event->scenePos() );
        }
    }

    QGraphicsScene::mouseMoveEvent( event );
}

void PaintArea::mouseReleaseEvent( QGraphicsSceneMouseEvent *event )
{
    if ( event->button() == Qt::LeftButton && mIsEnabled ) {
        switch ( mCurrentPaintMode ) {
        case Erase:
            erasePaintStroke( event->scenePos() );
            break;

        case Move:
            mCurrentPaintStroke = NULL;
            setCursor();
            mMoveOffset = QPointF(); // Set offset to 0,0
            break;

        case Pen:
        case Marker:
        default:
            mCurrentPaintStroke = NULL;
        }

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
void PaintArea::addNewPaintStroke( QPointF position )
{
    if ( mCurrentPaintMode == Pen ) {
        mCurrentPaintStroke = new PaintStroke( position, KsnipConfig::instance()->pen() );
    }
    else {
        mCurrentPaintStroke = new PaintStroke( position, KsnipConfig::instance()->marker(), true );
    }

    addItem( mCurrentPaintStroke );
}

void PaintArea::addToCurrentPaintStroke( QPointF position )
{
    if ( mCurrentPaintStroke == NULL ) {
        qCritical( "PaintArea::addToCurrentPaintStroke: Unable to add point to path, \
        current path set to NULL" );
        return;
    }

    if ( mIsSnapping ) {
        mCurrentPaintStroke->lastLineTo( position );
    }
    else {
        mCurrentPaintStroke->lineTo( position );
    }

    mCurrentPaintStroke->lineTo( position );
}

bool PaintArea::erasePaintStroke( QPointF mousePosition )
{
    PaintStroke *item = NULL;

    for ( int i = 0 ; i < items().count() ; i++ ) {
        item = qgraphicsitem_cast<PaintStroke *> ( items().at( i ) );

        if ( item && item->isUnderLocation( mousePosition , 6) ) {
            removeItem( items().at( i ) );
            return true;
        }
    }

    return false;
}

/*
 * Check if any of the paths is under this position, if yes grab it.
 */
bool PaintArea::getObjectForMove( QPointF position )
{
    for ( int i = 0 ; i < items().count() ; i++ ) {
        mCurrentPaintStroke = qgraphicsitem_cast<PaintStroke *> ( items().at( i ) );

        if ( mCurrentPaintStroke && mCurrentPaintStroke->isUnderLocation( position, 10 ) ) {
            mMoveOffset = position - mCurrentPaintStroke->boundingRect().topLeft();
            return true;
        }
    }

    // Have not found any path under location
    mCurrentPaintStroke = NULL;
    return false;
}

void PaintArea::moveObject( QPointF position )
{
    if ( mCurrentPaintStroke == NULL ) {
        return;
    }

    mCurrentPaintStroke->setPos( position - mMoveOffset );
}

/*
 * Set the mouse cursor on all views that show this scene to a specif cursor that represents the
 * currently selected paint tool.
 */
void PaintArea::setCursor()
{
    delete mCursor;
    mCursor = cursor();

    for ( int i = 0; i < views().length(); i++ ) {
        views().at( i )->setCursor( *mCursor );
    }
}

/*
 * Returns a new custom cursor based on currently selected paint tool, if the scene is disabled
 * return to default cursor.
 */
QCursor *PaintArea::cursor()
{
    if ( !mIsEnabled ) {
        return new CustomCursor();
    }

    switch ( mCurrentPaintMode ) {
    case Pen:
        return new CustomCursor( CustomCursor::Circle,
                                 KsnipConfig::instance()->penColor(),
                                 KsnipConfig::instance()->penSize() );

    case Marker:
        return new CustomCursor( CustomCursor::Circle,
                                 KsnipConfig::instance()->markerColor(),
                                 KsnipConfig::instance()->markerSize() );

    case Erase:
        return new CustomCursor( CustomCursor::Rect, QColor( "white" ), 6 );
        
    case Move:
        if (mCurrentPaintStroke == NULL)
            return new QCursor(Qt::OpenHandCursor);
        else
            return new QCursor(Qt::ClosedHandCursor);
    }
}