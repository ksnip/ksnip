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
*
*/
#include "PaintArea.h"
#include "src/backend/KsnipConfig.h"
#include "src/widgets/CaptureView.h"

#include <iostream>

PaintArea::PaintArea() : QGraphicsScene(),
    mScreenshot(nullptr),
    mCurrentItem(nullptr),
    mRubberBand(nullptr),
    mCursor(nullptr),
    mShiftPressed(false),
    mPaintMode(Pen),
    mUndoStack(new QUndoStack(this)),
    mUndoAction(nullptr),
    mRedoAction(nullptr),
    mConfig(KsnipConfig::instance())
{
    // Connect to update signal so that we are informed any time the config
    // changes, we use that to set the correct mouse cursor.
    connect(mConfig, &KsnipConfig::painterUpdated, this, &PaintArea::setCursor);
}

//
// Public Methods
//

/*
 * Load new captured image and add it to the scene and set the scene size to the
 * size of the loaded image.
 */
void PaintArea::loadCapture(const QPixmap& pixmap)
{
    clearItem();
    mUndoStack->clear();
    clear();
    clearSelection();
    PainterBaseItem::resetOrder();
    mScreenshot = addPixmap(pixmap);
    setSceneRect(pixmap.rect());
}

/*
 * Makes all parent view resize their parent widgets to fit the scene with some
 * additional space around it.
 */
void PaintArea::fitViewToParent()
{
    for (auto view : views()) {
        view->parentWidget()->resize(areaSize() + QSize(100, 150));
    }
}

// Return scene rect which is the current size of the area
QSize PaintArea::areaSize() const
{
    return sceneRect().size().toSize();
}

void PaintArea::setPaintMode(PaintMode paintMode)
{
    if (mPaintMode == paintMode) {
        return;
    }

    mPaintMode = paintMode;

    clearItem();
    setCursor();
}

PaintArea::PaintMode PaintArea::paintMode() const
{
    return mPaintMode;
}

/*
 * In order to export the scene as Image we must use a QPainter to draw all
 * scene items to a new image which we can the export. If no pixmap has been
 * loaded return a null image.
 */
QImage PaintArea::exportAsImage()
{
    if (!isValid()) {
        qWarning("PainteArea::exportAsImage: Unable to export image, image invalid.");
        return QImage();
    }
    // Prevent saving selection color
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

/*
 * The scene is only valid if a pixmap has been loaded.
 */
bool PaintArea::isValid() const
{
    if (mScreenshot == nullptr) {
        return false;
    } else {
        return true;
    }
}

/*
 * Return true if the user is currently editing a text item, otherwise returns
 * false
 */
bool PaintArea::isTextEditing() const
{
    if (mCurrentItem && mCurrentItem->ItemShape() == PainterBaseItem::Text) {
        if (static_cast<PainterText*>(mCurrentItem)->isEditable()) {
            return true;
        }
    }
    return false;
}

/*
 * Crop the capture image to the provided rect and set the scene rect
 * appropriately.
 */
void PaintArea::crop(const QRectF& rect)
{
    mUndoStack->push(new CropCommand(mScreenshot, rect, this));
}

QPointF PaintArea::cropOffset() const
{
    return mScreenshot->offset();
}

/*
 * Creates a pointer to the undo action so that it can be directly used without
 * creating custom functions and slots.
 */
QAction* PaintArea::getUndoAction()
{
    if (!mUndoAction) {
        mUndoAction = mUndoStack->createUndoAction(this, tr("Undo"));
    }
    return mUndoAction;
}

/*
 * Same as createUndoAction
 */
QAction* PaintArea::getRedoAction()
{
    if (!mRedoAction) {
        mRedoAction = mUndoStack->createRedoAction(this, tr("Redo"));
    }
    return mRedoAction;
}

QList<PainterBaseItem*> PaintArea::selectedItems(Qt::SortOrder order) const
{
    QList<PainterBaseItem*> list;
    for (auto item : items(order)) {
        auto base = static_cast<PainterBaseItem*>(item);
        if (base && base->isSelected()) {
            list.append(base);
        }
    }
    return list;
}

//
// Protected Methods
//

void PaintArea::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (!mIsEnabled) {
        return;
    }

    // When clicked with any button somewhere on the scene, the paint item
    // looses focus so we check if the paint item is valid at that time, if not
    // we remove it. Mostly used to check if empty text item was left on the
    // scene.
    clearItem();

    if (event->button() == Qt::LeftButton) {

        switch (mPaintMode) {
        case Pen:
            clearSelection();
            mCurrentItem = new PainterPath(event->scenePos(), mConfig->pen());
            mUndoStack->push(new AddCommand(mCurrentItem, this));
            break;
        case Marker:
            clearSelection();
            mCurrentItem = new PainterPath(event->scenePos(), mConfig->marker(), true);
            mUndoStack->push(new AddCommand(mCurrentItem, this));
            break;
        case Rect:
            clearSelection();
            mCurrentItem = new PainterRect(event->scenePos(),
                                           mConfig->rect(),
                                           mConfig->rectFill());
            mUndoStack->push(new AddCommand(mCurrentItem, this));
            break;
        case Ellipse:
            clearSelection();
            mCurrentItem = new PainterEllipse(event->scenePos(),
                                              mConfig->ellipse(),
                                              mConfig->ellipseFill());
            mUndoStack->push(new AddCommand(mCurrentItem, this));
            break;
        case Text:
            clearSelection();
            // The subtraction of the QPoint is to align the text with the cursor as
            // the IBeam cursor is centered so new text is written at the middle
            // instead of at the top.
            mCurrentItem = new PainterText(event->scenePos() - QPointF(0, 12),
                                           mConfig->text(), mConfig->textFont());
            mUndoStack->push(new AddCommand(mCurrentItem, this));
            mCurrentItem->setFocus();
            break;
        case Erase:
            clearSelection();
            eraseItemAt(event->scenePos(), mConfig->eraseSize());
            break;
        case Move:
            mCurrentItem = selectItemAt(event->scenePos());
            setCursor();
            for (auto item : selectedItems()) {
                if (item) {
                    item->setOffset(event->scenePos() - item->position());
                }
            }
            break;
        case Select:
            // We need the view as parent for the rubberband, can't proceed
            // without it
            if (views().isEmpty()) {
                break;
            }
            mRubberBandOrigin = mapToView(event->scenePos());
            if (!mRubberBand) {
                // As the QGraphicsScene doesn't inherit QWidget we can't use it
                // as parent so we use the hosting view.
                mRubberBand = new QRubberBand(QRubberBand::Rectangle, views().first());
            }
            mRubberBand->setGeometry(QRect(mRubberBandOrigin, QSize()));
            mRubberBand->show();
            break;
        }
    }

    // Not propagating the mouse press event as it overwrites our select
    // behavior and selects always items when we click on them.
//     QGraphicsScene::mousePressEvent(event);
}

void PaintArea::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton && mIsEnabled) {
        switch (mPaintMode) {
        case Pen:
        case Marker:
        case Rect:
        case Ellipse:
        case Text:
            if (mCurrentItem) {
                mCurrentItem->addPoint(event->scenePos(), mShiftPressed);
            }
            break;
        case Erase:
            eraseItemAt(event->scenePos(), mConfig->eraseSize());
            break;
        case Move:
            moveItems(event->scenePos());
            break;
        case Select:
            if (mRubberBand) {
                mRubberBand->setGeometry(QRect(mRubberBandOrigin,
                                               mapToView(event->scenePos())).normalized());
            }
            break;
        }
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void PaintArea::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && mIsEnabled) {
        switch (mPaintMode) {
        case Pen:
        case Marker:
            PainterPath* path;
            if (mConfig->smoothPath() &&
                    (path = qgraphicsitem_cast<PainterPath*> (mCurrentItem))) {
                path->smoothOut(mConfig->smoothFactor());
            }
        case Rect:
        case Ellipse:
        case Text:
            // We enable select first after the item was successfully added to
            // the scene, to prevent selection border around it while drawing.
            if (mCurrentItem) {
                mCurrentItem->setSelectable(true);
            }
            break;
        case Erase:
            break;
        case Move:
            for (auto item : selectedItems()) {
                if (item) {
                    item->setOffset(QPointF());
                }
            }
            mCurrentItem = nullptr;
            setCursor();
            break;
        case Select:
            if (mRubberBandOrigin == mapToView(event->scenePos())) {
                if (!mCtrlPressed) {
                    clearSelection();
                }
                // Check if we have clicked on an item, if yes, select it if its
                // not selected, otherwise, unselect it.
                mCurrentItem = findItemAt(event->scenePos());
                if (mCurrentItem) {
                    if (mCurrentItem->isSelected()) {
                        mCurrentItem->setSelected(false);
                    } else {
                        mCurrentItem->setSelected(true);
                    }
                }
            } else {
                if (mRubberBand) {
                    mRubberBand->hide();
                    setSelectionArea(mapFromView(mRubberBand->geometry()));
                }
            }
            mRubberBandOrigin = QPoint();
            mCurrentItem = nullptr;
            break;
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

/*
 * Called when the user requests a context menu on one of the painter items.
 */
void PaintArea::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    // Check if the user has clicked on any item and only show context menu if
    // an item was clicked. The clicked item is selected.
    auto item = selectItemAt(event->scenePos());
    if (!item) {
        return;
    }

    // Create context menu. Cancel at the end is only for hiding the menu
    QMenu contextMenu;
    QMenu* arrangeSubMenu = contextMenu.addMenu(tr("Arrange"));
    QAction* bringForwardAction = arrangeSubMenu->addAction(tr("Bring Forward"));
    QAction* bringToFrontAction = arrangeSubMenu->addAction(tr("Bring to Front"));
    QAction* sentBackwardAction = arrangeSubMenu->addAction(tr("Sent Backward"));
    QAction* sentToBackAction = arrangeSubMenu->addAction(tr("Sent to Back"));
    contextMenu.addSeparator();
    contextMenu.addAction(tr("Cancel"));

    // Show context menu and wait for it to finish, grab the action that was
    // clicked.
    QAction* selectedAction = contextMenu.exec(event->screenPos());

    if (selectedAction == bringForwardAction) {
        bringForward();
    } else if (selectedAction == bringToFrontAction) {
        bringForward(true);
    } else if (selectedAction == sentBackwardAction) {
        sendBackward();
    } else if (selectedAction == sentToBackAction) {
        sendBackward(true);
    }
}

bool PaintArea::eraseItemAt(const QPointF& position, int size)
{
    for (auto item : items()) {
        auto baseItem = qgraphicsitem_cast<PainterBaseItem*> (item);
        if (baseItem && baseItem->containsRect(position , QSize(size, size))) {
            mUndoStack->push(new DeleteCommand(baseItem, this));
            return true;
        }
    }
    return false;
}

/*
 * Check if any item is under this position, if yes, sets offset of this item 
 * and returns pointer to this to it.
 */
PainterBaseItem* PaintArea::findItemAt(const QPointF& position)
{
    for (auto item : items()) {
        auto baseItem = qgraphicsitem_cast<PainterBaseItem*> (item);

        if (baseItem && baseItem->containsRect(position, QSize(10, 10))) {
            baseItem->setOffset(position - baseItem->boundingRect().topLeft());
            return baseItem;
        }
    }

    // Have not found any path under location
    return nullptr;
}

void PaintArea::moveItems(const QPointF& position)
{
    if (selectedItems().count() > 0) {
        mUndoStack->push(new MoveCommand(this, position));
    }
}

void PaintArea::clearItem()
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
QCursor* PaintArea::cursor()
{
    if (!mIsEnabled) {
        return new CustomCursor();
    }
    switch (mPaintMode) {
    case Pen:
        return new CustomCursor(CustomCursor::Circle,
                                mConfig->penColor(),
                                mConfig->penSize());
    case Marker:
        return new CustomCursor(CustomCursor::Circle,
                                mConfig->markerColor(),
                                mConfig->markerSize());
    case Rect:
        return new CustomCursor(CustomCursor::Circle,
                                mConfig->rectColor(),
                                mConfig->rectSize());
    case Ellipse:
        return new CustomCursor(CustomCursor::Circle,
                                mConfig->ellipseColor(),
                                mConfig->ellipseSize());
    case Text:
        return new QCursor(Qt::IBeamCursor);
    case Erase:
        return new CustomCursor(CustomCursor::Rect, QColor("white"), mConfig->eraseSize());
    case Move:
        if (mCurrentItem == nullptr) {
            return new QCursor(Qt::OpenHandCursor);
        } else {
            return new QCursor(Qt::ClosedHandCursor);
        }
        break;
    default:
        return new CustomCursor();
    }
}

/*
 * Set the mouse cursor on all views that show this scene to a specif cursor
 * that represents the currently selected paint tool.
 */
void PaintArea::setCursor()
{
    delete mCursor;
    mCursor = cursor();

    for (auto view : views()) {
        view->setCursor(*mCursor);
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

/*
 * Checks the scene at the specified location for any item, if it doesn't find
 * one, unselects all, if it finds an item it checks if the items is already
 * among the selected items, if yes, does nothing, if not, unselects all and
 * selects only this item. Leaves mCurrentItem pointing to the found item.
 */
PainterBaseItem* PaintArea::selectItemAt(const QPointF& point)
{
    auto item = findItemAt(point);
    if (!item) {
        clearSelection();
        return nullptr;
    }

    if (!selectedItems().contains(item)) {
        clearSelection();
    }
    item->setSelected(true);
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
                    && !selection.contains((PainterBaseItem*)item)) {
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
                    && !selection.contains((PainterBaseItem*)item)) {
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

