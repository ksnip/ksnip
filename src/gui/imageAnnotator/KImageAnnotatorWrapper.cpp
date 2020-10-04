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

#include "KImageAnnotatorWrapper.h"

KImageAnnotatorWrapper::KImageAnnotatorWrapper() :
	mKImageAnnotator(new KImageAnnotator)
{
	connect(mKImageAnnotator, &KImageAnnotator::imageChanged, this, &KImageAnnotatorWrapper::imageChanged);
	connect(mKImageAnnotator, &KImageAnnotator::currentTabChanged, this, &KImageAnnotatorWrapper::currentTabChanged);
	connect(mKImageAnnotator, &KImageAnnotator::tabCloseRequested, this, &KImageAnnotatorWrapper::tabCloseRequested);
	connect(mKImageAnnotator, &KImageAnnotator::tabMoved, this, &KImageAnnotatorWrapper::tabMoved);
	connect(mKImageAnnotator, &KImageAnnotator::tabContextMenuOpened, this, &KImageAnnotatorWrapper::tabContextMenuOpened);
}

KImageAnnotatorWrapper::~KImageAnnotatorWrapper()
{
	delete mKImageAnnotator;
}

QImage KImageAnnotatorWrapper::image() const
{
	return mKImageAnnotator->image();
}

QImage KImageAnnotatorWrapper::imageAt(int index) const
{
	return mKImageAnnotator->imageAt(index);
}

QAction *KImageAnnotatorWrapper::undoAction()
{
	return mKImageAnnotator->undoAction();
}

QAction *KImageAnnotatorWrapper::redoAction()
{
	return mKImageAnnotator->redoAction();
}

QSize KImageAnnotatorWrapper::sizeHint() const
{
	return mKImageAnnotator->sizeHint();
}

void KImageAnnotatorWrapper::showAnnotator()
{
	mKImageAnnotator->showAnnotator();
}

void KImageAnnotatorWrapper::showCropper()
{
	mKImageAnnotator->showCropper();
}

void KImageAnnotatorWrapper::showScaler()
{
	mKImageAnnotator->showScaler();
}

void KImageAnnotatorWrapper::hide()
{
	mKImageAnnotator->hide();
}

void KImageAnnotatorWrapper::close()
{
	mKImageAnnotator->close();
}

bool KImageAnnotatorWrapper::isVisible() const
{
	return mKImageAnnotator->isVisible();
}

QWidget *KImageAnnotatorWrapper::widget() const
{
	return mKImageAnnotator;
}

void KImageAnnotatorWrapper::loadImage(const QPixmap &pixmap)
{
	mKImageAnnotator->loadImage(pixmap);
}

int KImageAnnotatorWrapper::addTab(const QPixmap &pixmap, const QString &title, const QString &toolTip)
{
	return mKImageAnnotator->addTab(pixmap, title, toolTip);
}

void KImageAnnotatorWrapper::updateTabInfo(int index, const QString &title, const QString &toolTip)
{
	mKImageAnnotator->updateTabInfo(index, title, toolTip);
}

void KImageAnnotatorWrapper::insertImageItem(const QPointF &position, const QPixmap &pixmap)
{
	mKImageAnnotator->insertImageItem(position, pixmap);
}

void KImageAnnotatorWrapper::setTextFont(const QFont &font)
{
	mKImageAnnotator->setTextFont(font);
}

void KImageAnnotatorWrapper::setNumberFont(const QFont &font)
{
	mKImageAnnotator->setNumberFont(font);
}

void KImageAnnotatorWrapper::setItemShadowEnabled(bool enabled)
{
	mKImageAnnotator->setItemShadowEnabled(enabled);
}

void KImageAnnotatorWrapper::setSmoothPathEnabled(bool enabled)
{
	mKImageAnnotator->setSmoothPathEnabled(enabled);
}

void KImageAnnotatorWrapper::setSaveToolSelection(bool enabled)
{
	mKImageAnnotator->setSaveToolSelection(enabled);
}

void KImageAnnotatorWrapper::setSmoothFactor(int factor)
{
	mKImageAnnotator->setSmoothFactor(factor);
}

void KImageAnnotatorWrapper::setTabBarAutoHide(bool enabled)
{
	mKImageAnnotator->setTabBarAutoHide(enabled);
}

void KImageAnnotatorWrapper::removeTab(int index)
{
	mKImageAnnotator->removeTab(index);
}

void KImageAnnotatorWrapper::setStickers(const QStringList &stickerPaths, bool keepDefault)
{
	mKImageAnnotator->setStickers(stickerPaths, keepDefault);
}

void KImageAnnotatorWrapper::addTabContextMenuActions(const QList<QAction *> &actions)
{
	mKImageAnnotator->addTabContextMenuActions(actions);
}
