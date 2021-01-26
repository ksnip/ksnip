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

#ifndef KSNIP_RECENTIMAGESPATHSTORETESTS_H
#define KSNIP_RECENTIMAGESPATHSTORETESTS_H

#include <QtTest>

#include "tests/mocks/RecentImagesPathStoreMock.h"


class RecentImagesPathStoreTests : public QObject
{
	Q_OBJECT
private slots:
	void initTestCase();
	void cleanup();

	void TestStoreInitialisation_Empty_When_Initialised();
	void TestStoreAddingImagePath_Paths_Added_And_Retrieved_Successfully();
	void TestStoreAddingImagePath_Should_Emit_Signal();
};

#endif //KSNIP_RECENTIMAGESPATHSTORETESTS_H

