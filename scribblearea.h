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

class ScribbleArea : public QGraphicsScene
{
    Q_OBJECT
public:
    ScribbleArea();                                                           /* Constructor                                           */
    enum ScribbleMode          { Paint, Mark, Shape, Erase };                 /* Enum for different scribbe area functions             */
    void                       loadCapture ( QPixmap );                       /* Load a QPixmap based capture image into scribble area */
    QSize                      getAreaSize();                                 /* Returns size of current scribbe area                  */
    void                       setScribbleMode ( enum ScribbleMode );         /* Sets current scribble mode                            */
    ScribbleMode               getScribbleMode();                             /* Returns current scribble mode                         */

protected:
    virtual void	       mousePressEvent ( QGraphicsSceneMouseEvent * ); /* Function called when mouse button down event happens  */
    virtual void	       mouseMoveEvent ( QGraphicsSceneMouseEvent * ); /* Function called when mouse move event happens         */
    virtual void               mouseReleaseEvent ( QGraphicsSceneMouseEvent * ); /* Function called when mouse button was released        */
    virtual void	       keyPressEvent ( QKeyEvent * );
    virtual void	       keyReleaseEvent ( QKeyEvent * );

private:
    QList<QGraphicsPathItem *> mList;                                         /* List holding all paint paths                          */
    QPainterPath              *mCurrentPath;                                  /* Pointer to latest painter path                        */
    QPainterPathStroker        mStroker;                                      /* Stroker used for setting the path width               */
    QPen                       mPen;                                          /* QPen used for drawing the path outline                */
    QBrush                     mBrush;                                        /* QBrush used to fill the drawing path                  */
    bool                       mIsSnapping;
    ScribbleMode               mCurrentScribbleMode;                          /* Current scribble mode                                 */
    void                       addNewPath ( QPointF );                        /* Function called when a new path is created            */
    void                       addToCurrentPath ( QPointF );                  /* Adds a new point to current path                      */
    bool                       erasePath();                                   /* Erases path under mouse                               */
    void                       setupPainter ( enum ScribbleMode );            /* Changing path properties based on drawing tool        */

};

#endif // SCRIBBLEAREA_H
