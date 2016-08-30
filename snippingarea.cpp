/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */
#include <QtGui>

#include "snippingarea.h"

/*
 * Constructor
 */
SnippingArea::SnippingArea( QWidget *parent ) : QWidget( parent )
{
    // Hide the widget background, we will draw it manually on the paint event
    setAttribute( Qt::WA_TranslucentBackground, true );

    // Make the frame span across the screen and show above any other widget
    setWindowFlags( Qt::FramelessWindowHint | Qt::ToolTip );
    setFixedSize( QDesktopWidget().size() );
}

/*
 * Detect mouse button down event and continue only when the pressed
 * button was the LMB, store the position where the button was pressed.
 */
void SnippingArea::mousePressEvent( QMouseEvent* event )
{
    if ( event->button() != Qt::LeftButton )
    {
        return;
    }
    mMouseDownPosition = event->pos();
    mCaptureArea =  calculateArea( event->pos(), event->pos() );
    mMouseIsDown = true;
}

/*
 * Detect when a mouse button was released and only continue when the
 * released button was the LMB, store the position and emit an event
 * so that other can be informed.
*/
void SnippingArea::mouseReleaseEvent( QMouseEvent* event )
{
    if ( event->button() != Qt::LeftButton )
    {
        return;
    }

    mMouseIsDown = false;
    hide();
    emit areaSelected( mCaptureArea );
}

/*
 * Called when mouse is moved and updates mouse current position and
 * also calls the update function to draw the screen with the rectangle
 * that the user wants to capture.
 */
void SnippingArea::mouseMoveEvent( QMouseEvent* event )
{
    if ( !mMouseIsDown )
    {
        return;
    }

    mCaptureArea = calculateArea( mMouseDownPosition, event->pos() );
    this->update();

    QWidget::mouseMoveEvent( event );
}

/*
 * This event is called when the widget is drawn, in any case we draw the background
 * as it's transparent by default, next, in case the mouse is down, we also skip drawing
 * the rectangle that was selected for capture and draw a border around that region.
 */
void SnippingArea::paintEvent( QPaintEvent* event )
{
    QPainter painter( this );

    if ( mMouseIsDown )
    {
        painter.setClipRegion( QRegion( QRect( QPoint(), this->size() ) ).subtracted( QRegion( mCaptureArea ) ) );
    }

    painter.setBrush( QColor( 0, 0, 0, 150 ) );
    painter.drawRect( QRect( QPoint(), this->size() ) );

    if ( mMouseIsDown )
    {
        painter.setPen( QPen( Qt::red, 4, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin ) );
        painter.drawRect( mCaptureArea );
    }
    QWidget::paintEvent( event );
}

/*
 * Calculates a rectangle area based on two points provided.
 */
QRect SnippingArea::calculateArea( QPoint pointA, QPoint pointB )
{
    return QRect( QPoint( ( pointA.x() <= pointB.x() ? pointA.x() : pointB.x() ),
                          ( pointA.y() <= pointB.y() ? pointA.y() : pointB.y() ) ),
                  QPoint( ( pointA.x() >= pointB.x() ? pointA.x() : pointB.x() ),
                          ( pointA.y() >= pointB.y() ? pointA.y() : pointB.y() ) ) );
}






