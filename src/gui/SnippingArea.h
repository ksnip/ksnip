/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */

#ifndef SNIPPINGAREA_H
#define SNIPPINGAREA_H

#include <QtGui>

#include "MainWindow.h"
#include "src/widgets/CustomCursor.h"

class MainWindow;

class SnippingArea : public QWidget
{
    Q_OBJECT
public:
    SnippingArea(QWidget *);
    void showWithoutBackground();
    void showWithBackground(const QPixmap& background);

signals:
    void areaSelected(QRect);

protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private:
    QPoint        mMouseDownPosition;
    bool          mMouseIsDown;
    QRect         mCaptureArea;
    CustomCursor *mCursor;
    QPixmap      *mBackground;

    void show();
    void setBackgroundImage(const QPixmap &background);
    void clearBackgroundImage();
    void init();
    QRect calculateArea(QPoint, QPoint);
};

#endif // SNIPPINGAREA_H
