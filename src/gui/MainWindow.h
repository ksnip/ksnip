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
#include "src/widgets/PaintArea.h"
#include "src/widgets/CustomToolButton.h"
#include "src/widgets/CaptureView.h"
#include "src/backend/ImageGrabber.h"
#include "src/backend/KsnipConfig.h"
#include "src/backend/StringManip.h"
#include "src/backend/ImgurUploader.h"

class SnippingArea;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();
    void show ( QPixmap screenshot );
    void show();
    int captureDelay();
    void instantCapture(ImageGrabber::CaptureMode captureMode, int delay = 0);

public slots:
    void setCaptureDelay ( int ms );

protected:
    void moveEvent ( QMoveEvent *event );
    void closeEvent ( QCloseEvent *event );

private:
    int               mCaptureDelay;
    bool              mIsUnsaved;
    QToolBar         *mToolBar;
    QMenuBar         *mMenuBar;
    CustomToolButton *mNewCaptureButton;
    QToolButton      *mSaveButton;
    QToolButton      *mCopyToClipboardButton;
    CustomToolButton *mPaintToolButton;
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
    QAction          *mEraseAction;
    QAction          *mMoveAction;
    QAction          *mUploadAction;  // TEST 
    QAction          *mCropAction;
    QAction          *mNewCaptureAction;
    QAction          *mQuitAction;
    QAction          *mSettingsDialogAction;
    QAction          *mAboutKsnipAction;
    QVBoxLayout      *mWindowLayout;
    PaintArea        *mCaptureScene;
    CaptureView      *mCaptureView;
    QClipboard       *mClipboard;
    SnippingArea     *mSnippingArea;
    ImageGrabber     *mImageGrabber;
    ImgurUploader    *mImgurUploader;   // TEST

    void delay ( int ms );
    void setSaveAble ( bool enabled );
    void loadSettings();
    void copyToClipboard();
    bool popupQuestion ( QString title, QString question );
    QIcon createIcon ( QString name );
    void instantSave( QPixmap pixmap);
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
    void eraseClicked();
    void moveClicked();
    void uploadClicked();  // TEST
    void cropClicked();
    void keyPressEvent ( QKeyEvent *event );
    void areaSelected ( QRect rect );
    void imageChanged();
    void uploadFinished( QString message, ImgurUploader::Result result); // TEST
    void openSettingsDialog();
    void openAboutDialog();
};

#endif // MAINWINDOW_H
