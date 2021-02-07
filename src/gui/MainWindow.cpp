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
	mToolBar(nullptr),
	mImageGrabber(imageGrabber),
	mServiceLocator(new ServiceLocator),
	mMode(mode),
	mImageAnnotator(new KImageAnnotatorAdapter),
	mSaveAsAction(new QAction(this)),
	mUploadAction(new QAction(this)),
	mCopyAsDataUriAction(new QAction(this)),
	mPrintAction(new QAction(this)),
	mPrintPreviewAction(new QAction(this)),
	mQuitAction(new QAction(this)),
	mCopyPathAction(new QAction(this)),
	mRenameAction(new QAction(this)),
	mOpenDirectoryAction(new QAction(this)),
	mToggleDocksAction(new QAction(this)),
	mSettingsAction(new QAction(this)),
	mAboutAction(new QAction(this)),
	mOpenImageAction(new QAction(this)),
	mRecentImagesMenu(new RecentImagesMenu(mServiceLocator->recentImageService(), this)),
	mScaleAction(new QAction(this)),
	mAddWatermarkAction(new QAction(this)),
	mPasteAction(new QAction(this)),
	mPasteEmbeddedAction(new QAction(this)),
	mPinAction(new QAction(this)),
	mRemoveImageAction(new QAction(this)),
	mModifyCanvasAction(new QAction(this)),
	mMainLayout(layout()),
	mConfig(KsnipConfigProvider::instance()),
	mClipboard(mServiceLocator->clipboard()),
	mCapturePrinter(new CapturePrinter(this)),
	mGlobalHotKeyHandler(new GlobalHotKeyHandler(mImageGrabber->supportedCaptureModes())),
	mTrayIcon(new TrayIcon(this)),
	mDragAndDropHandler(new DragAndDropHandler),
	mUploaderProvider(new UploaderProvider),
	mSessionManagerRequestedQuit(false),
	mCaptureHandler(CaptureHandlerFactory::create(mImageAnnotator, mTrayIcon, mServiceLocator, this)),
	mPinWindowHandler(new PinWindowHandler(this)),
	mVisibilityHandler(WidgetVisibilityHandlerFactory::create(this)),
	mFileDialog(FileDialogAdapterFactory::create())
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

	setWindowIcon(IconLoader::load(QLatin1String("ksnip")));
	setPosition();

	setAcceptDrops(true);
	qApp->installEventFilter(mDragAndDropHandler);
	connect(mDragAndDropHandler, &DragAndDropHandler::imageDropped, this, &MainWindow::loadImageFromFile);

	connect(mConfig, &KsnipConfig::annotatorConfigChanged, this, &MainWindow::setupImageAnnotator);

	connect(mImageGrabber, &AbstractImageGrabber::finished, this, &MainWindow::processCapture);
	connect(mImageGrabber, &AbstractImageGrabber::canceled, this, &MainWindow::captureCanceled);

	connect(mGlobalHotKeyHandler, &GlobalHotKeyHandler::newCaptureTriggered, this, &MainWindow::capture);

	connect(mUploaderProvider, &UploaderProvider::finished, this, &MainWindow::uploadFinished);

	connect(mRecentImagesMenu, &RecentImagesMenu::openRecentSelected, this, &MainWindow::loadImageFromFile);

	mCaptureHandler->addListener(this);

	handleGuiStartup();
	setupImageAnnotator();
	resize(minimumSize());
	loadSettings();
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
		auto mainWindowSize = size();
		position = QPoint(screenCenter.x() - mainWindowSize.width() / 2, screenCenter.y() - mainWindowSize.height() / 2);
	}
	move(position);
}

MainWindow::~MainWindow()
{
    delete mImageAnnotator;
    delete mUploadAction;
    delete mCopyAsDataUriAction;
    delete mPrintAction;
    delete mPrintPreviewAction;
    delete mQuitAction;
    delete mCopyPathAction;
    delete mRenameAction;
    delete mOpenDirectoryAction;
    delete mToggleDocksAction;
    delete mSettingsAction;
    delete mAboutAction;
    delete mOpenImageAction;
    delete mScaleAction;
    delete mAddWatermarkAction;
    delete mSaveAsAction;
    delete mModifyCanvasAction;
    delete mCapturePrinter;
    delete mTrayIcon;
    delete mDragAndDropHandler;
    delete mUploaderProvider;
    delete mCaptureHandler;
    delete mVisibilityHandler;
    delete mFileDialog;
}

void MainWindow::processInstantCapture(const CaptureDto &capture)
{
	mCaptureHandler->load(capture);
	mCaptureHandler->save();
	mImageAnnotator->close();
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
		auto title = tr("Unable to show image");
		auto message = tr("No image provided but one was expected.");
		NotifyOperation operation(mTrayIcon, title, message, NotificationTypes::Critical);
		operation.execute();
		showEmpty();
		return;
	}

	processImage(capture);
	capturePostProcessing();
}

void MainWindow::processImage(const CaptureDto &capture)
{
	loadImage(capture);
	showDefault();
	captureChanged();
}

void MainWindow::loadImage(const CaptureDto &capture)
{
	mCaptureHandler->load(capture);
}

void MainWindow::resizeToContent()
{
	if(!mToolBar->isCollapsed() || mImageAnnotator->isVisible()) {
		mMainLayout->setSizeConstraint(QLayout::SetFixedSize); // Workaround that allows us to return to toolbar only size
		QMainWindow::adjustSize();
	} else {
		setFixedSize(menuBar()->sizeHint());
	}
	mMainLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

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
	mVisibilityHandler->minimize();
	captureChanged();
    setEnablements(false);
}

void MainWindow::showHidden()
{
	captureChanged();
	setEnablements(false);
	mVisibilityHandler->hide();
}

void MainWindow::showDefault()
{
	auto enforceShow = mConfig->showMainWindowAfterTakingScreenshotEnabled();
	enforceShow ? mVisibilityHandler->enforceVisible() : mVisibilityHandler->restoreVisibility();

	if(!mVisibilityHandler->isMaximized()) {
		resizeToContent();
	}

	setEnablements(true);
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
	auto annotatorSize = mImageAnnotator->sizeHint();
	auto height = minHeight + annotatorSize.height();
	auto width = minWidth > annotatorSize.width() ? minWidth : annotatorSize.width();
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

	if(mTrayIcon->isVisible() && mConfig->closeToTray()) {
		mVisibilityHandler->hide();
	} else {
		quit();
	}
}

void MainWindow::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::WindowStateChange) {
		if(isMinimized() && mTrayIcon->isVisible() && mConfig->minimizeToTray()) {
			event->ignore();
			mVisibilityHandler->hide();
		}
		mVisibilityHandler->updateState();
	}
	QWidget::changeEvent(event);
}

void MainWindow::captureChanged()
{
	mToolBar->setSaveActionEnabled(!mCaptureHandler->isSaved());
	mCopyPathAction->setEnabled(mCaptureHandler->isPathValid());
	mRenameAction->setEnabled(mCaptureHandler->isPathValid());
	mOpenDirectoryAction->setEnabled(mCaptureHandler->isPathValid());
	mRemoveImageAction->setEnabled(mCaptureHandler->isPathValid());
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
    mCopyAsDataUriAction->setEnabled(enabled);
    mScaleAction->setEnabled(enabled);
    mAddWatermarkAction->setEnabled(enabled);
    mToolBar->setCopyActionEnabled(enabled);
    mToolBar->setCropEnabled(enabled);
    mSaveAsAction->setEnabled(enabled);
    mPinAction->setEnabled(enabled);
    mPasteEmbeddedAction->setEnabled(mClipboard->isPixmap() && mImageAnnotator->isVisible());
    mRenameAction->setEnabled(enabled);
    mModifyCanvasAction->setEnabled(enabled);
}

void MainWindow::loadSettings()
{
    mToolBar->selectCaptureMode(mConfig->captureMode());
    mToolBar->setCaptureDelay(mConfig->captureDelay() / 1000);

	if(mConfig->autoHideDocks()) {
		toggleDocks();
	}
}

void MainWindow::capture(CaptureModes captureMode)
{
	if(!mCaptureHandler->canTakeNew()){
		return;
	}

	hideMainWindowIfRequired();

	mConfig->setCaptureMode(captureMode);

	captureScreenshot(captureMode, mConfig->captureCursor(), mConfig->captureDelay());
}

void MainWindow::hideMainWindowIfRequired()
{
	if (mConfig->hideMainWindowDuringScreenshot()) {
		mVisibilityHandler->makeInvisible();
	}
}

void MainWindow::toggleDocks()
{
	auto newIsCollapsedState = !mToolBar->isCollapsed();

	mToolBar->setCollapsed(newIsCollapsedState);
	mImageAnnotator->setSettingsCollapsed(newIsCollapsedState);

	auto collapsedToggleText = newIsCollapsedState ? tr("Show Docks") : tr("Hide Docks");
	mToggleDocksAction->setText(collapsedToggleText);

	resizeToContent();
}

void MainWindow::initGui()
{
    mToolBar = new MainToolBar(mImageGrabber->supportedCaptureModes(), mImageAnnotator->undoAction(), mImageAnnotator->redoAction());

    connect(mToolBar, &MainToolBar::captureModeSelected, this, &MainWindow::capture);
    connect(mToolBar, &MainToolBar::saveActionTriggered, this, &MainWindow::saveClicked);
    connect(mToolBar, &MainToolBar::copyActionTriggered, this, &MainWindow::copyCaptureToClipboard);
    connect(mToolBar, &MainToolBar::captureDelayChanged, this, &MainWindow::captureDelayChanged);
    connect(mToolBar, &MainToolBar::cropActionTriggered, mImageAnnotator, &IImageAnnotator::showCropper);

	mSaveAsAction->setText(tr("Save As..."));
	mSaveAsAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_S);
	mSaveAsAction->setIcon(IconLoader::loadForTheme(QLatin1String("saveAs")));
	connect(mSaveAsAction, &QAction::triggered, this, &MainWindow::saveAsClicked);

    mUploadAction->setText(tr("Upload"));
    mUploadAction->setToolTip(tr("Upload capture to external source"));
    mUploadAction->setShortcut(Qt::SHIFT + Qt::Key_U);
    connect(mUploadAction, &QAction::triggered, this, &MainWindow::upload);

    mCopyAsDataUriAction->setText(tr("Copy as data URI"));
    mCopyAsDataUriAction->setToolTip(tr("Copy capture to system clipboard"));
    connect(mCopyAsDataUriAction, &QAction::triggered, this, &MainWindow::copyAsDataUri);

    mPrintAction->setText(tr("Print"));
    mPrintAction->setToolTip(tr("Opens printer dialog and provide option to print image"));
    mPrintAction->setShortcut(Qt::CTRL + Qt::Key_P);
    mPrintAction->setIcon(QIcon::fromTheme(QLatin1String("document-print")));
    connect(mPrintAction, &QAction::triggered, this, &MainWindow::printClicked);

    mPrintPreviewAction->setText(tr("Print Preview"));
    mPrintPreviewAction->setToolTip(tr("Opens Print Preview dialog where the image "
                                       "orientation can be changed"));
    mPrintPreviewAction->setIcon(QIcon::fromTheme(QLatin1String("document-print-preview")));
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
    mQuitAction->setIcon(QIcon::fromTheme(QLatin1String("application-exit")));
    connect(mQuitAction, &QAction::triggered, this, &MainWindow::quit);

	mCopyPathAction->setText(tr("Copy Path"));
	connect(mCopyPathAction, &QAction::triggered, mCaptureHandler, &ICaptureHandler::copyPath);

	mRenameAction->setText(tr("Rename"));
	mRenameAction->setShortcut(Qt::Key_F2);
	connect(mRenameAction, &QAction::triggered, mCaptureHandler, &ICaptureHandler::rename);

	mOpenDirectoryAction->setText(tr("Open Directory"));
	connect(mOpenDirectoryAction, &QAction::triggered, mCaptureHandler, &ICaptureHandler::openDirectory);

	mToggleDocksAction->setText(tr("Hide Docks"));
	mToggleDocksAction->setShortcut(Qt::Key_Tab);
	connect(mToggleDocksAction, &QAction::triggered, this, &MainWindow::toggleDocks);

    mSettingsAction->setText(tr("Settings"));
    mSettingsAction->setIcon(QIcon::fromTheme(QLatin1String("emblem-system")));
	mSettingsAction->setShortcut(Qt::ALT + Qt::Key_F7);
	connect(mSettingsAction, &QAction::triggered, this, &MainWindow::showSettingsDialog);

    mAboutAction->setText(tr("&About"));
	mAboutAction->setIcon(IconLoader::load(QLatin1String("ksnip")));
	connect(mAboutAction, &QAction::triggered, this, &MainWindow::showAboutDialog);

    mOpenImageAction->setText(tr("Open"));
    mOpenImageAction->setIcon(QIcon::fromTheme(QLatin1String("document-open")));
    mOpenImageAction->setShortcut(Qt::CTRL + Qt::Key_O);
    connect(mOpenImageAction, &QAction::triggered, this, &MainWindow::showOpenImageDialog);

	mRecentImagesMenu->setTitle(tr("Open &Recent"));
	mRecentImagesMenu->setIcon(QIcon::fromTheme(QLatin1String("document-open")));

	mPasteAction->setText(tr("Paste"));
	mPasteAction->setIcon(IconLoader::loadForTheme(QLatin1String("paste")));
	mPasteAction->setShortcut(Qt::CTRL + Qt::Key_V);
	mPasteAction->setEnabled(mClipboard->isPixmap());
	connect(mPasteAction, &QAction::triggered, this, &MainWindow::pasteFromClipboard);
	connect(mClipboard, &ClipboardAdapter::changed, mPasteAction, &QAction::setEnabled);

	mPasteEmbeddedAction->setText(tr("Paste Embedded"));
	mPasteEmbeddedAction->setIcon(IconLoader::loadForTheme(QLatin1String("pasteEmbedded")));
	mPasteEmbeddedAction->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_V);
	mPasteEmbeddedAction->setEnabled(mClipboard->isPixmap() && mImageAnnotator->isVisible());
	connect(mPasteEmbeddedAction, &QAction::triggered, this, &MainWindow::pasteEmbeddedFromClipboard);
	connect(mClipboard, &ClipboardAdapter::changed, [this] (bool isPixmap){ mPasteEmbeddedAction->setEnabled(isPixmap && mImageAnnotator->isVisible()); });

	mPinAction->setText(tr("Pin"));
	mPinAction->setToolTip(tr("Pin screenshot to foreground in frameless window"));
	mPinAction->setShortcut(Qt::SHIFT + Qt::Key_P);
	mPinAction->setIcon(IconLoader::loadForTheme(QLatin1String("pin")));
	connect(mPinAction, &QAction::triggered, this, &MainWindow::showPinWindow);

	mRemoveImageAction->setText(tr("Delete"));
	mRemoveImageAction->setIcon(IconLoader::loadForTheme(QLatin1String("delete")));
	connect(mRemoveImageAction, &QAction::triggered, mCaptureHandler, &ICaptureHandler::removeImage);

	mModifyCanvasAction->setText(tr("Modify Canvas"));
	connect(mModifyCanvasAction, &QAction::triggered, mImageAnnotator, &IImageAnnotator::showCanvasModifier);

	auto menu = menuBar()->addMenu(tr("&File"));
    menu->addAction(mToolBar->newCaptureAction());
    menu->addAction(mOpenImageAction);
    menu->addMenu(mRecentImagesMenu);
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
    menu->addAction(mCopyAsDataUriAction);
    menu->addAction(mCopyPathAction);
    menu->addAction(mRenameAction);
    menu->addAction(mPasteAction);
    menu->addAction(mPasteEmbeddedAction);
	menu->addSeparator();
    menu->addAction(mToolBar->cropAction());
    menu->addAction(mScaleAction);
    menu->addAction(mAddWatermarkAction);
	menu->addSeparator();
	menu->addAction(mRemoveImageAction);
	menu = menuBar()->addMenu(tr("&View"));
	menu->addAction(mOpenDirectoryAction);
	menu->addAction(mToggleDocksAction);
	menu->addAction(mModifyCanvasAction);
    menu = menuBar()->addMenu(tr("&Options"));
    menu->addAction(mPinAction);
    menu->addAction(mSettingsAction);
    menu = menuBar()->addMenu(tr("&Help"));
    menu->addAction(mAboutAction);

    addToolBar(mToolBar);

    if(mConfig->useTrayIcon()) {
	    connect(mTrayIcon, &TrayIcon::showEditorTriggered, [this](){ mVisibilityHandler->enforceVisible(); });
	    mTrayIcon->setCaptureActions(mToolBar->captureActions());
	    mTrayIcon->setOpenAction(mOpenImageAction);
	    mTrayIcon->setSaveAction(mToolBar->saveAction());
	    mTrayIcon->setPasteAction(mPasteAction);
	    mTrayIcon->setCopyAction(mToolBar->copyToClipboardAction());
	    mTrayIcon->setUploadAction(mUploadAction);
	    mTrayIcon->setQuitAction(mQuitAction);
	    mTrayIcon->setEnabled(true);
    }

	setCentralWidget(mImageAnnotator->widget());
}

void MainWindow::copyCaptureToClipboard()
{
    mCaptureHandler->copy();
}

void MainWindow::upload()
{
	auto image = mCaptureHandler->image();
	UploadOperation operation(image, mUploaderProvider->get());
	operation.execute();
}

void MainWindow::copyAsDataUri()
{
	auto image = mCaptureHandler->image();
	CopyAsDataUriOperation operation(image, mClipboard, mTrayIcon);
	operation.execute();
}

void MainWindow::printClicked()
{
	auto savePath = mSavePathProvider.savePathWithFormat(QLatin1String("pdf"));
	auto image = mCaptureHandler->image();
	mCapturePrinter->print(image, savePath);
}

void MainWindow::printPreviewClicked()
{
	auto savePath = mSavePathProvider.savePathWithFormat(QLatin1String("pdf"));
	auto image = mCaptureHandler->image();
	mCapturePrinter->printPreview(image, savePath);
}

void MainWindow::showOpenImageDialog()
{
	auto title = tr("Open Images");
	auto directory = mSavePathProvider.saveDirectory();
	auto filter = tr("Image Files (*.png *.jpg *.bmp)");
	auto pathList = mFileDialog->getOpenFileNames(this, title, directory, filter);

	for (const auto &path : pathList) {
		loadImageFromFile(path);
	}
}

void MainWindow::setupImageAnnotator()
{
	mImageAnnotator->setSaveToolSelection(mConfig->rememberToolSelection());
	mImageAnnotator->setSmoothFactor(mConfig->smoothFactor());
	mImageAnnotator->setSmoothPathEnabled(mConfig->smoothPathEnabled());
	mImageAnnotator->setTextFont(mConfig->textFont());
	mImageAnnotator->setNumberFont(mConfig->numberFont());
	mImageAnnotator->setItemShadowEnabled(mConfig->itemShadowEnabled());
	mImageAnnotator->setSwitchToSelectToolAfterDrawingItem(mConfig->switchToSelectToolAfterDrawingItem());
	mImageAnnotator->setNumberToolSeedChangeUpdatesAllItems(mConfig->numberToolSeedChangeUpdatesAllItems());
	mImageAnnotator->setStickers(mConfig->stickerPaths(), mConfig->useDefaultSticker());
	mImageAnnotator->setCanvasColor(mConfig->canvasColor());
}

void MainWindow::captureDelayChanged(int delay)
{
    mConfig->setCaptureDelay(delay * 1000);
}

void MainWindow::addWatermark()
{
	AddWatermarkOperation operation(mImageAnnotator);
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
		mImageAnnotator->showScaler();
	});
}

void MainWindow::pasteFromClipboard()
{
	auto pixmap = mClipboard->pixmap();

	if(!pixmap.isNull()) {
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
	LoadImageFromFileOperation operation(this, path, mTrayIcon, mServiceLocator);
	operation.execute();
}

void MainWindow::sessionFinished()
{
	mSessionManagerRequestedQuit = true;
}

void MainWindow::captureCanceled()
{
	mVisibilityHandler->restoreVisibility();
}

void MainWindow::uploadFinished(const UploadResult &result)
{
	HandleUploadResultOperation handleUploadResponseOperation(result, mTrayIcon);
	handleUploadResponseOperation.execute();
}

void MainWindow::captureEmpty()
{
	setEnablements(false);
	resizeToContent();
}

void MainWindow::showPinWindow()
{
	mPinWindowHandler->add(QPixmap::fromImage(mCaptureHandler->image()));
}
