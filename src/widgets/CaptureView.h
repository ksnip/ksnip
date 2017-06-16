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

#ifndef CAPTUREVIEW_H
#define CAPTUREVIEW_H

#include <QGraphicsView>

#include "src/painter/PaintArea.h"

class CaptureView : public QGraphicsView
{
    Q_OBJECT

public:
    CaptureView(QGraphicsScene *scene);
    void show();
    PaintArea *scene() const;
    void crop();
    bool isCropping() const;
    void setIsCropping(bool isCropping);
    QRectF cropRect() const;
    void setCropRect(const QRectF &rect);

signals:
    void cropRectChanged(const QRectF &rect);
    void closeCrop();

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void drawForeground(QPainter *painter, const QRectF &rect) override;

private:
    int     mRectSize;
    int     mSelectedBorderPoint;
    bool    mIsCropping;
    bool    mIsMovingSelection;
    QPointF mClickOffset;
    QRectF  mSelectedRect;
    QRectF  mBorderPoints[8];

    void moveBorderPoint(int borderPoint, const QPointF &pos);
    void setupBorderPoints(const QRectF &rect);
    QPointF restrictPointToScene(const QPointF &point) const;
    QPointF restrictRectMoveToScene(const QRectF &rect, const QPointF &newPos) const;
    void setCursor();
};

#endif // CAPTUREVIEW_H
