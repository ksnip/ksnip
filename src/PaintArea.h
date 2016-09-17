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

#include <QGraphicsScene>

#include "PaintStroke.h"

class PaintArea : public QGraphicsScene
{
    Q_OBJECT
public:
    PaintArea();
    enum PaintMode { Pen, Marker, Erase };
    void loadCapture ( QPixmap );
    QSize getAreaSize();
    void setPaintMode ( enum PaintMode );
    PaintMode getPaintMode();
    QImage exportAsImage();

signals:
    void imageChanged();

protected:
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * );
    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * );
    virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * );
    virtual void keyPressEvent ( QKeyEvent * );
    virtual void keyReleaseEvent ( QKeyEvent * );

private:
    PaintStroke *mCurrentPaintStroke;
    QPen        *mPen;
    QPen        *mMarker;
    bool         mIsSnapping;
    PaintMode    mCurrentPaintMode;
    void addNewPaintStroke ( QPointF );
    void addToCurrentPaintStroke ( QPointF );
    bool erasePaintStroke ( QPointF );
};

#endif // SCRIBBLEAREA_H
