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
	mCurrentTabIndex(-1)
{
}

void CaptureTabStateHandler::add(int index, const QString &filename, const QString &path, bool isSaved)
{
	auto newState = QSharedPointer<CaptureTabState>(new CaptureTabState(index, filename, path, isSaved));
	mCaptureTabStates.append(newState);
	refreshTabInfo(index);
}

bool CaptureTabStateHandler::isSaved(int index)
{
	auto tabState = getTabState(index);
	return tabState.isNull() || tabState->isSaved;
}

bool CaptureTabStateHandler::isPathValid(int index)
{
	auto tabState = getTabState(index);
	return tabState.isNull() || PathHelper::isPathValid(tabState->path);
}

QString CaptureTabStateHandler::path(int index)
{
	auto tabState = getTabState(index);
	return tabState.isNull() ? QString() : tabState->path;
}

QString CaptureTabStateHandler::filename(int index)
{
	auto tabState = getTabState(index);
	return tabState.isNull() ? QString() : tabState->filename;
}

void CaptureTabStateHandler::setSaveState(int index, const SaveResultDto &saveResult)
{
	auto tabState = getTabState(index);
	if (!tabState.isNull()) {
		tabState->isSaved = saveResult.isSuccessful;
		tabState->path = saveResult.path;
		tabState->filename = PathHelper::extractFilename(saveResult.path);
		refreshTabInfo(index);
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
}

void CaptureTabStateHandler::currentTabContentChanged()
{
	auto currentTabState = getTabState(mCurrentTabIndex);
	if (!currentTabState.isNull()) {
		currentTabState->isSaved = false;
		refreshTabInfo(mCurrentTabIndex);
	}
}

void CaptureTabStateHandler::refreshTabInfo(int index)
{
	auto tabState = getTabState(index);
	if (!tabState.isNull()) {
		auto title = tabState->isSaved ? tabState->filename : tabState->filename + QLatin1Literal("*");
		emit updateTabInfo(tabState->index, title, tabState->path);
	}
}

int CaptureTabStateHandler::count() const
{
	return mCaptureTabStates.count();
}

int CaptureTabStateHandler::currentTabIndex() const
{
	return mCurrentTabIndex;
}

QSharedPointer<CaptureTabState> CaptureTabStateHandler::getTabState(int index)
{
	for (auto &state : mCaptureTabStates) {
		if (state->index == index) {
			return state;
		}
	}
	return QSharedPointer<CaptureTabState>(nullptr);
}
