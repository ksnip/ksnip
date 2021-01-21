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

#ifndef KSNIP_RECENTIMAGESSTORE_H
#define KSNIP_RECENTIMAGESSTORE_H

#include <QQueue>
#include <QSettings>


class RecentImagesStore
{
public:
	explicit RecentImagesStore();
	~RecentImagesStore() = default;

	void storeImage(const QString &image);
	QStringList getRecentImages() const;

private:
	void loadRecentImages();
	void saveRecentImages();

	QQueue<QString> mRecentImages;
	QSettings mSettings;
	const QString mSettingsGroupPrefix;
	const QString mSettingsGroupKey;
	const int mMaxRecentItems;
};

#endif //KSNIP_RECENTIMAGESSTORE_H
