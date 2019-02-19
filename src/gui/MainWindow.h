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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

#include <kImageAnnotator/KImageAnnotator.h>

#include "SettingsDialog.h"
#include "AboutDialog.h"
#include "src/widgets/CustomToolButton.h"
#include "src/widgets/MainToolBar.h"
#include "src/backend/imageGrabber/AbstractImageGrabber.h"
#include "src/backend/KsnipConfig.h"
#include "backend/uploader/CaptureUploader.h"
#include "src/common/loader/IconLoader.h"
#include "src/common/handler/DelayHandler.h"
#include "src/common/enum/RunMode.h"
#include "src/common/helper/MessageBoxHelper.h"
#include "src/backend/CapturePrinter.h"

using kImageAnnotator::KImageAnnotator;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(AbstractImageGrabber *imageGrabber, RunMode mode = RunMode::GUI);
    void showEmpty();
    void captureScreenshot(CaptureModes captureMode, bool capureCursor = true, int delay = 0);
    QMenu *createPopupMenu() override;
    QSize sizeHint() const override;

public slots:
    void showCapture(const QPixmap &screenshot);

protected:
    void moveEvent(QMoveEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    AbstractImageGrabber *mImageGrabber;
    RunMode           mMode;
    bool              mIsUnsaved;
    bool              mHidden;
    QAction          *mUploadToImgurAction;
    QAction          *mPrintAction;
    QAction          *mPrintPreviewAction;
    QAction          *mCropAction;
    QAction          *mQuitAction;
    QAction          *mSettingsDialogAction;
    QAction          *mAboutKsnipAction;
    QAction          *mOpenImageAction;
    QAction          *mScaleAction;
    MainToolBar      *mToolBar;
    QAction          *mUndoAction;
    QAction          *mRedoAction;
    QClipboard       *mClipboard;
    KsnipConfig      *mConfig;
    DelayHandler     *mDelayHandler;
    CapturePrinter   *mCapturePrinter;
    CaptureUploader  *mCaptureUploader;
    KImageAnnotator *mkImageAnnotator;

    void setSaveAble(bool enabled);
    void setEnablements(bool enabled);
    void loadSettings();
    void setHidden(bool isHidden);
    bool hidden() const;
    void capture(CaptureModes captureMode);
    void triggerNewCapture(CaptureModes captureMode);
    void initGui();

private slots:
    void saveCapture();
    void copyCaptureToClipboard();
    void upload();
    void uploadFinished(QString message);
    void printClicked();
    void printPreviewClicked();
    void instantSave(const QPixmap &pixmap);
    void loadImageFromFile();
    void screenshotChanged();
    bool discardUnsavedChanges() const;
    bool proceedWithUpload() const;
    void copyToClipboard(const QString &message) const;
    QString &formatUrl(QString &message) const;
    void setupImageAnnotator();
    void captureDelayChanged(int delay);
};

#endif // MAINWINDOW_H
