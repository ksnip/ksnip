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
    mPaintToolMenu ( new QMenu ),
    mNewCaptureMenu ( new QMenu ),
    mToolBar ( new QToolBar ),
    mNewCaptureButton ( new CustomToolButton ),
    mSaveButton ( new QToolButton ),
    mCopyToClipboardButton ( new QToolButton ),
    mPaintToolButton ( new CustomToolButton ),
    mMenuBar ( new QMenuBar ),
    mNewRectAreaCaptureAction ( new QAction ( this ) ),
    mNewFullScreenCaptureAction ( new QAction ( this ) ),
    mNewCurrentScreenCaptureAction ( new QAction ( this ) ),
    mNewActiveWindowCaptureAction ( new QAction ( this ) ),
    mSaveAction ( new QAction ( this ) ),
    mCopyToClipboardAction ( new QAction ( this ) ),
    mPenAction ( new QAction ( this ) ),
    mMarkerAction ( new QAction ( this ) ),
    mEraseAction ( new QAction ( this ) ),
    mNewCaptureAction( new QAction ( this ) ),
    mQuitAction( new QAction (this) ),
    mSettingsDialogAction ( new QAction ( this ) ),
    mCaptureScene ( new PaintArea() ),
    mCaptureView ( new QGraphicsView ( mCaptureScene ) ),
    mWindowLayout ( new QVBoxLayout ),
    mSnippingArea ( new SnippingArea ( this ) ),
    mImageGrabber ( new ImageGrabber ( this ) )
{
    createActions();
    createToolButtons();
    createToolBar();
    createMenuBar();
    createLayout();

    // Disable frame around the image and hide it as on startup it's empty and enable Antialiasing
    mCaptureView->setFrameStyle ( 0 );
    mCaptureView->setRenderHints ( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
    mCaptureView->hide();

    // Setup the clipboard that we will use to copy images when required.
    mClipboard = QApplication::clipboard();

    // Setup application properties
    setWindowTitle ( "ksnip" );
    setWindowIcon ( QIcon::fromTheme ( "preferences-desktop-screensaver" ) );

    // Create a connection with other widget elements
    connect ( mSnippingArea, 
              SIGNAL ( areaSelected ( QRect ) ), 
              this, 
              SLOT ( areaSelected ( QRect ) ) );
    connect ( mCaptureScene, SIGNAL ( imageChanged() ), this, SLOT ( imageChanged() ) );

    // Setup application properties that are required for saving settings
    QCoreApplication::setOrganizationName ( "ksnip" );
    QCoreApplication::setOrganizationDomain ( "ksnip.local" );
    QCoreApplication::setApplicationName ( "ksnip" );

    // Temporary setting capture delay to 4000 for testing purpose
    setCaptureDelay ( 300 );

    loadSettings();
}

//
// Public Functions
//

void MainWindow::show ( QPixmap screenshot )
{
    setWindowState ( Qt::WindowActive );
    setWindowOpacity ( 1.0 );

    if ( screenshot.isNull() ) {
        qCritical ( "PaintWindow::showWindow: No image provided to but it was expected." );
        return show();
    }

    mCaptureScene->loadCapture ( screenshot );

    if ( mCaptureScene->getAreaSize().width() > mImageGrabber->getCurrectScreenRect().width() ||
            mCaptureScene->getAreaSize().height() > mImageGrabber->getCurrectScreenRect().height() ) {
        setWindowState ( Qt::WindowMaximized );
    }

    else {
        resize ( mCaptureScene->getAreaSize() + QSize ( 100, 150 ) );
    }

    mCaptureView->show();
    mCaptureView->setFocus();
    setSaveAble ( true );

    if ( mAlwaysCopyToClipboard ) {
        copyToClipboard();
    }

    QWidget::show();
}

void MainWindow::show()
{
    setWindowState ( Qt::WindowActive );
    mCaptureView->hide();
    setSaveAble ( false );
    QWidget::show();
}

void MainWindow::setAlwaysCopyToClipboard ( bool alwaysCopyToClipboard )
{
    mAlwaysCopyToClipboard = alwaysCopyToClipboard;
    saveSetting ( "Application/AlwaysCopyToClipboard", mAlwaysCopyToClipboard );
}

bool MainWindow::getAlwaysCopyToClipboard()
{
    return mAlwaysCopyToClipboard;
}

void MainWindow::setPromptSaveBeforeExit ( bool promptSaveBeforeExit )
{
    mPromptSaveBeforeExit = promptSaveBeforeExit;
    saveSetting ( "Application/PromptSaveBeforeExit" , mPromptSaveBeforeExit );
}

bool MainWindow::getPromptSaveBeforeExit()
{
    return mPromptSaveBeforeExit;
}

void MainWindow::setSaveKsnipPosition ( bool saveKsnipPosition )
{
    mSaveKsnipPosition = saveKsnipPosition;
    saveSetting ( "Application/SaveKsnipPosition", mSaveKsnipPosition );
}

bool MainWindow::getSaveKsnipPosition()
{
    return mSaveKsnipPosition;
}

void MainWindow::setSaveKsnipToolSelection ( bool saveKsnipToolSelection )
{
    mSaveKsnipToolSelection = saveKsnipToolSelection;
    saveSetting ( "Application/SaveKsnipToolsSelection", mSaveKsnipToolSelection );
}

bool MainWindow::getSaveKsnipToolSelection()
{
    return mSaveKsnipToolSelection;
}

void MainWindow::setPenProperties ( QColor color, int width)
{
    mCaptureScene->setPenProperties(color, width);
    saveSetting("Painter/PenColor", color);
    saveSetting("Painter/PenSize", width);
}

QPen MainWindow::getPenProperties()
{
    return mCaptureScene->getPenProperties();
}

void MainWindow::setMarkerProperties ( QColor color, int width )
{
    mCaptureScene->setMarkerProperties(color, width);
    saveSetting("Painter/MarkerColor", color);
    saveSetting("Painter/MarkerSize", width);
}

QPen MainWindow::getMarkerProperties()
{
    return mCaptureScene->getMarkerProperties();
}

//
// Protected Functions
// 

void MainWindow::moveEvent ( QMoveEvent *event )
{
    saveSetting ( "MainWindow/Position", pos() );
    QWidget::moveEvent ( event );
}

//
// Private Slots
//

void MainWindow::newRectAreaCaptureClicked()
{
    setWindowOpacity ( 0.0 );
    mSnippingArea->show();
    saveSetting ( "ImageGrabber/CaptureMode", ImageGrabber::RectArea );
}

void MainWindow::newCurrentScreenCaptureClicked()
{
    setWindowOpacity ( 0.0 );
    setWindowState ( Qt::WindowMinimized );
    delay ( mCaptureDelay );
    show ( mImageGrabber->grabImage ( ImageGrabber::CurrentScreen ) );
    saveSetting ( "ImageGrabber/CaptureMode", ImageGrabber::CurrentScreen );
}

void MainWindow::mNewFullScreenCaptureClicked()
{
    setWindowOpacity ( 0.0 );
    setWindowState ( Qt::WindowMinimized );
    delay ( mCaptureDelay );
    show ( mImageGrabber->grabImage ( ImageGrabber::FullScreen ) );
    saveSetting ( "ImageGrabber/CaptureMode", ImageGrabber::FullScreen );
}

void MainWindow::newActiveWindowCaptureClicked()
{
    setWindowOpacity ( 0.0 );
    setWindowState ( Qt::WindowMinimized );
    delay ( mCaptureDelay );
    show ( mImageGrabber->grabImage ( ImageGrabber::ActiveWindow ) );
    saveSetting ( "ImageGrabber/CaptureMode", ImageGrabber::ActiveWindow );
}

void MainWindow::saveCaptureClicked()
{
    QString format = "png";
    QString initialPath = QDir::homePath() + tr ( "/untitled." ) + format;

    QString fileName = QFileDialog::getSaveFileName ( this, tr ( "Save As" ),
                       initialPath,
                       tr ( "%1 Files (*.%2);;All Files (*)" )
                       .arg ( format.toUpper() )
                       .arg ( format ) );

    if ( fileName.isEmpty() ) {
        QMessageBox msgBox;
        msgBox.setWindowTitle ( tr ( "Unable to save" ) );
        msgBox.setText ( tr ( "Filename is empty, unable to save the image." ) );
        msgBox.exec();
        return;
    }

    if ( !mCaptureScene->exportAsImage().save ( fileName ) ) {
        qCritical ( "PaintWindow::saveCaptureClicked: Failed to save image, something went wrong." );
        return;
    }

    setSaveAble ( false );
}

void MainWindow::copyToClipboardClicked()
{
    copyToClipboard();
}

void MainWindow::penClicked()
{
    mCaptureScene->setPaintMode ( PaintArea::Pen );
    saveSetting ( "Painter/PaintMode", PaintArea::Pen );
}

void MainWindow::markerClicked()
{
    mCaptureScene->setPaintMode ( PaintArea::Marker );
    saveSetting ( "Painter/PaintMode", PaintArea::Marker );
}

void MainWindow::eraseClicked()
{
    mCaptureScene->setPaintMode ( PaintArea::Erase );
}

void MainWindow::keyPressEvent ( QKeyEvent *event )
{
    if ( event->key() == Qt::Key_Escape ) {
        mSnippingArea->hide();
        setWindowOpacity ( 1.0 );
    }

    QWidget::keyPressEvent ( event );
}

void MainWindow::areaSelected ( QRect rect )
{
    delay ( mCaptureDelay );
    show ( mImageGrabber->grabImage ( ImageGrabber::RectArea, &rect ) );
}

/*
 * Should be called when ever the paintArea was changed, like new drawing and similar
 */
void MainWindow::imageChanged()
{
    setSaveAble ( true );

    if ( mAlwaysCopyToClipboard ) {
        copyToClipboard();
    }
}

/*
 * Delay is never set below 300ms to leave enough time for the ksnip window to disappear before
 * taking the screenshot.
 */
void MainWindow::setCaptureDelay ( int ms )
{
    if ( ms < 300 ) {
        mCaptureDelay = 300;
    }
    else {
        mCaptureDelay = ms;
    }
}

void MainWindow::openSettingsDialog()
{
    SettingsDialog settingsDialog(this);
    settingsDialog.exec();
}

//
// Private Functions
//

void MainWindow::delay ( int ms )
{
    QTime dieTime = QTime::currentTime().addMSecs ( ms );

    while ( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents ( QEventLoop::AllEvents, 100 );
    }
}

/*
 * Sets the state of the widget when the image was changed or save, depending
 * on the provided boolean value. If true, the save action is enabled and
 * the title changed.
 */
void MainWindow::setSaveAble ( bool saveAble )
{
    if ( saveAble ) {
        mSaveButton->setEnabled ( true );
        setWindowTitle ( "*ksnip - " + tr ( "Unsaved" ) );
    }
    else {
        mSaveAction->setEnabled ( false );
        setWindowTitle ( "ksnip" );
    }
}

/*
 * This function loads all settings for ksnip and it also loads a default settings for that variable
 * in case there is no valid previously saved value. 
 */
void MainWindow::loadSettings()
{
    QSettings settings;
    
    // Default False
    mAlwaysCopyToClipboard = settings.value ( "Application/AlwaysCopyToClipboard", false ).toBool();

    // Default False
    mPromptSaveBeforeExit = settings.value ( "Application/PromptSaveBeforeExit", false ).toBool();

    // Default true
    mSaveKsnipPosition = settings.value ( "Application/SaveKsnipPosition", true ).toBool();

    // Default true
    mSaveKsnipToolSelection = settings.value ( "Application/SaveKsnipToolsSelection", 
                                               true ).toBool();

    if ( mSaveKsnipPosition ) {
        // Default Position Center of the screen
        move ( settings.value ( "MainWindow/Position", positionAtCenter() ).value<QPoint>() );
    }
    else {
        move ( positionAtCenter() );
    }
    
    if ( mSaveKsnipToolSelection ) {
        // Default is Pen
        if ( settings.value ( "Painter/PaintMode" ).toInt() == PaintArea::Marker ) {
            mCaptureScene->setPaintMode ( PaintArea::Marker );
            mPaintToolButton->setDefaultAction ( mMarkerAction );
        }
        else {
            mCaptureScene->setPaintMode ( PaintArea::Pen );
            mPaintToolButton->setDefaultAction ( mPenAction );
        }

        // Default is Rect Area Capture
        switch ( settings.value ( "ImageGrabber/CaptureMode" ).toInt() ) {
        case ImageGrabber::ActiveWindow:
            mNewCaptureButton->setDefaultAction ( mNewActiveWindowCaptureAction );
            break;

        case ImageGrabber::CurrentScreen:
            mNewCaptureButton->setDefaultAction ( mNewCurrentScreenCaptureAction );
            break;

        case ImageGrabber::FullScreen:
            mNewCaptureButton->setDefaultAction ( mNewFullScreenCaptureAction );
            break;

        default
                :
            mNewCaptureButton->setDefaultAction ( mNewRectAreaCaptureAction );
        }

        // Default Pen Color=Red and Size=3
        mCaptureScene->setPenProperties ( settings.value ( "Painter/PenColor",
                                          QColor ( "Red" ) ).value<QColor>(),
                                          settings.value ( "Painter/PenSize",
                                                  3 ).toInt() );

        // Default Marker Color=Yellow and Size=20
        mCaptureScene->setMarkerProperties ( settings.value ( "Painter/MarkerColor",
                                             QColor ( "Yellow" ) ).value<QColor>(),
                                             settings.value ( "Painter/MarkerSize", 20 ).toInt() );
    }
    else {
        // Default Pen Color=Red and Size=3
        mCaptureScene->setPenProperties ( QColor ( "Red" ), 3 );

        // Default Marker Color=Yellow and Size=20
        mCaptureScene->setMarkerProperties ( QColor ( "Yellow" ),  20 );
    }
}

void MainWindow::saveSetting ( QString key, QVariant value )
{
    QSettings settings;
    settings.setValue ( key, value );
}

/*
 * Calculate the position for ksnip so that it's at the center of the current screen
 */
QPoint MainWindow::positionAtCenter()
{
    return QPoint( mImageGrabber->getActiveWindowRect().width() / 2 - sizeHint().width() / 2, 
                   mImageGrabber->getActiveWindowRect().height() / 2 - sizeHint().height() / 2);
}

void MainWindow::copyToClipboard()
{
    mClipboard->setImage ( mCaptureScene->exportAsImage() );
}

void MainWindow::createActions()
{
    // Create actions for capture modes
    mNewRectAreaCaptureAction->setIconText ( tr ( "Rectangular Area" ) );
    mNewRectAreaCaptureAction->setIcon ( QIcon::fromTheme ( "tool_rectangle" ) );
    connect ( mNewRectAreaCaptureAction,
              SIGNAL ( triggered() ),
              this,
              SLOT ( newRectAreaCaptureClicked() ) );

    mNewCurrentScreenCaptureAction->setIconText ( tr ( "Current Screen" ) );
    mNewCurrentScreenCaptureAction->setIcon ( QIcon::fromTheme ( "view-fullscreen" ) );
    connect ( mNewCurrentScreenCaptureAction,
              SIGNAL ( triggered() ),
              this,
              SLOT ( newCurrentScreenCaptureClicked() ) );

    mNewFullScreenCaptureAction->setIconText ( tr ( "Full Screen (All Monitors)" ) );
    mNewFullScreenCaptureAction->setIcon ( QIcon::fromTheme ( "view-fullscreen" ) );
    connect ( mNewFullScreenCaptureAction,
              SIGNAL ( triggered() ),
              this,
              SLOT ( mNewFullScreenCaptureClicked() ) );

    mNewActiveWindowCaptureAction->setIconText ( tr ( "Active Window" ) );
    mNewActiveWindowCaptureAction->setIcon ( QIcon::fromTheme ( "window" ) );
    connect ( mNewActiveWindowCaptureAction,
              SIGNAL ( triggered() ),
              this,
              SLOT ( newActiveWindowCaptureClicked() ) );

    // Create action for save button
    mSaveAction->setText ( tr ( "Save" ) );
    mSaveAction->setToolTip ( tr ( "Save Screen Capture to file system" ) );
    mSaveAction->setIcon ( QIcon::fromTheme ( "document-save-as" ) );
    mSaveAction->setShortcuts(QKeySequence::Save);
    mSaveAction->connect ( mSaveAction, SIGNAL ( triggered() ), this, 
                           SLOT ( saveCaptureClicked() ) );
    mSaveAction->setEnabled ( false );

    // Create action for copy to clipboard button
    mCopyToClipboardAction->setText ( tr ( "Copy" ) );
    mCopyToClipboardAction->setToolTip ( "Copy Screen Capture to clipboard" );
    mCopyToClipboardAction->setIcon ( QIcon::fromTheme ( "edit-copy" ) );
    mCopyToClipboardAction->setShortcut(QKeySequence::Copy);
    mCopyToClipboardAction->connect ( mCopyToClipboardButton, SIGNAL ( clicked() ), this,
                                      SLOT ( copyToClipboardClicked() ) );

    // Create actions for paint mode
    mPenAction->setText ( tr ( "Pen" ) );
    mPenAction->setIcon ( QIcon::fromTheme ( "tool_pen" ) );
    connect ( mPenAction, SIGNAL ( triggered() ), this, SLOT ( penClicked() ) );

    mMarkerAction->setText ( tr ( "Marker" ) );
    mMarkerAction->setIcon ( QIcon::fromTheme ( "draw-brush" ) );
    connect ( mMarkerAction, SIGNAL ( triggered() ), this, SLOT ( markerClicked() ) );

    mEraseAction->setText ( tr ( "Erase" ) );
    mEraseAction->setIcon ( QIcon::fromTheme ( "draw-eraser" ) );
    connect ( mEraseAction, SIGNAL ( triggered() ), this, SLOT ( eraseClicked() ) );
    
    // Create action for new capture, this will be only used in the menu bar
    mNewCaptureAction->setText( tr ("New"));
    mNewCaptureAction->setShortcut(QKeySequence::New);
    connect( mNewCaptureAction, SIGNAL(triggered()), mNewCaptureButton, SLOT(trigger()));
    
    // Create exit action
    mQuitAction->setText(tr("Quit"));
    mQuitAction->setShortcut(QKeySequence::Quit);
    connect( mQuitAction, SIGNAL(triggered()), this, SLOT(close()));
    
    // Create action for opening settings dialog
    mSettingsDialogAction->setText ( tr ( "Settings" ) );
    connect ( mSettingsDialogAction, SIGNAL ( triggered() ), this, SLOT ( openSettingsDialog() ) );
}

void MainWindow::createToolButtons()
{
    // Create tool button for selecting new capture mode
    mNewCaptureMenu->addAction ( mNewRectAreaCaptureAction );
    mNewCaptureMenu->addAction ( mNewFullScreenCaptureAction );
    mNewCaptureMenu->addAction ( mNewCurrentScreenCaptureAction );
    mNewCaptureMenu->addAction ( mNewActiveWindowCaptureAction );

    mNewCaptureButton->setMenu ( mNewCaptureMenu );
    mNewCaptureButton->setToolButtonStyle ( Qt::ToolButtonTextBesideIcon );
    mNewCaptureButton->setDefaultAction ( mNewRectAreaCaptureAction );
    mNewCaptureButton->setButtonText ( tr ( "New" ) );

    // Create save tool button
    mSaveButton->setToolButtonStyle ( Qt::ToolButtonTextBesideIcon );
    mSaveButton->addAction ( mSaveAction );
    mSaveButton->setDefaultAction ( mSaveAction );

    // Create copy to clipboard tool button
    mCopyToClipboardButton->setToolButtonStyle ( Qt::ToolButtonTextBesideIcon );
    mCopyToClipboardButton->addAction ( mCopyToClipboardAction );
    mCopyToClipboardButton->setDefaultAction ( mCopyToClipboardAction );

    // Create tool button for selecting paint tool
    mPaintToolMenu->addAction ( mPenAction );
    mPaintToolMenu->addAction ( mMarkerAction );
    mPaintToolMenu->addAction ( mEraseAction );

    mPaintToolButton->setMenu ( mPaintToolMenu );
    mPaintToolButton->setToolButtonStyle ( Qt::ToolButtonTextBesideIcon );
    mPaintToolButton->setDefaultAction( mPenAction );
}

void MainWindow::createToolBar()
{   
    mToolBar->addWidget ( mNewCaptureButton );
    mToolBar->addSeparator();
    mToolBar->addWidget ( mSaveButton );
    mToolBar->addWidget ( mCopyToClipboardButton );
    mToolBar->addSeparator();
    mToolBar->addWidget ( mPaintToolButton );
    mToolBar->setFixedSize(mToolBar->sizeHint());
}

void MainWindow::createLayout()
{
    mWindowLayout->addWidget ( mMenuBar );
    mWindowLayout->addWidget ( mToolBar );
    mWindowLayout->addWidget ( mCaptureView );
    mWindowLayout->setAlignment ( Qt::AlignTop | Qt::AlignLeft );
    mWindowLayout->setContentsMargins ( 0, 0, 0, 0 );
    setLayout ( mWindowLayout );
}

void MainWindow::createMenuBar()
{
    QMenu *tmpMenu;

    tmpMenu = mMenuBar->addMenu ( tr ( "File" ) );
    tmpMenu->addAction ( mNewCaptureAction );
    tmpMenu->addAction ( mSaveAction );
    tmpMenu->addSeparator();
    tmpMenu->addAction(mQuitAction);
    tmpMenu = mMenuBar->addMenu ( tr ( "&Edit" ) );
    tmpMenu->addAction(mCopyToClipboardAction);
    tmpMenu = mMenuBar->addMenu ( tr ( "&Options" ) );
    tmpMenu->addAction ( mSettingsDialogAction );
    tmpMenu = mMenuBar->addMenu ( tr ( "&Help" ) );
}