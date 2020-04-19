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

CursorDto WinWrapper::getCursorWithPosition() const
{
	CURSORINFO cursorInfo = { sizeof(cursorInfo) };
	GetCursorInfo(&cursorInfo);
	auto cursorPosition = getCursorPosition(QRect(), cursorInfo);
	auto cursorPixmap = getCursorPixmap(cursorInfo);

	return {cursorPixmap, cursorPosition};
}

QPoint WinWrapper::getCursorPosition(const QRect &rect, const CURSORINFO &cursor) const
{
    ICONINFOEXW iconInfo = {sizeof(iconInfo)};
    GetIconInfoExW(cursor.hCursor, &iconInfo);

    auto x = cursor.ptScreenPos.x - (int)iconInfo.xHotspot;
    auto y = cursor.ptScreenPos.y - (int)iconInfo.yHotspot;

    return {x, y};
}

QPixmap WinWrapper::getCursorPixmap(const CURSORINFO &cursor) const
{
    // Get Cursor Size
    auto cursorWidth = GetSystemMetrics(SM_CXCURSOR);
    auto cursorHeight = GetSystemMetrics(SM_CYCURSOR);

    // Get your device contexts.
    auto screenHandle = GetDC(nullptr);
    auto memoryHandle = CreateCompatibleDC(screenHandle);

    // Create the bitmap to use as a canvas.
    auto canvasBitmap = CreateCompatibleBitmap(screenHandle, cursorWidth, cursorHeight);

    // Select the bitmap into the device context.
    auto oldBitmap = SelectObject(memoryHandle, canvasBitmap);

    // Draw the cursor into the canvas.
    DrawIcon(memoryHandle, 0, 0, cursor.hCursor);

    // Convert to QPixmap
    auto cursorPixmap = fromHBITMAP(canvasBitmap, QtWin::HBitmapAlpha);

    // Clean up after yourself.
    SelectObject(memoryHandle, oldBitmap);
    DeleteObject(canvasBitmap);
    DeleteDC(memoryHandle);
    ReleaseDC(nullptr, screenHandle);

    return cursorPixmap;
}
