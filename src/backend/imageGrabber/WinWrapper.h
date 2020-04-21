/*
 * Copyright (C) 2018 Damir Porobic <https://github.com/damirporobic>
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

#ifndef KSNIP_WINWRAPPER_H
#define KSNIP_WINWRAPPER_H

#include <QtWinExtras>
#include <QPainter>

#include <wtypes.h>
#include <dwmapi.h>

#include "common/dtos/CursorDto.h"

class WinWrapper
{
public:
    QRect getFullScreenRect() const;
    QRect getActiveWindowRect() const;
	CursorDto getCursorWithPosition() const;

private:
    QPixmap getCursorPixmap(const CURSORINFO &cursor) const;
    QPoint getCursorPosition(const QRect &rect, const CURSORINFO &cursor) const;
};

#endif //KSNIP_WINWRAPPER_H
