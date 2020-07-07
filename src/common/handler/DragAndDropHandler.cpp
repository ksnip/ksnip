/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "DragAndDropHandler.h"

bool DragAndDropHandler::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::DragEnter) {
		return handleDragEnter(dynamic_cast<QDragEnterEvent *>(event));
	} else if(event->type() == QEvent::Drop) {
		return handleDrop(dynamic_cast<QDropEvent *>(event));
	} else if(event->type() == QEvent::GraphicsSceneDrop) {
		return handleDrop(dynamic_cast<QGraphicsSceneDragDropEvent *>(event));
	} else if (event->type() ==  QEvent::GraphicsSceneDragEnter) {
		return handleDragEnter(dynamic_cast<QGraphicsSceneDragDropEvent *>(event));
	}
	return QObject::eventFilter(obj, event);
}

bool DragAndDropHandler::handleDragEnter(QDragEnterEvent *event)
{
	if (event->mimeData()->hasUrls()) {
		event->acceptProposedAction();
		return true;
	}
	return false;
}

bool DragAndDropHandler::handleDragEnter(QGraphicsSceneDragDropEvent *event)
{
	if (event->mimeData()->hasUrls()) {
		event->acceptProposedAction();
		return true;
	}
	return false;
}

bool DragAndDropHandler::handleDrop(QDropEvent *event)
{
	auto path = getUrlFromMimeData(event->mimeData());
	event->acceptProposedAction();
	emit imageDropped(path);
	return true;
}

bool DragAndDropHandler::handleDrop(QGraphicsSceneDragDropEvent *event)
{
	auto path = getUrlFromMimeData(event->mimeData());
	event->acceptProposedAction();
	emit imageDropped(path);
	return true;
}

QString DragAndDropHandler::getUrlFromMimeData(const QMimeData *mimeData) const
{
	return FileUrlHelper::parse(mimeData->urls().first().toString());
}