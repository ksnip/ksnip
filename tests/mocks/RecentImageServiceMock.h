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

#ifndef KSNIP_RECENTIMAGESERVICEMOCK_H
#define KSNIP_RECENTIMAGESERVICEMOCK_H

#include <QString>
#include <QStringList>

#include "src/backend/recentImages/IRecentImageService.h"
#include "tests/utils/CallCounter.h"

class RecentImageServiceMock : public IRecentImageService
{
public:
	void storeImagePath(const QString &imagePath) override;
	QStringList getRecentImagesPath() const override;

	// Mock Methods
	QString storeImagePath_get() const;
	int storeImagePath_callCounter(const QString &path) const;
	int storeImagePath_callCounter() const;
	void getRecentImagesPath_set(const QStringList &imagePaths);
	int getRecentImagesPath_callCounter() const;

private:
	QString mLastStoreImagePathParameter;
	CallCounter<QString> mStoreImagePathCallCounter;
	QStringList mGetRecentImagesPathResult;
	CallCounter<int> mGetRecentImagesPathCallCounter;
};


#endif //KSNIP_RECENTIMAGESERVICEMOCK_H
