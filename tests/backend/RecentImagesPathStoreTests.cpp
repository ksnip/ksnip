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

#include "RecentImagesPathStoreTests.h"

void RecentImagesPathStoreTests::initTestCase()
{
	qApp->setOrganizationName(QLatin1String("ksnip"));
	qApp->setOrganizationDomain(QLatin1String("ksnip.ksnip.org"));
	qApp->setApplicationName(QLatin1String("ksnip_recentimagespath_test"));
}

void RecentImagesPathStoreTests::cleanup()
{
	QSettings settings;
	settings.clear();
}

void RecentImagesPathStoreTests::TestStoreInitialisation_Empty_When_Initialised()
{
	RecentImagesPathStoreMock recentImagesPathStore;
	const auto recentImagesPath = recentImagesPathStore.getRecentImagesPath();
	QCOMPARE(recentImagesPath.size(), 0);
}

void RecentImagesPathStoreTests::TestStoreAddingImagePath_Paths_Added_And_Retrieved_Successfully()
{
	RecentImagesPathStoreMock recentImagesPathStore;

	recentImagesPathStore.storeImagePath("/path/image.png");

	auto recentImagesPath =	recentImagesPathStore.getRecentImagesPath();

	QCOMPARE(recentImagesPath.size(), 1);
	QCOMPARE(recentImagesPath.at(0), "/path/image.png");

	recentImagesPathStore.storeImagePath("/path/image2.png");

	recentImagesPath = recentImagesPathStore.getRecentImagesPath();

	QCOMPARE(recentImagesPath.size(), 2);
	QCOMPARE(recentImagesPath.at(0), "/path/image.png");
	QCOMPARE(recentImagesPath.at(1), "/path/image2.png");
}

void RecentImagesPathStoreTests::TestStoreAddingImagePath_Should_Emit_Signal()
{
	RecentImagesPathStoreMock recentImagesPathStore;

	bool signalEmitted(false);

	connect(&recentImagesPathStore,
			&RecentImagesPathStore::recentImagesPathChanged,
			[&signalEmitted]() {
		signalEmitted = true;
	});

	recentImagesPathStore.storeImagePath("/path/image.png");
	QVERIFY(signalEmitted);
}


QTEST_MAIN(RecentImagesPathStoreTests)
