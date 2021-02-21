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

#ifndef KSNIP_DRAGANDDROPPROCESSOR_H
#define KSNIP_DRAGANDDROPPROCESSOR_H

#include <QObject>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QGraphicsSceneDragDropEvent>
#include <QDrag>
#include <QApplication>
#include <QPixmap>
#include <QList>
#include <QUrl>

#include "IDragContentProvider.h"
#include "src/common/helper/FileUrlHelper.h"
#include "src/common/provider/TempFileProvider.h"

class DragAndDropProcessor : public QObject
{
	Q_OBJECT
public:
	explicit DragAndDropProcessor(IDragContentProvider *dragContentProvider);
	~DragAndDropProcessor() override = default;
	bool eventFilter(QObject *object, QEvent *event) override;

signals:
	void imageDropped(const QString &path);

private:
	IDragContentProvider *mDragContentProvider;
	QPoint mDragStartPosition;

	static bool handleDragEnter(QDragEnterEvent *event);
	static bool handleDragEnter(QGraphicsSceneDragDropEvent *event);
	bool handleDrop(QDropEvent *event);
	bool handleDrop(QGraphicsSceneDragDropEvent *event);
	bool handleDragStart(QMouseEvent *event);
	bool handleDragMove(QMouseEvent *event);
	static QStringList getUrlsFromMimeData(const QMimeData *mimeData);
	static bool isDragStarting(const QMouseEvent *event);
	bool isMinDragDistanceReached(const QMouseEvent *event) const;
	void createDrag(const DragContent &dragContent);
	static QString getPathToDraggedImage(const DragContent &dragContent);
};

#endif //KSNIP_DRAGANDDROPPROCESSOR_H
