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

#ifndef KSNIP_CAPTURETABSTATEHANDLERMOCK_H
#define KSNIP_CAPTURETABSTATEHANDLERMOCK_H

#include <gmock/gmock.h>

#include "src/gui/captureHandler/ICaptureTabStateHandler.h"

class CaptureTabStateHandlerMock : public ICaptureTabStateHandler
{
public:
	MOCK_METHOD(void, add, (int index, const QString &filename, const QString &path, bool isSaved), (override));
	MOCK_METHOD(bool, isSaved, (int index), (override));
	MOCK_METHOD(bool, isPathValid, (int index), (override));
	MOCK_METHOD(QString, path, (int index), (override));
	MOCK_METHOD(QString, filename, (int index), (override));
	MOCK_METHOD(void, setSaveState, (int index, const SaveResultDto &saveResult), (override));
	MOCK_METHOD(void, renameFile, (int index, const RenameResultDto &renameResult), (override));
	MOCK_METHOD(int, count, (), (const, override));
	MOCK_METHOD(int, currentTabIndex, (), (const, override));

	MOCK_METHOD(void, tabMoved, (int fromIndex, int toIndex), (override));
	MOCK_METHOD(void, currentTabChanged, (int index), (override));
	MOCK_METHOD(void, tabRemoved, (int index), (override));
	MOCK_METHOD(void, currentTabContentChanged, (), (override));
};

#endif //KSNIP_CAPTURETABSTATEHANDLERMOCK_H
