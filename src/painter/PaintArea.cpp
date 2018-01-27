/*
*  Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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
#include "PaintArea.h"

PaintArea::PaintArea() : QGraphicsScene(),
    mScreenshot(nullptr),
    mCurrentItem(nullptr),
    mRubberBand(new QRubberBand(QRubberBand::Rectangle, nullptr)),
    mShiftPressed(false),
    mPaintMode(Painter::Pen),
    mUndoStack(new QUndoStack(this)),
    mUndoAction(nullptr),
    mRedoAction(nullptr),
    mConfig(KsnipConfig::instance()),
    mPainterItemFactory(new PainterItemFactory()),
    mCursorFactory(new CursorFactory())
{
    connect(mConfig, &KsnipConfig::painterUpdated, this, &PaintArea::setCursor);

    mRubberBand->hide();
}

PaintArea::~PaintArea()
{
    delete mCursorFactory;
    delete mPainterItemFactory;
    delete mUndoStack;
}

//
// Public Methods
//

void PaintArea::loadCapture(const QPixmap& pixmap)
{
    clearCurrentItem();
    mUndoStack->clear();
    mPainterItemFactory->reset();
    clear();
    clearSelection();
    AbstractPainterItem::resetOrder();
    mScreenshot = addPixmap(pixmap);
    setSceneRect(pixmap.rect());
}

void PaintArea::fitViewToParent()
{
    for (auto view : views()) {
        view->parentWidget()->resize(areaSize() + QSize(100, 150));
    }
}

QSize PaintArea::areaSize() const
{
    return sceneRect().size().toSize();
}

void PaintArea::setPaintMode(Painter::Modes paintMode)
{
    if (mPaintMode == paintMode) {
        return;
    }

    mPaintMode = paintMode;

    clearCurrentItem();
    setCursor();
}

Painter::Modes PaintArea::paintMode() const
{
    return mPaintMode;
}

QImage PaintArea::exportAsImage()
{
    if (!isValid()) {
        qWarning("PainteArea::exportAsImage: Unable to export image, image invalid.");
        return QImage();
    }

    clearSelection();

    QImage image(sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    render(&painter);
    return image;
}

void PaintArea::setIsEnabled(bool enabled)
{
    mIsEnabled = enabled;
    mUndoAction->setEnabled(enabled);
    mRedoAction->setEnabled(enabled);
    setCursor();
}

bool PaintArea::isEnabled() const
{
    return mIsEnabled;
}

bool PaintArea::isValid() const
{
    if (mScreenshot == nullptr) {
        return false;
    } else {
        return true;
    }
}

bool PaintArea::isTextEditing() const
{
    auto textItem = dynamic_cast<PainterText*>(mCurrentItem);
    if (textItem) {
        return textItem->isEditable();
    }
    return false;
}

void PaintArea::crop(const QRectF& rect)
{
    mUndoStack->push(new CropCommand(mScreenshot, rect, this));
}

QPointF PaintArea::cropOffset() const
{
    return mScreenshot->offset();
}

QAction* PaintArea::getUndoAction()
{
    if (!mUndoAction) {
        mUndoAction = mUndoStack->createUndoAction(this, tr("Undo"));
    }
    return mUndoAction;
}

QAction* PaintArea::getRedoAction()
{
    if (!mRedoAction) {
        mRedoAction = mUndoStack->createRedoAction(this, tr("Redo"));
    }
    return mRedoAction;
}

QList<AbstractPainterItem*> PaintArea::selectedItems(Qt::SortOrder order) const
{
    QList<AbstractPainterItem*> list;
    for (auto item : items(order)) {
        auto base = static_cast<AbstractPainterItem*>(item);
        if (base && base->isSelected()) {
            list.append(base);
        }
    }
    return list;
}

QList<AbstractPainterItem *> PaintArea::copiedItems() const
{
    return mCopiedItems;
}

void PaintArea::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (!mIsEnabled) {
        return;
    }

    clearCurrentItem();

    if (event->button() != Qt::LeftButton) {
        return;
    }

    if (mPaintMode == Painter::Erase) {
        eraseItemAt(event->scenePos(), mConfig->eraseSize());
    } else if (mPaintMode == Painter::Select) {
        mCurrentItem = handleSelectionAt(event->scenePos());
        if (mCurrentItem != nullptr) {
            setOffsetForSelectedItems(event->scenePos());
        } else {
            // clicked on empty, show selecting rubber band
            showRubberBand(event->scenePos());
        }
        setCursor();
    } else {
        clearSelection();
        mCurrentItem = mPainterItemFactory->createItem(mPaintMode, event->scenePos());
        mUndoStack->push(new AddCommand(mCurrentItem, this));
        auto textItem = dynamic_cast<PainterText*>(mCurrentItem);
        if (textItem) {
            textItem->setFocus();
        }
    }
}

void PaintArea::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton && mIsEnabled) {
        if (mPaintMode == Painter::Erase) {
            eraseItemAt(event->scenePos(), mConfig->eraseSize());
        } else if (mPaintMode == Painter::Select) {
            if (mRubberBand->isHidden()) {
                moveItems(event->scenePos());
            } else {
                mRubberBand->setGeometry(QRect(mRubberBandOrigin, mapToView(event->scenePos())).normalized());
            }
        } else if (mCurrentItem) {
            mCurrentItem->addPoint(event->scenePos(), mShiftPressed);
        }
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void PaintArea::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() != Qt::LeftButton || !mIsEnabled) {
        return;
    }
    if (mPaintMode == Painter::Select) {
        if (mRubberBand->isHidden()) {
            clearOffsetForSelectedItems();
            mCurrentItem = nullptr;
            setCursor();
        } else {
            hideRubberBand();
        }
    } else {
        if (mPaintMode == Painter::Pen || Painter::Pen == Painter::Marker) {
            PainterPen* path = qgraphicsitem_cast<PainterPen*>(mCurrentItem);
            if (mConfig->smoothPathEnabled() && path != nullptr) {
                path->smoothOut(mConfig->smoothFactor());
            }
        }
        // We enable select first after the item was successfully added to
        // the scene, to prevent selection border around it while drawing.
        if (mCurrentItem) {
            mCurrentItem->setSelectable(true);
        }
    }
    // Inform the MainWindow that something was drawn on the image so the user
    // should be able to save again.
    emit imageChanged();

    QGraphicsScene::mouseReleaseEvent(event);
}

void PaintArea::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
        case Qt::Key_Shift:
            mShiftPressed = true;
            break;
        case Qt::Key_Control:
            mCtrlPressed = true;
            break;
    }
    QGraphicsScene::keyPressEvent(event);
}

void PaintArea::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key()) {
        case Qt::Key_Shift:
            mShiftPressed = false;
            break;
        case Qt::Key_Control:
            mCtrlPressed = false;
            break;
    }
    QGraphicsScene::keyReleaseEvent(event);
}

void PaintArea::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    auto item = findItemAt(event->scenePos());

    ContextMenu contextMenu;

    if (item) {
        clearSelection();
        item->setSelected(true);
        contextMenu.addArrangeMenu();
        contextMenu.addEraseAction();
        contextMenu.addSeparator();
    }
    contextMenu.addCopyAction(item != nullptr);
    contextMenu.addPastAction(mCopiedItems.count() > 0);
    contextMenu.addSeparator();
    contextMenu.addCancelAction();

    connect(&contextMenu, &ContextMenu::bringForwardTriggered, [this]() {
        bringForward();
    });
    connect(&contextMenu, &ContextMenu::bringToFrontTriggered, [this]() {
        bringForward(true);
    });
    connect(&contextMenu, &ContextMenu::sendBackwardTriggered, [this]() {
        sendBackward();
    });
    connect(&contextMenu, &ContextMenu::sendToBackTriggered, [this]() {
        sendBackward(true);
    });
    connect(&contextMenu, &ContextMenu::copyTriggered, this, &PaintArea::copySelectedItems);
    connect(&contextMenu, &ContextMenu::pastTriggered, this, &PaintArea::pastCopiedItems);
    connect(&contextMenu, &ContextMenu::eraseTriggered, this, &PaintArea::eraseSelectedItems);

    contextMenu.exec(event->screenPos());
}

void PaintArea::eraseItemAt(const QPointF& position, int size)
{
    auto item = findItemAt(position, size);
    if (item) {
        eraseSelectedItems();
    }
}

AbstractPainterItem* PaintArea::findItemAt(const QPointF& position, int size)
{
    for (auto item : items()) {
        auto baseItem = qgraphicsitem_cast<AbstractPainterItem*> (item);

        if (baseItem && baseItem->containsRect(position, QSize(size, size))) {
            baseItem->setOffset(position - baseItem->boundingRect().topLeft());
            return baseItem;
        }
//         if (baseItem && baseItem->contains(position)) {
//             baseItem->setOffset(position - baseItem->boundingRect().topLeft());
//             return baseItem;
//         }
    }

    // Have not found any path under location
    return nullptr;
}

/*
 * Moves all selected items to new provided position. Items own offset is taken
 * into account.
 */
void PaintArea::moveItems(const QPointF& position)
{
    if (!selectedItems().isEmpty()) {
        mUndoStack->push(new MoveCommand(this, position));
    }
}

void PaintArea::clearCurrentItem()
{
    if (!mCurrentItem) {
        return;
    }
    if (!mCurrentItem->isValid()) {
        mUndoStack->undo();
        mUndoStack->push(new QUndoCommand(""));
        mUndoStack->undo();
    }
    mCurrentItem = nullptr;
}

/*
 * Returns a new custom cursor based on currently selected paint tool, if the
 * scene is disabled return to default cursor.
 */
QCursor* PaintArea::createCursor()
{
    if (!mIsEnabled) {
        return mCursorFactory->createDefaultCursor();
    }

    return mCursorFactory->createPainterCursor(mPaintMode, mCurrentItem);
}

void PaintArea::setCursor()
{
     QScopedPointer<QCursor> cursor(createCursor());

    // Set cursor on all views, probably just one
    for (auto view : views()) {
        if (mPaintMode == Painter::Select) {
            view->viewport()->unsetCursor();
        } else {
            view->viewport()->setCursor(*cursor);
        }
    }

    // Set move cursor for all movable items
    for (auto item : items()) {
        auto baseItem = qgraphicsitem_cast<AbstractPainterItem*> (item);
        if (baseItem != nullptr) {
            if (mPaintMode == Painter::Select) {
                baseItem->setCursor(*cursor);
            } else {
                baseItem->unsetCursor();
            }
        }
    }
}

QPoint PaintArea::mapToView(const QPointF &point) const
{
    if (views().isEmpty()) {
        return point.toPoint();
    }
    return views().first()->mapFromScene(point);
}

QRectF PaintArea::mapFromView(const QRectF &rect) const
{
    if (views().isEmpty()) {
        return rect.toRect();
    }
    return views().first()->mapToScene(rect.toRect()).boundingRect();
}

AbstractPainterItem* PaintArea::handleSelectionAt(const QPointF& point, int size)
{
    auto item = findItemAt(point, size);

    // no item found at location, clear all selection
    if (!item) {
        clearSelection();
        return nullptr;
    }

    // if item is already not between selected and ctrl is not pressed, clear
    // selection
    if (!selectedItems().contains(item) && !mCtrlPressed) {
        clearSelection();
    }

    // if control is pressed inverse selection, otherwise always select
    if (mCtrlPressed) {
        item->setSelected(!item->isSelected());
    } else {
        item->setSelected(true);
    }
    return item;
}

/*
 * The QGraphicsScene setSelectionArea only accepts paths so we use this
 * function as a workaround and turn the rect into a path.
 */
void PaintArea::setSelectionArea(const QRectF& rect)
{
    QPainterPath path;
    path.addRect(rect);
    QGraphicsScene::setSelectionArea(path, Qt::ContainsItemShape);
}

void PaintArea::setOffsetForSelectedItems(const QPointF& point)
{
    for (auto item : selectedItems()) {
        if (item) {
            item->setOffset(point - item->position());
        }
    }
}

void PaintArea::clearOffsetForSelectedItems()
{
    for (auto item : selectedItems()) {
        if (item) {
            item->setOffset(QPointF());
        }
    }
}


void PaintArea::showRubberBand(const QPointF& point)
{
    if (views().isEmpty()) {
        return;
    }
    mRubberBandOrigin = mapToView(point);
    mRubberBand->setParent(views().first());
    mRubberBand->setGeometry(QRect(mRubberBandOrigin, QSize()));
    mRubberBand->show();
}

void PaintArea::hideRubberBand()
{
    mRubberBand->hide();
    setSelectionArea(mapFromView(mRubberBand->geometry()));
    mRubberBandOrigin = QPoint();
}

/*
 * Bring items forward by swapping their z value. If to front is selected, we
 * will bring the items to the top, otherwise, we bring them only one layer up.
 */
void PaintArea::bringForward(bool toFront)
{
    auto list = new QList<QPair<QGraphicsItem*, QGraphicsItem*>>();
    auto selection = selectedItems();
    for (auto selected : selection) {
        // Loop through all items on the scene
        for (auto item : items(Qt::AscendingOrder)) {
            // Swap with any item that has a bigger z value, except items that
            // are among the selected items, this is because we are not swapping
            // the items here but later in the undo/redo command so the item is
            // not yet bubbling up yet.
            if (item->zValue() > selected->zValue()
                    && !selection.contains(static_cast<AbstractPainterItem*>(item))) {
                list->append(qMakePair(item, selected));
                if (!toFront) {
                    break;
                }
            }
        }
    }
    // Check if we have any swapping, if yes, create a new undo/redo command
    if (!list->isEmpty()) {
        mUndoStack->push(new ReOrderCommand(list));
    }
}

void PaintArea::sendBackward(bool toBack)
{
    auto list = new QList<QPair<QGraphicsItem*, QGraphicsItem*>>();
    auto selection = selectedItems(Qt::AscendingOrder);
    for (auto selected : selection) {
        // Loop through all items on the scene
        for (auto item : items()) {
            // Swap with any item that has a smaller z value, except items that
            // are among the selected items, this is because we are not swapping
            // the items here but later in the undo/redo command so the item is
            // not yet bubbling up yet.
            if (item->zValue() < selected->zValue()
                    && item->zValue() > 0
                    && !selection.contains(static_cast<AbstractPainterItem*>(item))) {
                list->append(qMakePair(item, selected));
                if (!toBack) {
                    break;
                }
            }
        }
    }
    // Check if we have any swapping, if yes, create a new undo/redo command
    if (!list->isEmpty()) {
        mUndoStack->push(new ReOrderCommand(list));
    }
}

void PaintArea::copySelectedItems(const QPointF& pos)
{
    for (auto copiedItem : mCopiedItems) {
        delete copiedItem;
    }
    mCopiedItems.clear();

    for (auto selectedItem : selectedItems(Qt::AscendingOrder)) {
        auto newItem = mPainterItemFactory->createCopyOfItem(selectedItem);
        newItem->setOffset(pos - newItem->position());
        mCopiedItems.append(newItem);
    }
}

void PaintArea::pastCopiedItems(const QPointF& pos)
{
    if (mCopiedItems.count() > 0) {
        mUndoStack->push(new PastCommand(this, pos));
    }
}

void PaintArea::eraseSelectedItems()
{
    mUndoStack->push(new DeleteCommand(this));
}
