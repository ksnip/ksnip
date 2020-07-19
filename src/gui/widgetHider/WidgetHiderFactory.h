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

#ifndef KSNIP_WIDGETHIDERFACTORY_H
#define KSNIP_WIDGETHIDERFACTORY_H

#if defined(__APPLE__) || defined(_WIN32)
#include "WidgetHider.h"
#endif

#if defined(__linux__)
#include "GnomeWaylandWidgetHider.h"
#include "src/common/platform/PlatformChecker.h"
#endif

class WidgetHiderFactory
{
public:
	static WidgetHider* create(QWidget *widget);
};

#endif //KSNIP_WIDGETHIDERFACTORY_H
