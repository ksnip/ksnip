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

MultiCaptureHandler::MultiCaptureHandler(KImageAnnotator *kImageAnnotator, AbstractToastService *toastService, QWidget *parent) :
	mKImageAnnotator(kImageAnnotator),
	mToastService(toastService),
	mParent(parent),
	mTabStateHandler(new CaptureTabStateHandler)
{
	connect(mKImageAnnotator, &KImageAnnotator::currentTabChanged, mTabStateHandler, &CaptureTabStateHandler::currentTabChanged);
	connect(mKImageAnnotator, &KImageAnnotator::tabMoved, mTabStateHandler, &CaptureTabStateHandler::tabMoved);
	connect(mKImageAnnotator, &KImageAnnotator::imageChanged, mTabStateHandler, &CaptureTabStateHandler::currentTabContentChanged);
	connect(mTabStateHandler, &CaptureTabStateHandler::updateTabInfo, mKImageAnnotator, &KImageAnnotator::updateTabInfo);
}

MultiCaptureHandler::~MultiCaptureHandler()
{
	delete mTabStateHandler;
}

void MultiCaptureHandler::close()
{
	while (mTabStateHandler->count() != 0) {
		if (!discardChanges()) {
			return;
		}
		int currentTabIndex = mTabStateHandler->currentTabIndex();
		removeTab(currentTabIndex);
	}
}

bool MultiCaptureHandler::discardChanges()
{
	auto image = mKImageAnnotator->image();
	auto isUnsaved = !mTabStateHandler->currentTabIsSaved();
	auto pathToSource = mTabStateHandler->currentTabPath();
	auto filename = mTabStateHandler->currentTabFilename();
	CanDiscardOperation operation(mParent, image, isUnsaved, pathToSource, filename, mToastService);
	return operation.execute();
}

void MultiCaptureHandler::removeTab(int currentTabIndex)
{
	mKImageAnnotator->removeTab(currentTabIndex);
	mTabStateHandler->tabRemoved(currentTabIndex);
	emit captureChanged();

	if(mTabStateHandler->count() == 0) {
		emit captureEmpty();
	}
}

bool MultiCaptureHandler::isSaved() const
{
	return mTabStateHandler->currentTabIsSaved();
}

QString MultiCaptureHandler::path() const
{
	return mTabStateHandler->currentTabPath();
}

void MultiCaptureHandler::save(bool isInstant)
{
	auto image = mKImageAnnotator->image();
	SaveOperation operation(mParent, image, isInstant, mTabStateHandler->currentTabPath(), mToastService);
	auto saveResult = operation.execute();
	mTabStateHandler->setCurrentTabSaveState(saveResult);

	emit captureChanged();
}

void MultiCaptureHandler::load(const CaptureDto &capture)
{
	auto path = mPathFromCaptureProvider.pathFrom(capture);
	auto isSaved = PathHelper::isPathValid(path);
	auto filename = mNewCaptureNameProvider.nextName(path);
	auto index = mKImageAnnotator->addImage(capture.screenshot, filename, path);
	mTabStateHandler->add(index, filename, path, isSaved);
	if (capture.isCursorValid()) {
		mKImageAnnotator->insertImageItem(capture.cursor.position, capture.cursor.image);
	}
}
