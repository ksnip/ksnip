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
#include "MainWindow.h"

MainWindow::MainWindow() : QWidget(),
    mToolBar( new QToolBar ),
    mMenuBar( new QMenuBar ),
    mNewCaptureButton( new CustomToolButton ),
    mSaveButton( new QToolButton ),
    mCopyToClipboardButton( new QToolButton ),
    mPaintToolButton( new CustomToolButton ),
    mPaintToolMenu( new QMenu ),
    mNewCaptureMenu( new QMenu ),
    mNewRectAreaCaptureAction( new QAction( this ) ),
    mNewCurrentScreenCaptureAction( new QAction( this ) ),
    mNewFullScreenCaptureAction( new QAction( this ) ),
    mNewActiveWindowCaptureAction( new QAction( this ) ),
    mSaveAction( new QAction( this ) ),
    mCopyToClipboardAction( new QAction( this ) ),
    mPenAction( new QAction( this ) ),
    mMarkerAction( new QAction( this ) ),
    mEraseAction( new QAction( this ) ),
    mCropAction( new QAction( this ) ),
    mNewCaptureAction( new QAction( this ) ),
    mQuitAction( new QAction( this ) ),
    mSettingsDialogAction( new QAction( this ) ),
    mAboutKsnipAction( new QAction( this ) ),
    mWindowLayout( new QVBoxLayout ),
    mCaptureScene( new PaintArea() ),
    mCaptureView( new CaptureView( mCaptureScene ) ),
    mClipboard( QApplication::clipboard() ),
    mSnippingArea( new SnippingArea( this ) ),
    mImageGrabber( new ImageGrabber( this ) )
{
    initGui();

    mCaptureView->hide();

    setWindowIcon( createIcon( "ksnip" ) );
    move( KsnipConfig::instance()->windowPosition() );

    // Create a connection with other widget elements
    connect( mSnippingArea, SIGNAL( areaSelected( QRect ) ), this, SLOT( areaSelected( QRect ) ) );
    connect( mCaptureScene, SIGNAL( imageChanged() ), this, SLOT( imageChanged() ) );
    connect( KsnipConfig::instance(),
             SIGNAL( captureDelayUpdated( int ) ),
             this,
             SLOT( setCaptureDelay( int ) ) );

    loadSettings();
}

//
// Public Functions
//

void MainWindow::show( QPixmap screenshot )
{
    setWindowState( Qt::WindowActive );
    setWindowOpacity( 1.0 );

    if ( screenshot.isNull() ) {
        qCritical( "PaintWindow::showWindow: No image provided to but it was expected." );
        return show();
    }

    mCaptureScene->loadCapture( screenshot );

    if ( mCaptureScene->areaSize().width() > mImageGrabber->currectScreenRect().width() ||
            mCaptureScene->areaSize().height() > mImageGrabber->currectScreenRect().height() ) {
        setWindowState( Qt::WindowMaximized );
    }

    else {
        resize( mCaptureScene->areaSize() + QSize( 100, 150 ) );
    }

    mCaptureView->show();
    setSaveAble( true );

    if ( KsnipConfig::instance()->alwaysCopyToClipboard() ) {
        copyToClipboard();
    }

    QWidget::show();
}

void MainWindow::show()
{
    setWindowState( Qt::WindowActive );
    mCaptureView->hide();
    setSaveAble( false );
    QWidget::show();
}

int MainWindow::captureDelay()
{
    return mCaptureDelay;
}

/*
 * Function for instant capturing used from command line. The function grabs the image and saves it
 * directly to disk. If some delay was set it will be added, otherwise delay is set to 0 and skipped
 */
void MainWindow::instantCapture( ImageGrabber::CaptureMode captureMode, int seconds )
{
    delay( seconds * 1000 );
    
    switch ( captureMode ) {
    case ImageGrabber::RectArea:
        break;

    case ImageGrabber::CurrentScreen:
        instantSave(mImageGrabber->grabImage( ImageGrabber::CurrentScreen ));
        break;

    case ImageGrabber::ActiveWindow:
        instantSave(mImageGrabber->grabImage( ImageGrabber::ActiveWindow ));
        break;
    
    case ImageGrabber::FullScreen:
    default:
        instantSave(mImageGrabber->grabImage( ImageGrabber::FullScreen ));
    }
}

//
// Public Slots
//

/*
 * Delay is never set below 300ms to leave enough time for the ksnip window to disappear before
 * taking the screenshot.
 */
void MainWindow::setCaptureDelay( int ms )
{
    if ( ms < 300 ) {
        mCaptureDelay = 300;
    }
    else {
        mCaptureDelay = ms;
    }
}

//
// Protected Functions
//

void MainWindow::moveEvent( QMoveEvent *event )
{
    KsnipConfig::instance()->setWindowPosition( pos() );
    QWidget::moveEvent( event );
}

void MainWindow::closeEvent( QCloseEvent *event )
{
    if ( KsnipConfig::instance()->promptSaveBeforeExit() && mIsUnsaved ) {
        bool reply = popupQuestion( tr( "Warning - " ) + QApplication::applicationName(),
                                    tr( "The capture has been modified.\nDo you want to save it?" ) );

        if ( reply ) {
            saveCaptureClicked();
            event->ignore();
        }
        else {
            event->accept();
        }
    }
    else {
        event->accept();
    }
}

//
// Private Functions
//

void MainWindow::delay( int ms )
{
    QTime dieTime = QTime::currentTime().addMSecs( ms );

    while ( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

/*
 * Sets the state of the widget when the image was changed or save, depending
 * on the provided boolean value. If true, the save action is enabled and
 * the title changed.
 */
void MainWindow::setSaveAble( bool enabled )
{
    if ( enabled ) {
        mSaveButton->setEnabled( true );
        setWindowTitle( "*" + QApplication::applicationName() + " - " + tr( "Unsaved" ) );
        mIsUnsaved = true;
    }
    else {
        mSaveButton->setEnabled( false );
        setWindowTitle( QApplication::applicationName() );
        mIsUnsaved = false;
    }
}

/*
 * This loads ksnip settings from the config file
 */
void MainWindow::loadSettings()
{
    // Load capture delay setting
    setCaptureDelay( KsnipConfig::instance()->captureDelay() );

    // Load paintmode setting
    if ( KsnipConfig::instance()->paintMode() == PaintArea::Marker ) {
        mCaptureScene->setPaintMode( PaintArea::Marker );
        mPaintToolButton->setDefaultAction( mMarkerAction );
    }
    else {
        mCaptureScene->setPaintMode( PaintArea::Pen );
        mPaintToolButton->setDefaultAction( mPenAction );
    }

    // Load capture mode setting
    switch ( KsnipConfig::instance()->captureMode() ) {
    case ImageGrabber::ActiveWindow:
        mNewCaptureButton->setDefaultAction( mNewActiveWindowCaptureAction );
        break;

    case ImageGrabber::CurrentScreen:
        mNewCaptureButton->setDefaultAction( mNewCurrentScreenCaptureAction );
        break;

    case ImageGrabber::FullScreen:
        mNewCaptureButton->setDefaultAction( mNewFullScreenCaptureAction );
        break;

    default:
        mNewCaptureButton->setDefaultAction( mNewRectAreaCaptureAction );
    }
}

void MainWindow::copyToClipboard()
{
    mClipboard->setImage( mCaptureScene->exportAsImage() );
}

/*
 * Generic function that can be used to display a simple yes/no question and return appropriate
 * boolean feedback.
 */
bool MainWindow::popupQuestion( QString title, QString question )
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question( this, title, question, QMessageBox::Yes | QMessageBox::No );

    if ( reply == QMessageBox::Yes ) {
        return true;
    }
    else {
        return false;
    }
}

/*
 * Checks what png icons are available for that button and adds them to the icon which can then be
 * added to a button, action or similar.
 */
QIcon MainWindow::createIcon( QString name )
{
    QIcon tmpIcon;

    for ( int i = 16; i <= 64; i = i * 2 ) {
        if ( QResource( ":" + name + QString::number( i ) + ".png" ).isValid() ) {
            tmpIcon.addFile( ( ":" + name + QString::number( i ) + ".png" ), QSize( i, i ) );
        }
    }

    return tmpIcon;
}

/*
 * This function when called saves the provided pixmap directly to the default save location without
 * asking the user for a new path. Existing images are not overwritten, just names with increasing
 * number.
 */
void MainWindow::instantSave( QPixmap pixmap )
{                             
    QString savePath = StringManip::makeUniqueFilename(KsnipConfig::instance()->saveDirectory(), 
                       StringManip::updateTimeAndDate(KsnipConfig::instance()->saveFilename()), 
                       KsnipConfig::instance()->saveFormat());
    
    // Turn any special characters, like $Y into a valid date and time value.
    if(!pixmap.save(savePath)){
        qCritical( "MainWindow::instantSave: Unable to save capture at " + savePath.toLatin1());
    }
}

void MainWindow::initGui()
{
    // Create actions

    // Create actions for capture modes
    mNewRectAreaCaptureAction->setIconText( tr( "Rectangular Area" ) );
    mNewRectAreaCaptureAction->setToolTip( tr( "Draw a rectangular area with your mouse." ) );
    mNewRectAreaCaptureAction->setIcon( createIcon( "drawRect" ) ) ;
    connect( mNewRectAreaCaptureAction,
             SIGNAL( triggered() ),
             this,
             SLOT( newRectAreaCaptureClicked() ) );

    mNewFullScreenCaptureAction->setIconText( tr( "Full Screen (All Monitors)" ) );
    mNewFullScreenCaptureAction->setToolTip( tr( "Capture full screen including all monitors." ) );
    mNewFullScreenCaptureAction->setIcon( createIcon( "fullScreen" ) );
    connect( mNewFullScreenCaptureAction,
             SIGNAL( triggered() ),
             this,
             SLOT( newFullScreenCaptureClicked() ) );

    mNewCurrentScreenCaptureAction->setIconText( tr( "Current Screen" ) );
    mNewCurrentScreenCaptureAction->setToolTip( tr( "Capture screen where the mouse is located." ) );
    mNewCurrentScreenCaptureAction->setIcon( createIcon( "currentScreen" ) );
    connect( mNewCurrentScreenCaptureAction,
             SIGNAL( triggered() ),
             this,
             SLOT( newCurrentScreenCaptureClicked() ) );

    mNewActiveWindowCaptureAction->setIconText( tr( "Active Window" ) );
    mNewActiveWindowCaptureAction->setToolTip( tr( "Capture window that currently has focus." ) );
    mNewActiveWindowCaptureAction->setIcon( createIcon( "activeWindow" ) );
    connect( mNewActiveWindowCaptureAction,
             SIGNAL( triggered() ),
             this,
             SLOT( newActiveWindowCaptureClicked() ) );

    // Create action for save button
    mSaveAction->setText( tr( "Save" ) );
    mSaveAction->setToolTip( tr( "Save Screen Capture to file system" ) );
    mSaveAction->setIcon( createIcon( "save" ) );
    mSaveAction->setShortcut( QKeySequence::Save );
    mSaveAction->connect( mSaveAction, SIGNAL( triggered() ), this,
                          SLOT( saveCaptureClicked() ) );
    mSaveAction->setEnabled( false );

    // Create action for copy to clipboard button
    mCopyToClipboardAction->setText( tr( "Copy" ) );
    mCopyToClipboardAction->setToolTip( tr( "Copy Screen Capture to clipboard" ) );
    mCopyToClipboardAction->setIcon( createIcon( "copyToClipboard" ) ) ;
    mCopyToClipboardAction->setShortcut( QKeySequence::Copy );
    mCopyToClipboardAction->connect( mCopyToClipboardAction, SIGNAL( triggered() ), this,
                                     SLOT( copyToClipboardClicked() ) );

    // Create crop action
    mCropAction->setText( tr( "Crop" ) );
    mCropAction->setToolTip( tr( "Crop Screen Capture" ) );
    mCropAction->setShortcut( Qt::SHIFT + Qt::Key_C );
    mCropAction->connect( mCropAction, SIGNAL( triggered() ), this, SLOT( cropClicked() ) );

    // Create actions for paint mode
    mPenAction->setText( tr( "Pen" ) );
    mPenAction->setIcon( createIcon( "pen" ) );
    connect( mPenAction, SIGNAL( triggered() ), this, SLOT( penClicked() ) );

    mMarkerAction->setText( tr( "Marker" ) );
    mMarkerAction->setIcon( createIcon( "marker" ) );
    connect( mMarkerAction, SIGNAL( triggered() ), this, SLOT( markerClicked() ) );

    mEraseAction->setText( tr( "Erase" ) );
    mEraseAction->setIcon( createIcon( "eraser" ) );
    connect( mEraseAction, SIGNAL( triggered() ), this, SLOT( eraseClicked() ) );

    // Create action for new capture, this will be only used in the menu bar
    mNewCaptureAction->setText( tr( "New" ) );
    mNewCaptureAction->setShortcut( QKeySequence::New );
    connect( mNewCaptureAction, SIGNAL( triggered() ), mNewCaptureButton, SLOT( trigger() ) );

    // Create exit action
    mQuitAction->setText( tr( "Quit" ) );
    mQuitAction->setShortcut( QKeySequence::Quit );
    connect( mQuitAction, SIGNAL( triggered() ), this, SLOT( close() ) );

    // Create action for opening settings dialog
    mSettingsDialogAction->setText( tr( "Settings" ) );
    connect( mSettingsDialogAction, SIGNAL( triggered() ), this, SLOT( openSettingsDialog() ) );

    mAboutKsnipAction->setText( tr( "&About" ) );
    connect( mAboutKsnipAction, SIGNAL( triggered() ), this, SLOT( openAboutDialog() ) );

    // Create tool buttons

    // Create tool button for selecting new capture mode
    mNewCaptureMenu->addAction( mNewRectAreaCaptureAction );
    mNewCaptureMenu->addAction( mNewFullScreenCaptureAction );
    mNewCaptureMenu->addAction( mNewCurrentScreenCaptureAction );
    mNewCaptureMenu->addAction( mNewActiveWindowCaptureAction );

    mNewCaptureButton->setMenu( mNewCaptureMenu );
    mNewCaptureButton->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
    mNewCaptureButton->setDefaultAction( mNewRectAreaCaptureAction );
    mNewCaptureButton->setButtonText( tr( "New" ) );

    // Create save tool button
    mSaveButton->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
    mSaveButton->addAction( mSaveAction );
    mSaveButton->setDefaultAction( mSaveAction );

    // Create copy to clipboard tool button
    mCopyToClipboardButton->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
    mCopyToClipboardButton->addAction( mCopyToClipboardAction );
    mCopyToClipboardButton->setDefaultAction( mCopyToClipboardAction );

    // Create tool button for selecting paint tool
    mPaintToolMenu->addAction( mPenAction );
    mPaintToolMenu->addAction( mMarkerAction );
    mPaintToolMenu->addAction( mEraseAction );

    mPaintToolButton->setMenu( mPaintToolMenu );
    mPaintToolButton->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
    mPaintToolButton->setDefaultAction( mPenAction );

    // Create toolbar

    mToolBar->addWidget( mNewCaptureButton );
    mToolBar->addSeparator();
    mToolBar->addWidget( mSaveButton );
    mToolBar->addWidget( mCopyToClipboardButton );
    mToolBar->addSeparator();
    mToolBar->addWidget( mPaintToolButton );
    mToolBar->setFixedSize( mToolBar->sizeHint() );

    // Create menu bar

    QMenu *tmpMenu;
    tmpMenu = mMenuBar->addMenu( tr( "File" ) );
    tmpMenu->addAction( mNewCaptureAction );
    tmpMenu->addAction( mSaveAction );
    tmpMenu->addSeparator();
    tmpMenu->addAction( mQuitAction );
    tmpMenu = mMenuBar->addMenu( tr( "&Edit" ) );
    tmpMenu->addAction( mCopyToClipboardAction );
    tmpMenu->addAction( mCropAction );
    tmpMenu = mMenuBar->addMenu( tr( "&Options" ) );
    tmpMenu->addAction( mSettingsDialogAction );
    tmpMenu = mMenuBar->addMenu( tr( "&Help" ) );
    tmpMenu->addAction( mAboutKsnipAction );

    // Create Layout

    mWindowLayout->addWidget( mMenuBar );
    mWindowLayout->addWidget( mToolBar );
    mWindowLayout->addWidget( mCaptureView );
    mWindowLayout->setAlignment( Qt::AlignTop | Qt::AlignLeft );
    mWindowLayout->setContentsMargins( 0, 0, 0, 0 );
    setLayout( mWindowLayout );
}

//
// Private Slots
//

void MainWindow::newRectAreaCaptureClicked()
{
    setWindowOpacity( 0.0 );
    mSnippingArea->show();
    KsnipConfig::instance()->setCaptureMode( ImageGrabber::RectArea );
}

void MainWindow::newCurrentScreenCaptureClicked()
{
    setWindowOpacity( 0.0 );
    setWindowState( Qt::WindowMinimized );
    delay( mCaptureDelay );
    show( mImageGrabber->grabImage( ImageGrabber::CurrentScreen ) );
    KsnipConfig::instance()->setCaptureMode( ImageGrabber::CurrentScreen );
}

void MainWindow::newFullScreenCaptureClicked()
{
    setWindowOpacity( 0.0 );
    setWindowState( Qt::WindowMinimized );
    delay( mCaptureDelay );
    show( mImageGrabber->grabImage( ImageGrabber::FullScreen ) );
    KsnipConfig::instance()->setCaptureMode( ImageGrabber::FullScreen );
}

void MainWindow::newActiveWindowCaptureClicked()
{
    setWindowOpacity( 0.0 );
    setWindowState( Qt::WindowMinimized );
    delay( mCaptureDelay );
    show( mImageGrabber->grabImage( ImageGrabber::ActiveWindow ) );
    KsnipConfig::instance()->setCaptureMode( ImageGrabber::ActiveWindow );
}

void MainWindow::saveCaptureClicked()
{
    QFileDialog saveDialog( this, tr( "Save As" ),
                            KsnipConfig::instance()->saveDirectory() + tr( "untitled" ) +
                            KsnipConfig::instance()->saveFormat(),
                            tr( "Images" ) + " (*.png *.gif *.jpg);;" + tr( "All Files" ) + "(*)" );
    saveDialog.setAcceptMode( QFileDialog::AcceptSave );

    if ( saveDialog.exec() == QDialog::Accepted ) {

        if ( !mCaptureScene->exportAsImage().save( saveDialog.selectedFiles().first() ) ) {
            qCritical( "PaintWindow::saveCaptureClicked: Unable to save file " + 
                        saveDialog.selectedFiles().first().toLatin1() );
            return;
        }

        setSaveAble( false );
    }
}

void MainWindow::copyToClipboardClicked()
{
    copyToClipboard();
}

void MainWindow::penClicked()
{
    mCaptureScene->setPaintMode( PaintArea::Pen );
    KsnipConfig::instance()->setPaintMode( PaintArea::Pen );
}

void MainWindow::markerClicked()
{
    mCaptureScene->setPaintMode( PaintArea::Marker );
    KsnipConfig::instance()->setPaintMode( PaintArea::Marker );
}

void MainWindow::eraseClicked()
{
    mCaptureScene->setPaintMode( PaintArea::Erase );
}

void MainWindow::cropClicked()
{
    mCaptureView->setIsCropping( true );
}

void MainWindow::keyPressEvent( QKeyEvent *event )
{
    if ( event->key() == Qt::Key_Escape ) {
        mSnippingArea->hide();
        setWindowOpacity( 1.0 );
    }

    QWidget::keyPressEvent( event );
}

void MainWindow::areaSelected( QRect rect )
{
    delay( mCaptureDelay );
    show( mImageGrabber->grabImage( ImageGrabber::RectArea, &rect ) );
}

/*
 * Should be called when ever the paintArea was changed, like new drawing and similar
 */
void MainWindow::imageChanged()
{
    setSaveAble( true );

    if ( KsnipConfig::instance()->alwaysCopyToClipboard() ) {
        copyToClipboard();
    }
}

void MainWindow::openSettingsDialog()
{
    SettingsDialog settingsDialog( this );
    settingsDialog.exec();
}

void MainWindow::openAboutDialog()
{
    AboutDialog aboutDialog( this );
    aboutDialog.exec();
}