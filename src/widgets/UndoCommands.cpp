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

#include "UndoCommands.h"
#include "src/painter/PaintArea.h"

//
// Move Command
//
MoveCommand::MoveCommand(PaintArea* scene, const QPointF& newPos, QUndoCommand* parent)
    : QUndoCommand(parent)
{
    mScene = scene;
    for (auto item : scene->selectedItems()) {
        if (item) {
            Entry e(item, item->position(), newPos);
            mItems.append(e);
        }
    }
}

bool MoveCommand::mergeWith(const QUndoCommand* command)
{
    const auto moveCommand = static_cast<const MoveCommand*>(command);
    auto items = moveCommand->mItems;

    // Check if lists are equal, if not, don't merge
    if (mItems != items) {
        return false;
    }

    for (auto i = 0; i < items.count(); i++) {
        mItems[i].newPos = items.at(i).item->position();
    }
    return true;
}

void MoveCommand::undo()
{
    for (auto i : mItems) {
        i.item->moveTo(i.oldPos);
    }
    mScene->update();
}

void MoveCommand::redo()
{
    for (auto i : mItems) {
        i.item->moveTo(i.newPos);
    }
    mScene->update();
}

//
// Delete Command
//
DeleteCommand::DeleteCommand(PainterBaseItem* painterItem,
                             PaintArea* scene,
                             QUndoCommand* parent)
    : QUndoCommand(parent)
{
    mScene = scene;
    mPainterItem = painterItem;
}

void DeleteCommand::undo()
{
    mScene->addItem(mPainterItem);
    mPainterItem->show();
    mScene->update();
}

void DeleteCommand::redo()
{
    mScene->removeItem(mPainterItem);
    // Items that are out of the scene rect sometimes even after removing them
    // from the scene are still shown on the View as they are not deleted due to
    // being still used by the undo/redo framework. We hide those items anytime
    // we remove the from the scene.
    mPainterItem->hide();
    mScene->update();
}

//
// Add Command
//
AddCommand::AddCommand(PainterBaseItem* painterItem,
                       PaintArea* scene,
                       QUndoCommand* parent)
    : QUndoCommand(parent)
{
    mScene = scene;
    mPainterItem = painterItem;
    mInitialPosition = mPainterItem->position();
}

AddCommand::~AddCommand()
{
    delete mPainterItem;
}

void AddCommand::undo()
{
    mScene->removeItem(mPainterItem);
    mPainterItem->hide();
    mScene->update();
}

void AddCommand::redo()
{
    mScene->addItem(mPainterItem);
    mPainterItem->show();
    mScene->update();
}

//
// Crop Command
//
CropCommand::CropCommand(QGraphicsPixmapItem* pixmapItem, const QRectF& newRect,
                         PaintArea* scene, QUndoCommand* parent) : QUndoCommand(parent)
{
    mScene = scene;
    mPixmapItem = pixmapItem;
    mNewRect = newRect;
    mOldRect = mScene->sceneRect();
    auto offset = mNewRect.topLeft() - mPixmapItem->offset();
    mNewRect.moveTo(offset);
    mOldPixmap = new QPixmap(pixmapItem->pixmap());
    mNewPixmap = new QPixmap(pixmapItem->pixmap().copy(mNewRect.toRect()));
    mOldOffset = pixmapItem->offset();
    mNewOffset = offset;
}

CropCommand::~CropCommand()
{
    delete mOldPixmap;
    delete mNewPixmap;
}

void CropCommand::undo()
{
    for (auto item : mScene->items()) {
        PainterBaseItem* baseItem = qgraphicsitem_cast<PainterBaseItem*> (item);
        if (baseItem) {
            baseItem->moveTo(baseItem->position() + mOldOffset);
        }
    }

    mPixmapItem->setPixmap(*mOldPixmap);
    mPixmapItem->setOffset(mOldOffset);
    mScene->setSceneRect(mOldRect);
    mScene->fitViewToParent();
}

void CropCommand::redo()
{
    // Move all painter items to old offset, if this is not done, on the second
    // crop the items are positioned incorrectly bug#27
    for (auto item : mScene->items()) {
        PainterBaseItem* baseItem = qgraphicsitem_cast<PainterBaseItem*> (item);
        if (baseItem) {
            baseItem->moveTo(baseItem->position() - mPixmapItem->offset());
        }
    }


    mPixmapItem->setPixmap(*mNewPixmap);
    mPixmapItem->setOffset(mNewOffset);
    mScene->setSceneRect(mNewRect);
    mScene->fitViewToParent();
}
