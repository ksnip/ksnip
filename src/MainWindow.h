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

#include <QWidget>

#include "SnippingArea.h"
#include "PaintArea.h"
#include "CustomToolButton.h"
#include "ImageGrabber.h"

class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QGraphicsScene;
class QGraphicsView;
class QClipboard;
class SnippingArea;
class QKeyEvent;
class QMoveEvent;
class QToolBar;
class QMenuBar;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();
    void show ( QPixmap );
    void show();
    
protected:
    void moveEvent ( QMoveEvent* );

private slots:
    void newRectAreaCaptureClicked();
    void newCurrentScreenCaptureClicked();
    void mNewFullScreenCaptureClicked();
    void newActiveWindowCaptureClicked();
    void saveCaptureClicked();
    void copyToClipboardClicked();
    void penClicked();
    void markerClicked();
    void eraseClicked();
    void keyPressEvent ( QKeyEvent * );
    void areaSelected ( QRect );
    void imageChanged();
    void setCaptureDelay(int);

private:
    int               captureDelay;
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
    QAction          *mPenAction;
    QAction          *mMarkerAction;
    QAction          *mEraseAction;
    QVBoxLayout      *mWindowLayout;
    PaintArea        *mCaptureScene;
    QGraphicsView    *mCaptureView;
    QClipboard       *mClipboard;
    SnippingArea     *mSnippingArea;
    ImageGrabber     *mImageGrabber;
    void delay ( int ms );
    void setSaveAble ( bool );
    void saveSetting ( QString, QVariant );
    void loadSettings();
    void createToolBar();
    void createToolButtons();
    void createLayout();
    void createMenuBar();
};

#endif // MAINWINDOW_H
