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

#ifndef PAINTWINDOW_H
#define PAINTWINDOW_H

#include <QWidget>

#include "capturewindow.h"

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QGraphicsScene;
class QGraphicsView;
class QClipboard;

class PaintWindow : public QWidget
{
  Q_OBJECT
public:
    PaintWindow( CaptureWindow* parent);          /* Constructor                                                              */
    void show(QPixmap captureImage);              /* Function used to show the widget, takes the image to present as argument */
    
private slots:
    void newCaptureClicked();                     /* Slot called when the new capture button is clicked                       */
    void saveCaptureClicked();                    /* Slot called when the save button is clicked                              */
    void copyToClipClicked();                     /* Slot called when the copy to clipboard button is clicked                 */
       
private:
    CaptureWindow  *parent;                       /* Parent window that opened the SnippingFrame                              */
    QPushButton    *newCapButton;                 /* Push button that starts new capture                                      */
    QPushButton    *saveButton;                   /* Button to save the captured image to disk                                */
    QPushButton    *copyClipButton;               /* Button used to copy the image to clipboard                               */
    QHBoxLayout    *buttonsLayout;                /* Layout used to organize all buttons on this widget                       */
    QVBoxLayout    *windowLayout;                 /* Layout used to organize the overall widget layout                        */
    QGraphicsScene *captureScene;                 /* Graphics Scene used to present the captured image and allow editing      */ 
    QGraphicsView  *captureView;                  /* Graphics view used to present the captured image and allow editing       */
    QClipboard     *clipboard;                    /* Clipboard that is used to store capture images to the OS clipboard       */
};

#endif // PAINTWINDOW_H
