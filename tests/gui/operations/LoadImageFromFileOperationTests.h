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

#ifndef KSNIP_LOADIMAGEFROMFILEOPERATIONTESTS_H
#define KSNIP_LOADIMAGEFROMFILEOPERATIONTESTS_H

#include <QtTest>

#include "src/gui/operations/LoadImageFromFileOperation.h"
#include "tests/mocks/ToastServiceMock.h"
#include "tests/mocks/ImageProcessorMock.h"
#include "tests/mocks/ServiceLocatorMock.h"

class LoadImageFromFileOperationTests : public QObject
{
Q_OBJECT
private slots:
	void Execute_Should_ShowNotificationAndNotOpenImage_When_PathToImageCannotBeOpened();
	void Execute_Should_OpenImageAndNotShowNotification_When_PathToImageCanBeOpened();
};


#endif //KSNIP_LOADIMAGEFROMFILEOPERATIONTESTS_H
