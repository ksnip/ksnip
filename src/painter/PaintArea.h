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

#include "PainterItemFactory.h"
#include "PainterPen.h"
#include "PainterRect.h"
#include "PainterEllipse.h"
#include "PainterArrow.h"
#include "PainterText.h"
#include "PainterNumber.h"
#include "PaintModes.h"
#include "src/widgets/UndoCommands.h"
#include "src/widgets/CursorFactory.h"
#include "src/widgets/ContextMenu.h"

class PaintArea : public QGraphicsScene
{
    Q_OBJECT
public:
    PaintArea();
    ~PaintArea();
    void loadCapture(const QPixmap &pixmap);
    void fitViewToParent();
    QSize areaSize() const;
    void setPaintMode(Painter::Modes paintMode);
    Painter::Modes paintMode() const;
    QImage exportAsImage();
    void setIsEnabled(bool enabled);
    bool isEnabled() const;
    bool isValid() const;
    bool isTextEditing() const;
    void crop(const QRectF &rect);
    QPointF cropOffset() const;
    QAction *getUndoAction();
    QAction *getRedoAction();
    QList<AbstractPainterItem *> selectedItems(Qt::SortOrder order = Qt::DescendingOrder) const;
    QList<AbstractPainterItem *> copiedItems() const;

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
    AbstractPainterItem *mCurrentItem;
    QRubberBand         *mRubberBand;
    QPoint               mRubberBandOrigin;
    QCursor             *mCursor;
    bool                 mShiftPressed;
    bool                 mCtrlPressed;
    Painter::Modes       mPaintMode;
    QUndoStack          *mUndoStack;
    QAction             *mUndoAction;
    QAction             *mRedoAction;
    KsnipConfig         *mConfig;
    PainterItemFactory  *mPainterItemFactory;
    CursorFactory       *mCursorFactory;
    QList<AbstractPainterItem *> mCopiedItems;

    void eraseItemAt(const QPointF &position, int size = 10);
    AbstractPainterItem *findItemAt(const QPointF &position, int size = 10);
    void moveItems(const QPointF &position);
    void clearCurrentItem();
    QCursor *cursor();
    QPoint mapToView(const QPointF &point) const;
    QRectF mapFromView(const QRectF &rect) const;
    AbstractPainterItem *selectItemAt(const QPointF &point, int size = 10);
    void setSelectionArea(const QRectF &rect);


private slots:
    void setCursor();
    void bringForward(bool toFront = false);
    void sendBackward(bool toBack = false);
    void copySelectedItems(const QPointF& pos);
    void pastCopiedItems(const QPointF& pos);
    void eraseSelectedItems();
};

#endif // PAINTAREA_H
