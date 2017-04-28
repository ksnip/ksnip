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

#include "SnippingArea.h"
#include "SettingsDialog.h"
#include "AboutDialog.h"
#include "src/painter/PaintArea.h"
#include "src/widgets/CustomToolButton.h"
#include "src/widgets/CaptureView.h"
#include "src/widgets/CropPanel.h"
#include "src/widgets/PainterSettingsPicker.h"
#include "src/backend/ImageGrabber.h"
#include "src/backend/KsnipConfig.h"
#include "src/backend/StringManip.h"
#include "src/backend/ImgurUploader.h"

class SnippingArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    void show(const QPixmap &screenshot);
    void show();
    int captureDelay() const;
    void instantCapture(ImageGrabber::CaptureMode captureMode, int delay = 0, bool capureMouse = false);
    void resize();
    virtual QMenu *createPopupMenu() override;

public slots:
    void setCaptureDelay(int ms);
    void openCrop();
    void closeCrop();
    void colorChanged(const QColor &color);
    void fillChanged(bool fill);
    void sizeChanged(int size);

protected:
    virtual void moveEvent(QMoveEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;

private:
    int               mCaptureDelay;
    bool              mIsUnsaved;
    CustomToolButton *mNewCaptureButton;
    QToolButton      *mSaveButton;
    QToolButton      *mCopyToClipboardButton;
    CustomToolButton *mPaintToolButton;
    PainterSettingsPicker *mPainterSettingsButton;
    QMenu            *mPaintToolMenu;
    QMenu            *mNewCaptureMenu;
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
    QAction          *mTextAction;
    QAction          *mEraseAction;
    QAction          *mMoveAction;
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
    SnippingArea     *mSnippingArea;
    ImageGrabber     *mImageGrabber;
    ImgurUploader    *mImgurUploader;
    CropPanel        *mCropPanel;
    KsnipConfig      *mConfig;

    void delay(int ms);
    void setSaveAble(bool enabled);
    void setEnablements(bool enabled);
    void loadSettings();
    void copyToClipboard();
    bool popupQuestion(const QString &title, const QString &question);
    QIcon createIcon(const QString &name);
    void instantSave(const QPixmap &pixmap);
    void hide();
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
    void setPaintMode(PaintArea::PaintMode mode, bool save = true);
};

#endif // MAINWINDOW_H
