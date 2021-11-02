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

#include "KeyHandlerFactory.h"

QSharedPointer<IKeyHandler> KeyHandlerFactory::create(const QSharedPointer<IPlatformChecker> &platformChecker)
{
#if defined(__APPLE__)
	return QSharedPointer<IKeyHandler>(new DummyKeyHandler);
#endif

#if defined(UNIX_X11)
    if(platformChecker->isWayland()) {
		return QSharedPointer<IKeyHandler>(new DummyKeyHandler);
    } else {
		return QSharedPointer<IKeyHandler>(new X11KeyHandler);
    }
#endif

#if  defined(_WIN32)
	return QSharedPointer<IKeyHandler>(new WinKeyHandler);
#endif
}
