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

#include "capturewindow.h"
#include "snippingframe.h"
#include "paintwindow.h"

/*
 * Constructor
 */

CaptureWindow::CaptureWindow()
{
  // Create the three buttons that we need
  newCapButton    = new QPushButton("New");
  cancelCapButton = new QPushButton("Cancel");
  optionsButton   = new QPushButton("Options");
  
  // Connect button signals with widget slots so that we can capture the events
  newCapButton->connect(newCapButton, SIGNAL(clicked()), this, SLOT(newCaptureClicked()));
  cancelCapButton->connect(cancelCapButton, SIGNAL(clicked()), this, SLOT(cancelCaptureClicked()));
  optionsButton->connect(optionsButton, SIGNAL(clicked()), this, SLOT(optionsClicked()));
  
  // Add the buttons to the layout
  buttonsLayout = new QHBoxLayout;
  buttonsLayout->addStretch();
  buttonsLayout->addWidget(newCapButton);
  buttonsLayout->addWidget(cancelCapButton);
  buttonsLayout->addWidget(optionsButton); 
  setLayout(buttonsLayout);
  
  setWindowTitle("ksnip");
  cancelCapButton->setEnabled(false);
  
  // Disable widget resizing
  setFixedSize(this->minimumSize());
  setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);    
  
  snipframe = new SnippingFrame(this);
  connect(snipframe, SIGNAL(rectSelected(QPoint,QPoint)), this, SLOT(rectSelected(QPoint,QPoint)));
  
  paintWindow = new PaintWindow(this);
}

/*
 * Check if we have a valid snipping frame, if not, create a new snipping frame 
 * and connect to the rectSelected signal. Show the new snipping window and 
 * bring this window to front. 
 */
void CaptureWindow::newCaptureClicked()
{  
    snipframe->show();
       
    this->activateWindow();
    newCapButton->setEnabled(false);
    cancelCapButton->setEnabled(true);
}

/*
 * Called when the cancel button was pressed, check if we have a valid snipping frame
 * if yes, hide it, we are not longer capturing.
 */
void CaptureWindow::cancelCaptureClicked()
{
    snipframe->hide();
    newCapButton->setEnabled(true);
    cancelCapButton->setEnabled(false);
}

/*
 * NOT YET IMPLEMENTED
 */
void CaptureWindow::optionsClicked()
{
    setWindowTitle("Options");
}

/*
 * This function is called when the user has finished selecting a rectangular 
 * area for the capture, we will use the two QPoints to capture the screen 
 * between them. Before we start the capture, we hide all window so that we can 
 * see the screen. With the captured screen we open the paint window.
 */
void CaptureWindow::rectSelected ( QPoint mouseDownPos, QPoint mouseUpPos )
{
    snipframe->hide();
    newCapButton->setEnabled(true);
    cancelCapButton->setEnabled(false);
    
    hide();
    delay(400);
    paintWindow->show(grabScreen(mouseDownPos, mouseUpPos));
}

/*
 * Captures the screen between the two provided QPoints.
 */
QPixmap CaptureWindow::grabScreen (QPoint mouseDownPos, QPoint mouseUpPos)
{
    QPixmap capImage;
    capImage = QPixmap(); 
    capImage = QPixmap::grabWindow(QApplication::desktop()->winId(), mouseDownPos.x(), mouseDownPos.y(), mouseUpPos.x() - mouseDownPos.x(), mouseUpPos.y() - mouseDownPos.y());
    return capImage;
}

/*
 * Stops the executions for the time provided in milliseconds effectively
 * adding delay so that the hide() call can be propagated.
 */
void CaptureWindow::delay (int ms)
{
    QTime dieTime= QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

/*
 * Called when the window is closed so that we can clean up before closing.
 */
void CaptureWindow::closeEvent ( QCloseEvent* event)
{
    snipframe->close();
    paintWindow->close();
    QWidget::closeEvent(event);
}

void CaptureWindow::TakeNewCapture()
{
    this->show();
    newCaptureClicked();
}








