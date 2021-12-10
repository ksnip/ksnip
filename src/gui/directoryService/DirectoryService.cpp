/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "DirectoryService.h"

QList<QFileInfo> DirectoryService::childDirectories(const QString &path) const
{
	return getChildrenOfType(path, QDir::Dirs | QDir::NoDotAndDotDot);
}

QList<QFileInfo> DirectoryService::childFiles(const QString &path) const
{
	return getChildrenOfType(path, QDir::Files);
}

QList<QFileInfo> DirectoryService::getChildrenOfType(const QString &path, QFlags<QDir::Filter> filters) const
{
	QDir parent(path);
	return parent.entryInfoList(filters);
}
