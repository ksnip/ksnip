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

#include "mainwindow.h"

/*
 * Constructor
 */
MainWindow::MainWindow () : QWidget(),
    mNewCaptureButton(new QPushButton),
    mSaveButton(new QPushButton),
    mCopyToClipboardButton(new QPushButton),
    mPaintButton(new QPushButton),
    mEraseButton(new QPushButton),
    mCaptureScene(new ScribbleArea),
    mCaptureView(new QGraphicsView(mCaptureScene)),
    mButtonsLayout(new QHBoxLayout),
    mWindowLayout(new QVBoxLayout),
    mSnippingArea(new SnippingArea(this))
   
{   
    // Setup buttons
    mNewCaptureButton->setText("New");
    mNewCaptureButton->setToolTip("Make new Screen Capture");
    mNewCaptureButton->setIcon(QIcon::fromTheme("edit-cut"));
    mNewCaptureButton->connect(mNewCaptureButton, SIGNAL(clicked()), this, SLOT(newCaptureClicked()));

    mSaveButton->setText("Save");    
    mSaveButton->setToolTip("Save Screen Capture to file system");
    mSaveButton->setIcon(QIcon::fromTheme("document-save-as"));
    mSaveButton->connect(mSaveButton, SIGNAL(clicked()), this, SLOT(saveCaptureClicked()));
    mSaveButton->setEnabled(false);
    
    mCopyToClipboardButton->setText("Copy");
    mCopyToClipboardButton->setToolTip("Copy Screen Capture to clipboard");
    mCopyToClipboardButton->setIcon(QIcon::fromTheme("edit-copy"));
    mCopyToClipboardButton->connect(mCopyToClipboardButton, SIGNAL(clicked()), this, SLOT(copyToClipboardClicked()));
    
    mPaintButton->setText("Paint");
    mPaintButton->setToolTip("Draw on the Screen Capture");
    mPaintButton->connect(mPaintButton, SIGNAL(clicked()), this, SLOT(paintClicked()));
    
    mEraseButton->setText("Erase");
    mEraseButton->setToolTip("Erase drawing from Screen Capture");
    mEraseButton->connect(mEraseButton, SIGNAL(clicked()), this, SLOT(eraseClicked()));
    
    // Disable frame around the image and hide it as on startup it's empty
    mCaptureView->setFrameStyle(0);
    mCaptureView->hide();
    
    // Setup the clipboard that we will use to copy images when required.
    mClipboard = QApplication::clipboard();
    
    // Setup widget layout
    mButtonsLayout->addWidget(mNewCaptureButton);
    mButtonsLayout->addWidget(mSaveButton);
    mButtonsLayout->addWidget(mCopyToClipboardButton); 
    mButtonsLayout->addWidget(mPaintButton);
    mButtonsLayout->addWidget(mEraseButton);
    mButtonsLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    
    mWindowLayout->addLayout(mButtonsLayout);
    mWindowLayout->addWidget(mCaptureView);
    setLayout(mWindowLayout);
        
    // Setup application properties
    setWindowTitle("ksnip");
    setWindowIcon(QIcon::fromTheme("preferences-desktop-screensaver"));
    move(200,200);
    
    // Create a connection between the snipping area and and the main window
    connect(mSnippingArea, SIGNAL(areaSelected(QRect)), this, SLOT(areaSelected(QRect)));
    
    mCaptureView->setRenderHints(QPainter::Antialiasing);
}

/*
 *  This function is supposed to be called when we want to show an image that we have capture.
 *  First, we clean the Graphical View from any previous captures and setup the environment 
 *  for the new capture. In case the picture is not valid we call the default show.
 */
void MainWindow::show (QPixmap screenshot)
{
    setWindowOpacity(1.0);
    
    if (screenshot.isNull())
    {
	qCritical("PaintWindow::showWindow: No image provided to but it was expected.");
	return show();
    }
    
    mCaptureScene->loadCapture(screenshot);
    resize(mCaptureScene->getSize() + QSize(100,100));
	    
    mCaptureView->show();
    mSaveButton->setEnabled(true);
    setWindowTitle("*ksnip - Unsaved");  

    QWidget::show();
}

/*
 * When the show without provided capture is called the capture view is hidden as this 
 * would be the case when we open the window up for the first time.
 */
void MainWindow::show()
{
    mCaptureView->hide();
    mSaveButton->setEnabled(false);
    setWindowTitle("ksnip");
    QWidget::show();
}


/*
 * Called when the New Capture button was clicked, hides itself and show the snipping area
 * window.
 */
void MainWindow::newCaptureClicked()
{
    setWindowOpacity(0.0);
    mSnippingArea->show();  
}

/*
 * This function is called when the save button is clicked, it will open a new dialog where
 * the user can pick a location where to save the file. By default the home directory is 
 * picked with name "Untitled" and file format png.
 */
void MainWindow::saveCaptureClicked()
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
	return;
    }
    
    if (!QPixmap::grabWidget(mCaptureView).save(fileName, format.toAscii()))
    {
	qCritical("PaintWindow::saveCaptureClicked: Failed to save image, something went wrong.");
	return;
    }	
    
    mSaveButton->setEnabled(false);
    setWindowTitle("ksnip");
}

/*
 * Copy the image currently present to the OS clipboard.
 */
void MainWindow::copyToClipboardClicked()
{
    mClipboard->setPixmap(QPixmap::grabWidget(mCaptureView));  
}

void MainWindow::paintClicked()
{
    mCaptureScene->setErase(false);
}

void MainWindow::eraseClicked()
{
    mCaptureScene->setErase(true);
}

void MainWindow::keyPressEvent ( QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
	mSnippingArea->hide();
	setWindowOpacity(1.0);
    }
    QWidget::keyPressEvent(event);
}

/*
 * Called by a signal from snipping area window when finished selecting an area
 * so that we can proceed with capturing the image
 */
void MainWindow::areaSelected ( QRect rect )
{
    delay(300);
    show(grabScreen(rect));
}

/*
 * Captures the screen at the area selected by the rectangle provided as
 * argument
 */
QPixmap MainWindow::grabScreen (QRect rect)
{
    QPixmap screenshot;
    screenshot = QPixmap(); 
    screenshot = QPixmap::grabWindow(QApplication::desktop()->winId(), 
				   rect.topLeft().x(), 
				   rect.topLeft().y(), 
				   rect.width(), 
				   rect.height());
    return screenshot;
}

/*
 * Stops the executions for the time provided in milliseconds effectively
 * adding delay so that the hide() call can be propagated.
 */
void MainWindow::delay (int ms)
{
    QTime dieTime= QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}




