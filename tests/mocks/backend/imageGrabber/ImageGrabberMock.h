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

#ifndef KSNIP_IMAGEGRABBERMOCK_H
#define KSNIP_IMAGEGRABBERMOCK_H

#include <gmock/gmock.h>

#include "src/backend/imageGrabber/IImageGrabber.h"

class ImageGrabberMock : public IImageGrabber
{
public:
	MOCK_METHOD(bool, isCaptureModeSupported, (CaptureModes captureMode), (const, override));
	MOCK_METHOD(QList<CaptureModes>, supportedCaptureModes, (), (const, override));
	MOCK_METHOD(void, grabImage, (CaptureModes captureMode, bool captureCursor, int delay), (override));
};

#endif //KSNIP_IMAGEGRABBERMOCK_H
