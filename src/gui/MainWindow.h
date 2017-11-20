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
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>

#include "SettingsDialog.h"
#include "AboutDialog.h"
#include "src/painter/PaintArea.h"
#include "src/painter/PaintModes.h"
#include "src/widgets/CustomToolButton.h"
#include "src/widgets/CaptureView.h"
#include "src/widgets/CropPanel.h"
#include "src/widgets/settingsPicker/SettingsPickerConfigurator.h"
#include "src/backend/ImageGrabber.h"
#include "src/backend/KsnipConfig.h"
#include "src/backend/ImgurUploader.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum RunMode {
        GUI,
        CLI
    };

public:
    MainWindow(RunMode mode = GUI);
    void show();
    void instantCapture(ImageGrabber::CaptureMode captureMode,
                        bool capureCursor = true,
                        int delay = 0);
    void resize();
    RunMode getMode() const;
    virtual QMenu *createPopupMenu() override;

public slots:
    void showCapture(const QPixmap &screenshot);
    void openCrop();
    void closeCrop();
    void colorChanged(const QColor &color);
    void fillChanged(bool fill);
    void sizeChanged(int size);

protected:
    virtual void moveEvent(QMoveEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
    RunMode           mMode;
    bool              mIsUnsaved;
    bool              mHidden;
    CustomToolButton *mNewCaptureButton;
    QToolButton      *mSaveButton;
    QToolButton      *mCopyToClipboardButton;
    CustomToolButton *mPaintToolButton;
    SettingsPicker   *mSettingsButton;
    CustomMenu       *mPaintToolMenu;
    CustomMenu       *mNewCaptureMenu;
    QAction          *mNewRectAreaCaptureAction;
    QAction          *mNewCurrentScreenCaptureAction;
    QAction          *mNewFullScreenCaptureAction;
    QAction          *mNewActiveWindowCaptureAction;
    QAction          *mSaveAction;
    QAction          *mCopyToClipboardAction;
    QAction          *mPenAction;
    QAction          *mMarkerAction;
    QAction          *mRectAction;
    QAction          *mEllipseAction;
    QAction          *mLineAction;
    QAction          *mArrowAction;
    QAction          *mTextAction;
    QAction          *mNumberAction;
    QAction          *mEraseAction;
    QAction          *mMoveAction;
    QAction          *mSelectAction;
    QAction          *mUploadToImgurAction;
    QAction          *mPrintAction;
    QAction          *mPrintPreviewAction;
    QAction          *mCropAction;
    QAction          *mNewCaptureAction;
    QAction          *mQuitAction;
    QAction          *mSettingsDialogAction;
    QAction          *mAboutKsnipAction;
    QToolBar         *mToolBar;
    PaintArea        *mPaintArea;
    CaptureView      *mCaptureView;
    QAction          *mUndoAction;
    QAction          *mRedoAction;
    QClipboard       *mClipboard;
    ImageGrabber     *mImageGrabber;
    ImgurUploader    *mImgurUploader;
    CropPanel        *mCropPanel;
    KsnipConfig      *mConfig;
    SettingsPickerConfigurator *mSettingsPickerConfigurator;

    void setSaveAble(bool enabled);
    void setEnablements(bool enabled);
    void loadSettings();
    void copyToClipboard();
    bool popupQuestion(const QString &title, const QString &question);
    QIcon createIcon(const QString &name);
    void setHidden(bool isHidden);
    bool hidden() const;
    void capture(ImageGrabber::CaptureMode captureMode);
    void initGui();

private slots:
    void saveCaptureClicked();
    void imgurUploadClicked();
    void printClicked();
    void printPreviewClicked();
    void printCapture(QPrinter *p);
    void imgurUploadFinished(QString message);
    void imgurError(const QString &message);
    void imgurTokenUpdated(const QString &accessToken,
                           const QString &refreshTocken,
                           const QString &username);
    void imgurTokenRefresh();
    void setPaintMode(Painter::Modes mode, bool save = true);
    void instantSave(const QPixmap &pixmap);
};

#endif // MAINWINDOW_H
