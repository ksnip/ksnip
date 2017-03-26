/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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
 */

#ifndef UNDOCOMMANDS_H
#define UNDOCOMMANDS_H

#include <QUndoCommand>

#include "src/painter/PaintArea.h"
#include "src/painter/PainterBaseItem.h"

class PaintArea;

class MoveCommand : public QUndoCommand
{
public:
    enum { Id = 1234 };

    MoveCommand(PainterBaseItem *painterItem, const QPointF &newPos, QUndoCommand *parent = 0);
    void undo() override;
    void redo() override;
    bool mergeWith(const QUndoCommand *command) override;
    int id() const override { return Id; }

private:
    PainterBaseItem *mPainterItem;
    QPointF mOldPos;
    QPointF mNewPos;
};


class DeleteCommand : public QUndoCommand
{
public:
    explicit DeleteCommand(PainterBaseItem *painterItem, PaintArea *scene, QUndoCommand *parent = 0);
    void undo() override;
    void redo() override;

private:
    PainterBaseItem *mPainterItem;
    PaintArea       *mScene;
};


class AddCommand : public QUndoCommand
{
public:
    AddCommand(PainterBaseItem *painterItem, PaintArea *scene, QUndoCommand *parent = 0);
    ~AddCommand();
    void undo() override;
    void redo() override;

private:
    PainterBaseItem *mPainterItem;
    PaintArea       *mScene;
    QPointF mInitialPosition;
};


class CropCommand : public QUndoCommand
{
public:
    CropCommand(QGraphicsPixmapItem *pixmap, const QRectF &newRect, PaintArea *scene, QUndoCommand *parent = 0);
    ~CropCommand();
    void undo() override;
    void redo() override;

private:
    PaintArea           *mScene;
    QPixmap             *mOldPixmap;
    QPixmap             *mNewPixmap;
    QGraphicsPixmapItem *mPixmapItem;
    QRectF              mNewRect;
    QRectF              mOldRect;
    QPointF             mOldOffset;
    QPointF             mNewOffset;
};

#endif // UNDOCOMMANDS_H
