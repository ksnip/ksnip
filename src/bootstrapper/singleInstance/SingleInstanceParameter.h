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

#ifndef KSNIP_SINGLEINSTANCEPARAMETER_H
#define KSNIP_SINGLEINSTANCEPARAMETER_H

#include <QString>

#include "src/bootstrapper/singleInstance/SingleInstanceStartupModes.h"
#include "src/common/enum/CaptureModes.h"

struct SingleInstanceParameter
{
	SingleInstanceStartupModes startupMode;
	CaptureModes captureMode;
	QString imagePath;
	bool save;
	bool captureCursor;
	int delay;

	SingleInstanceParameter() {
		this->startupMode = SingleInstanceStartupModes::Start;
	}

	SingleInstanceParameter(const QString &path) {
		this->startupMode = SingleInstanceStartupModes::Edit;
		this->imagePath = path;
	}

	SingleInstanceParameter(CaptureModes captureMode, bool save, bool captureCursor, int delay) {
		this->startupMode = SingleInstanceStartupModes::Capture;
		this->captureMode = captureMode;
		this->save = save;
		this->captureCursor = captureCursor;
		this->delay = delay;
	}
};

#endif //KSNIP_SINGLEINSTANCEPARAMETER_H
