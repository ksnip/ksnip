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

#include "MultiCaptureHandler.h"

MultiCaptureHandler::MultiCaptureHandler(KImageAnnotator *kImageAnnotator, IToastService *toastService, QWidget *parent) :
	mKImageAnnotator(kImageAnnotator),
	mToastService(toastService),
	mParent(parent),
	mCaptureChangeListener(nullptr),
	mTabStateHandler(new CaptureTabStateHandler),
	mConfig(KsnipConfigProvider::instance())
{
	connect(mKImageAnnotator, &KImageAnnotator::currentTabChanged, mTabStateHandler, &CaptureTabStateHandler::currentTabChanged);
	connect(mKImageAnnotator, &KImageAnnotator::tabMoved, mTabStateHandler, &CaptureTabStateHandler::tabMoved);
	connect(mKImageAnnotator, &KImageAnnotator::imageChanged, mTabStateHandler, &CaptureTabStateHandler::currentTabContentChanged);
	connect(mTabStateHandler, &CaptureTabStateHandler::updateTabInfo, mKImageAnnotator, &KImageAnnotator::updateTabInfo);

	connect(mKImageAnnotator, &KImageAnnotator::imageChanged, this, &MultiCaptureHandler::captureChanged);
	connect(mKImageAnnotator, &KImageAnnotator::currentTabChanged, this, &MultiCaptureHandler::captureChanged);
	connect(mKImageAnnotator, &KImageAnnotator::tabCloseRequested, this, &MultiCaptureHandler::tabCloseRequested);

	connect(mConfig, &KsnipConfig::annotatorConfigChanged, this, &MultiCaptureHandler::annotatorConfigChanged);

	annotatorConfigChanged();
}

MultiCaptureHandler::~MultiCaptureHandler()
{
	delete mTabStateHandler;
}

bool MultiCaptureHandler::canClose()
{
	while (mTabStateHandler->count() != 0) {
		int index = mTabStateHandler->currentTabIndex();
		if (!discardChanges(index)) {
			return false;
		}
		removeTab(index);
	}
	return true;
}

bool MultiCaptureHandler::canTakeNew()
{
	return true;
}

bool MultiCaptureHandler::discardChanges(int index)
{
	auto image = mKImageAnnotator->imageAt(index);
	auto isUnsaved = !mTabStateHandler->isSaved(index);
	auto pathToSource = mTabStateHandler->path(index);
	auto filename = mTabStateHandler->filename(index);
	CanDiscardOperation operation(mParent, image, isUnsaved, pathToSource, filename, mToastService);
	return operation.execute();
}

void MultiCaptureHandler::removeTab(int currentTabIndex)
{
	mKImageAnnotator->removeTab(currentTabIndex);
	mTabStateHandler->tabRemoved(currentTabIndex);
	captureChanged();

	if(mTabStateHandler->count() == 0) {
		mKImageAnnotator->hide();
		captureEmpty();
	}
}

bool MultiCaptureHandler::isSaved() const
{
	return mTabStateHandler->isSaved(mTabStateHandler->currentTabIndex());
}

QString MultiCaptureHandler::path() const
{
	return mTabStateHandler->path(mTabStateHandler->currentTabIndex());
}

void MultiCaptureHandler::saveAs()
{
	saveAt(mTabStateHandler->currentTabIndex(), false);
}

void MultiCaptureHandler::save()
{
	saveAt(mTabStateHandler->currentTabIndex(), true);
}

void MultiCaptureHandler::saveAt(int index, bool isInstant)
{
	auto image = mKImageAnnotator->imageAt(index);
	SaveOperation operation(mParent, image, isInstant, mTabStateHandler->path(index), mToastService);
	auto saveResult = operation.execute();
	mTabStateHandler->setSaveState(index, saveResult);
	captureChanged();
}

void MultiCaptureHandler::load(const CaptureDto &capture)
{
	auto path = mPathFromCaptureProvider.pathFrom(capture);
	auto isSaved = PathHelper::isPathValid(path);
	auto filename = mNewCaptureNameProvider.nextName(path);
	auto index = mKImageAnnotator->addTab(capture.screenshot, filename, path);
	mTabStateHandler->add(index, filename, path, isSaved);
	if (capture.isCursorValid()) {
		mKImageAnnotator->insertImageItem(capture.cursor.position, capture.cursor.image);
	}
}

void MultiCaptureHandler::tabCloseRequested(int index)
{
	if (!discardChanges(index)) {
		return;
	}
	removeTab(index);
}

QImage MultiCaptureHandler::image() const
{
	return mKImageAnnotator->image();
}

void MultiCaptureHandler::insertImageItem(const QPointF &pos, const QPixmap &pixmap)
{
	mKImageAnnotator->insertImageItem(pos, pixmap);
}

void MultiCaptureHandler::addListener(ICaptureChangeListener *captureChangeListener)
{
	mCaptureChangeListener = captureChangeListener;
}

void MultiCaptureHandler::captureChanged()
{
	if(mCaptureChangeListener != nullptr) {
		mCaptureChangeListener->captureChanged();
	}
}

void MultiCaptureHandler::captureEmpty()
{
	if(mCaptureChangeListener != nullptr) {
		mCaptureChangeListener->captureEmpty();
	}
}

void MultiCaptureHandler::annotatorConfigChanged()
{
	mKImageAnnotator->setTabBarAutoHide(mConfig->autoHideTabs());
}
