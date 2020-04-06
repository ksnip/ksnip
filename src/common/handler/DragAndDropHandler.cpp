/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "DragAndDropHandler.h"

bool DragAndDropHandler::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::DragEnter) {
		handleDragEnter(dynamic_cast<QDragEnterEvent *>(event));
	} else if(event->type() == QEvent::Drop) {
		handleDrop(dynamic_cast<QDropEvent *>(event));
	} else if(event->type() == QEvent::GraphicsSceneDrop) {
		handleDrop(dynamic_cast<QGraphicsSceneDragDropEvent *>(event));
	} else if (event->type() ==  QEvent::GraphicsSceneDragEnter) {
		handleDragEnter(dynamic_cast<QGraphicsSceneDragDropEvent *>(event));
	}
	return QObject::eventFilter(obj, event);
}

void DragAndDropHandler::handleDragEnter(QDragEnterEvent *event)
{
	if (event->mimeData()->hasUrls()) {
		event->acceptProposedAction();
	}
}

void DragAndDropHandler::handleDragEnter(QGraphicsSceneDragDropEvent *event)
{
	if (event->mimeData()->hasUrls()) {
		event->acceptProposedAction();
	}
}

void DragAndDropHandler::handleDrop(QDropEvent *event)
{
	auto path = getUrlFromMimeData(event->mimeData());
	event->acceptProposedAction();
	emit imageDropped(path);
}

void DragAndDropHandler::handleDrop(QGraphicsSceneDragDropEvent *event)
{
	auto path = getUrlFromMimeData(event->mimeData());
	event->acceptProposedAction();
	emit imageDropped(path);
}

QString DragAndDropHandler::getUrlFromMimeData(const QMimeData *mimeData) const
{
	return mimeData->urls().first().toString().remove("file://");
}