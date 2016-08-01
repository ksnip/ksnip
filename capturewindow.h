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

#ifndef CAPTUREWINDOW_H
#define CAPTUREWINDOW_H

#include <QWidget>

class QPushButton;
class QHBoxLayout;
class SnippingArea;
class PaintWindow;

class CaptureWindow : public QWidget
{
    Q_OBJECT
public:
    CaptureWindow();                           /* Constructor                                                    */
    void TakeNewCapture();                     /* Callable externally to allow starting from beginning           */
    
protected:
    void closeEvent(QCloseEvent *);            /* Close event, called when the window is closing for cleanup     */ 
    void keyPressEvent(QKeyEvent *);           /* Event which is called when any key is pressed                  */
    
private slots:
    void newCaptureClicked();                  /* Slot called when the new capture button is clicked             */
    void cancelCaptureClicked();               /* Slot called when the cancel button is clicked                  */
    void optionsClicked();                     /* Slot called when the options button is clicked                 */
    void areaSelected(QRect);         /* Slot called when the user finished selecting an capture area   */
    
private:
    QPushButton *newCapButton;                 /* Push button that starts new capture                            */
    QPushButton *cancelCapButton;              /* Push button that cancels current open capture                  */
    QPushButton *optionsButton;                /* Push button that opens the option menu                         */
    QHBoxLayout *buttonsLayout;                /* Horizontal Layout Box used to organize buttons                 */
    SnippingArea *sniparea;                    /* SnippingFrame widget used to select a capturing area           */
    PaintWindow *paintWindow;                  /* Paint window widget used to edit the captured image            */
    QPixmap grabScreen(QRect);                 /* Function that captures the screen between the two QPoints      */
    void delay( int ms );                      /* Adds some delay to execution so that the screen can be updated */
};

#endif // CAPTUREWINDOW_H
