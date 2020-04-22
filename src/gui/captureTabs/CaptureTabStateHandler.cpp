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

#include "CaptureTabStateHandler.h"

CaptureTabStateHandler::CaptureTabStateHandler() :
	mCurrentTabIndex(-1),
	mCachedCurrentTabState(nullptr)
{
}

void CaptureTabStateHandler::add(int index, const QString &filename, const QString &path, bool isSaved)
{
	auto newState = QSharedPointer<CaptureTabState>(new CaptureTabState(index, filename, path, isSaved));
	mCaptureTabStates.append(newState);
	updateCurrentTabInfo();
}

bool CaptureTabStateHandler::currentTabIsSaved()
{
	auto currentTabState = getCurrentTabStateFromCache();
	return currentTabState.isNull() ? true : currentTabState->isSaved;
}

QString CaptureTabStateHandler::currentTabPath()
{
	auto currentTabState = getCurrentTabStateFromCache();
	return currentTabState.isNull() ? QString() : currentTabState->path;
}

QString CaptureTabStateHandler::currentTabFilename()
{
	auto currentTabState = getCurrentTabStateFromCache();
	return currentTabState.isNull() ? QString() : currentTabState->filename;
}

void CaptureTabStateHandler::setCurrentTabSaveState(const SaveResultDto &saveResult)
{
	auto currentTabState = getCurrentTabStateFromCache();
	if (!currentTabState.isNull()) {
		currentTabState->isSaved = saveResult.isSuccessful;
		currentTabState->path = saveResult.path;
		currentTabState->filename = PathHelper::extractFilename(saveResult.path);
		updateCurrentTabInfo();
	}
}

void CaptureTabStateHandler::tabMoved(int fromIndex, int toIndex)
{
	for (auto& state : mCaptureTabStates) {
		if(state->index == fromIndex) {
			state->index = toIndex;
		} else if(state->index == toIndex) {
			state->index = fromIndex;
		}
	}
}

void CaptureTabStateHandler::currentTabChanged(int index)
{
	mCurrentTabIndex = index;
}

void CaptureTabStateHandler::tabRemoved(int index)
{
	auto iterator = mCaptureTabStates.begin();
	while (iterator != mCaptureTabStates.end()) {
		if (iterator->data()->index == index) {
			iterator = mCaptureTabStates.erase(iterator);
		} else {
			if (iterator->data()->index > index) {
				iterator->data()->index--;
			}
			iterator++;
		}
	}

	if(mCachedCurrentTabState->index == index) {
		mCachedCurrentTabState.clear();
	}
}

void CaptureTabStateHandler::currentTabContentChanged()
{
	auto currentTabState = getCurrentTabStateFromCache();
	if (!currentTabState.isNull()) {
		currentTabState->isSaved = false;
		updateCurrentTabInfo();
	}
}

void CaptureTabStateHandler::updateCurrentTabInfo()
{
	auto currentTabState = getCurrentTabStateFromCache();
	if (!currentTabState.isNull()) {
		auto title = currentTabState->isSaved ? currentTabState->filename : currentTabState->filename + QStringLiteral("*");
		emit updateTabInfo(currentTabState->index, title, currentTabState->path);
	}
}

QSharedPointer<CaptureTabState> CaptureTabStateHandler::getCurrentTabStateFromCache()
{
	if (mCachedCurrentTabState.isNull() || mCachedCurrentTabState->index != mCurrentTabIndex) {
		for (auto &state : mCaptureTabStates) {
			if (state->index == mCurrentTabIndex) {
				mCachedCurrentTabState = state;
			}
		}
	}

	return mCachedCurrentTabState;
}

int CaptureTabStateHandler::count() const
{
	return mCaptureTabStates.count();
}
int CaptureTabStateHandler::currentTabIndex() const
{
	return mCurrentTabIndex;
}

