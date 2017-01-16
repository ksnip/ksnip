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

#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QtGui>
#include <QGraphicsScene>

#include "PaintStroke.h"
#include "src/widgets/CustomCursor.h"

class PaintArea : public QGraphicsScene
{
    Q_OBJECT
public:
    PaintArea();
    enum PaintMode { Pen, Marker, Erase, Move };
    void loadCapture ( QPixmap pixmap );
    QSize areaSize();
    void setPaintMode ( PaintMode paintMode );
    QImage exportAsImage();
    void setIsEnabled ( bool enabled );
    bool isEnabled();
    bool isValid();
    void crop ( QRect rect );
    QPoint getCropOffset();

signals:
    void imageChanged();

protected:
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent *event );
    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent *event );
    virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent *event );
    virtual void keyPressEvent ( QKeyEvent *event );
    virtual void keyReleaseEvent ( QKeyEvent *event );

private:
    bool                 mIsEnabled;
    QGraphicsPixmapItem *mPixmap;
    PaintStroke         *mCurrentPaintStroke;
    QCursor             *mCursor;
    bool                 mIsSnapping;
    PaintMode            mCurrentPaintMode;
    QPointF              mMoveOffset;
    QPoint               mCropOffset;

    void addNewPaintStroke ( QPointF position );
    void addToCurrentPaintStroke ( QPointF position );
    bool erasePaintStroke ( QPointF position );
    bool getObjectForMove ( QPointF position );
    void moveObject( QPointF position );
    QCursor *cursor();

private slots:
    void setCursor();
};

#endif // SCRIBBLEAREA_H
