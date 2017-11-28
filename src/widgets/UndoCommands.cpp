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
DeleteCommand::DeleteCommand(PaintArea* scene,
                             QUndoCommand* parent)
    : QUndoCommand(parent)
{
    mItems = scene->selectedItems();
    mScene = scene;
}

void DeleteCommand::undo()
{
    for (auto item : mItems) {
        mScene->addItem(item);
        item->show();
    }
    mScene->update();
}

void DeleteCommand::redo()
{
    for (auto item : mItems) {
        mScene->removeItem(item);
        // Items that are out of the scene rect sometimes even after removing them
        // from the scene are still shown on the View as they are not deleted due to
        // being still used by the undo/redo framework. We hide those items anytime
        // we remove the from the scene.
        item->hide();
    }
    mScene->update();
}

//
// Add Command
//
AddCommand::AddCommand(AbstractPainterItem* painterItem,
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
        AbstractPainterItem* baseItem = qgraphicsitem_cast<AbstractPainterItem*> (item);
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
        AbstractPainterItem* baseItem = qgraphicsitem_cast<AbstractPainterItem*> (item);
        if (baseItem) {
            baseItem->moveTo(baseItem->position() - mPixmapItem->offset());
        }
    }

    mPixmapItem->setPixmap(*mNewPixmap);
    mPixmapItem->setOffset(mNewOffset);
    mScene->setSceneRect(mNewRect);
    mScene->fitViewToParent();
}

//
// ReOrder Command
//
ReOrderCommand::ReOrderCommand(QList<QPair<QGraphicsItem*, QGraphicsItem*> >* list,
                               QUndoCommand*)
{
    mList = list;
}

ReOrderCommand::~ReOrderCommand()
{
    delete mList;
}

void ReOrderCommand::undo()
{
    for (auto i = mList->count() - 1; i >= 0; i--) {
        auto tmp = mList->at(i).first->zValue();
        mList->at(i).first->setZValue(mList->at(i).second->zValue());
        mList->at(i).second->setZValue(tmp);
    }
}

void ReOrderCommand::redo()
{
    for (auto item : *mList) {
        auto tmp = item.first->zValue();
        item.first->setZValue(item.second->zValue());
        item.second->setZValue(tmp);
    }
}

//
// Past Command
//

PastCommand::PastCommand(PaintArea* scene, const QPointF& pos, QUndoCommand* parent)
{
    mScene = scene;
    mPosition = pos;
    PainterItemFactory paintItemFactory;
    for (auto item : mScene->copiedItems()) {
        auto newItem = paintItemFactory.createCopyOfItem(item);
        mList.append(newItem);
    }
}

PastCommand::~PastCommand()
{
    for (auto item : mList) {
        delete item;
    }
    mList.clear();
}

void PastCommand::undo()
{
    for (auto item : mList) {
        mScene->removeItem(item);
        item->hide();
    }
    mScene->update();
}

void PastCommand::redo()
{
    for (auto item : mList) {
        mScene->addItem(item);
        item->moveTo(mPosition);
        item->show();
    }
    mScene->update();
}
