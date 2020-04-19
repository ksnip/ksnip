/*
 * Copyright (C) 2019 Damir Porobic <https://github.com/damirporobic>
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

#ifndef KSNIP_KEYHANDLERFACTORY_H
#define KSNIP_KEYHANDLERFACTORY_H

#if defined(__APPLE__)
#include "DummyKeyHandler.h"
#endif

#if defined(__linux__)
#include "X11KeyHandler.h"
#include "DummyKeyHandler.h"
#include "src/common/platform/PlatformChecker.h"
#endif

#if  defined(_WIN32)
#include "WinKeyHandler.h"
#endif

class KeyHandlerFactory
{
public:
    static AbstractKeyHandler* create();
};

#endif //KSNIP_KEYHANDLERFACTORY_H
