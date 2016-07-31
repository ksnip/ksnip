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

#ifndef SNIPWINDOW_H
#define SNIPWINDOW_H

#include <QWidget>

#include "capturewindow.h"

class SnippingFrame : public QWidget
{
    Q_OBJECT

public:
    SnippingFrame( CaptureWindow* parent );       /* Constructor                                              */
    void show();
    
signals:
    void rectSelected(QPoint, QPoint);            /* Signal sent when user finished selecting capture area    */
  
protected:
    void mousePressEvent(QMouseEvent *);          /* Function called when mouse button was pressed            */
    void mouseReleaseEvent(QMouseEvent *);        /* Function called when mouse button was released           */
    void mouseMoveEvent(QMouseEvent *);           /* Function called when the mouse is moved on the widget    */
    void paintEvent(QPaintEvent *);               /* Function called when the widget is drawn                 */
    
private:
    CaptureWindow *parent;                        /* Parent window that opened the SnippingFrame              */
    QPoint         mouseDownPosistion;            /* Screen Position where the mouse button was pressed       */
    QPoint         mouseCurrentPosistion;         /* Screen Position where the mouse button was released      */
    bool           mouseIsDown;                   /* True when the user is currently drawing the capture area */
};

#endif // SNIPWINDOW_H
