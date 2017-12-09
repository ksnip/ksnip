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
    mCursor(new CustomCursor(CustomCursor::Cross)),
    mBackground(nullptr)
{
    // Make the frame span across the screen and show above any other widget
    setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);

    // Set the default cursor for this widget to a custom cursor
    QWidget::setCursor(*mCursor);
}

void SnippingArea::showWithoutBackground()
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    clearBackgroundImage();
    show();
}

void SnippingArea::showWithBackground(const QPixmap& background)
{
    setAttribute(Qt::WA_TranslucentBackground, false);
    setBackgroundImage(background);
    show();
}

void SnippingArea::show()
{
    init();
    setFixedSize(QDesktopWidget().size());
    QWidget::show();
    activateWindow();
}

void SnippingArea::setBackgroundImage(const QPixmap& background)
{
    clearBackgroundImage();
    mBackground = new QPixmap(background);
}

void SnippingArea::clearBackgroundImage()
{
    if (mBackground != nullptr) {
        delete mBackground;
    }
}

void SnippingArea::init()
{
    mMouseIsDown = false;
}

void SnippingArea::mousePressEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    mMouseDownPosition = event->pos();
    mCaptureArea =  calculateArea(event->pos(), event->pos());
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

    mCaptureArea = calculateArea(mMouseDownPosition, event->pos());
    update();

    QWidget::mouseMoveEvent(event);
}

void SnippingArea::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);


    if (mBackground != nullptr) {
        painter.drawPixmap(geometry(), *mBackground);
    }

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

//
// Private Functions
//

/*
 * Calculate area for the screen capture, between the first mouse down location
 * and current mouse position.
 */
QRect SnippingArea::calculateArea(QPoint pointA, QPoint pointB)
{
    return QRect(QPoint((pointA.x() <= pointB.x() ? pointA.x() : pointB.x()),
                        (pointA.y() <= pointB.y() ? pointA.y() : pointB.y())),
                 QPoint((pointA.x() >= pointB.x() ? pointA.x() : pointB.x()),
                        (pointA.y() >= pointB.y() ? pointA.y() : pointB.y())));
}
