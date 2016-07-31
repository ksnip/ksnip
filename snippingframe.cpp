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

#include "snippingframe.h"

#include <QtGui>

/*
 * Constructor
 */
SnippingFrame::SnippingFrame(CaptureWindow *parent) : QWidget()
{
    // Create a connection back to the parent
    this->parent = parent;
    
    // Make the frame span across the screen
    setWindowFlags( Qt::FramelessWindowHint | Qt::Tool);
    setFixedSize(QDesktopWidget().size()); 
    
    // Hide the widget background, we will draw it manually on the paint event
    this->setAttribute( Qt::WA_TranslucentBackground, true );
}

/* 
 * Detect mouse button down event and continue only when the pressed
 * button was the LMB, store the position where the button was pressed.
 */ 
void SnippingFrame::mousePressEvent ( QMouseEvent* event)
{
    if(event->button() != Qt::LeftButton)
      return;
    mouseDownPosistion = event->pos();
    mouseCurrentPosistion = event->pos();
    mouseIsDown = true;
}

/*
 * Detect when a mouse button was released and only continue when the
 * released button was the LMB, store the position and emit an event
 * so that other can be informed.
*/ 
void SnippingFrame::mouseReleaseEvent ( QMouseEvent* event)
{
    if(event->button() != Qt::LeftButton)
      return;
    
    mouseIsDown = false;
    emit rectSelected(mouseDownPosistion, mouseCurrentPosistion);
}

/*
 * Called when mouse is moved and updates mouse current position and
 * also calls the update function to draw the screen with the rectangle
 * that the user wants to capture.
 */
void SnippingFrame::mouseMoveEvent ( QMouseEvent* event)
{
    if(!mouseIsDown)
      return;
    
    mouseCurrentPosistion = event->pos();
    this->update();
    
    QWidget::mouseMoveEvent(event);
}

/*
 * This event is called when the widget is drawn, in any case we draw the background 
 * as it's transparent by default, next, in case the mouse is down, we also skip drawing
 * the rectangle that was selected for capture and draw a border around that region.
 */
void SnippingFrame::paintEvent ( QPaintEvent* event)
{
    QPainter painter(this);
    
    if(mouseIsDown)
	painter.setClipRegion(QRegion(QRect(QPoint(), this->size())).subtracted(QRegion(mouseDownPosistion.x(), 
											mouseDownPosistion.y(), 
											mouseCurrentPosistion.x() - mouseDownPosistion.x(), 
											mouseCurrentPosistion.y() - mouseDownPosistion.y())));
    
    painter.setBrush(QColor(0, 0, 0, 150));
    painter.drawRect(QRect(QPoint(), this->size()));
    
    if(mouseIsDown)
    {
	painter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter.drawRect(mouseDownPosistion.x() - 2, 
			 mouseDownPosistion.y() - 2, 
			 mouseCurrentPosistion.x() - mouseDownPosistion.x() + 3, 
			 mouseCurrentPosistion.y() - mouseDownPosistion.y() + 3); 
    }  
    QWidget::paintEvent(event);
}

/*
 * Function that is called any time the widget is brought up, we need
 * to clear any mask that was used from previous captures. 
 */
void SnippingFrame::show()
{
    this->clearMask();
    QWidget::show();
}


