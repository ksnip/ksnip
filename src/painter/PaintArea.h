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

#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QAction>
#include <QRubberBand>
#include <QMenu>

#include "PainterPath.h"
#include "PainterRect.h"
#include "PainterEllipse.h"
#include "PainterText.h"
#include "src/widgets/CustomCursor.h"
#include "src/widgets/UndoCommands.h"

class KsnipConfig;

class PaintArea : public QGraphicsScene
{
    Q_OBJECT
public:
    enum PaintMode {
        Pen,
        Marker,
        Rect,
        Ellipse,
        Text,
        Erase,
        Move,
        Select
    };

public:
    PaintArea();
    void loadCapture(const QPixmap &pixmap);
    void fitViewToParent();
    QSize areaSize() const;
    void setPaintMode(PaintMode paintMode);
    PaintMode paintMode() const;
    QImage exportAsImage();
    void setIsEnabled(bool enabled);
    bool isEnabled() const;
    bool isValid() const;
    bool isTextEditing() const;
    void crop(const QRectF &rect);
    QPointF cropOffset() const;
    QAction *getUndoAction();
    QAction *getRedoAction();
    QList<PainterBaseItem *> selectedItems(Qt::SortOrder order = Qt::DescendingOrder) const;

signals:
    void imageChanged();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event)override;
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
    bool                 mIsEnabled;
    QGraphicsPixmapItem *mScreenshot;
    PainterBaseItem     *mCurrentItem;
    QRubberBand         *mRubberBand;
    QPoint               mRubberBandOrigin;
    QCursor             *mCursor;
    bool                 mShiftPressed;
    bool                 mCtrlPressed;
    PaintMode            mPaintMode;
    QUndoStack          *mUndoStack;
    QAction             *mUndoAction;
    QAction             *mRedoAction;
    KsnipConfig         *mConfig;

    bool eraseItemAt(const QPointF &position, int size);
    PainterBaseItem *findItemAt(const QPointF &position);
    void moveItems(const QPointF &position);
    void clearItem();
    QCursor *cursor();
    QPoint mapToView(const QPointF &point) const;
    QRectF mapFromView(const QRectF &rect) const;
    PainterBaseItem *selectItemAt(const QPointF &point);
    void setSelectionArea(const QRectF &rect);
    void bringForward(bool toFront = false);
    void sendBackward(bool toBack = false);

private slots:
    void setCursor();
};

#endif // PAINTAREA_H
