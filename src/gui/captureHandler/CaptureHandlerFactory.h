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

#ifndef KSNIP_CAPTUREHANDLERFACTORY_H
#define KSNIP_CAPTUREHANDLERFACTORY_H

#include "src/gui/captureHandler/SingleCaptureHandler.h"
#include "src/gui/captureHandler/MultiCaptureHandler.h"
#include "src/gui/captureHandler/CaptureTabStateHandler.h"
#include "src/gui/desktopService/DesktopServiceAdapter.h"
#include "src/backend/config/KsnipConfigProvider.h"

class CaptureHandlerFactory
{
public:
	explicit CaptureHandlerFactory() = default;
	~CaptureHandlerFactory() = default;
	static ICaptureHandler *create(IImageAnnotator *imageAnnotator, IToastService *toastService, IClipboard *clipboard, QWidget *parent);
};

#endif //KSNIP_CAPTUREHANDLERFACTORY_H
