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
#include "SnippingArea.h"

SnippingArea::SnippingArea(QWidget* parent) : QWidget(parent),
    mCursorFactory(new CursorFactory())
{
    // Hide the widget background, we will draw it manually on the paint event
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAutoFillBackground(false);
    setStyleSheet("QFrame#ImageFrame { background-color: transparent; }");

    // Make the frame span across the screen and show above any other widget
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);

    // Set the default cursor for this widget to a custom cursor
    QWidget::setCursor(*mCursorFactory->createSnippingCursor());
}

SnippingArea::~SnippingArea()
{
    delete mCursorFactory;
}

void SnippingArea::show()
{
    setFixedSize(QDesktopWidget().size());
    QWidget::show();
    activateWindow();
}

void SnippingArea::mousePressEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    mMouseDownPosition = event->pos();
    mCaptureArea =  MathHelper::getRectBetweenTwoPoints(event->pos(), event->pos());
    mMouseIsDown = true;
}

void SnippingArea::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    mMouseIsDown = false;
    hide();
    emit areaSelected(mCaptureArea);
}

void SnippingArea::mouseMoveEvent(QMouseEvent* event)
{
    if (!mMouseIsDown) {
        return;
    }

    mCaptureArea = MathHelper::getRectBetweenTwoPoints(mMouseDownPosition, event->pos());
    update();

    QWidget::mouseMoveEvent(event);
}

void SnippingArea::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    if (mMouseIsDown) {
        painter.setClipRegion(QRegion(geometry()).subtracted(QRegion(mCaptureArea)));
    }

    painter.setBrush(QColor(0, 0, 0, 150));
    painter.drawRect(geometry());

    if (mMouseIsDown) {
        painter.setPen(QPen(Qt::red, 4, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        painter.drawRect(mCaptureArea);
    }

    QWidget::paintEvent(event);
}

void SnippingArea::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape) {
        emit cancel();
        close();
    }
    QWidget::keyPressEvent(event);
}
