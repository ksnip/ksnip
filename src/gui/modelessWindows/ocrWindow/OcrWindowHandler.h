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

#ifndef KSNIP_OCRWINDOWHANDLER_H
#define KSNIP_OCRWINDOWHANDLER_H

#include "IOcrWindowHandler.h"
#include "src/gui/modelessWindows/ModelessWindowHandler.h"

class OcrWindowHandler : public IOcrWindowHandler, public ModelessWindowHandler
{
public:
	explicit OcrWindowHandler(const QSharedPointer<IModelessWindowCreator> &windowCreator);
	~OcrWindowHandler() override = default;
	void add(const QPixmap &pixmap) override;
};

#endif //KSNIP_OCRWINDOWHANDLER_H
