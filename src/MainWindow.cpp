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

#include "MainWindow.h"

#include <iostream>

/*
 * Constructor
 */
MainWindow::MainWindow() : QWidget(),
    mNewCaptureButton( new QPushButton ),
    mSaveButton( new QPushButton ),
    mCopyToClipboardButton( new QPushButton ),
    mMenu( new QMenu ),
    mToolBar( new QToolBar ),
    mToolButton( new CustomToolButton ),
    mPenAction( new QAction( this ) ),
    mMarkerAction( new QAction( this ) ),
    mEraseAction( new QAction( this ) ),
    mCaptureScene( new PaintArea ),
    mCaptureView( new QGraphicsView( mCaptureScene ) ),
    mMenuLayout( new QHBoxLayout ),
    mWindowLayout( new QVBoxLayout ),
    mSnippingArea( new SnippingArea( this ) )

{
    createButtons();
    createToolBar();
    createLayout();


    // Disable frame around the image and hide it as on startup it's empty
    mCaptureView->setFrameStyle( 0 );
    mCaptureView->hide();

    // Setup the clipboard that we will use to copy images when required.
    mClipboard = QApplication::clipboard();

    // Setup application properties
    setWindowTitle( "ksnip" );
    setWindowIcon( QIcon::fromTheme( "preferences-desktop-screensaver" ) );
    move( 200, 200 );

    // Create a connection between the snipping area and and the main window
    connect( mSnippingArea, SIGNAL( areaSelected( QRect ) ), this, SLOT( areaSelected( QRect ) ) );

    mCaptureView->setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
}

void MainWindow::show( QPixmap screenshot )
{
    setWindowOpacity( 1.0 );

    if ( screenshot.isNull() )
    {
        qCritical( "PaintWindow::showWindow: No image provided to but it was expected." );
        return show();
    }

    mCaptureScene->loadCapture( screenshot );
    resize( mCaptureScene->getAreaSize() + QSize( 100, 100 ) ); 

    mCaptureView->show();
    mCaptureView->setFocus();
    mSaveButton->setEnabled( true );
    mToolBar->setEnabled( true );
    setWindowTitle( "*ksnip - Unsaved" );

    QWidget::show();
}

void MainWindow::show()
{
    mCaptureView->hide();
    mSaveButton->setEnabled( false );
    setWindowTitle( "ksnip" );
    QWidget::show();
}

void MainWindow::newCaptureClicked()
{
    setWindowOpacity( 0.0 );
    mSnippingArea->show();
}

void MainWindow::saveCaptureClicked()
{
    QString format = "png";
    QString initialPath = QDir::homePath() + tr( "/untitled." ) + format;

    QString fileName = QFileDialog::getSaveFileName( this, tr( "Save As" ),
                       initialPath,
                       tr( "%1 Files (*.%2);;All Files (*)" )
                       .arg( format.toUpper() )
                       .arg( format ) );

    if ( fileName.isEmpty() )
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle( tr( "Unable to save" ) );
        msgBox.setText( tr( "Filename is empty, unable to save the image." ) );
        msgBox.exec();
        return;
    }

    if ( !mCaptureScene->exportAsImage().save(fileName) )
    {
        qCritical( "PaintWindow::saveCaptureClicked: Failed to save image, something went wrong." );
        return;
    }
    
    mSaveButton->setEnabled( false );
    setWindowTitle( "ksnip" );
}

void MainWindow::copyToClipboardClicked()
{
    mClipboard->setImage(mCaptureScene->exportAsImage());
}

void MainWindow::penClicked()
{
    mCaptureScene->setScribbleMode( PaintArea::Pen );
}

void MainWindow::markerClicked()
{
    mCaptureScene->setScribbleMode( PaintArea::Marker );
}

void MainWindow::eraseClicked()
{
    mCaptureScene->setScribbleMode( PaintArea::Erase );
}

void MainWindow::keyPressEvent( QKeyEvent* event )
{
    if ( event->key() == Qt::Key_Escape )
    {
        mSnippingArea->hide();
        setWindowOpacity( 1.0 );
    }

    QWidget::keyPressEvent( event );
}

void MainWindow::areaSelected( QRect rect )
{
    delay( 300 );
    show( grabScreen( rect ) );
}

QPixmap MainWindow::grabScreen( QRect rect )
{
    QPixmap screenshot;
    screenshot = QPixmap();
    screenshot = QPixmap::grabWindow( QApplication::desktop()->winId(),
                                      rect.topLeft().x(),
                                      rect.topLeft().y(),
                                      rect.width(),
                                      rect.height() );
    return screenshot;
}

void MainWindow::delay( int ms )
{
    QTime dieTime = QTime::currentTime().addMSecs( ms );
    while ( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void MainWindow::createButtons()
{
    mNewCaptureButton->setText( "New" );
    mNewCaptureButton->setToolTip( "Make new Screen Capture" );
    mNewCaptureButton->setIcon( QIcon::fromTheme( "edit-cut" ) );
    mNewCaptureButton->connect( mNewCaptureButton, SIGNAL( clicked() ), this, SLOT( newCaptureClicked() ) );

    mSaveButton->setText( "Save" );
    mSaveButton->setToolTip( "Save Screen Capture to file system" );
    mSaveButton->setIcon( QIcon::fromTheme( "document-save-as" ) );
    mSaveButton->connect( mSaveButton, SIGNAL( clicked() ), this, SLOT( saveCaptureClicked() ) );
    mSaveButton->setEnabled( false );

    mCopyToClipboardButton->setText( "Copy" );
    mCopyToClipboardButton->setToolTip( "Copy Screen Capture to clipboard" );
    mCopyToClipboardButton->setIcon( QIcon::fromTheme( "edit-copy" ) );
    mCopyToClipboardButton->connect( mCopyToClipboardButton, SIGNAL( clicked() ), this, SLOT( copyToClipboardClicked() ) );
}

void MainWindow::createToolBar()
{
    mPenAction->setText( "Paint" );
    mPenAction->setIcon( QIcon::fromTheme( "tool_pen" ) );
    connect( mPenAction, SIGNAL( triggered() ), this, SLOT( penClicked() ) );

    mMarkerAction->setText( "Mark" );
    mMarkerAction->setIcon( QIcon::fromTheme( "draw-brush" ) );
    connect( mMarkerAction, SIGNAL( triggered() ), this, SLOT( markerClicked() ) );

    mEraseAction->setText( "Erase" );
    mEraseAction->setIcon( QIcon::fromTheme( "draw-eraser" ) );
    connect( mEraseAction, SIGNAL( triggered() ), this, SLOT( eraseClicked() ) );

    mMenu->addAction( mPenAction );
    mMenu->addAction( mMarkerAction );
    mMenu->addAction( mEraseAction );

    mToolButton->setMenu( mMenu );
    mToolButton->setDefaultAction( mPenAction );
    mToolBar->addWidget( mToolButton );
    mToolBar->setEnabled( false );
}

void MainWindow::createLayout()
{
    mMenuLayout->addWidget( mNewCaptureButton );
    mMenuLayout->addWidget( mSaveButton );
    mMenuLayout->addWidget( mCopyToClipboardButton );
    mMenuLayout->addWidget( mToolBar );
    mMenuLayout->setAlignment( Qt::AlignTop | Qt::AlignLeft );

    mWindowLayout->addLayout( mMenuLayout );
    mWindowLayout->addWidget( mCaptureView );
    setLayout( mWindowLayout );
}





