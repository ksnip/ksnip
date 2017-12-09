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

MainWindow::MainWindow() : QMainWindow(),
    mNewCaptureButton(new CustomToolButton),
    mSaveButton(new QToolButton),
    mCopyToClipboardButton(new QToolButton),
    mPaintToolButton(new CustomToolButton),
    mPainterSettingsButton(new PainterSettingsPicker(this, 5)),
    mPaintToolMenu(new QMenu),
    mNewCaptureMenu(new QMenu),
    mNewRectAreaCaptureAction(new QAction(this)),
    mNewCurrentScreenCaptureAction(new QAction(this)),
    mNewFullScreenCaptureAction(new QAction(this)),
    mNewActiveWindowCaptureAction(new QAction(this)),
    mSaveAction(new QAction(this)),
    mCopyToClipboardAction(new QAction(this)),
    mPenAction(new QAction(this)),
    mMarkerAction(new QAction(this)),
    mRectAction(new QAction(this)),
    mEllipseAction(new QAction(this)),
    mTextAction(new QAction(this)),
    mEraseAction(new QAction(this)),
    mMoveAction(new QAction(this)),
    mUploadToImgurAction(new QAction(this)),
    mPrintAction(new QAction(this)),
    mPrintPreviewAction(new QAction(this)),
    mCropAction(new QAction(this)),
    mNewCaptureAction(new QAction(this)),
    mQuitAction(new QAction(this)),
    mSettingsDialogAction(new QAction(this)),
    mAboutKsnipAction(new QAction(this)),
    mPaintArea(new PaintArea()),
    mCaptureView(new CaptureView(mPaintArea)),
    mUndoAction(mPaintArea->createUndoAction()),
    mRedoAction(mPaintArea->createRedoAction()),
    mClipboard(QApplication::clipboard()),
    mSnippingArea(new SnippingArea(this)),
    mImageGrabber(new ImageGrabber(this)),
    mImgurUploader(new ImgurUploader(this)),
    mCropPanel(new CropPanel(mCaptureView))
{
    initGui();

    mCaptureView->hide();

    setWindowIcon(createIcon("ksnip"));
    move(KsnipConfig::instance()->windowPosition());

    // Create a connection with other widget elements
    connect(mSnippingArea, SIGNAL(areaSelected(QRect)), this, SLOT(areaSelected(QRect)));
    connect(mPaintArea, SIGNAL(imageChanged()), this, SLOT(imageChanged()));
    connect(KsnipConfig::instance(), SIGNAL(captureDelayUpdated(int)),
            this, SLOT(setCaptureDelay(int)));
    connect(mImgurUploader, SIGNAL(uploadFinished(QString)), this, SLOT(imgurUploadFinished(QString)));
    connect(mImgurUploader, SIGNAL(error(QString)), this, SLOT(imgurError(QString)));
    connect(mImgurUploader, SIGNAL(tokenUpdated(QString, QString, QString)),
            this, SLOT(imgurTokenUpdated(QString, QString, QString)));
    connect(mImgurUploader, SIGNAL(tokenRefreshRequired()), this, SLOT(imgurTokenRefresh()));
    connect(mCropPanel, SIGNAL(close()), this, SLOT(closeCrop()));
    connect(mCaptureView, SIGNAL(closeCrop()), this, SLOT(closeCrop()));

    loadSettings();
}

//
// Public Functions
//

void MainWindow::show(QPixmap screenshot)
{
    setWindowState(Qt::WindowActive);
    setWindowOpacity(1.0);

    if (screenshot.isNull()) {
        qCritical("PaintWindow::showWindow: No image provided to but it was expected.");
        return show();
    }

    mPaintArea->loadCapture(screenshot);
    mPaintArea->setIsEnabled(true);

    if (mPaintArea->areaSize().width() > mImageGrabber->currectScreenRect().width() ||
            mPaintArea->areaSize().height() > mImageGrabber->currectScreenRect().height()) {
        setWindowState(Qt::WindowMaximized);
    } else {
        resize();
    }

    mCaptureView->show();
    setSaveAble(true);
    setEnablements(true);
    closeCrop();

    if (KsnipConfig::instance()->alwaysCopyToClipboard()) {
        copyToClipboard();
    }

    QWidget::show();
}

void MainWindow::show()
{
    setWindowState(Qt::WindowActive);
    mCaptureView->hide();
    setSaveAble(false);
    setEnablements(false);
    closeCrop();
    QWidget::show();
}

int MainWindow::captureDelay() const
{
    return mCaptureDelay;
}

/*
 * Function for instant capturing used from command line. The function grabs the image and saves it
 * directly to disk. If some delay was set it will be added, otherwise delay is set to 0 and skipped
 */
void MainWindow::instantCapture(ImageGrabber::CaptureMode captureMode, int seconds)
{
    delay(seconds * 1000);

    switch (captureMode) {
    case ImageGrabber::RectArea:
        break;

    case ImageGrabber::CurrentScreen:
        instantSave(mImageGrabber->grabImage(ImageGrabber::CurrentScreen,
                                             KsnipConfig::instance()->captureMouse()));
        break;

    case ImageGrabber::ActiveWindow:
        instantSave(mImageGrabber->grabImage(ImageGrabber::ActiveWindow,
                                             KsnipConfig::instance()->captureMouse()));
        break;

    case ImageGrabber::FullScreen:
    default:
        instantSave(mImageGrabber->grabImage(ImageGrabber::FullScreen,
                                             KsnipConfig::instance()->captureMouse()));
    }
}

/*
 * Sets the Main Window size to fit all content correctly, it takes into account if an image was
 * loaded or not,  if the status bar is show or not, and so on. If no image is loaded the status bar
 * is hidden too.
 */
void MainWindow::resize()
{
    if (!mPaintArea->isValid()) {
        statusBar()->setHidden(true);
        QWidget::resize(minimumSize());
    } else {
        statusBar()->setHidden(false);
        mPaintArea->fitViewToParent();
    }
}

//
// Public Slots
//

/*
 * Delay is never set below 300ms to leave enough time for the ksnip window to disappear before
 * taking the screenshot.
 */
void MainWindow::setCaptureDelay(int ms)
{
    if (ms < 300) {
        mCaptureDelay = 300;
    } else {
        mCaptureDelay = ms;
    }
}

void MainWindow::openCrop()
{
    if (!mPaintArea->isValid()) {
        return;
    }
    statusBar()->addPermanentWidget(mCropPanel, 1);
    mCropPanel->show();
    statusBar()->setHidden(false);
}

void MainWindow::closeCrop()
{
    statusBar()->removeWidget(mCropPanel);
    statusBar()->setHidden(true);
}

QMenu* MainWindow::createPopupMenu()
{
    // Filtering out the option to hide main toolbar which should no be allowed.
    QMenu* filteredMenu = QMainWindow::createPopupMenu();
    filteredMenu->removeAction(mToolBar->toggleViewAction());
    return filteredMenu;
}

/*
 * Called by signals from painter settings picker tool button to change the
 * color of the current tool.
 */
void MainWindow::colorChanged(const QColor& color)
{
    KsnipConfig* config = KsnipConfig::instance();
    switch (mPaintArea->paintMode()) {
    case PaintArea::Pen:
        config->setPenColor(color);
        break;
    case PaintArea::Marker:
        config->setMarkerColor(color);
        break;
    case PaintArea::Rect:
        config->setRectColor(color);
        break;
    case PaintArea::Ellipse:
        config->setEllipseColor(color);
        break;
    case PaintArea::Text:
        config->setTextColor(color);
        break;
    default:
        break;
    }
}

/*
 * Called by signals from painter settings picker tool button to change the
 * fill of the current tool.
 */
void MainWindow::fillChanged(const bool& fill)
{
    KsnipConfig* config = KsnipConfig::instance();
    switch (mPaintArea->paintMode()) {
    case PaintArea::Rect:
        config->setRectFill(fill);
        break;
    case PaintArea::Ellipse:
        config->setEllipseFill(fill);
        break;
    default:
        break;
    }
}

/*
 * Called by signals from painter settings picker tool button to change the
 * size of the current tool.
 */
void MainWindow::sizeChanged(const int& size)
{
    KsnipConfig* config = KsnipConfig::instance();
    switch (mPaintArea->paintMode()) {
    case PaintArea::Pen:
        config->setPenSize(size);
        break;
    case PaintArea::Marker:
        config->setMarkerSize(size);
        break;
    case PaintArea::Rect:
        config->setRectSize(size);
        break;
    case PaintArea::Ellipse:
        config->setEllipseSize(size);
        break;
    case PaintArea::Text:
        config->setTextSize(size);
        break;
    case PaintArea::Erase:
        config->setEraseSize(size);
    default:
        break;
    }
}

//
// Protected Functions
//

void MainWindow::moveEvent(QMoveEvent* event)
{
    KsnipConfig::instance()->setWindowPosition(pos());
    QWidget::moveEvent(event);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (KsnipConfig::instance()->promptSaveBeforeExit() && mIsUnsaved) {
        bool reply = popupQuestion(tr("Warning - ") + QApplication::applicationName(),
                                   tr("The capture has been modified.\nDo you want to save it?"));

        if (reply) {
            saveCaptureClicked();
            event->ignore();
        } else {
            event->accept();
        }
    } else {
        event->accept();
    }
}

//
// Private Functions
//

void MainWindow::delay(int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);

    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

/*
 * Sets the state of the widget when the image was changed or save, depending
 * on the provided boolean value. If true, the save action is enabled and
 * the title changed.
 */
void MainWindow::setSaveAble(bool enabled)
{
    if (enabled) {
        mSaveAction->setEnabled(true);
        setWindowTitle("*" + QApplication::applicationName() + " - " + tr("Unsaved"));
        mIsUnsaved = true;
    } else {
        mSaveAction->setEnabled(false);
        setWindowTitle(QApplication::applicationName());
        mIsUnsaved = false;
    }
}

/*
 * Sets and disables image related buttons, only save button related stuff is
 * set under setSaveAble
 */
void MainWindow::setEnablements(bool enabled)
{
    if (enabled) {
        mCropAction->setEnabled(true);
        mPrintAction->setEnabled(true);
        mPrintPreviewAction->setEnabled(true);
        mUploadToImgurAction->setEnabled(true);
        mCopyToClipboardAction->setEnabled(true);
    } else {
        mCropAction->setEnabled(false);
        mPrintAction->setEnabled(false);
        mPrintPreviewAction->setEnabled(false);
        mUploadToImgurAction->setEnabled(false);
        mCopyToClipboardAction->setEnabled(false);
    }
}


/*
 * This loads ksnip settings from the config file
 */
void MainWindow::loadSettings()
{
    // Load capture delay setting
    setCaptureDelay(KsnipConfig::instance()->captureDelay());

    // Load paintmode setting
    KsnipConfig::instance()->paintMode();
    switch (KsnipConfig::instance()->paintMode()) {
    case PaintArea::Pen:
        setPaintMode(PaintArea::Pen, false);
        mPaintToolButton->setDefaultAction(mPenAction);
        break;
    case PaintArea::Marker:
        setPaintMode(PaintArea::Marker, false);
        mPaintToolButton->setDefaultAction(mMarkerAction);
        break;
    case PaintArea::Rect:
        setPaintMode(PaintArea::Rect, false);
        mPaintToolButton->setDefaultAction(mRectAction);
        break;
    case PaintArea::Ellipse:
        setPaintMode(PaintArea::Ellipse, false);
        mPaintToolButton->setDefaultAction(mEllipseAction);
        break;
    case PaintArea::Text:
        setPaintMode(PaintArea::Text, false);
        mPaintToolButton->setDefaultAction(mTextAction);
        break;
    default:
        setPaintMode(PaintArea::Pen, false);
        mPaintToolButton->setDefaultAction(mPenAction);
    }

    // Load capture mode setting
    switch (KsnipConfig::instance()->captureMode()) {
    case ImageGrabber::ActiveWindow:
        mNewCaptureButton->setDefaultAction(mNewActiveWindowCaptureAction);
        break;

    case ImageGrabber::CurrentScreen:
        mNewCaptureButton->setDefaultAction(mNewCurrentScreenCaptureAction);
        break;

    case ImageGrabber::FullScreen:
        mNewCaptureButton->setDefaultAction(mNewFullScreenCaptureAction);
        break;

    default:
        mNewCaptureButton->setDefaultAction(mNewRectAreaCaptureAction);
    }
}

void MainWindow::copyToClipboard()
{
    mClipboard->setImage(mPaintArea->exportAsImage());
}

/*
 * Generic function that can be used to display a simple yes/no question and return appropriate
 * boolean feedback.
 */
bool MainWindow::popupQuestion(QString title, QString question)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, title, question, QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        return true;
    } else {
        return false;
    }
}

/*
 * Checks what png icons are available for that button and adds them to the icon which can then be
 * added to a button, action or similar.
 */
QIcon MainWindow::createIcon(QString name)
{
    QIcon tmpIcon;

    for (int i = 16; i <= 64; i = i * 2) {
        if (QResource(":" + name + QString::number(i) + ".png").isValid()) {
            tmpIcon.addFile((":" + name + QString::number(i) + ".png"), QSize(i, i));
        }
    }

    return tmpIcon;
}

/*
 * This function when called saves the provided pixmap directly to the default save location without
 * asking the user for a new path. Existing images are not overwritten, just names with increasing
 * number.
 */
void MainWindow::instantSave(QPixmap pixmap)
{
    QString savePath = StringManip::makeUniqueFilename(KsnipConfig::instance()->saveDirectory(),
                       StringManip::updateTimeAndDate(KsnipConfig::instance()->saveFilename()),
                       KsnipConfig::instance()->saveFormat());

    // Turn any special characters, like $Y into a valid date and time value.
    if (!pixmap.save(savePath)) {
        qCritical("MainWindow::instantSave: Failed to save file at '%s'", qPrintable(savePath));
    }
}

void MainWindow::initGui()
{
    // Create actions

    // Create actions for capture modes
    mNewRectAreaCaptureAction->setIconText(tr("Rectangular Area"));
    mNewRectAreaCaptureAction->setToolTip(tr("Draw a rectangular area with your mouse"));
    mNewRectAreaCaptureAction->setIcon(createIcon("drawRect"));
    connect(mNewRectAreaCaptureAction, SIGNAL(triggered()),
            this, SLOT(newRectAreaCaptureClicked()));

    mNewFullScreenCaptureAction->setIconText(tr("Full Screen (All Monitors)"));
    mNewFullScreenCaptureAction->setToolTip(tr("Capture full screen including all monitors"));
    mNewFullScreenCaptureAction->setIcon(createIcon("fullScreen"));
    connect(mNewFullScreenCaptureAction, SIGNAL(triggered()),
            this, SLOT(newFullScreenCaptureClicked()));

    mNewCurrentScreenCaptureAction->setIconText(tr("Current Screen"));
    mNewCurrentScreenCaptureAction->setToolTip(tr("Capture screen where the mouse is located"));
    mNewCurrentScreenCaptureAction->setIcon(createIcon("currentScreen"));
    connect(mNewCurrentScreenCaptureAction, SIGNAL(triggered()),
            this, SLOT(newCurrentScreenCaptureClicked()));

    mNewActiveWindowCaptureAction->setIconText(tr("Active Window"));
    mNewActiveWindowCaptureAction->setToolTip(tr("Capture window that currently has focus"));
    mNewActiveWindowCaptureAction->setIcon(createIcon("activeWindow"));
    connect(mNewActiveWindowCaptureAction, SIGNAL(triggered()),
            this, SLOT(newActiveWindowCaptureClicked()));

    // Create action for save button
    mSaveAction->setText(tr("Save"));
    mSaveAction->setToolTip(tr("Save Screen Capture to file system"));
    mSaveAction->setIcon(createIcon("save"));
    mSaveAction->setShortcut(QKeySequence::Save);
    connect(mSaveAction, SIGNAL(triggered()), this, SLOT(saveCaptureClicked()));

    // Create action for copy to clipboard button
    mCopyToClipboardAction->setText(tr("Copy"));
    mCopyToClipboardAction->setToolTip(tr("Copy Screen Capture to clipboard"));
    mCopyToClipboardAction->setIcon(createIcon("copyToClipboard"));
    mCopyToClipboardAction->setShortcut(QKeySequence::Copy);
    connect(mCopyToClipboardAction, SIGNAL(triggered()),
            this, SLOT(copyToClipboardClicked()));

    // Create Action for imgur.com uploader
    mUploadToImgurAction->setText(tr("Upload"));
    mUploadToImgurAction->setToolTip(tr("Upload capture image to imgur.com"));
    mUploadToImgurAction->setShortcut(Qt::SHIFT + Qt::Key_U);
    connect(mUploadToImgurAction, SIGNAL(triggered()), this, SLOT(imgurUploadClicked()));

    // Create print action
    mPrintAction->setText(tr("Print"));
    mPrintAction->setToolTip(tr("Opens printer dialog and provide option to print image"));
    mPrintAction->setShortcut(QKeySequence::Print);
    mPrintAction->setIcon(QIcon::fromTheme("document-print"));
    connect(mPrintAction, SIGNAL(triggered()), this, SLOT(printClicked()));

    // Create print preview action
    mPrintPreviewAction->setText(tr("Print Preview"));
    mPrintPreviewAction->setToolTip(tr("Opens Print Preview dialog where the image "
                                       "orientation can be changed"));
    mPrintPreviewAction->setIcon(QIcon::fromTheme("document-print-preview"));
    connect(mPrintPreviewAction, SIGNAL(triggered()), this, SLOT(printPreviewClicked()));

    // Create crop action
    mCropAction->setText(tr("Crop"));
    mCropAction->setToolTip(tr("Crop Screen Capture"));
    mCropAction->setShortcut(Qt::SHIFT + Qt::Key_C);
    connect(mCropAction, SIGNAL(triggered()), this, SLOT(openCrop()));

    // Create actions for paint mode
    mPenAction->setText(tr("Pen"));
    mPenAction->setIcon(createIcon("pen"));
    connect(mPenAction, SIGNAL(triggered()), this, SLOT(penClicked()));

    mMarkerAction->setText(tr("Marker"));
    mMarkerAction->setIcon(createIcon("marker"));
    connect(mMarkerAction, SIGNAL(triggered()), this, SLOT(markerClicked()));

    mRectAction->setText(tr("Rect"));
    mRectAction->setIcon(createIcon("rect"));
    connect(mRectAction, SIGNAL(triggered()), this, SLOT(rectClicked()));

    mEllipseAction->setText(tr("Ellipse"));
    mEllipseAction->setIcon(createIcon("ellipse"));
    connect(mEllipseAction, SIGNAL(triggered()), this, SLOT(ellipseClicked()));

    mTextAction->setText(tr("Text"));
    mTextAction->setIcon(createIcon("text"));
    connect(mTextAction, SIGNAL(triggered()), this, SLOT(textClicked()));

    mEraseAction->setText(tr("Erase"));
    mEraseAction->setIcon(createIcon("eraser"));
    connect(mEraseAction, SIGNAL(triggered()), this, SLOT(eraseClicked()));

    mMoveAction->setText(tr("Move"));
    mMoveAction->setIcon(createIcon("move"));
    connect(mMoveAction, SIGNAL(triggered()), this, SLOT(moveClicked()));

    // Create action for new capture, this will be only used in the menu bar
    mNewCaptureAction->setText(tr("New"));
    mNewCaptureAction->setShortcut(QKeySequence::New);
    connect(mNewCaptureAction, SIGNAL(triggered()), mNewCaptureButton, SLOT(trigger()));

    // Create exit action
    mQuitAction->setText(tr("Quit"));
    mQuitAction->setShortcut(QKeySequence::Quit);
    mQuitAction->setIcon(QIcon::fromTheme("application-exit"));
    connect(mQuitAction, SIGNAL(triggered()), this, SLOT(close()));

    // Create action for opening settings dialog
    mSettingsDialogAction->setText(tr("Settings"));
    mSettingsDialogAction->setIcon(QIcon::fromTheme("emblem-system"));
    connect(mSettingsDialogAction, SIGNAL(triggered()), this, SLOT(openSettingsDialog()));

    mAboutKsnipAction->setText(tr("&About"));
    mAboutKsnipAction->setIcon(createIcon("ksnip"));
    connect(mAboutKsnipAction, SIGNAL(triggered()), this, SLOT(openAboutDialog()));

    // Undo and redo actions, the action itself is created in the paintarea
    // class and only a pointer returned here.
    mUndoAction->setIcon(QIcon::fromTheme("edit-undo"));
    mUndoAction->setShortcut(QKeySequence::Undo);

    mRedoAction->setIcon(QIcon::fromTheme("edit-redo"));
    mRedoAction->setShortcut(QKeySequence::Redo);

    // Create tool buttons

    // Create tool button for selecting new capture mode
    mNewCaptureMenu->addAction(mNewRectAreaCaptureAction);
    mNewCaptureMenu->addAction(mNewFullScreenCaptureAction);
    mNewCaptureMenu->addAction(mNewCurrentScreenCaptureAction);
    mNewCaptureMenu->addAction(mNewActiveWindowCaptureAction);

    mNewCaptureButton->setMenu(mNewCaptureMenu);
    mNewCaptureButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mNewCaptureButton->setDefaultAction(mNewRectAreaCaptureAction);
    mNewCaptureButton->setButtonText(tr("New"));

    // Create save tool button
    mSaveButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mSaveButton->addAction(mSaveAction);
    mSaveButton->setDefaultAction(mSaveAction);

    // Create copy to clipboard tool button
    mCopyToClipboardButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mCopyToClipboardButton->addAction(mCopyToClipboardAction);
    mCopyToClipboardButton->setDefaultAction(mCopyToClipboardAction);

    // Create tool button for selecting paint tool
    mPaintToolMenu->addAction(mPenAction);
    mPaintToolMenu->addAction(mMarkerAction);
    mPaintToolMenu->addAction(mRectAction);
    mPaintToolMenu->addAction(mEllipseAction);
    mPaintToolMenu->addAction(mTextAction);
    mPaintToolMenu->addAction(mEraseAction);
    mPaintToolMenu->addAction(mMoveAction);

    // Create painter settings tool button;
    mPainterSettingsButton->setIcon(createIcon("painterSettings"));
    mPainterSettingsButton->setToolTip(tr("Setting Painter tool configuration"));
    connect(mPainterSettingsButton,
            SIGNAL(colorChanged(const QColor&)),
            SLOT(colorChanged(const QColor&)));
    connect(mPainterSettingsButton,
            SIGNAL(fillChanged(const bool&)),
            SLOT(fillChanged(const bool&)));
    connect(mPainterSettingsButton,
            SIGNAL(sizeChanged(const int&)),
            SLOT(sizeChanged(const int&)));

    mPaintToolButton->setMenu(mPaintToolMenu);
    mPaintToolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mPaintToolButton->setDefaultAction(mPenAction);

    // Create menu bar
    QMenu* menu;
    menu = menuBar()->addMenu(tr("File"));
    menu->addAction(mNewCaptureAction);
    menu->addAction(mSaveAction);
    menu->addAction(mUploadToImgurAction);
    menu->addSeparator();
    menu->addAction(mPrintAction);
    menu->addAction(mPrintPreviewAction);
    menu->addSeparator();
    menu->addAction(mQuitAction);
    menu = menuBar()->addMenu(tr("&Edit"));
    menu->addAction(mUndoAction);
    menu->addAction(mRedoAction);
    menu->addSeparator();
    menu->addAction(mCopyToClipboardAction);
    menu->addAction(mCropAction);
    menu = menuBar()->addMenu(tr("&Options"));
    menu->addAction(mSettingsDialogAction);
    menu = menuBar()->addMenu(tr("&Help"));
    menu->addAction(mAboutKsnipAction);

    // Create toolbar
    mToolBar = addToolBar("Tools");
    mToolBar->setFloatable(false);
    mToolBar->setMovable(false);
    mToolBar->setAllowedAreas(Qt::BottomToolBarArea);
    mToolBar->addWidget(mNewCaptureButton);
    mToolBar->addSeparator();
    mToolBar->addWidget(mSaveButton);
    mToolBar->addWidget(mCopyToClipboardButton);
    mToolBar->addSeparator();
    mToolBar->addWidget(mPaintToolButton);
    mToolBar->addWidget(mPainterSettingsButton);
    mToolBar->setFixedSize(mToolBar->sizeHint());

    setCentralWidget(mCaptureView);
    resize();
}

//
// Private Slots
//

void MainWindow::newRectAreaCaptureClicked()
{
    setWindowOpacity(0.0);
    setWindowState(Qt::WindowMinimized);
    if(X11GraphicsHelper::isCompositorActive()) {
        mSnippingArea->showWithoutBackground();
    } else {
        delay(200);
        mSnippingArea->showWithBackground(mImageGrabber->grabImage(ImageGrabber::FullScreen, false));
    }
    mPaintArea->setIsEnabled(false);
    KsnipConfig::instance()->setCaptureMode(ImageGrabber::RectArea);
}

void MainWindow::newCurrentScreenCaptureClicked()
{
    setWindowOpacity(0.0);
    setWindowState(Qt::WindowMinimized);
    mPaintArea->setIsEnabled(false);
    delay(mCaptureDelay);
    show(mImageGrabber->grabImage(ImageGrabber::CurrentScreen,
                                  KsnipConfig::instance()->captureMouse()));
    KsnipConfig::instance()->setCaptureMode(ImageGrabber::CurrentScreen);
}

void MainWindow::newFullScreenCaptureClicked()
{
    setWindowOpacity(0.0);
    setWindowState(Qt::WindowMinimized);
    mPaintArea->setIsEnabled(false);
    delay(mCaptureDelay);
    show(mImageGrabber->grabImage(ImageGrabber::FullScreen,
                                  KsnipConfig::instance()->captureMouse()));
    KsnipConfig::instance()->setCaptureMode(ImageGrabber::FullScreen);
}

void MainWindow::newActiveWindowCaptureClicked()
{
    setWindowOpacity(0.0);
    setWindowState(Qt::WindowMinimized);
    mPaintArea->setIsEnabled(false);
    delay(mCaptureDelay);
    show(mImageGrabber->grabImage(ImageGrabber::ActiveWindow,
                                  KsnipConfig::instance()->captureMouse()));
    KsnipConfig::instance()->setCaptureMode(ImageGrabber::ActiveWindow);
}

void MainWindow::saveCaptureClicked()
{
    QFileDialog saveDialog(this, tr("Save As"),
                           KsnipConfig::instance()->saveDirectory() + tr("untitled") +
                           KsnipConfig::instance()->saveFormat(),
                           tr("Images") + " (*.png *.gif *.jpg);;" + tr("All Files") + "(*)");
    saveDialog.setAcceptMode(QFileDialog::AcceptSave);

    if (saveDialog.exec() != QDialog::Accepted) {
        return;
    }

    if (!mPaintArea->exportAsImage().save(saveDialog.selectedFiles().first())) {
        qCritical("PaintWindow::saveCaptureClicked: Unable to save file '%s'",
                  qPrintable(saveDialog.selectedFiles().first()));
        return;
    }

    setSaveAble(false);
}

void MainWindow::copyToClipboardClicked()
{
    copyToClipboard();
}

void MainWindow::penClicked()
{
    if (mPaintArea->paintMode() == PaintArea::Pen) {
        return;
    }
    setPaintMode(PaintArea::Pen);
}

void MainWindow::markerClicked()
{
    if (mPaintArea->paintMode() == PaintArea::Marker) {
        return;
    }
    setPaintMode(PaintArea::Marker);
}

void MainWindow::rectClicked()
{
    if (mPaintArea->paintMode() == PaintArea::Rect) {
        return;
    }
    setPaintMode(PaintArea::Rect);
}

void MainWindow::ellipseClicked()
{
    if (mPaintArea->paintMode() == PaintArea::Ellipse) {
        return;
    }
    setPaintMode(PaintArea::Ellipse);
}

void MainWindow::textClicked()
{
    if (mPaintArea->paintMode() == PaintArea::Text) {
        return;
    }
    setPaintMode(PaintArea::Text);
}

void MainWindow::eraseClicked()
{
    if (mPaintArea->paintMode() == PaintArea::Erase) {
        return;
    }
    setPaintMode(PaintArea::Erase);
}

void MainWindow::moveClicked()
{
    if (mPaintArea->paintMode() == PaintArea::Move) {
        return;
    }
    setPaintMode(PaintArea::Move);
}

/*
 * Upload Image to Imgur page, this function only starts the upload, if the
 * upload was successful is determent by the uploadToImgurFinished function.
 */
void MainWindow::imgurUploadClicked()
{
    // If we have no capture, abort here.
    if (!mPaintArea->isValid()) {
        return;
    }

    // Upload to Imgur Account
    if (!KsnipConfig::instance()->imgurForceAnonymous() &&
            !KsnipConfig::instance()->imgurAccessToken().isEmpty()) {
        mImgurUploader->startUpload(mPaintArea->exportAsImage(),
                                    KsnipConfig::instance()->imgurAccessToken());
    } else {
        // Upload Anonymous
        mImgurUploader->startUpload(mPaintArea->exportAsImage());
    }

    statusBar()->showMessage(tr("Waiting for imgur.com..."));
}

void MainWindow::printClicked()
{
    if (!mPaintArea->isValid()) {
        return;
    }

    QPrinter printer;
    printer.setOutputFileName(KsnipConfig::instance()->saveDirectory() + "untitled.pdf");
    printer.setOutputFormat(QPrinter::NativeFormat);
    QPrintDialog* printDialog = new QPrintDialog(&printer, 0);
    if (printDialog->exec() == QDialog::Accepted) {
        printCapture(&printer);
    }

    delete printDialog;
}

void MainWindow::printPreviewClicked()
{
    if (!mPaintArea->isValid()) {
        return;
    }

    // Opens a print preview dialog where the user change orientation of the print
    QPrinter printer;
    printer.setOutputFileName(KsnipConfig::instance()->saveDirectory() + "untitled.pdf");
    printer.setOutputFormat(QPrinter::NativeFormat);
    QPrintPreviewDialog* pd = new QPrintPreviewDialog(&printer);
    connect(pd, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printCapture(QPrinter*)));
    pd->exec();
}

void MainWindow::printCapture(QPrinter* p)
{
    QPainter painter;
    painter.begin(p);
    QImage image = mPaintArea->exportAsImage();
    double xscale = p->pageRect().width() / double(image.width());
    double yscale = p->pageRect().height() / double(image.height());
    double scale = qMin(xscale, yscale);
    painter.translate(p->paperRect().x() + p->pageRect().width() / 2,
                      p->paperRect().y() + p->pageRect().height() / 2);
    painter.scale(scale, scale);
    painter.translate(-image.width() / 2, -image.height() / 2);
    painter.drawImage(QPoint(0, 0), image);
    painter.end();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape) {
        mSnippingArea->hide();
        setWindowOpacity(1.0);
        mPaintArea->setIsEnabled(true);
    }

    QWidget::keyPressEvent(event);
}

void MainWindow::areaSelected(QRect rect)
{
    delay(mCaptureDelay);
    show(mImageGrabber->grabImage(ImageGrabber::RectArea,
                                  KsnipConfig::instance()->captureMouse(),
                                  &rect));
}

/*
 * Should be called when ever the paintArea was changed, like new drawing and similar
 */
void MainWindow::imageChanged()
{
    setSaveAble(true);

    if (KsnipConfig::instance()->alwaysCopyToClipboard()) {
        copyToClipboard();
    }
}

/*
 * Called when the upload to a file sharing site has finished. Depending on the result value the
 * message either contains the link to the image on the hosting site or the error message
 */
void MainWindow::imgurUploadFinished(QString message)
{
    // When the file extension is provided in the link, it opens the image directly on a blank
    // white background. If the link is opened without the extension then the usual Imgur page
    // is shown
    if (!KsnipConfig::instance()->imgurOpenLinkDirectlyToImage()) {
        message = message.remove(".png");
    }

    // Open the link in the default browser
    QDesktopServices::openUrl(message);

    // If we always copy to clipboard is enabled then copy the link to clipboard
    if (KsnipConfig::instance()->imgurAlwaysCopyToClipboard()) {
        mClipboard->setText(message);
    }

    statusBar()->showMessage(tr("Upload to imgur.com finished!"), 3000);
}

/*
 * Some error happened while uploading and we are not able to proceed.
 */
void MainWindow::imgurError(QString message)
{
    qCritical("MainWindow: Imgur uploader returned error: '%s'", qPrintable(message));
    statusBar()->showMessage(tr("An error occurred while uploading to imgur.com."), 3000);
}

/*
 * New token received from imgur, this could be the case when we have refreshed the token.
 */
void MainWindow::imgurTokenUpdated(const QString accessToken,
                                   const QString refreshTocken,
                                   const QString username)
{
    KsnipConfig::instance()->setImgurAccessToken(accessToken.toUtf8());
    KsnipConfig::instance()->setImgurRefreshToken(refreshTocken.toUtf8());
    KsnipConfig::instance()->setImgurUsername(username);

    // Currently we presume that a token update here only happens when we were trying to upload an
    // image and the token was expired, so right after the token has been refreshed, we try to
    // upload again.
    statusBar()->showMessage("Received new token, trying upload again...");
    imgurUploadClicked();
}

/*
 * The imgur uploader informs us that the token must be refreshed so we refresh it right away
 */
void MainWindow::imgurTokenRefresh()
{
    mImgurUploader->refreshToken(KsnipConfig::instance()->imgurRefreshToken(),
                                 KsnipConfig::instance()->imgurClientId(),
                                 KsnipConfig::instance()->imgurClientSecret());

    statusBar()->showMessage("Imgur token has expired, requesting new token...");
}

void MainWindow::openSettingsDialog()
{
    SettingsDialog settingsDialog(this);
    settingsDialog.exec();
}

void MainWindow::openAboutDialog()
{
    AboutDialog aboutDialog(this);
    aboutDialog.exec();
}

void MainWindow::setPaintMode(const PaintArea::PaintMode& mode, const bool& save)
{
    KsnipConfig* config = KsnipConfig::instance();
    mPaintArea->setPaintMode(mode);

    if (save && mode != PaintArea::Erase && mode != PaintArea::Move) {
        config->setPaintMode(mode);
    }

    mPainterSettingsButton->clearPopup();
    switch (mode) {
    case PaintArea::Pen:
        mPainterSettingsButton->addPopupColorGrid(true, false, true);
        mPainterSettingsButton->addPopupSizeSlider(1, 10, 1);
        mPainterSettingsButton->setColor(config->penColor());
        mPainterSettingsButton->setSize(config->penSize());
        break;
    case PaintArea::Marker:
        mPainterSettingsButton->addPopupColorGrid(false, false, false);
        mPainterSettingsButton->insertColor("yellow");
        mPainterSettingsButton->insertColor("blue");
        mPainterSettingsButton->insertColor("cyan");
        mPainterSettingsButton->insertColor("orange");
        mPainterSettingsButton->insertColor("red");
        mPainterSettingsButton->addPopupSizeSlider(10, 30, 2);
        mPainterSettingsButton->setColor(config->markerColor());
        mPainterSettingsButton->setSize(config->markerSize());
        break;
    case PaintArea::Rect:
        mPainterSettingsButton->addPopupColorGrid(true, true, true);
        mPainterSettingsButton->addPopupSizeSlider(1, 10, 1);
        mPainterSettingsButton->setColor(config->rectColor());
        mPainterSettingsButton->setSize(config->rectSize());
        mPainterSettingsButton->setFill(config->rectFill());
        break;
    case PaintArea::Ellipse:
        mPainterSettingsButton->addPopupColorGrid(true, true, true);
        mPainterSettingsButton->addPopupSizeSlider(1, 10, 1);
        mPainterSettingsButton->setColor(config->ellipseColor());
        mPainterSettingsButton->setSize(config->ellipseSize());
        mPainterSettingsButton->setFill(config->ellipseFill());
        break;
    case PaintArea::Text:
        mPainterSettingsButton->addPopupColorGrid(true, false, true);
        mPainterSettingsButton->addPopupSizeSlider(10, 20, 1);
        mPainterSettingsButton->setColor(config->textColor());
        mPainterSettingsButton->setSize(config->textSize());
        break;
    case PaintArea::Erase:
        mPainterSettingsButton->addPopupSizeSlider(1, 10, 1);
        mPainterSettingsButton->setSize(config->eraseSize());
        break;
    case PaintArea::Move:
        break;
    }
}
