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

#ifndef KSNIP_MAINWINDOW_H
#define KSNIP_MAINWINDOW_H

#include <QtWidgets>

#include <functional>

#include <kImageAnnotator/KImageAnnotator.h>

#include "src/gui/aboutDialog/AboutDialog.h"
#include "src/gui/settingsDialog/SettingsDialog.h"
#include "src/widgets/CustomToolButton.h"
#include "src/widgets/MainToolBar.h"
#include "src/backend/imageGrabber/AbstractImageGrabber.h"
#include "src/backend/config/KsnipConfigProvider.h"
#include "src/backend/uploader/UploaderProvider.h"
#include "src/backend/CapturePrinter.h"
#include "src/backend/uploader/script/ScriptUploader.h"
#include "src/common/loader/IconLoader.h"
#include "src/common/enum/RunMode.h"
#include "src/common/provider/ApplicationTitleProvider.h"
#include "src/common/provider/NewCaptureNameProvider.h"
#include "src/common/provider/PathFromCaptureProvider.h"
#include "src/common/dtos/CaptureFromFileDto.h"
#include "src/common/handler/DragAndDropHandler.h"
#include "src/gui/operations/SaveOperation.h"
#include "src/gui/operations/AddWatermarkOperation.h"
#include "src/gui/operations/CanDiscardOperation.h"
#include "src/gui/operations/UploadOperation.h"
#include "src/gui/operations/HandleUploadResponseOperation.h"
#include "src/gui/globalHotKeys/GlobalHotKeyHandler.h"
#include "src/gui/TrayIcon.h"
#include "ClipboardWrapper.h"
#include "captureTabs/CaptureTabStateHandler.h"

using kImageAnnotator::KImageAnnotator;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(AbstractImageGrabber *imageGrabber, RunMode mode = RunMode::GUI);
    ~MainWindow() override;
    void showEmpty();
	void showHidden();
    void show();
    void captureScreenshot(CaptureModes captureMode, bool captureCursor, int delay);

public slots:
    void processCapture(const CaptureDto &capture);
	void processImage(const CaptureDto &capture);
	void quit();

protected:
    void moveEvent(QMoveEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
	void changeEvent(QEvent *event) override;
    QMenu *createPopupMenu() override;
    QSize sizeHint() const override;

private:
    AbstractImageGrabber *mImageGrabber;
    RunMode mMode;
    bool mHidden;
    bool mSessionManagerRequestedQuit;
    Qt::WindowState mSelectedWindowState;
    bool mWindowStateChangeLock;
    QAction *mSaveAsAction;
    QAction *mUploadAction;
    QAction *mPrintAction;
    QAction *mPrintPreviewAction;
    QAction *mQuitAction;
    QAction *mSettingsDialogAction;
    QAction *mAboutAction;
    QAction *mOpenImageAction;
    QAction *mScaleAction;
    QAction *mAddWatermarkAction;
    QAction *mPasteAction;
    QAction *mPasteEmbeddedAction;
    MainToolBar *mToolBar;
	ClipboardWrapper *mClipboard;
    KsnipConfig *mConfig;
    CapturePrinter *mCapturePrinter;
    KImageAnnotator *mKImageAnnotator;
    SavePathProvider mSavePathProvider;
    GlobalHotKeyHandler *mGlobalHotKeyHandler;
    TrayIcon *mTrayIcon;
	DragAndDropHandler *mDragAndDropHandler;
	CaptureTabStateHandler *mTabStateHandler;
	NewCaptureNameProvider mNewCaptureNameProvider;
	PathFromCaptureProvider mPathFromCaptureProvider;
	UploaderProvider *mUploaderProvider;

    void currentCaptureChanged();
    void setEnablements(bool enabled);
    void loadSettings();
    void setHidden(bool isHidden);
    bool hidden() const;
    void capture(CaptureModes captureMode);
    void initGui();
	void loadCapture(const CaptureDto &capture);
	void processInstantCapture(const CaptureDto &capture);
	void showDialog(const std::function<void ()>& showDialogMethod);

private slots:
    void saveCapture(bool saveInstant);
    void copyCaptureToClipboard();
    void upload();
    void uploadFinished(const UploadResult &result);
    void printClicked();
    void printPreviewClicked();
    void instantSave();
    void showOpenImageDialog();
    void pasteFromClipboard();
    void pasteEmbeddedFromClipboard();
    bool discardChanges();
    void setupImageAnnotator();
    void captureDelayChanged(int delay);
    void addWatermark();
    void showSettingsDialog();
    void showAboutDialog();
    void showScaleDialog();
	void setPosition();
	void handleGuiStartup();
	void saveClicked();
	void saveAsClicked();
	void updateApplicationTitle();
	void capturePostProcessing();
	void showImage(const CaptureDto &capture);
	void loadImageFromFile(const QString &path);
	void tabCloseRequested(int index);
	void removeTab(int currentTabIndex);
	void sessionFinished();
	void captureCanceled();
};

#endif // KSNIP_MAINWINDOW_H
