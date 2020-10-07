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

#include "ImageAnnotatorMock.h"

QImage ImageAnnotatorMock::image() const
{
	return QImage();
}

QImage ImageAnnotatorMock::imageAt(int index) const
{
	auto ptr =  const_cast<ImageAnnotatorMock*>(this);
	ptr->mImageAtCallCounter.increment(index);
	return mImageAtMap[index];
}

QAction *ImageAnnotatorMock::undoAction()
{
	return nullptr;
}

QAction *ImageAnnotatorMock::redoAction()
{
	return nullptr;
}

QSize ImageAnnotatorMock::sizeHint() const
{
	return {};
}

void ImageAnnotatorMock::showAnnotator()
{

}

void ImageAnnotatorMock::showCropper()
{

}

void ImageAnnotatorMock::showScaler()
{

}

void ImageAnnotatorMock::hide()
{

}

void ImageAnnotatorMock::close()
{

}

bool ImageAnnotatorMock::isVisible() const
{
	return false;
}

QWidget *ImageAnnotatorMock::widget() const
{
	return nullptr;
}

void ImageAnnotatorMock::loadImage(const QPixmap &pixmap)
{

}

int ImageAnnotatorMock::addTab(const QPixmap &pixmap, const QString &title, const QString &toolTip)
{
	return 0;
}

void ImageAnnotatorMock::updateTabInfo(int index, const QString &title, const QString &toolTip)
{

}

void ImageAnnotatorMock::insertImageItem(const QPointF &position, const QPixmap &pixmap)
{

}

void ImageAnnotatorMock::setTextFont(const QFont &font)
{

}

void ImageAnnotatorMock::setNumberFont(const QFont &font)
{

}

void ImageAnnotatorMock::setItemShadowEnabled(bool enabled)
{

}

void ImageAnnotatorMock::setSmoothPathEnabled(bool enabled)
{

}

void ImageAnnotatorMock::setSaveToolSelection(bool enabled)
{

}

void ImageAnnotatorMock::setSmoothFactor(int factor)
{

}

void ImageAnnotatorMock::setTabBarAutoHide(bool enabled)
{

}

void ImageAnnotatorMock::removeTab(int index)
{

}

void ImageAnnotatorMock::setStickers(const QStringList &stickerPaths, bool keepDefault)
{

}

void ImageAnnotatorMock::addTabContextMenuActions(const QList<QAction *> &actions)
{
	mCustomContextMenuActions = actions;
}

int ImageAnnotatorMock::imageAt_callCounter(int index) const
{
	return mImageAtCallCounter.count(index);
}

void ImageAnnotatorMock::imageAt_set(int index, const QImage &image)
{
	mImageAtMap[index] = image;
}

QList<QAction *> ImageAnnotatorMock::tabContextMenuActions_get() const
{
	return mCustomContextMenuActions;
}

void ImageAnnotatorMock::tabContextMenuOpened_emit(int index) const
{
	emit tabContextMenuOpened(index);
}
