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

#include <QtGui>

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
#include "src/helper/X11GraphicsHelper.h"

class SnippingArea;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    void show(QPixmap screenshot);
    void show();
    int captureDelay() const;
    void instantCapture(ImageGrabber::CaptureMode captureMode, int delay = 0);
    void resize();

public slots:
    void setCaptureDelay(int ms);
    void openCrop();
    void closeCrop();
    QMenu *createPopupMenu();
    void colorChanged(const QColor &color);
    void fillChanged(const bool &fill);
    void sizeChanged(const int &size);

protected:
    void moveEvent(QMoveEvent *event);
    void closeEvent(QCloseEvent *event);

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

    void delay(int ms);
    void setSaveAble(bool enabled);
    void setEnablements(bool enabled);
    void loadSettings();
    void copyToClipboard();
    bool popupQuestion(QString title, QString question);
    QIcon createIcon(QString name);
    void instantSave(QPixmap pixmap);
    void initGui();

private slots:
    void newRectAreaCaptureClicked();
    void newCurrentScreenCaptureClicked();
    void newFullScreenCaptureClicked();
    void newActiveWindowCaptureClicked();
    void saveCaptureClicked();
    void copyToClipboardClicked();
    void penClicked();
    void markerClicked();
    void rectClicked();
    void ellipseClicked();
    void textClicked();
    void eraseClicked();
    void moveClicked();
    void imgurUploadClicked();
    void printClicked();
    void printPreviewClicked();
    void printCapture(QPrinter *p);
    void keyPressEvent(QKeyEvent *event);
    void areaSelected(QRect rect);
    void imageChanged();
    void imgurUploadFinished(QString message);
    void imgurError(QString message);
    void imgurTokenUpdated(const QString accessToken, const QString refreshTocken, const QString username);
    void imgurTokenRefresh();
    void openSettingsDialog();
    void openAboutDialog();
    void setPaintMode(const PaintArea::PaintMode &mode, const bool &save = true);
};

#endif // MAINWINDOW_H
