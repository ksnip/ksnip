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
#include <QtGui>
#include <iostream>

#include "scribblearea.h"

/*
 * Constructor
 */
ScribbleArea::ScribbleArea()
{
    mStroker.setCapStyle( Qt::RoundCap );
    mStroker.setJoinStyle( Qt::RoundJoin  );
    mStroker.setWidth( 5 );
	mCurrentPath = NULL;
    mCurrentScribbleMode = Paint;
}

/*
 * Adds the provided pixmap to the Graphics Scene, this function is used to add
 * the screen capture which functions as background
 */
void ScribbleArea::loadCapture ( QPixmap pixmap )
{
    clear();
    addPixmap(pixmap);
    setSceneRect(0,0, pixmap.width(), pixmap.height());
}

/*
 * Returns the size of the scribble area
 */
QSize ScribbleArea::getAreaSize()
{
    return sceneRect().size().toSize(); 
}

/*
 * Sets the scribble mode which is used to define if we are currently painting,
 * marking, erasing or doing some other operations.
 */
void ScribbleArea::setScribbleMode (ScribbleMode scribbleMode)
{
    mCurrentScribbleMode = scribbleMode;
}

/*
 * Gets current scribble mode
 */
ScribbleArea::ScribbleMode ScribbleArea::getScribbleMode()
{
    return mCurrentScribbleMode;	
}

/*
 * Called when mouse button was pressed, only left mouse button is used, others
 * are silently ignored. Depending on current snipping mode one of several 
 * drawing functions is called.
 */
void ScribbleArea::mousePressEvent ( QGraphicsSceneMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		switch (mCurrentScribbleMode)
		{
		  case Paint:
			addNewPath(event->lastScenePos());
			break;
		  case Mark:
			addNewPath(event->lastScenePos());
			break;
		  case Shape:
			break;
		  case Erase:
			erasePath();
			break;
		}
	}
    QGraphicsScene::mousePressEvent(event);
}

/*
 * Called when mouse is moved, the function works only when the left mouse 
 * button is the only button that was pressed. Depending on the scribbling mode
 * one of several drawing functions is called.
 */
void ScribbleArea::mouseMoveEvent ( QGraphicsSceneMouseEvent* event)
{
	if(event->buttons() == Qt::LeftButton)
	{
		switch (mCurrentScribbleMode)
		{
		  case Paint:
			addToCurrentPath(event->lastScenePos());
			break;
		  case Mark:
			addToCurrentPath(event->lastScenePos());
			break;
		  case Shape:
			break;
		  case Erase:
			erasePath();
			break;
		}
	}
	QGraphicsScene::mouseMoveEvent(event);
}

/*
 * Called when a mouse button was released. When the button that was released is
 * the left mouse button the current paint path is set to NULL.
 */
void ScribbleArea::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->button() != Qt::LeftButton)
		mCurrentPath = NULL;
	
    QGraphicsScene::mouseReleaseEvent(event);
}

/*
 * Creates a new painter path which is added to pointer mCurrentPath, further, 
 * the path is added to the Scene and to the List so it can be tracked later on.
 */
void ScribbleArea::addNewPath(QPointF mousePos)
{
	mCurrentPath = new QPainterPath();
	mCurrentPath->moveTo(mousePos);
	mList.append(addPath(mStroker.createStroke(*mCurrentPath), 
						QPen(Qt::red), 
						QBrush(Qt::red)
	));
}

/*
 * Adds more points to current painter path and re-adds the same path again to 
 * the scene so that the change made is visible.
 */
void ScribbleArea::addToCurrentPath(QPointF mousePos)
{
	if(mCurrentPath == NULL)
	{
	    qCritical("ScribbleArea::addToCurrentPath: Unable to add point to path, current path set to NULL");
		return;
	}
	
	mCurrentPath->lineTo(mousePos);
	mList[mList.count()-1]->setPath(mStroker.createStroke(*mCurrentPath));
}

/*
 * Goes through a list of all paths on the current scene and checks if any of 
 * the paths is currently under the mouse, if yes, it removes this path from the
 * scene and deletes it. The functions checks all paths from the last added to 
 * the first and returns true upon finding a match, otherwise it returns false.
 */
bool ScribbleArea::erasePath()
{
  for(int i = mList.count() - 1 ; i >= 0 ; i--)
  {
	if(mList[i]->isUnderMouse())
	{
	  removeItem(mList[i]);
	  delete mList[i];
	  mList.removeAt(i);
	  return true;
	}
  }
  return false;
}




