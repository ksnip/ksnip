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

#include "DragAndDropProcessor.h"

DragAndDropProcessor::DragAndDropProcessor(IDragContentProvider *dragContentProvider) :
	mDragContentProvider(dragContentProvider)
{

}

bool DragAndDropProcessor::eventFilter(QObject *object, QEvent *event)
{
	if(event->type() == QEvent::DragEnter) {
		return handleDragEnter(dynamic_cast<QDragEnterEvent *>(event));
	} else if(event->type() == QEvent::Drop) {
		return handleDrop(dynamic_cast<QDropEvent *>(event));
	} else if(event->type() == QEvent::GraphicsSceneDrop) {
		return handleDrop(dynamic_cast<QGraphicsSceneDragDropEvent *>(event));
	} else if (event->type() ==  QEvent::GraphicsSceneDragEnter) {
		return handleDragEnter(dynamic_cast<QGraphicsSceneDragDropEvent *>(event));
	} else if (event->type() == QEvent::MouseButtonPress) {
		return handleDragStart(dynamic_cast<QMouseEvent *>(event));
	} else if (event->type() == QEvent::MouseMove) {
		return handleDragMove(dynamic_cast<QMouseEvent *>(event));
	}
	return QObject::eventFilter(object, event);
}

bool DragAndDropProcessor::handleDragEnter(QDragEnterEvent *event)
{
	if (event->mimeData()->hasUrls()) {
		event->acceptProposedAction();
		return true;
	}
	return false;
}

bool DragAndDropProcessor::handleDragEnter(QGraphicsSceneDragDropEvent *event)
{
	if (event->mimeData()->hasUrls()) {
		event->acceptProposedAction();
		return true;
	}
	return false;
}

bool DragAndDropProcessor::handleDrop(QDropEvent *event)
{
	auto paths = getUrlsFromMimeData(event->mimeData());
	for(const auto& path: paths) {
		emit imageDropped(path);
	}

	event->acceptProposedAction();
	return true;
}

bool DragAndDropProcessor::handleDrop(QGraphicsSceneDragDropEvent *event)
{
	auto paths = getUrlsFromMimeData(event->mimeData());
	for(const auto& path: paths) {
		emit imageDropped(path);
	}

	event->acceptProposedAction();
	return true;
}

bool DragAndDropProcessor::handleDragStart(QMouseEvent *event)
{
	if (isDragStarting(event)) {
		mDragStartPosition = event->pos();
		return true;
	}
	return false;
}

bool DragAndDropProcessor::handleDragMove(QMouseEvent *event)
{
	if (isDragStarting(event) && isMinDragDistanceReached(event)) {
		auto dragContent = mDragContentProvider->dragContent();
		if (dragContent.isValid()) {
			createDrag(dragContent);
			return true;
		}
	}
	return false;
}

QStringList DragAndDropProcessor::getUrlsFromMimeData(const QMimeData *mimeData)
{
	QStringList urls;

	for (const auto &url : mimeData->urls()) {
		urls.push_back(FileUrlHelper::toPath(url.toString()));
	}

	return urls;
}

bool DragAndDropProcessor::isDragStarting(const QMouseEvent *event)
{
	return event->buttons() & Qt::LeftButton && event->modifiers() & Qt::ShiftModifier;
}

bool DragAndDropProcessor::isMinDragDistanceReached(const QMouseEvent *event) const
{
	return (event->pos() - mDragStartPosition).manhattanLength() >= QApplication::startDragDistance();
}

void DragAndDropProcessor::createDrag(const DragContent &dragContent)
{
	auto imagePath = getPathToDraggedImage(dragContent);
	auto mimeData = new QMimeData;
	mimeData->setUrls( { QUrl(FileUrlHelper::toFileUrl(imagePath)) });
	mimeData->setData(QLatin1String("text/uri-list"), FileUrlHelper::toFileUrl(imagePath).toLatin1());

	auto icon = QPixmap::fromImage(dragContent.image).scaled(256, 256, Qt::KeepAspectRatio, Qt::FastTransformation);
	auto drag = new QDrag(this);
	drag->setMimeData(mimeData);
	drag->setPixmap(icon);
	drag->exec();
}

QString DragAndDropProcessor::getPathToDraggedImage(const DragContent &dragContent)
{
	QString imagePath;
	if(dragContent.isSaved) {
		imagePath = dragContent.path;
	} else{
		imagePath = TempFileProvider::tempFile();
		if(!dragContent.image.save(imagePath)){
			qWarning("Failed to save temporary dragImage %s for drag and drop operation.", qPrintable(imagePath));
		}
	}
	return imagePath;
}
