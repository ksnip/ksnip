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

ScribbleArea::ScribbleArea()
{
    mStroker.setCapStyle( Qt::RoundCap );
    mStroker.setJoinStyle( Qt::RoundJoin  );
    mStroker.setWidth( 5 );
}

void ScribbleArea::loadCapture ( QPixmap pixmap)
{
    clear();
    addPixmap(pixmap);
    setSceneRect(0,0, pixmap.width(), pixmap.height());
}

QSize ScribbleArea::getSize()
{
    return sceneRect().size().toSize(); 
}

void ScribbleArea::mousePressEvent ( QGraphicsSceneMouseEvent* event)
{
    if(!mErase)
    {
	mCurrentPath = new QPainterPath();
	mCurrentPath->moveTo(event->lastScenePos());
	mList.append(addPath(mStroker.createStroke(*mCurrentPath), QPen(Qt::red), QBrush(Qt::red)));
    }
    QGraphicsScene::mousePressEvent(event);
}

void ScribbleArea::mouseMoveEvent ( QGraphicsSceneMouseEvent* event)
{ 
      if(!mErase)
      {
	  mCurrentPath->lineTo(event->lastScenePos());
	  mList[mList.count()-1]->setPath(mStroker.createStroke(*mCurrentPath));
      }
      else
      {
	  for(int i=0; i < mList.count(); i++)
	  {
	      if(mList[i]->isUnderMouse())
	      {
		  removeItem(mList[i]);
		  delete mList[i];
		  mList.removeAt(i);
	      }
	  }
      }    
      QGraphicsScene::mouseMoveEvent(event);
}

void ScribbleArea::setErase (bool erase)
{
    mErase = erase;

}



