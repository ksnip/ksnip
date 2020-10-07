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

#include "CaptureTabStateHandlerMock.h"

void CaptureTabStateHandlerMock::add(int index, const QString &filename, const QString &path, bool isSaved)
{

}

bool CaptureTabStateHandlerMock::isSaved(int index)
{
	return mIsSaveMap[index];
}

bool CaptureTabStateHandlerMock::isPathValid(int index)
{
	return mIsPathValidMap[index];
}

QString CaptureTabStateHandlerMock::path(int index)
{
	mPathCallCounter.increment(index);
	return mPathMap[index];
}

QString CaptureTabStateHandlerMock::filename(int index)
{
	return QString();
}

void CaptureTabStateHandlerMock::setSaveState(int index, const SaveResultDto &saveResult)
{

}

int CaptureTabStateHandlerMock::count() const
{
	return 0;
}

int CaptureTabStateHandlerMock::currentTabIndex() const
{
	return mCurrentTabIndex;
}

void CaptureTabStateHandlerMock::tabMoved(int fromIndex, int toIndex)
{

}

void CaptureTabStateHandlerMock::currentTabChanged(int index)
{

}

void CaptureTabStateHandlerMock::tabRemoved(int index)
{

}

void CaptureTabStateHandlerMock::currentTabContentChanged()
{

}

void CaptureTabStateHandlerMock::currentTabIndex_set(int index)
{
	mCurrentTabIndex = index;
}

void CaptureTabStateHandlerMock::path_set(int index, const QString &path)
{
	mPathMap[index] = path;
}

int CaptureTabStateHandlerMock::path_callCounter(int index) const
{
	return mPathCallCounter.count(index);
}

void CaptureTabStateHandlerMock::isPathValid_set(int index, bool value)
{
	mIsPathValidMap[index] = value;
}

void CaptureTabStateHandlerMock::isSaved_set(int index, bool value)
{
	mIsSaveMap[index] = value;
}
