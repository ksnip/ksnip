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

#ifndef KSNIP_DRAGANDDROPHANDLER_H
#define KSNIP_DRAGANDDROPHANDLER_H

#include <QObject>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QGraphicsSceneDragDropEvent>

#include "src/common/helper/FileUrlHelper.h"

class DragAndDropHandler : public QObject
{
	Q_OBJECT
public:
	bool eventFilter(QObject *obj, QEvent *event) override;

signals:
	void imageDropped(const QString &path);

private:
	bool handleDragEnter(QDragEnterEvent *event);
	bool handleDragEnter(QGraphicsSceneDragDropEvent *event);
	bool handleDrop(QDropEvent *event);
	bool handleDrop(QGraphicsSceneDragDropEvent *event);
	QString getUrlFromMimeData(const QMimeData *mimeData) const;
};

#endif //KSNIP_DRAGANDDROPHANDLER_H
