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
    mEraseAction(new QAction(this)),
    mMoveAction(new QAction(this)),
    mUploadToImgurAction(new QAction(this)),
    mPrintImage(new QAction(this)),
    mCropAction(new QAction(this)),
    mNewCaptureAction(new QAction(this)),
    mQuitAction(new QAction(this)),
    mSettingsDialogAction(new QAction(this)),
    mAboutKsnipAction(new QAction(this)),
    mCaptureScene(new PaintArea()),
    mCaptureView(new CaptureView(mCaptureScene)),
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
    connect(mCaptureScene, SIGNAL(imageChanged()), this, SLOT(imageChanged()));
    connect(KsnipConfig::instance(), SIGNAL(captureDelayUpdated(int)),
            this, SLOT(setCaptureDelay(int)));
    connect(mImgurUploader, SIGNAL(uploadFinished(QString)), this, SLOT(imgurUploadFinished(QString)));
    connect(mImgurUploader, SIGNAL(error(QString)), this, SLOT(imgurError(QString)));
    connect(mImgurUploader, SIGNAL(tokenUpdated(QString, QString, QString)),
            this, SLOT(imgurTokenUpdated(QString, QString, QString)));
    connect(mImgurUploader, SIGNAL(tokenRefreshRequired()), this, SLOT(imgurTokenRefresh()));
    connect(mCropPanel, SIGNAL(close()), this, SLOT(closeCrop()));

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

    mCaptureScene->loadCapture(screenshot);
    mCaptureScene->setIsEnabled(true);

    if (mCaptureScene->areaSize().width() > mImageGrabber->currectScreenRect().width() ||
            mCaptureScene->areaSize().height() > mImageGrabber->currectScreenRect().height()) {
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
    if (!mCaptureScene->isValid()) {
        statusBar()->setHidden(true);
        QWidget::resize(minimumSize());
    } else {
        statusBar()->setHidden(false);
        QWidget::resize(mCaptureScene->areaSize() + QSize(100, 150));
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
    if (!mCaptureScene->isValid()) {
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
 * Sets and disables image related buttons
 */
void MainWindow::setEnablements(bool enabled)
{
    if (enabled) {
        mCropAction->setEnabled(true);
        mPrintImage->setEnabled(true);
        mUploadToImgurAction->setEnabled(true);
        mCopyToClipboardAction->setEnabled(true);
    } else {
        mCropAction->setEnabled(false);
        mPrintImage->setEnabled(false);
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
    if (KsnipConfig::instance()->paintMode() == PaintArea::Marker) {
        mCaptureScene->setPaintMode(PaintArea::Marker);
        mPaintToolButton->setDefaultAction(mMarkerAction);
    } else {
        mCaptureScene->setPaintMode(PaintArea::Pen);
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
    mClipboard->setImage(mCaptureScene->exportAsImage());
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
        qCritical("MainWindow::instantSave: Unable to save capture at " + savePath.toLatin1());
    }
}

void MainWindow::initGui()
{
    // Create actions

    // Create actions for capture modes
    mNewRectAreaCaptureAction->setIconText(tr("Rectangular Area"));
    mNewRectAreaCaptureAction->setToolTip(tr("Draw a rectangular area with your mouse."));
    mNewRectAreaCaptureAction->setIcon(createIcon("drawRect")) ;
    connect(mNewRectAreaCaptureAction,
            SIGNAL(triggered()),
            this,
            SLOT(newRectAreaCaptureClicked()));

    mNewFullScreenCaptureAction->setIconText(tr("Full Screen (All Monitors)"));
    mNewFullScreenCaptureAction->setToolTip(tr("Capture full screen including all monitors."));
    mNewFullScreenCaptureAction->setIcon(createIcon("fullScreen"));
    connect(mNewFullScreenCaptureAction,
            SIGNAL(triggered()),
            this,
            SLOT(newFullScreenCaptureClicked()));

    mNewCurrentScreenCaptureAction->setIconText(tr("Current Screen"));
    mNewCurrentScreenCaptureAction->setToolTip(tr("Capture screen where the mouse is located."));
    mNewCurrentScreenCaptureAction->setIcon(createIcon("currentScreen"));
    connect(mNewCurrentScreenCaptureAction,
            SIGNAL(triggered()),
            this,
            SLOT(newCurrentScreenCaptureClicked()));

    mNewActiveWindowCaptureAction->setIconText(tr("Active Window"));
    mNewActiveWindowCaptureAction->setToolTip(tr("Capture window that currently has focus."));
    mNewActiveWindowCaptureAction->setIcon(createIcon("activeWindow"));
    connect(mNewActiveWindowCaptureAction,
            SIGNAL(triggered()),
            this,
            SLOT(newActiveWindowCaptureClicked()));

    // Create action for save button
    mSaveAction->setText(tr("Save"));
    mSaveAction->setToolTip(tr("Save Screen Capture to file system"));
    mSaveAction->setIcon(createIcon("save"));
    mSaveAction->setShortcut(QKeySequence::Save);
    mSaveAction->connect(mSaveAction, SIGNAL(triggered()), this,
                         SLOT(saveCaptureClicked()));
    mSaveAction->setEnabled(false);

    // Create action for copy to clipboard button
    mCopyToClipboardAction->setText(tr("Copy"));
    mCopyToClipboardAction->setToolTip(tr("Copy Screen Capture to clipboard"));
    mCopyToClipboardAction->setIcon(createIcon("copyToClipboard")) ;
    mCopyToClipboardAction->setShortcut(QKeySequence::Copy);
    mCopyToClipboardAction->connect(mCopyToClipboardAction, SIGNAL(triggered()), this,
                                    SLOT(copyToClipboardClicked()));

    // Create Action for imgur.com uploader
    mUploadToImgurAction->setText(tr("Upload"));
    mUploadToImgurAction->setToolTip(tr("Upload capture image to imgur.com"));
    connect(mUploadToImgurAction, SIGNAL(triggered()),
            this, SLOT(imgurUploadClicked()));

    // Create print action
    mPrintImage->setText(tr("Print"));
    mPrintImage->setToolTip(tr("Open printer dialog and provide option to print image."));
    mPrintImage->setShortcut(QKeySequence::Print);
    connect(mPrintImage, SIGNAL(triggered()), this, SLOT(printClicked()));

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
    connect(mQuitAction, SIGNAL(triggered()), this, SLOT(close()));

    // Create action for opening settings dialog
    mSettingsDialogAction->setText(tr("Settings"));
    connect(mSettingsDialogAction, SIGNAL(triggered()), this, SLOT(openSettingsDialog()));

    mAboutKsnipAction->setText(tr("&About"));
    connect(mAboutKsnipAction, SIGNAL(triggered()), this, SLOT(openAboutDialog()));

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
    mPaintToolMenu->addAction(mEraseAction);
    mPaintToolMenu->addAction(mMoveAction);

    mPaintToolButton->setMenu(mPaintToolMenu);
    mPaintToolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mPaintToolButton->setDefaultAction(mPenAction);

    // Create menu bar
    QMenu* menu;
    menu = menuBar()->addMenu(tr("File"));
    menu->addAction(mNewCaptureAction);
    menu->addAction(mSaveAction);
    menu->addAction(mUploadToImgurAction);
    menu->addAction(mPrintImage);
    menu->addSeparator();
    menu->addAction(mQuitAction);
    menu = menuBar()->addMenu(tr("&Edit"));
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
    mSnippingArea->show();
    mCaptureScene->setIsEnabled(false);
    KsnipConfig::instance()->setCaptureMode(ImageGrabber::RectArea);
}

void MainWindow::newCurrentScreenCaptureClicked()
{
    setWindowOpacity(0.0);
    setWindowState(Qt::WindowMinimized);
    mCaptureScene->setIsEnabled(false);
    delay(mCaptureDelay);
    show(mImageGrabber->grabImage(ImageGrabber::CurrentScreen,
                                  KsnipConfig::instance()->captureMouse()));
    KsnipConfig::instance()->setCaptureMode(ImageGrabber::CurrentScreen);
}

void MainWindow::newFullScreenCaptureClicked()
{
    setWindowOpacity(0.0);
    setWindowState(Qt::WindowMinimized);
    mCaptureScene->setIsEnabled(false);
    delay(mCaptureDelay);
    show(mImageGrabber->grabImage(ImageGrabber::FullScreen,
                                  KsnipConfig::instance()->captureMouse()));
    KsnipConfig::instance()->setCaptureMode(ImageGrabber::FullScreen);
}

void MainWindow::newActiveWindowCaptureClicked()
{
    setWindowOpacity(0.0);
    setWindowState(Qt::WindowMinimized);
    mCaptureScene->setIsEnabled(false);
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

    if (saveDialog.exec() == QDialog::Accepted) {

        if (!mCaptureScene->exportAsImage().save(saveDialog.selectedFiles().first())) {
            qCritical("PaintWindow::saveCaptureClicked: Unable to save file " +
                      saveDialog.selectedFiles().first().toLatin1());
            return;
        }

        setSaveAble(false);
    }
}

void MainWindow::copyToClipboardClicked()
{
    copyToClipboard();
}

void MainWindow::penClicked()
{
    mCaptureScene->setPaintMode(PaintArea::Pen);
    KsnipConfig::instance()->setPaintMode(PaintArea::Pen);
}

void MainWindow::markerClicked()
{
    mCaptureScene->setPaintMode(PaintArea::Marker);
    KsnipConfig::instance()->setPaintMode(PaintArea::Marker);
}

void MainWindow::eraseClicked()
{
    mCaptureScene->setPaintMode(PaintArea::Erase);
}

void MainWindow::moveClicked()
{
    mCaptureScene->setPaintMode(PaintArea::Move);
}

/*
 * Upload Image to Imgur page, this function only starts the upload, if the upload was successful
 * is determent by the uploadToImgurFinished function.
 */
void MainWindow::imgurUploadClicked()
{
    // If we have no capture, abort here.
    if (!mCaptureScene->isValid()) {
        return;
    }

    // Upload to Imgur Account
    if (!KsnipConfig::instance()->imgurForceAnonymous() &&
            !KsnipConfig::instance()->imgurAccessToken().isEmpty()) {
        mImgurUploader->startUpload(mCaptureScene->exportAsImage(),
                                    KsnipConfig::instance()->imgurAccessToken());
    } else {
        // Upload Anonymous
        mImgurUploader->startUpload(mCaptureScene->exportAsImage());
    }

    statusBar()->showMessage(tr("Waiting for imgur.com..."));
}

void MainWindow::printClicked()
{
    if (!mCaptureScene->isValid()) {
        return;
    }

    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog* dlg = new QPrintDialog(&printer);
    if (dlg->exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        painter.drawImage(QPoint(0, 0), mCaptureScene->exportAsImage());
        painter.end();
    }
    delete dlg;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape) {
        mSnippingArea->hide();
        setWindowOpacity(1.0);
        mCaptureScene->setIsEnabled(true);
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
    qCritical(message.toLatin1());
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
