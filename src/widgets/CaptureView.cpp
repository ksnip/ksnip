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

#include "CaptureView.h"

CaptureView::CaptureView(QGraphicsScene* scene) : QGraphicsView(scene)
{
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    setIsCropping(false);
    mSelectedBorderPoint = -1;   // -1 means no border point selected
    mIsMovingSelection = false;
    mClickOffset = QPoint(0, 0);
    mRectSize = 15;
}

//
// Public Functions
//

void CaptureView::show()
{
    setFocus();
    setIsCropping(false);
    QGraphicsView::show();
}

PaintArea* CaptureView::scene() const
{
    return static_cast<PaintArea*>(QGraphicsView::scene());
}

void CaptureView::crop()
{
    setIsCropping(false);
    scene()->crop(mSelectedRect);
}

void CaptureView::setIsCropping(const bool& isCropping)
{
    // We can't crop if there was no pixmap loaded to the scene
    if (!scene()->isValid()) {
        return;
    }

    mIsCropping = isCropping;

    // Disable paint area, set selected area to full scene size, we haven't selected anything yet
    // last setup the border points
    if (mIsCropping) {
        scene()->setIsEnabled(false);
        mSelectedRect = sceneRect();
        setupBorderPoints(mSelectedRect);
    } else {
        scene()->setIsEnabled(true);
    }
    setCursor(QCursor::pos());
    scene()->update();
}

bool CaptureView::getIsCropping() const
{
    return mIsCropping;
}

QRectF CaptureView::getSelectedRect() const
{
    // Take into account offset of any previous crops
    QRectF rect = mSelectedRect.normalized();
    rect.moveTo(rect.topLeft() - scene()->cropOffset());
    return rect;
}

/*
 * Sets the selectedRect to the provided rect. Boundary checks should be done by the caller.
 * Takes crop offset into account.
 */
void CaptureView::setSelectedRect(const QRectF& rect)
{
    mSelectedRect = rect;
    mSelectedRect.moveTo(rect.topLeft() + scene()->cropOffset());
    setupBorderPoints(mSelectedRect);
    scene()->update();
}

//
// Protected Function
//
void CaptureView::keyPressEvent(QKeyEvent* event)
{
    if (mIsCropping) {
        // Cancel cropping
        if (event->key() == Qt::Key_Escape) {
            setIsCropping(false);
            emit closeCrop();
        } else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
            // We have selected an area and want to crop it
            crop();
            emit closeCrop();
        }
    }
    QGraphicsView::keyPressEvent(event);
}

void CaptureView::mousePressEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton && mIsCropping) {
        for (int i = 0; i < 8; i++) {
            if (mBorderPoints[i].contains(mapToScene(event->pos()).toPoint())) {
                mSelectedBorderPoint = i;
                mClickOffset = mapToScene(event->pos()) - mBorderPoints[i].topLeft();
                break;
            }
        }

        if (mSelectedBorderPoint == -1 && mSelectedRect.contains(mapToScene(event->pos()).toPoint())) {
            mIsMovingSelection = true;
            mClickOffset = mapToScene(event->pos()).toPoint() - mSelectedRect.topLeft();
        }
        setCursor(mapToScene(event->pos()).toPoint());
    }
    QGraphicsView::mousePressEvent(event);
}

void CaptureView::mouseReleaseEvent(QMouseEvent* event)
{
    // Reverting all variables for tracking change back to default
    mSelectedBorderPoint = -1;
    mIsMovingSelection = false;
    mClickOffset = QPoint(0, 0);

    mSelectedRect = mSelectedRect.normalized();
    setupBorderPoints(mSelectedRect);
    setCursor(mapToScene(event->pos()).toPoint());

    scene()->update();
    QGraphicsView::mouseReleaseEvent(event);
}

void CaptureView::mouseMoveEvent(QMouseEvent* event)
{
    if (mIsCropping) {
        if (mSelectedBorderPoint != -1) {
            // If we we are dragging one of the border points and have moved the mouse, calculate
            // new border point position
            moveBorderPoint(mSelectedBorderPoint, mapToScene(event->pos()).toPoint());
            scene()->update();

            // Inform anyone all stakeholders that the selection has changed
            emit selectedRectChanged(getSelectedRect());
        }

        if (mIsMovingSelection) {
            mSelectedRect.moveTo(restrictRectMoveToScene(mSelectedRect,
                                 mapToScene(event->pos()) - mClickOffset));
            scene()->update();

            // Inform anyone all stakeholders that the selection has changed
            emit selectedRectChanged(getSelectedRect());
        }
    }

    QGraphicsView::mouseMoveEvent(event);
}

void CaptureView::drawForeground(QPainter* painter, const QRectF& rect)
{
    if (mIsCropping) {
        // Draw semi transparent background for not selected area
        painter->setClipRegion(QRegion(sceneRect().toRect()).subtracted(
                                   QRegion(mSelectedRect.normalized().toRect()))
                              );
        painter->setBrush(QColor(0, 0, 0, 150));
        painter->drawRect(sceneRect());


        // Draw border around selected are
        painter->setClipRect(rect);
        painter->setBrush(Qt::NoBrush);
        painter->setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        painter->drawRect(mSelectedRect.normalized());

        // Draw border points but only when we are not currently dragging borderpoints
        if (mSelectedBorderPoint == -1 && mIsMovingSelection == false) {
            painter->setBrush(QColor(255, 0, 0, 150));

            for (int i = 0; i < 8; i++) {
                painter->drawRect(mBorderPoints[i]);
            }
        }
    }

    QGraphicsView::drawForeground(painter, rect);
}

//
// Private Functions
//

/*
 * Move the border point under the provided index to new position
 */
void CaptureView::moveBorderPoint(const int& borderPoint, const QPointF& pos)
{
    if (borderPoint == -1 || !mIsCropping) {
        return;
    }

    switch (borderPoint) {
    case 0:
        mSelectedRect.setTopLeft(restrictPointToScene(pos - mClickOffset));
        break;

    case 1:
        mSelectedRect.setTop(restrictPointToScene(QPoint(pos.x(),
                             pos.y() - mClickOffset.y())).y());
        break;

    case 2:
        mSelectedRect.setTopRight(restrictPointToScene(QPoint(pos.x() + mClickOffset.x(),
                                  pos.y() - mClickOffset.y())));
        break;

    case 3:
        mSelectedRect.setRight(restrictPointToScene(QPoint(pos.x() + mClickOffset.x(),
                               pos.y())).x());
        break;

    case 4:
        mSelectedRect.setBottomRight(restrictPointToScene(pos + mClickOffset));
        break;

    case 5:
        mSelectedRect.setBottom(restrictPointToScene(QPoint(pos.x(),
                                pos.y() + mClickOffset.y())).y());
        break;

    case 6:
        mSelectedRect.setBottomLeft(restrictPointToScene(QPoint(pos.x() - mClickOffset.x(),
                                    pos.y() + mClickOffset.y())));
        break;

    case 7:
        mSelectedRect.setLeft(restrictPointToScene(QPoint(pos.x() - mClickOffset.x(),
                              pos.y())).x());
        break;
    }
}

/*
 * Base on the provided rect, calculate new border point position.
 */
void CaptureView::setupBorderPoints(const QRectF& rect)
{
    // Top Left
    mBorderPoints[0].setRect(rect.x(),     // x
                             rect.y(),     // y
                             mRectSize,    // w
                             mRectSize);   // h
    // Top
    mBorderPoints[1].setRect(rect.x() + (rect.width() / 2) - (mRectSize / 2),
                             rect.y(),
                             mRectSize,
                             mRectSize);

    // Top Right
    mBorderPoints[2].setRect(rect.x() + rect.width()  - mRectSize,
                             rect.y(),
                             mRectSize,
                             mRectSize);

    // Right
    mBorderPoints[3].setRect(rect.x() + rect.width()  - mRectSize,
                             rect.y() + (rect.height() / 2) - (mRectSize / 2) ,
                             mRectSize,
                             mRectSize);

    // Bottom Right
    mBorderPoints[4].setRect(rect.x() + rect.width()  - mRectSize,
                             rect.y() + rect.height() - mRectSize ,
                             mRectSize,
                             mRectSize);

    // Bottom
    mBorderPoints[5].setRect(rect.x() + (rect.width() / 2) - (mRectSize / 2),
                             rect.y() + rect.height() - mRectSize ,
                             mRectSize,
                             mRectSize);

    // Bottom Left
    mBorderPoints[6].setRect(rect.x(),
                             rect.y() + rect.height() - mRectSize ,
                             mRectSize,
                             mRectSize);
    // Left
    mBorderPoints[7].setRect(rect.x(),
                             rect.y() + (rect.height() / 2) - (mRectSize / 2),
                             mRectSize,
                             mRectSize);
}

/*
 * Restrict point movement only to current scene rect
 */
QPointF CaptureView::restrictPointToScene(const QPointF& point) const
{
    QPointF p = point;
    if (point.x() < sceneRect().left()) {
        p.setX(sceneRect().left());
    } else if (point.x() >= sceneRect().right() - 1) {
        p.setX(sceneRect().right() - 1);
    }

    if (point.y() < sceneRect().top()) {
        p.setY(sceneRect().top());
    } else if (point.y() >= sceneRect().bottom() - 1) {
        p.setY(sceneRect().bottom() - 1);
    }

    return p;
}

/*
 * Restrict rect movement only to current scene rect
 */
QPointF CaptureView::restrictRectMoveToScene(const QRectF& rect, const QPointF& newPos) const
{
    QPointF p = newPos;
    if (newPos.x() < sceneRect().left()) {
        p.setX(sceneRect().left());
    } else if (newPos.x() + rect.width() > sceneRect().right()) {
        p.setX(sceneRect().right() - rect.width());
    }

    if (newPos.y() < sceneRect().top()) {
        p.setY(sceneRect().top());
    } else if (newPos.y() + rect.height() > sceneRect().bottom()) {
        p.setY(sceneRect().bottom() - rect.height());
    }

    return p;
}

/*
 * Sets the mouse cursor based on the current status
 */
void CaptureView::setCursor(const QPointF& pos)
{
    if (!mIsCropping) {
        return;
    }

    // If we are dragging border point, set resize arrows
    if (mSelectedBorderPoint != -1 || mIsMovingSelection) {
        QGraphicsView::setCursor(Qt::ClosedHandCursor);
    } else {
        QGraphicsView::setCursor(Qt::OpenHandCursor);
    }
}
