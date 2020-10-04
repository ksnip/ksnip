/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
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
	mSaveAsAction(new QAction(this)),
	mUploadAction(new QAction(this)),
	mPrintAction(new QAction(this)),
	mPrintPreviewAction(new QAction(this)),
	mQuitAction(new QAction(this)),
	mSettingsDialogAction(new QAction(this)),
	mAboutAction(new QAction(this)),
	mOpenImageAction(new QAction(this)),
	mScaleAction(new QAction(this)),
	mAddWatermarkAction(new QAction(this)),
	mPasteAction(new QAction(this)),
	mPasteEmbeddedAction(new QAction(this)),
	mPinAction(new QAction(this)),
	mMainLayout(layout()),
	mClipboard(new ClipboardWrapper(QApplication::clipboard())),
	mConfig(KsnipConfigProvider::instance()),
	mCapturePrinter(new CapturePrinter(this)),
	mGlobalHotKeyHandler(new GlobalHotKeyHandler(mImageGrabber->supportedCaptureModes())),
	mTrayIcon(new TrayIcon(this)),
	mSelectedWindowState(Qt::WindowActive),
	mWindowStateChangeLock(false),
	mDragAndDropHandler(new DragAndDropHandler),
	mUploaderProvider(new UploaderProvider),
	mSessionManagerRequestedQuit(false),
	mCaptureHandler(CaptureHandlerFactory::create(mKImageAnnotator, mTrayIcon, this)),
	mPinWindowHandler(new PinWindowHandler(this)),
	mWidgetHider(WidgetHiderFactory::create(this))
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

	connect(qApp, &QGuiApplication::commitDataRequest, this, &MainWindow::sessionFinished);

	setWindowIcon(QIcon(QLatin1Literal(":/icons/ksnip.svg")));
	setPosition();

	setAcceptDrops(true);
	qApp->installEventFilter(mDragAndDropHandler);
	connect(mDragAndDropHandler, &DragAndDropHandler::imageDropped, this, &MainWindow::loadImageFromFile);

	connect(mConfig, &KsnipConfig::annotatorConfigChanged, this, &MainWindow::setupImageAnnotator);

	connect(mImageGrabber, &AbstractImageGrabber::finished, this, &MainWindow::processCapture);
	connect(mImageGrabber, &AbstractImageGrabber::canceled, this, &MainWindow::captureCanceled);

	connect(mGlobalHotKeyHandler, &GlobalHotKeyHandler::newCaptureTriggered, this, &MainWindow::capture);

	connect(mUploaderProvider, &UploaderProvider::finished, this, &MainWindow::uploadFinished);

	mCaptureHandler->addListener(this);

	loadSettings();
	handleGuiStartup();
	setupImageAnnotator();
	resize(minimumSize());
}

void MainWindow::handleGuiStartup()
{
	if (mMode == RunMode::GUI) {
		if (mConfig->captureOnStartup()) {
			capture(mConfig->captureMode());
		} else if (mConfig->startMinimizedToTray() && mConfig->useTrayIcon()) {
			showHidden();
		} else {
			showEmpty();
		}
	}
}

void MainWindow::setPosition()
{
	auto position = mConfig->windowPosition();
	auto screenGeometry = QApplication::desktop()->screenGeometry();
	if(!screenGeometry.contains(position)) {
		auto screenCenter = screenGeometry.center();
		auto ksnipSize = size();
		position = QPoint(screenCenter.x() - ksnipSize.width() / 2, screenCenter.y() - ksnipSize.height() / 2);
	}
	move(position);
}

MainWindow::~MainWindow()
{
    delete mKImageAnnotator;
    delete mUploadAction;
    delete mPrintAction;
    delete mPrintPreviewAction;
    delete mQuitAction;
    delete mSettingsDialogAction;
    delete mAboutAction;
    delete mOpenImageAction;
    delete mScaleAction;
    delete mAddWatermarkAction;
    delete mSaveAsAction;
    delete mCapturePrinter;
    delete mTrayIcon;
    delete mClipboard;
    delete mDragAndDropHandler;
    delete mUploaderProvider;
    delete mCaptureHandler;
    delete mWidgetHider;
}

void MainWindow::processInstantCapture(const CaptureDto &capture)
{
	mCaptureHandler->load(capture);
	mCaptureHandler->save();
	mKImageAnnotator->close();
	close();
}

void MainWindow::captureScreenshot(CaptureModes captureMode, bool captureCursor, int delay)
{
    mImageGrabber->grabImage(captureMode, captureCursor, delay);
}

void MainWindow::quit()
{
	if(!mCaptureHandler->canClose()){
		return;
	}

	mTrayIcon->hide();
	QCoreApplication::exit(0);
}

void MainWindow::processCapture(const CaptureDto &capture)
{
	if (!capture.isValid()) {
		NotifyOperation operation(mTrayIcon, tr("Unable to show image"), tr("No image provided but one was expected."), NotificationTypes::Critical);
		operation.execute();
		showEmpty();
		return;
	}

	showImage(capture);
	captureChanged();
	capturePostProcessing();
}

void MainWindow::processImage(const CaptureDto &capture)
{
	showImage(capture);
	captureChanged();
}

void MainWindow::showImage(const CaptureDto &capture)
{
	mCaptureHandler->load(capture);

	setInvisible(false);
	setEnablements(true);

	if(mSelectedWindowState != Qt::WindowMaximized) {
		adjustSize();
	}

	show();
}

void MainWindow::capturePostProcessing()
{
	if (mConfig->autoCopyToClipboardNewCaptures()) {
		copyCaptureToClipboard();
	}

	if (mConfig->autoSaveNewCaptures()) {
		mCaptureHandler->save();
	}
}

void MainWindow::showEmpty()
{
	setInvisible(false);
	captureChanged();
    setEnablements(false);
    QMainWindow::show();
}

void MainWindow::showHidden()
{
	captureChanged();
	setEnablements(false);
	hide();
}

void MainWindow::show()
{
	setWindowState(mSelectedWindowState);
	activateWindow();
	raise();
	QMainWindow::show();
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

void MainWindow::moveEvent(QMoveEvent* event)
{
    mConfig->setWindowPosition(pos());
    QWidget::moveEvent(event);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	if(!mSessionManagerRequestedQuit) {
		event->ignore();
	}
	mTrayIcon->isVisible() && mConfig->closeToTray() ? hide() : quit();
}

void MainWindow::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::WindowStateChange) {
		if(isMinimized() && mTrayIcon->isVisible() && mConfig->minimizeToTray()) {
			event->ignore();
			hide();
		} else if (!mWindowStateChangeLock)  {
			mSelectedWindowState = isMaximized() ? Qt::WindowMaximized : Qt::WindowActive;
		}
	}
	QWidget::changeEvent(event);
}

void MainWindow::captureChanged()
{
    mToolBar->setSaveActionEnabled(!mCaptureHandler->isSaved());
	updateApplicationTitle();
}

void MainWindow::updateApplicationTitle()
{
	auto path = mCaptureHandler->path();
	auto isUnsaved = !mCaptureHandler->isSaved();
	auto applicationTitle = ApplicationTitleProvider::getApplicationTitle(QApplication::applicationName(), path, tr("Unsaved"), isUnsaved);
	setWindowTitle(applicationTitle);
}

void MainWindow::setEnablements(bool enabled)
{
    mPrintAction->setEnabled(enabled);
    mPrintPreviewAction->setEnabled(enabled);
    mUploadAction->setEnabled(enabled);
	mScaleAction->setEnabled(enabled);
	mAddWatermarkAction->setEnabled(enabled);
    mToolBar->setCopyActionEnabled(enabled);
    mToolBar->setCropEnabled(enabled);
	mSaveAsAction->setEnabled(enabled);
	mPinAction->setEnabled(enabled);
	mPasteEmbeddedAction->setEnabled(mClipboard->isPixmap() && mKImageAnnotator->isVisible());
}

void MainWindow::loadSettings()
{
    mToolBar->selectCaptureMode(mConfig->captureMode());
    mToolBar->setCaptureDelay(mConfig->captureDelay() / 1000);
}

void MainWindow::setInvisible(bool isInvisible)
{
    if (isInvisible == mIsInvisible) {
        return;
    }

	mIsInvisible = isInvisible;
	mWidgetHider->setHidden(isInvisible);
	mWindowStateChangeLock = isInvisible;
}

void MainWindow::capture(CaptureModes captureMode)
{
	if(!mCaptureHandler->canTakeNew()){
		return;
	}

	setInvisible(true);
    mConfig->setCaptureMode(captureMode);

	captureScreenshot(captureMode, mConfig->captureCursor(), mConfig->captureDelay());
}

void MainWindow::initGui()
{
    mToolBar = new MainToolBar(mImageGrabber->supportedCaptureModes(), mKImageAnnotator->undoAction(), mKImageAnnotator->redoAction());

    connect(mToolBar, &MainToolBar::captureModeSelected, this, &MainWindow::capture);
    connect(mToolBar, &MainToolBar::saveActionTriggered, this, &MainWindow::saveClicked);
    connect(mToolBar, &MainToolBar::copyActionTriggered, this, &MainWindow::copyCaptureToClipboard);
    connect(mToolBar, &MainToolBar::captureDelayChanged, this, &MainWindow::captureDelayChanged);
    connect(mToolBar, &MainToolBar::cropActionTriggered, mKImageAnnotator, &KImageAnnotator::showCropper);

	mSaveAsAction->setText(tr("Save As..."));
	mSaveAsAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_S);
	mSaveAsAction->setIcon(IconLoader::load(QStringLiteral("saveAs")));
	connect(mSaveAsAction, &QAction::triggered, this, &MainWindow::saveAsClicked);

    mUploadAction->setText(tr("Upload"));
    mUploadAction->setToolTip(tr("Upload capture to external source"));
    mUploadAction->setShortcut(Qt::SHIFT + Qt::Key_U);
    connect(mUploadAction, &QAction::triggered, this, &MainWindow::upload);

    mPrintAction->setText(tr("Print"));
    mPrintAction->setToolTip(tr("Opens printer dialog and provide option to print image"));
    mPrintAction->setShortcut(Qt::CTRL + Qt::Key_P);
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
    mQuitAction->setShortcut(Qt::CTRL + Qt::Key_Q);
    mQuitAction->setIcon(QIcon::fromTheme(QStringLiteral("application-exit")));
    connect(mQuitAction, &QAction::triggered, this, &MainWindow::quit);

    mSettingsDialogAction->setText(tr("Settings"));
    mSettingsDialogAction->setIcon(QIcon::fromTheme(QStringLiteral("emblem-system")));
	mSettingsDialogAction->setShortcut(Qt::ALT + Qt::Key_F7);
	connect(mSettingsDialogAction, &QAction::triggered, this, &MainWindow::showSettingsDialog);

    mAboutAction->setText(tr("&About"));
	mAboutAction->setIcon(QIcon(QStringLiteral(":/icons//ksnip")));
	connect(mAboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);

    mOpenImageAction->setText(tr("Open"));
    mOpenImageAction->setIcon(QIcon::fromTheme(QStringLiteral("document-open")));
    mOpenImageAction->setShortcut(Qt::CTRL + Qt::Key_O);
    connect(mOpenImageAction, &QAction::triggered, this, &MainWindow::showOpenImageDialog);

	mPasteAction->setText(tr("Paste"));
	mPasteAction->setIcon(IconLoader::load(QStringLiteral("paste")));
	mPasteAction->setShortcut(Qt::CTRL + Qt::Key_V);
	mPasteAction->setEnabled(mClipboard->isPixmap());
	connect(mPasteAction, &QAction::triggered, this, &MainWindow::pasteFromClipboard);
	connect(mClipboard, &ClipboardWrapper::changed, mPasteAction, &QAction::setEnabled);

	mPasteEmbeddedAction->setText(tr("Paste Embedded"));
	mPasteEmbeddedAction->setIcon(IconLoader::load(QStringLiteral("pasteEmbedded")));
	mPasteEmbeddedAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_V);
	mPasteEmbeddedAction->setEnabled(mClipboard->isPixmap() && mKImageAnnotator->isVisible());
	connect(mPasteEmbeddedAction, &QAction::triggered, this, &MainWindow::pasteEmbeddedFromClipboard);
	connect(mClipboard, &ClipboardWrapper::changed, [this] (bool isPixmap){ mPasteEmbeddedAction->setEnabled(isPixmap && mKImageAnnotator->isVisible()); });

	mPinAction->setText(tr("Pin"));
	mPinAction->setToolTip(tr("Pin screenshot to foreground in frameless window"));
	mPinAction->setShortcut(Qt::SHIFT + Qt::Key_P);
	mPinAction->setIcon(IconLoader::load(QStringLiteral("pin")));
	connect(mPinAction, &QAction::triggered, this, &MainWindow::showPinWindow);

	auto menu = menuBar()->addMenu(tr("&File"));
    menu->addAction(mToolBar->newCaptureAction());
    menu->addAction(mOpenImageAction);
    menu->addAction(mToolBar->saveAction());
    menu->addAction(mSaveAsAction);
    menu->addAction(mUploadAction);
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
    menu->addAction(mPasteAction);
    menu->addAction(mPasteEmbeddedAction);
	menu->addSeparator();
    menu->addAction(mToolBar->cropAction());
    menu->addAction(mScaleAction);
    menu->addAction(mAddWatermarkAction);
    menu = menuBar()->addMenu(tr("&Options"));
    menu->addAction(mPinAction);
    menu->addAction(mSettingsDialogAction);
    menu = menuBar()->addMenu(tr("&Help"));
    menu->addAction(mAboutAction);

    addToolBar(mToolBar);

    if(mConfig->useTrayIcon()) {
	    connect(mTrayIcon, &TrayIcon::showEditorTriggered, this, &MainWindow::show);
	    mTrayIcon->setCaptureActions(mToolBar->captureActions());
	    mTrayIcon->setOpenAction(mOpenImageAction);
	    mTrayIcon->setSaveAction(mToolBar->saveAction());
	    mTrayIcon->setCopyAction(mToolBar->copyToClipboardAction());
	    mTrayIcon->setUploadAction(mUploadAction);
	    mTrayIcon->setQuitAction(mQuitAction);
	    mTrayIcon->setEnabled(true);
    }

	setCentralWidget(mKImageAnnotator);
}

void MainWindow::copyCaptureToClipboard()
{
    auto image = mCaptureHandler->image();
    if (!image.isNull()) {
	    mClipboard->setImage(image);
    }
}

void MainWindow::upload()
{
	auto image = mCaptureHandler->image();
	UploadOperation operation(image, mUploaderProvider->get());
	operation.execute();
}

void MainWindow::printClicked()
{
	auto savePath = mSavePathProvider.savePathWithFormat(QStringLiteral("pdf"));
	auto image = mCaptureHandler->image();
	mCapturePrinter->print(image, savePath);
}

void MainWindow::printPreviewClicked()
{
	auto savePath = mSavePathProvider.savePathWithFormat(QStringLiteral("pdf"));
	auto image = mCaptureHandler->image();
	mCapturePrinter->printPreview(image, savePath);
}

void MainWindow::showOpenImageDialog()
{
    auto path = QFileDialog::getOpenFileName(this, tr("Open Image"), mSavePathProvider.saveDirectory(), tr("Image Files (*.png *.jpg *.bmp)"));
	loadImageFromFile(path);
}

void MainWindow::setupImageAnnotator()
{
	mKImageAnnotator->setSaveToolSelection(mConfig->rememberToolSelection());
	mKImageAnnotator->setSmoothFactor(mConfig->smoothFactor());
	mKImageAnnotator->setSmoothPathEnabled(mConfig->smoothPathEnabled());
	mKImageAnnotator->setTextFont(mConfig->textFont());
	mKImageAnnotator->setNumberFont(mConfig->numberFont());
	mKImageAnnotator->setItemShadowEnabled(mConfig->itemShadowEnabled());
	mKImageAnnotator->setStickers(mConfig->stickerPaths(), mConfig->useDefaultSticker());
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
		SettingsDialog settingsDialog(this, mImageGrabber->supportedCaptureModes());
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

void MainWindow::pasteFromClipboard()
{
	auto pixmap = mClipboard->pixmap();

	if(!pixmap.isNull()) {
		setInvisible(false);
		if(mClipboard->url().isNull()) {
			CaptureDto captureDto(pixmap);
			processImage(captureDto);
		} else {
			CaptureFromFileDto captureDto(pixmap, mClipboard->url());
			processImage(captureDto);
		}
	}
}

void MainWindow::pasteEmbeddedFromClipboard()
{
	auto pixmap = mClipboard->pixmap();
	mCaptureHandler->insertImageItem({}, pixmap);
}

void MainWindow::saveClicked()
{
	mCaptureHandler->save();
}

void MainWindow::saveAsClicked()
{
	mCaptureHandler->saveAs();
}

void MainWindow::loadImageFromFile(const QString &path)
{
	auto pixmap = QPixmap(path);
	if(!pixmap.isNull()) {
		setInvisible(false);
		CaptureFromFileDto captureDto(pixmap, path);
		processImage(captureDto);
	}
}

void MainWindow::sessionFinished()
{
	mSessionManagerRequestedQuit = true;
}

void MainWindow::captureCanceled()
{
	setInvisible(false);
	show();
}

void MainWindow::uploadFinished(const UploadResult &result)
{
	HandleUploadResultOperation handleUploadResponseOperation(result, mTrayIcon);
	handleUploadResponseOperation.execute();
}

void MainWindow::captureEmpty()
{
	setEnablements(false);
	mMainLayout->setSizeConstraint(QLayout::SetFixedSize); // Workaround that allows us to return to toolbar only size
	resize(minimumSize());
	mMainLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
}

void MainWindow::showPinWindow()
{
	mPinWindowHandler->add(QPixmap::fromImage(mCaptureHandler->image()));
}
