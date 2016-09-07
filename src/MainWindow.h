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
    void newCaptureClicked();
    void saveCaptureClicked();
    void copyToClipboardClicked();
    void penClicked();
    void markerClicked();
    void eraseClicked();
    void keyPressEvent ( QKeyEvent * );
    void areaSelected ( QRect );
    void imageChanged();

private:
    QPushButton      *mNewCaptureButton;
    QPushButton      *mSaveButton;
    QPushButton      *mCopyToClipboardButton;
    QToolBar         *mToolBar;
    CustomToolButton *mToolButton;
    QMenu            *mMenu;
    QAction          *mPenAction;
    QAction          *mMarkerAction;
    QAction          *mEraseAction;
    QHBoxLayout      *mMenuLayout;
    QVBoxLayout      *mWindowLayout;
    PaintArea        *mCaptureScene;
    QGraphicsView    *mCaptureView;
    QClipboard       *mClipboard;
    SnippingArea     *mSnippingArea;
    QPixmap grabScreen ( QRect );
    void delay ( int ms );
    void setSaveAble ( bool );
    void createButtons();
    void createToolBar();
    void createLayout();
    void loadSettings();
};

#endif // MAINWINDOW_H
