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

PaintArea::PaintArea() : QGraphicsScene(),
    mScreenshot(nullptr),
    mCurrentItem(nullptr),
    mCursor(nullptr),
    mModifierPressed(false),
    mPaintMode(Pen),
    mUndoStack(new QUndoStack(this))
{
    // Connect to update signal so that we are informed any time the config changes, we use that to
    // set the correct mouse cursor
    connect(KsnipConfig::instance(), SIGNAL(painterUpdated()), this, SLOT(setCursor()));
}

//
// Public Functions
//

/*
 * Load new captured image and add it to the scene and set the scene size to the size of the loaded
 * image.
 */
void PaintArea::loadCapture(const QPixmap& pixmap)
{
    clearItem();
    mUndoStack->clear();
    clear();
    mScreenshot = addPixmap(pixmap);
    setSceneRect(pixmap.rect());
}

/*
 * Makes all parent view resize their parent widgets to fit the scene with some
 * additional space around it.
 */
void PaintArea::fitViewToParent()
{
    for (QGraphicsView* view : views()) {
        view->parentWidget()->resize(areaSize() + QSize(100, 150));
    }
}

// Return scene rect which is the current size of the area
QSize PaintArea::areaSize() const
{
    return sceneRect().size().toSize();
}

void PaintArea::setPaintMode(const PaintMode& paintMode)
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
 * In order to export the scene as Image we must use a QPainter to draw all scene items to a new
 * image which we can the export. If no pixmap has been loaded return a null image.
 */
QImage PaintArea::exportAsImage()
{
    if (!isValid()) {
        qWarning("PainteArea::exportAsImage: Unable to export image, image invalid.");
        return QImage();
    }

    QImage image(sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    render(&painter);
    return image;
}

void PaintArea::setIsEnabled(const bool& enabled)
{
    mIsEnabled = enabled;
    setCursor();
}

bool PaintArea::isEnabled() const
{
    return mIsEnabled;
}

/*
 * The scene is only valid if a pixmap has been loaded
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
 * Crop the capture image to the provided rect and set the scene rect appropriately
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
QAction* PaintArea::createUndoAction()
{
    return mUndoStack->createUndoAction(this, tr("Undo"));
}

/*
 * Same as createUndoAction
 */
QAction* PaintArea::createRedoAction()
{
    return mUndoStack->createRedoAction(this, tr("Redo"));
}

//
// Protected Functions
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

        KsnipConfig* config = KsnipConfig::instance();
        switch (mPaintMode) {
        case Pen:
            mCurrentItem = new PainterPath(event->scenePos(), config->pen());
            mUndoStack->push(new AddCommand(mCurrentItem, this));
            break;
        case Marker:
            mCurrentItem = new PainterPath(event->scenePos(), config->marker(), true);
            mUndoStack->push(new AddCommand(mCurrentItem, this));
            break;
        case Rect:
            mCurrentItem = new PainterRect(event->scenePos(),
                                           config->rect(),
                                           config->rectFill());
            mUndoStack->push(new AddCommand(mCurrentItem, this));
            break;
        case Ellipse:
            mCurrentItem = new PainterEllipse(event->scenePos(),
                                              config->ellipse(),
                                              config->ellipseFill());
            mUndoStack->push(new AddCommand(mCurrentItem, this));
            break;
        case Text:
            // The subtraction of the QPoint is to align the text with the cursor as
            // the IBeam cursor is centered so new text is written at the middle
            // instead of at the top.
            mCurrentItem = new PainterText(event->scenePos() - QPointF(0, 12),
                                           config->text(), config->textFont());
            mUndoStack->push(new AddCommand(mCurrentItem, this));
            break;
        case Erase:
            eraseItem(event->scenePos(), config->eraseSize());
            break;
        case Move:
            if (grabItem(event->scenePos())) {
                setCursor();
            }
            break;
        }
    }

    QGraphicsScene::mousePressEvent(event);
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
                mCurrentItem->addPoint(event->scenePos(), mModifierPressed);
            }
            break;
        case Erase:
            eraseItem(event->scenePos(), KsnipConfig::instance()->eraseSize());
            break;
        case Move:
            moveItem(event->scenePos());
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
        case Marker: {
            PainterPath* path;
            KsnipConfig* config = KsnipConfig::instance();
            if (config->smoothPath() &&
                    (path = qgraphicsitem_cast<PainterPath*> (mCurrentItem))) {
                path->smoothOut(config->smoothFactor());
            }
            break;
        }
        case Rect:
        case Ellipse:
        case Text:
        case Erase:
            break;
        case Move:
            if (mCurrentItem != nullptr) {
                mCurrentItem->setOffset(QPointF());
            }
            mCurrentItem = nullptr;
            setCursor();
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
    if (event->key() == Qt::Key_Shift) {
        mModifierPressed = true;
    }
    QGraphicsScene::keyPressEvent(event);
}

void PaintArea::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Shift) {
        mModifierPressed = false;
    }

    QGraphicsScene::keyReleaseEvent(event);
}

bool PaintArea::eraseItem(const QPointF& position, const int& size)
{
    for (QGraphicsItem* item : items()) {
        PainterBaseItem* baseItem = qgraphicsitem_cast<PainterBaseItem*> (item);
        if (baseItem && baseItem->containsRect(position , QSize(size, size))) {
            mUndoStack->push(new DeleteCommand(baseItem, this));
            return true;
        }
    }

    return false;
}

/*
 * Check if any of the paths is under this position, if yes grab it.
 */
bool PaintArea::grabItem(const QPointF& position)
{
    for (QGraphicsItem* item : items()) {
        mCurrentItem = qgraphicsitem_cast<PainterBaseItem*> (item);

        if (mCurrentItem && mCurrentItem->containsRect(position, QSize(10, 10))) {
            mCurrentItem->setOffset(position - mCurrentItem->boundingRect().topLeft());
            return true;
        }
    }

    // Have not found any path under location
    mCurrentItem = nullptr;
    return false;
}

void PaintArea::moveItem(const QPointF& position)
{
    if (mCurrentItem == nullptr) {
        return;
    }
    mUndoStack->push(new MoveCommand(mCurrentItem, position));
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
    KsnipConfig* config = KsnipConfig::instance();
    switch (mPaintMode) {
    case Pen:
        return new CustomCursor(CustomCursor::Circle,
                                config->penColor(),
                                config->penSize());
    case Marker:
        return new CustomCursor(CustomCursor::Circle,
                                config->markerColor(),
                                config->markerSize());
    case Rect:
        return new CustomCursor(CustomCursor::Circle,
                                config->rectColor(),
                                config->rectSize());
    case Ellipse:
        return new CustomCursor(CustomCursor::Circle,
                                config->ellipseColor(),
                                config->ellipseSize());
    case Text:
        return new QCursor(Qt::IBeamCursor);
    case Erase:
        return new CustomCursor(CustomCursor::Rect, QColor("white"), config->eraseSize());
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

    for (QGraphicsView *view : views()){
        view->setCursor(*mCursor);
    }
}
