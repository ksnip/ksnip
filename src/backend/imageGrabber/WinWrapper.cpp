/*
 * Copyright (C) 2018 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "WinWrapper.h"

QRect WinWrapper::getFullScreenRect() const
{
    auto height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    auto width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    auto x = GetSystemMetrics(SM_XVIRTUALSCREEN);
    auto y = GetSystemMetrics(SM_YVIRTUALSCREEN);

    return {x, y, width, height};
}

QRect WinWrapper::getActiveWindowRect() const
{
    RECT window, frame;
    auto handle = GetForegroundWindow();
    GetWindowRect(handle, &window);

    DwmGetWindowAttribute(handle, DWMWA_EXTENDED_FRAME_BOUNDS, &frame, sizeof(RECT));

    return {QPoint(frame.left, frame.top), QPoint(frame.right, frame.bottom)};
}
