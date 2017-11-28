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

#include "src/painter/AbstractPainterItem.h"
#include "src/painter/PaintArea.h"
#include "src/painter/PainterItemFactory.h"

class PaintArea;

class MoveCommand : public QUndoCommand
{
public:
    enum { Id = 1234 };

    struct Entry {
        AbstractPainterItem *item;
        QPointF oldPos;
        QPointF newPos;

        Entry(AbstractPainterItem *item, const QPointF &oldPos,  QPointF newPos)
        {
            this->item = item;
            this->oldPos = oldPos;
            this->newPos = newPos;
        }

        bool operator==(const Entry &entry) const
        {
            return (this->item == entry.item);
        }
    };

    MoveCommand(PaintArea *scene, const QPointF &newPos, QUndoCommand *parent = 0);
    virtual void undo() override;
    virtual void redo() override;
    virtual bool mergeWith(const QUndoCommand *command) override;
    virtual int id() const override
    {
        return Id;
    }

private:
    QList<Entry> mItems;
    PaintArea   *mScene;
};


class DeleteCommand : public QUndoCommand
{
public:
    explicit DeleteCommand(PaintArea *scene, QUndoCommand *parent = 0);
    virtual void undo() override;
    virtual void redo() override;

private:
    QList<AbstractPainterItem *>  mItems;
    PaintArea                    *mScene;
};


class AddCommand : public QUndoCommand
{
public:
    AddCommand(AbstractPainterItem *painterItem, PaintArea *scene, QUndoCommand *parent = 0);
    ~AddCommand();
    virtual void undo() override;
    virtual void redo() override;

private:
    AbstractPainterItem *mPainterItem;
    PaintArea           *mScene;
    QPointF              mInitialPosition;
};


class CropCommand : public QUndoCommand
{
public:
    CropCommand(QGraphicsPixmapItem *pixmap, const QRectF &newRect, PaintArea *scene, QUndoCommand *parent = 0);
    ~CropCommand();
    virtual void undo() override;
    virtual void redo() override;

private:
    PaintArea           *mScene;
    QPixmap             *mOldPixmap;
    QPixmap             *mNewPixmap;
    QGraphicsPixmapItem *mPixmapItem;
    QRectF               mNewRect;
    QRectF               mOldRect;
    QPointF              mOldOffset;
    QPointF              mNewOffset;
};

class ReOrderCommand : public QUndoCommand
{
public:
    ReOrderCommand(QList<QPair<QGraphicsItem*, QGraphicsItem*>> *list, QUndoCommand *parent = 0);
    ~ReOrderCommand();
    virtual void undo() override;
    virtual void redo() override;

private:
    QList<QPair<QGraphicsItem*, QGraphicsItem*>> *mList;
};


class PastCommand : public QUndoCommand
{
public:
    PastCommand(PaintArea *scene, const QPointF& pos, QUndoCommand *parent = 0);
    ~PastCommand();
    virtual void undo() override;
    virtual void redo() override;

private:
    QList<AbstractPainterItem*> mList;
    PaintArea                  *mScene;
    QPointF                     mPosition;
};

#endif // UNDOCOMMANDS_H
