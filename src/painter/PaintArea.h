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

#include <QtGui>
#include <QGraphicsScene>

#include "PainterPath.h"
#include "PainterRect.h"
#include "PainterEllipse.h"
#include "PainterText.h"
#include "src/widgets/CustomCursor.h"
#include "src/widgets/UndoCommands.h"

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
        Move
    };

public:
    PaintArea();
    void loadCapture(const QPixmap &pixmap);
    void fitViewToParent();
    QSize areaSize() const;
    void setPaintMode(const PaintMode &paintMode);
    PaintMode paintMode() const;
    QImage exportAsImage();
    void setIsEnabled(const bool &enabled);
    bool isEnabled() const;
    bool isValid() const;
    void crop(const QRectF &rect);
    QPointF cropOffset() const;
    QAction *createUndoAction();
    QAction *createRedoAction();

signals:
    void imageChanged();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    bool                 mIsEnabled;
    QGraphicsPixmapItem *mScreenshot;
    PainterBaseItem     *mCurrentItem;
    QCursor             *mCursor;
    bool                 mModifierPressed;
    PaintMode            mPaintMode;
    QUndoStack          *mUndoStack;

    bool eraseItem(const QPointF &position, const int &size);
    bool grabItem(const QPointF &position);
    void moveItem(const QPointF &position);
    void clearItem();
    QCursor *cursor();

private slots:
    void setCursor();
};

#endif // PAINTAREA_H
