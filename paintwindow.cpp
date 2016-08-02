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

#include "paintwindow.h"

/*
 * Constructor
 */
PaintWindow::PaintWindow ( CaptureWindow* parent ) : QWidget(),
    newCapButton(new QPushButton("New")),
    saveButton(new QPushButton("Save")),
    copyClipButton(new QPushButton("Copy")),
    captureScene(new QGraphicsScene),
    captureView(new QGraphicsView(captureScene)),
    buttonsLayout(new QHBoxLayout),
    windowLayout(new QVBoxLayout)
    
    
{
    this->parent = parent;
    
    // Setup buttons
    newCapButton->setText("New");
    newCapButton->setToolTip("Make new Screen Capture");
    newCapButton->setIcon(QIcon::fromTheme("edit-cut"));
    newCapButton->connect(newCapButton, SIGNAL(clicked()), this, SLOT(newCaptureClicked()));

    saveButton->setText("Save");    
    saveButton->setToolTip("Save Screen Capture to file system");
    saveButton->setIcon(QIcon::fromTheme("document-save-as"));
    saveButton->connect(saveButton, SIGNAL(clicked()), this, SLOT(saveCaptureClicked()));
    saveButton->setEnabled(false);
    
    copyClipButton->setText("Copy");
    copyClipButton->setToolTip("Copy Screen Capture to clipboard");
    copyClipButton->setIcon(QIcon::fromTheme("edit-copy"));
    copyClipButton->connect(copyClipButton, SIGNAL(clicked()), this, SLOT(copyToClipClicked()));
    
    // Disable frame around the image
    captureView->setFrameStyle(0);
    
    // Setup the clipboard that we will use to copy images when required.
    clipboard = QApplication::clipboard();
    
    // Setup widget layout
    buttonsLayout->addWidget(newCapButton);
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(copyClipButton); 
    buttonsLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    
    windowLayout->addLayout(buttonsLayout);
    windowLayout->addWidget(captureView);
    setLayout(windowLayout);
    
    // Setup application properties
    setWindowTitle("ksnip");
    setWindowIcon(QIcon::fromTheme("preferences-desktop-screensaver"));
    move(200,200);
}

/*
 *  Overwrites the default show() function as we require an image any time we open this 
 *  window. Firs we check if an image was provided, if yes, we clear any existing image 
 *  in the scene and add the image.
 */
void PaintWindow::show ( QPixmap captureImage )
{
    if (captureImage.isNull())
    {
      qCritical("PaintWindow::showWindow: No image provided to Paint Window, unable to proceed.");
      return;
    }
    
    captureScene->clear();
    captureScene->addPixmap(captureImage);
    captureScene->setSceneRect(0,0, captureImage.width(), captureImage.height());
    this->resize(captureScene->sceneRect().size().toSize() + QSize(100,100));
    saveButton->setEnabled(true);
    setWindowTitle("*ksnip - Unsaved");
    QWidget::show();
}

/*
 * Called when the New Capture button was clicked, the function hides it's owning widget
 * and calls a function on the parent widget to start a new capture.
 */
void PaintWindow::newCaptureClicked()
{
    this->hide();
    parent->TakeNewCapture();
}

/*
 * This function is called when the save button is clicked, it will open a new dialog where
 * the user can pick a location where to save the file. By default the home directory is 
 * picked with name "Untitled" and file format png.
 */
void PaintWindow::saveCaptureClicked()
{
    QString format = "png";
    QString initialPath = QDir::homePath() + tr("/untitled.") + format;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(format.toUpper())
                               .arg(format));
    
    if (fileName.isEmpty())
    {
	QMessageBox msgBox;
	msgBox.setWindowTitle("Unable to save");
	msgBox.setText("Filename is empty, unable to save the image.");
	msgBox.exec();
    }
    else
    {
      if(!QPixmap::grabWidget(captureView).save(fileName, format.toAscii()))
      {
	  qCritical("PaintWindow::saveCaptureClicked: Failed to save image, something went wrong.");
	  return;
      }	  
      saveButton->setEnabled(false);
      setWindowTitle("ksnip");
    }
}

/*
 * Copy the image currently present to the OS clipboard.
 */
void PaintWindow::copyToClipClicked()
{
    clipboard->setPixmap(QPixmap::grabWidget(captureView));  
}



