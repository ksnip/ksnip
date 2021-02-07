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

#include "FileServiceMock.h"

FileServiceMock::FileServiceMock() :
	mRemoveResult(false)
{

}

bool FileServiceMock::remove(const QString &path)
{
	mLastRemovePathParameter = path;
	mRemoveCallCounter.increment(path);
	return mRemoveResult;
}

QPixmap FileServiceMock::openPixmap(const QString &path)
{
	mLastOpenPixmapParameter = path;
	mOpenPixmapCallCounter.increment(path);
	return mOpenPixmapResult;
}

QString FileServiceMock::remove_get() const
{
	return mLastRemovePathParameter;
}

void FileServiceMock::remove_set(bool result)
{
	mRemoveResult = result;
}

int FileServiceMock::remove_callCounter(const QString &path) const
{
	return mRemoveCallCounter.count(path);
}

QString FileServiceMock::openPixmap_get() const
{
	return mLastOpenPixmapParameter;
}

void FileServiceMock::openPixmap_set(const QPixmap &pixmap)
{
	mOpenPixmapResult = pixmap;
}

int FileServiceMock::openPixmap_callCounter(const QString &path) const
{
	return mOpenPixmapCallCounter.count(path);
}
