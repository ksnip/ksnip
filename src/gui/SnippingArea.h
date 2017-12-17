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

#include <QWidget>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>

#include "src/widgets/CursorFactory.h"
#include "src/helper/MathHelper.h"
#include "src/backend/KsnipConfig.h"

class SnippingArea : public QWidget
{
    Q_OBJECT
public:
    SnippingArea(QWidget *parent);
    ~SnippingArea();
    void showWithoutBackground();
    void showWithBackground(const QPixmap& background);
    QRect selectedRectArea() const;
    bool close();

signals:
    void finished();
    void canceled();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QPoint         mMouseDownPosition;
    bool           mMouseIsDown;
    bool           mCursorRulerEnabled;
    bool           mCursorInfoEnabled;
    QRect          mCaptureArea;
    CursorFactory *mCursorFactory;
    KsnipConfig   *mConfig;
    QPixmap       *mBackground;

    void show();
    void setBackgroundImage(const QPixmap &background);
    void clearBackgroundImage();
    void init();
    void updateCapturedArea(const QPoint &pos1, const QPoint &pos2);
    QString createPositionInfoText(int number1, int number2) const;
    void drawCursorRuler(QPainter &painter) const;
    void drawCursorPositionInfo(QPainter &painter) const;
    void drawCursorSizeInfo(QPainter &painter) const;
    void drawCursorWidthInfo(QPainter &painter) const;
    void drawCursorHeightInfo(QPainter &painter) const;
    QRect getTextBounding(const QPainter &painter, const QString &text) const;
};

#endif // SNIPPINGAREA_H
