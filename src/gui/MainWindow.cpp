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

MainWindow::MainWindow(AbstractImageGrabber *imageGrabber, RunMode mode) :
	QMainWindow(),
	mImageGrabber(imageGrabber),
	mMode(mode),
	mKImageAnnotator(new KImageAnnotator),
	mUploadToImgurAction(new QAction(this)),
	mPrintAction(new QAction(this)),
	mPrintPreviewAction(new QAction(this)),
	mQuitAction(new QAction(this)),
	mSettingsDialogAction(new QAction(this)),
	mAboutAction(new QAction(this)),
	mOpenImageAction(new QAction(this)),
	mScaleAction(new QAction(this)),
	mAddWatermarkAction(new QAction(this)),
	mClipboard(QApplication::clipboard()),
	mConfig(KsnipConfig::instance()),
	mCapturePrinter(new CapturePrinter),
	mCaptureUploader(new CaptureUploader()),
	mGlobalHotKeyHandler(new GlobalHotKeyHandler(mImageGrabber->supportedCaptureModes())),
	mTrayIcon(new TrayIcon(this))
{
    // When we run in CLI only mode we don't need to setup gui, but only need
    // to connect imagegrabber signals to mainwindow slots to handle the
    // feedback.
    if (mMode == RunMode::CLI) {
        connect(mImageGrabber, &AbstractImageGrabber::finished, this, &MainWindow::processInstantCapture);
        connect(mImageGrabber, &AbstractImageGrabber::canceled, this, &MainWindow::close);
        return;
    }

    initGui();

	setWindowIcon(QIcon(QStringLiteral(":/icons/ksnip.svg")));
	setPosition(mConfig->windowPosition());

	connect(mConfig, &KsnipConfig::toolConfigChanged, this, &MainWindow::setupImageAnnotator);

	connect(mKImageAnnotator, &KImageAnnotator::imageChanged, this, &MainWindow::screenshotChanged);

    connect(mImageGrabber, &AbstractImageGrabber::finished, this, &MainWindow::showCapture);
    connect(mImageGrabber, &AbstractImageGrabber::canceled, [this]() { setHidden(false); });

    connect(mCaptureUploader, &CaptureUploader::finished, this, &MainWindow::uploadFinished);

    connect(mGlobalHotKeyHandler, &GlobalHotKeyHandler::newCaptureTriggered, this, &MainWindow::triggerNewCapture);

    loadSettings();

    if (mMode == RunMode::GUI) {
        if (mConfig->captureOnStartup()) {
            capture(mConfig->captureMode());
        } else {
            showEmpty();
        }
    }

	setupImageAnnotator();
	QWidget::resize(minimumSize());
}

void MainWindow::setPosition(const QPoint &lastPosition)
{
	auto position = lastPosition;
	auto screenGeometry = QApplication::desktop()->screenGeometry();
	if(!screenGeometry.contains(lastPosition)) {
		auto screenCenter = screenGeometry.center();
		position = QPoint(screenCenter.x() - size().width(), screenCenter.y() - size().height());
	}
	move(position);
}

MainWindow::~MainWindow()
{
    delete mKImageAnnotator;
    delete mUploadToImgurAction;
    delete mPrintAction;
    delete mPrintPreviewAction;
    delete mQuitAction;
    delete mSettingsDialogAction;
    delete mAboutAction;
    delete mOpenImageAction;
    delete mScaleAction;
    delete mAddWatermarkAction;
    delete mCapturePrinter;
    delete mCaptureUploader;
    delete mTrayIcon;
}

void MainWindow::processInstantCapture(const CaptureDto &capture)
{
	loadCapture(capture);
	instantSave();
	mKImageAnnotator->close();
	close();
}

void MainWindow::screenshotChanged()
{
    setSaveable(true);

    if (mConfig->alwaysCopyToClipboard()) {
        copyCaptureToClipboard();
    }
}

//
// Public Functions
//

void MainWindow::captureScreenshot(CaptureModes captureMode, bool captureCursor, int delay)
{
	mImageGrabber->grabImage(captureMode, captureCursor, delay, mConfig->freezeImageWhileSnippingEnabled());
}

void MainWindow::quit()
{
	if (!discardChanges()) {
		return;
	}
	mTrayIcon->hide();
	QCoreApplication::exit(0);
}

void MainWindow::showCapture(const CaptureDto &capture)
{
    if (!capture.isValid()) {
    	NotifyOperation operation(mTrayIcon, tr("Unable to show image"), tr("No image provided to but one was expected."), NotificationTypes::Critical);
    	operation.execute();
        showEmpty();
        return;
    }

	loadCapture(capture);

	if (mConfig->alwaysCopyToClipboard()) {
		copyCaptureToClipboard();
	}

	setHidden(false);
    setSaveable(true);
    setEnablements(true);

    adjustSize();
    QMainWindow::show();
}

void MainWindow::loadCapture(const CaptureDto &capture)
{
	mKImageAnnotator->loadImage(capture.screenshot);
	if (capture.isCursorValid()) {
		mKImageAnnotator->insertImageItem(capture.cursor.position, capture.cursor.image);
	}
}

void MainWindow::showEmpty()
{
    setHidden(false);
    setSaveable(false);
    setEnablements(false);
    QMainWindow::show();
}

void MainWindow::show()
{
	activateWindow();
	raise();
	QWidget::show();
	setWindowState(Qt::WindowActive);
}


void MainWindow::triggerNewDefaultCapture()
{
    triggerNewCapture(mConfig->captureMode());
}

QMenu* MainWindow::createPopupMenu()
{
    // Filtering out the option to hide main toolbar which should no be allowed.
    auto filteredMenu = QMainWindow::createPopupMenu();
    filteredMenu->removeAction(mToolBar->toggleViewAction());
    return filteredMenu;
}

QSize MainWindow::sizeHint() const
{
	auto minHeight = mToolBar->sizeHint().height();
	auto minWidth = mToolBar->sizeHint().width();
	auto annotatorHeight = mKImageAnnotator->sizeHint().height();
	auto annotatorWidth = mKImageAnnotator->sizeHint().width();
	auto height = minHeight + annotatorHeight;
	auto width = minWidth > annotatorWidth ? minWidth : annotatorWidth;
	return { width, height };
}

//
// Protected Functions
//

void MainWindow::moveEvent(QMoveEvent* event)
{
    mConfig->setWindowPosition(pos());
    QWidget::moveEvent(event);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	event->ignore();
	if(mTrayIcon->isVisible() && mConfig->closeToTray()) {
		hide();
	} else{
		quit();
	}
}

void MainWindow::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::WindowStateChange && isMinimized() && mTrayIcon->isVisible() && mConfig->minimizeToTray()) {
		event->ignore();
		hide();
	}
	QWidget::changeEvent(event);
}

//
// Private Functions
//

void MainWindow::setSaveable(bool enabled)
{
    if (enabled) {
        setWindowTitle(QStringLiteral("*") + QApplication::applicationName() + " - " + tr("Unsaved"));
    } else {
        setWindowTitle(QApplication::applicationName());
    }
    mIsUnsaved = enabled;
    mToolBar->setSaveActionEnabled(enabled);
}

void MainWindow::setEnablements(bool enabled)
{
    mPrintAction->setEnabled(enabled);
    mPrintPreviewAction->setEnabled(enabled);
    mUploadToImgurAction->setEnabled(enabled);
	mScaleAction->setEnabled(enabled);
	mAddWatermarkAction->setEnabled(enabled);
    mToolBar->setCopyActionEnabled(enabled);
    mToolBar->setCropEnabled(enabled);
}

void MainWindow::loadSettings()
{
    mToolBar->selectCaptureMode(mConfig->captureMode());
    mToolBar->setCaptureDelay(mConfig->captureDelay() / 1000);
}

void MainWindow::setHidden(bool isHidden)
{
    if (isHidden == hidden()) {
        return;
    }

    mHidden = isHidden;
    if (mHidden) {
        setWindowOpacity(0.0);
        showMinimized();
    } else {
        setWindowOpacity(1.0);
        setWindowState(Qt::WindowActive);
    }
}

bool MainWindow::hidden() const
{
    return mHidden;
}

void MainWindow::capture(CaptureModes captureMode)
{
    setHidden(true);
    mConfig->setCaptureMode(captureMode);

	captureScreenshot(captureMode, mConfig->captureCursor(), mConfig->captureDelay());
}

void MainWindow::triggerNewCapture(CaptureModes captureMode)
{
	if (!discardChanges()) {
        return;
    }
    capture(captureMode);
}

void MainWindow::initGui()
{
    mToolBar = new MainToolBar(mImageGrabber->supportedCaptureModes(), mKImageAnnotator->undoAction(), mKImageAnnotator->redoAction());

    connect(mToolBar, &MainToolBar::captureModeSelected, this, &MainWindow::triggerNewCapture);
    connect(mToolBar, &MainToolBar::saveActionTriggered, this, &MainWindow::saveCapture);
    connect(mToolBar, &MainToolBar::copyActionTriggered, this, &MainWindow::copyCaptureToClipboard);
    connect(mToolBar, &MainToolBar::captureDelayChanged, this, &MainWindow::captureDelayChanged);
    connect(mToolBar, &MainToolBar::cropActionTriggered, mKImageAnnotator, &KImageAnnotator::showCropper);

    mUploadToImgurAction->setText(tr("Upload"));
    mUploadToImgurAction->setToolTip(tr("Upload capture image to imgur.com"));
    mUploadToImgurAction->setShortcut(Qt::SHIFT + Qt::Key_I);
    connect(mUploadToImgurAction, &QAction::triggered, this, &MainWindow::upload);

    mPrintAction->setText(tr("Print"));
    mPrintAction->setToolTip(tr("Opens printer dialog and provide option to print image"));
    mPrintAction->setShortcut(QKeySequence::Print);
    mPrintAction->setIcon(QIcon::fromTheme(QStringLiteral("document-print")));
    connect(mPrintAction, &QAction::triggered, this, &MainWindow::printClicked);

    mPrintPreviewAction->setText(tr("Print Preview"));
    mPrintPreviewAction->setToolTip(tr("Opens Print Preview dialog where the image "
                                       "orientation can be changed"));
    mPrintPreviewAction->setIcon(QIcon::fromTheme(QStringLiteral("document-print-preview")));
    connect(mPrintPreviewAction, &QAction::triggered, this, &MainWindow::printPreviewClicked);

    mScaleAction->setText(tr("Scale"));
    mScaleAction->setToolTip(tr("Scale Screen Capture"));
    mScaleAction->setShortcut(Qt::SHIFT + Qt::Key_S);
	connect(mScaleAction, &QAction::triggered, this, &MainWindow::showScaleDialog);

	mAddWatermarkAction->setText(tr("Add Watermark"));
	mAddWatermarkAction->setToolTip(tr("Add Watermark to captured image. Multiple watermarks can be added."));
	mAddWatermarkAction->setShortcut(Qt::SHIFT + Qt::Key_W);
	connect(mAddWatermarkAction, &QAction::triggered, this, &MainWindow::addWatermark);

    mQuitAction->setText(tr("Quit"));
    mQuitAction->setShortcut(QKeySequence::Quit);
    mQuitAction->setIcon(QIcon::fromTheme(QStringLiteral("application-exit")));
    connect(mQuitAction, &QAction::triggered, this, &MainWindow::quit);

    mSettingsDialogAction->setText(tr("Settings"));
    mSettingsDialogAction->setIcon(QIcon::fromTheme(QStringLiteral("emblem-system")));
	connect(mSettingsDialogAction, &QAction::triggered, this, &MainWindow::showSettingsDialog);

    mAboutAction->setText(tr("&About"));
	mAboutAction->setIcon(QIcon(QStringLiteral(":/ksnip")));
	connect(mAboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);

    mOpenImageAction->setText(tr("Open"));
    mOpenImageAction->setIcon(QIcon::fromTheme(QStringLiteral("document-open")));
    mOpenImageAction->setShortcut(Qt::CTRL + Qt::Key_O);
    connect(mOpenImageAction, &QAction::triggered, this, &MainWindow::loadImageFromFile);

	auto menu = menuBar()->addMenu(tr("&File"));
    menu->addAction(mToolBar->newCaptureAction());
    menu->addAction(mOpenImageAction);
    menu->addAction(mToolBar->saveAction());
    menu->addAction(mUploadToImgurAction);
    menu->addSeparator();
    menu->addAction(mPrintAction);
    menu->addAction(mPrintPreviewAction);
    menu->addSeparator();
    menu->addAction(mQuitAction);
    menu = menuBar()->addMenu(tr("&Edit"));
    menu->addAction(mToolBar->undoAction());
    menu->addAction(mToolBar->redoAction());
    menu->addSeparator();
    menu->addAction(mToolBar->copyToClipboardAction());
    menu->addAction(mToolBar->cropAction());
    menu->addAction(mScaleAction);
    menu->addAction(mAddWatermarkAction);
    menu = menuBar()->addMenu(tr("&Options"));
    menu->addAction(mSettingsDialogAction);
    menu = menuBar()->addMenu(tr("&Help"));
    menu->addAction(mAboutAction);

    addToolBar(mToolBar);

    if(mConfig->useTrayIcon()) {
	    connect(mTrayIcon, &TrayIcon::showEditorTriggered, this, &MainWindow::show);
	    mTrayIcon->setNewCaptureAction(mToolBar->newCaptureAction());
	    mTrayIcon->setOpenAction(mOpenImageAction);
	    mTrayIcon->setSaveAction(mToolBar->saveAction());
	    mTrayIcon->setCopyAction(mToolBar->copyToClipboardAction());
	    mTrayIcon->setUploadAction(mUploadToImgurAction);
	    mTrayIcon->setQuitAction(mQuitAction);
	    mTrayIcon->setEnabled(true);
    }

	setCentralWidget(mKImageAnnotator);
}

void MainWindow::saveCapture()
{
	auto image = mKImageAnnotator->image();
	SaveOperation operation(this, image, mConfig->useInstantSave(), mTrayIcon);
	bool successful = operation.execute();

    setSaveable(!successful);
}

void MainWindow::copyCaptureToClipboard()
{
    auto image = mKImageAnnotator->image();
    if (image.isNull()) {
        return;
    }
    mClipboard->setImage(image);
}

void MainWindow::upload()
{
	auto image = mKImageAnnotator->image();
	UploadOperation operation(image, mCaptureUploader);
	operation.execute();
}

void MainWindow::uploadFinished(const QString &response)
{
	HandleUploadResponseOperation handleUploadResponseOperation(response, mTrayIcon);
	handleUploadResponseOperation.execute();
}

void MainWindow::printClicked()
{
	auto savePath = mSavePathProvider.savePathWithFormat(QStringLiteral("pdf"));
	auto image = mKImageAnnotator->image();
	mCapturePrinter->print(image, savePath);
}

void MainWindow::printPreviewClicked()
{
	auto savePath = mSavePathProvider.savePathWithFormat(QStringLiteral("pdf"));
	auto image = mKImageAnnotator->image();
	mCapturePrinter->printPreview(image, savePath);
}

void MainWindow::instantSave()
{
	auto screenshot = mKImageAnnotator->image();
    SaveOperation operation(this, screenshot, true, mTrayIcon);
    operation.execute();
}

void MainWindow::loadImageFromFile()
{
	if (!discardChanges()) {
		return;
	}

    auto pixmapFilename = QFileDialog::getOpenFileName(this, tr("Open Image"), mSavePathProvider.saveDirectory(), tr("Image Files (*.png *.jpg *.bmp)"));
	auto pixmap = QPixmap(pixmapFilename);

	if(!pixmap.isNull()) {
		setHidden(true);
		CaptureDto captureDto(pixmap);
		showCapture(captureDto);
	}
}

bool MainWindow::discardChanges()
{
	auto image = mKImageAnnotator->image();
	CanDiscardOperation operation(this, image, mIsUnsaved, mTrayIcon);
	return operation.execute();
}

void MainWindow::setupImageAnnotator()
{
	mKImageAnnotator->setSaveToolSelection(mConfig->saveToolSelection());
	mKImageAnnotator->setSmoothFactor(mConfig->smoothFactor());
	mKImageAnnotator->setSmoothPathEnabled(mConfig->smoothPathEnabled());
	mKImageAnnotator->setTextFont(mConfig->textFont());
	mKImageAnnotator->setNumberFont(mConfig->numberFont());
	mKImageAnnotator->setItemShadowEnabled(mConfig->itemShadowEnabled());
}

void MainWindow::captureDelayChanged(int delay)
{
    mConfig->setCaptureDelay(delay * 1000);
}

void MainWindow::addWatermark()
{
	AddWatermarkOperation operation(mKImageAnnotator);
	operation.execute();
}

void MainWindow::showDialog(const std::function<void ()>& showDialogMethod)
{
	mGlobalHotKeyHandler->setEnabled(false);
	showDialogMethod();
	mGlobalHotKeyHandler->setEnabled(true);
}

void MainWindow::showSettingsDialog()
{
	showDialog([&](){
		SettingsDialog settingsDialog(this);
		settingsDialog.exec();
	});
}

void MainWindow::showAboutDialog()
{
	showDialog([&](){
		AboutDialog aboutDialog(this);
		aboutDialog.exec();
	});
}

void MainWindow::showScaleDialog()
{
	showDialog([&](){
		mKImageAnnotator->showScaler();
	});
}
