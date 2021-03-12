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

#ifndef KSNIP_FILESERVICEMOCK_H
#define KSNIP_FILESERVICEMOCK_H

#include <QString>

#include "src/gui/fileService/IFileService.h"
#include "tests/utils/CallCounter.h"

class FileServiceMock : public IFileService
{
public:
	explicit FileServiceMock();
	~FileServiceMock() override = default;
	bool remove(const QString &path) override;
	QPixmap openPixmap(const QString &path) override;

	// Mock Methods
	QString remove_get() const;
	void remove_set(bool result);
	int remove_callCounter(const QString &path) const;
	QString openPixmap_get() const;
	void openPixmap_set(const QPixmap &pixmap);
	int openPixmap_callCounter(const QString &path) const;

public:
	QString mLastRemovePathParameter;
	bool mRemoveResult;
	CallCounter<QString> mRemoveCallCounter;
	QString mLastOpenPixmapParameter;
	QPixmap mOpenPixmapResult;
	CallCounter<QString> mOpenPixmapCallCounter;
};


#endif //KSNIP_FILESERVICEMOCK_H
