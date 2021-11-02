/*
 *  Copyright (C) 2016 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_MAINWINDOW_H
#define KSNIP_MAINWINDOW_H

#include <QtWidgets>

#include <functional>

#include "src/gui/actions/ActionProcessor.h"
#include "src/gui/actions/ActionsMenu.h"
#include "src/gui/TrayIcon.h"
#include "src/gui/IImageProcessor.h"
#include "src/gui/imageAnnotator/KImageAnnotatorAdapter.h"
#include "src/gui/aboutDialog/AboutDialog.h"
#include "src/gui/settingsDialog/SettingsDialog.h"
#include "src/gui/notificationService/NotificationServiceFactory.h"
#include "src/gui/operations/AddWatermarkOperation.h"
#include "src/gui/operations/CopyAsDataUriOperation.h"
#include "src/gui/operations/UploadOperation.h"
#include "src/gui/operations/HandleUploadResultOperation.h"
#include "src/gui/operations/LoadImageFromFileOperation.h"
#include "src/gui/globalHotKeys/GlobalHotKeyHandler.h"
#include "src/gui/captureHandler/CaptureHandlerFactory.h"
#include "src/gui/captureHandler/ICaptureChangeListener.h"
#include "src/gui/widgetVisibilityHandler/WidgetVisibilityHandlerFactory.h"
#include "src/gui/pinWindow/PinWindowHandler.h"
#include "src/gui/RecentImagesMenu.h"
#include "src/gui/dragAndDrop/DragAndDropProcessor.h"
#include "src/gui/dragAndDrop/IDragContentProvider.h"
#include "src/gui/windowResizer/IResizableWindow.h"
#include "src/gui/windowResizer/WindowResizer.h"
#include "src/widgets/MainToolBar.h"
#include "src/backend/uploader/UploadHandler.h"
#include "src/backend/CapturePrinter.h"
#include "src/backend/imageGrabber/IImageGrabber.h"
#include "src/common/provider/ApplicationTitleProvider.h"
#include "src/common/dtos/CaptureFromFileDto.h"
#include "src/common/adapter/fileDialog/IFileDialogService.h"
#include "src/dependencyInjector/DependencyInjector.h"


class MainWindow : public QMainWindow, public ICaptureChangeListener, public IImageProcessor, public IResizableWindow, public IDragContentProvider
{
    Q_OBJECT
public:
    explicit MainWindow(DependencyInjector *dependencyInjector);
    ~MainWindow() override;
    void showEmpty();
	void showHidden();
    void showDefault();
    void captureScreenshot(CaptureModes captureMode, bool captureCursor, int delay);
	void resizeToContent() override;
	bool isWindowMaximized() override;
	void processImage(const CaptureDto &capture) override;
	DragContent dragContent() const override;

public slots:
    void processCapture(const CaptureDto &capture);
	void quit();

signals:
	void imageLoaded() const;

protected:
    void moveEvent(QMoveEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
	void changeEvent(QEvent *event) override;
    QMenu *createPopupMenu() override;
    QSize sizeHint() const override;

private:
	DependencyInjector *mDependencyInjector;
	QSharedPointer<IConfig> mConfig;
	QSharedPointer<IImageGrabber> mImageGrabber;
	TrayIcon *mTrayIcon;
	QSharedPointer<INotificationService> mNotificationService;
	bool mSessionManagerRequestedQuit;
	QAction *mSaveAsAction;
	QAction *mUploadAction;
	QAction *mCopyAsDataUriAction;
	QAction *mPrintAction;
	QAction *mPrintPreviewAction;
	QAction *mQuitAction;
	QAction *mCopyPathAction;
	QAction *mRenameAction;
	QAction *mOpenDirectoryAction;
	QAction *mToggleDocksAction;
	QAction *mSettingsAction;
	QAction *mAboutAction;
	QAction *mOpenImageAction;
	QAction *mScaleAction;
	QAction *mRotateAction;
	QAction *mAddWatermarkAction;
	QAction *mPasteAction;
	QAction *mPasteEmbeddedAction;
	QAction *mPinAction;
	QAction *mRemoveImageAction;
	QAction *mModifyCanvasAction;
	MainToolBar *mToolBar;
	QLayout *mMainLayout;
	ActionsMenu *mActionsMenu;
	RecentImagesMenu *mRecentImagesMenu;
	QSharedPointer<IClipboard> mClipboard;
	CapturePrinter *mCapturePrinter;
	IImageAnnotator *mImageAnnotator;
	QSharedPointer<ISavePathProvider> mSavePathProvider;
	GlobalHotKeyHandler *mGlobalHotKeyHandler;
	DragAndDropProcessor *mDragAndDropProcessor;
	QSharedPointer<IUploadHandler> mUploadHandler;
	ICaptureHandler *mCaptureHandler;
	PinWindowHandler *mPinWindowHandler;
	WidgetVisibilityHandler *mVisibilityHandler;
	QSharedPointer<IFileDialogService> mFileDialogService;
	WindowResizer *mWindowResizer;
	ActionProcessor *mActionProcessor;

    void setEnablements(bool enabled);
    void loadSettings();
    void triggerCapture(CaptureModes captureMode);
    void capture(CaptureModes captureMode, bool captureCursor, int delay);
    void initGui();
	void showDialog(const std::function<void ()>& showDialogMethod);

private slots:
	void captureChanged() override;
	void captureEmpty() override;
    void copyCaptureToClipboard();
    void upload();
    void uploadFinished(const UploadResult &result);
    void copyAsDataUri();
    void printClicked();
    void printPreviewClicked();
    void showOpenImageDialog();
    void pasteFromClipboard();
    void pasteEmbeddedFromClipboard();
    void setupImageAnnotator();
    void captureDelayChanged(int delay);
    void addWatermark();
    void showSettingsDialog();
    void showAboutDialog();
    void showScaleDialog();
    void showRotateDialog();
	void setPosition();
	void handleGuiStartup();
	void saveClicked();
	void saveAsClicked();
	void updateApplicationTitle();
	void capturePostProcessing();
	void loadImageFromFile(const QString &path);
	void loadImageFromPixmap(const QPixmap &pixmap);
	void sessionFinished();
	void captureCanceled();
	void showPinWindow();
	void hideMainWindowIfRequired();
	void toggleDocks();
	void actionTriggered(const Action &action);
	void showAfterAction(bool minimized);
};

#endif // KSNIP_MAINWINDOW_H
