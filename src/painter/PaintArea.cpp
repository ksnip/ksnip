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
    mPixmap(nullptr),
    mCurrentItem(nullptr),
    mCursor(nullptr),
    mModifierPressed(false),
    mCurrentPaintMode(Pen),
    mCropOffset(QPoint())
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
void PaintArea::loadCapture(QPixmap pixmap)
{
    clear();
    mPixmap = addPixmap(pixmap);
    setSceneRect(0, 0, pixmap.width(), pixmap.height());
    mCropOffset = QPoint(0, 0);
}

// Return scene rect which is the current size of the area
QSize PaintArea::areaSize() const
{
    return sceneRect().size().toSize();
}

void PaintArea::setPaintMode(PaintMode paintMode)
{
    mCurrentPaintMode = paintMode;
    setCursor();
}

/*
 * In order to export the scene as Image we must use a QPainter to draw all scene items to a new
 * image which we can the export. If no pixmap has been loaded return a null image.
 */
QImage PaintArea::exportAsImage()
{
    if (!isValid()) {
        return QImage();
    }

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
    if (mPixmap == nullptr) {
        return false;
    } else {
        return true;
    }
}

/*
 * Crop the capture image to the provided rect and set the scene rect appropriately
 */
void PaintArea::crop(QRect rect)
{
    // Move all painter items to old offset, if this is not done, on the second
    // crop the items are positioned incorrectly bug#27
    for (QGraphicsItem* item : items()) {
        PainterBaseItem* baseItem = qgraphicsitem_cast<PainterBaseItem*> (item);
        if (baseItem) {
            baseItem->moveTo(baseItem->position() - mCropOffset);
        }
    }
    mCropOffset = rect.topLeft() - mCropOffset;

    // Store offset of crop, we will need it in case of cropping again.
    rect.moveTo(mCropOffset);
    setSceneRect(rect);

    mPixmap->setPixmap(mPixmap->pixmap().copy(rect));
    mPixmap->setPos(rect.x(), rect.y());
}

QPoint PaintArea::cropOffset()
{
    return mCropOffset;
}

//
// Protected Functions
//

void PaintArea::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && mIsEnabled) {
        switch (mCurrentPaintMode) {
        case Pen:
            mCurrentItem = new PainterPath(event->scenePos(), KsnipConfig::instance()->pen());
            addItem(mCurrentItem);
            break;
        case Marker:
            mCurrentItem = new PainterPath(event->scenePos(), KsnipConfig::instance()->marker(), true);
            addItem(mCurrentItem);
            break;
        case Rect:
            mCurrentItem = new PainterRect(event->scenePos(), KsnipConfig::instance()->pen());
            addItem(mCurrentItem);
            break;
        case Ellipse:
            mCurrentItem = new PainterEllipse(event->scenePos(), KsnipConfig::instance()->pen());
            addItem(mCurrentItem);
            break;
        case Text:
            // The subtraction of the QPoint is to align the text with the cursor as
            // the IBeam cursor is centered so new text is written at the middle
            // instead of at the top.
            mCurrentItem = new PainterText(event->scenePos() - QPointF(0, 12), KsnipConfig::instance()->pen());
            addItem(mCurrentItem);
            break;
        case Erase:
            eraseItem(event->scenePos());
            break;
        case Move:
            if (grabItem(event->scenePos())) {
                setCursor();
            }
            break;
        default:
            mCurrentItem = new PainterPath(event->scenePos(), KsnipConfig::instance()->pen());
            addItem(mCurrentItem);
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void PaintArea::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton && mIsEnabled) {
        switch (mCurrentPaintMode) {
        case Pen:
        case Marker:
        case Rect:
        case Ellipse:
        case Text:
            mCurrentItem->addPoint(event->scenePos(), mModifierPressed);
            break;
        case Erase:
            eraseItem(event->scenePos());
            break;
        case Move:
            moveItem(event->scenePos());
            break;
        default:
            mCurrentItem->addPoint(event->scenePos());
        }
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void PaintArea::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && mIsEnabled) {
        switch (mCurrentPaintMode) {
        case Pen:
        case Marker:
        case Rect:
        case Ellipse:
        case Text:
            mCurrentItem = nullptr;
            break;
        case Erase:
            break;
        case Move:
            if (mCurrentItem != nullptr) {
                mCurrentItem->setOffset(QPointF());
            }
            mCurrentItem = nullptr;
            setCursor();
            break;
        default:
            mCurrentItem = nullptr;
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

bool PaintArea::eraseItem(QPointF mousePosition)
{
    for (QGraphicsItem* item : items()) {
        PainterBaseItem* baseItem = qgraphicsitem_cast<PainterBaseItem*> (item);
        if (baseItem && baseItem->containsRect(mousePosition , QSize(6, 6))) {
            removeItem(item);
            delete item;
            return true;
        }
    }

    return false;
}

/*
 * Check if any of the paths is under this position, if yes grab it.
 */
bool PaintArea::grabItem(QPointF position)
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

void PaintArea::moveItem(QPointF position)
{
    if (mCurrentItem == nullptr) {
        return;
    }

    mCurrentItem->moveTo(position);
}

/*
 * Set the mouse cursor on all views that show this scene to a specif cursor that represents the
 * currently selected paint tool.
 */
void PaintArea::setCursor()
{
    delete mCursor;
    mCursor = cursor();

    for (QGraphicsItem* item : items()) {
        item->setCursor(*mCursor);
    }
}

/*
 * Returns a new custom cursor based on currently selected paint tool, if the scene is disabled
 * return to default cursor.
 */
QCursor* PaintArea::cursor()
{
    if (!mIsEnabled) {
        return new CustomCursor();
    }
    switch (mCurrentPaintMode) {
    case Marker:
        return new CustomCursor(CustomCursor::Circle,
                                KsnipConfig::instance()->markerColor(),
                                KsnipConfig::instance()->markerSize());
        break;
    case Pen:
    case Rect:
    case Ellipse:
        return new CustomCursor(CustomCursor::Circle,
                                KsnipConfig::instance()->penColor(),
                                KsnipConfig::instance()->penSize());
        break;
    case Text:
        return new QCursor(Qt::IBeamCursor);
        break;
    case Erase:
        return new CustomCursor(CustomCursor::Rect, QColor("white"), 6);
        break;
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
