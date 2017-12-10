/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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

/*
 * blendCursorImage() and getNativeCursorPosition() functions have been taken
 * from KDE Spectacle X11ImageGrabber and slightly modified to fit this
 * implementation.
 */

#include "X11GraphicsHelper.h"

#include <X11/Xlib.h>

bool X11GraphicsHelper::isCompositorActive()
{
    auto display = XOpenDisplay(0);
    auto prop_atom = XInternAtom(display, "_NET_WM_CM_S0", False);
    return XGetSelectionOwner(display, prop_atom) != None;
}

QRect X11GraphicsHelper::getFullScreenRect()
{
    return getWindowRect(QX11Info::appRootWindow());
}

QRect X11GraphicsHelper::getActiveWindowRect()
{
    auto windowId = getActiveWindowId();
    return getWindowRect(windowId);
}

QRect X11GraphicsHelper::getWindowRect(xcb_window_t windowId)
{
    // In case of window id 0 return empty rect
    if (windowId == 0) {
        return QRect();
    }

    auto connection = QX11Info::connection();
    auto geomCookie = xcb_get_geometry_unchecked(connection, windowId);
    ScopedCPointer<xcb_get_geometry_reply_t> geomReply(xcb_get_geometry_reply(connection, geomCookie, nullptr));

    return QRect(geomReply->x, geomReply->y, geomReply->width, geomReply->height);
}

xcb_window_t X11GraphicsHelper::getActiveWindowId()
{
    xcb_query_tree_cookie_t treeCookie;
    auto connection = QX11Info::connection();
    ScopedCPointer<xcb_get_input_focus_reply_t> focusReply(xcb_get_input_focus_reply(connection, xcb_get_input_focus(connection), nullptr));

    // Get ID of focused window, however, this must not always be the top level
    // window so we loop through parents and search for the top level window.
    auto windowId = focusReply->focus;
    while (1) {
        treeCookie = xcb_query_tree_unchecked(connection, windowId);
        ScopedCPointer<xcb_query_tree_reply_t> treeReply(xcb_query_tree_reply(connection, treeCookie, nullptr));
        if (!treeReply) {
            return 0;
        }
        // If the root window it is equal to the parent or the window ID itself
        // the this must be the top level window.
        if (windowId == treeReply->root || treeReply->parent == treeReply->root) {
            return windowId;
        } else {
            windowId = treeReply->parent;
        }
    }
}

QPoint X11GraphicsHelper::getNativeCursorPosition()
{
    // QCursor::pos() is not used because it requires additional calculations.
    // Its value is the offset to the origin of the current screen is in
    // device-independent pixels while the origin itself uses native pixels.

    auto xcbConn = QX11Info::connection();
    auto pointerCookie = xcb_query_pointer_unchecked(xcbConn, QX11Info::appRootWindow());
    ScopedCPointer<xcb_query_pointer_reply_t> pointerReply(xcb_query_pointer_reply(xcbConn, pointerCookie, nullptr));

    return QPoint(pointerReply->root_x, pointerReply->root_y);
}

// Note: x, y, width and height are measured in device pixels
QPixmap X11GraphicsHelper::blendCursorImage(const QPixmap& pixmap, const QRect& rect)
{
    auto cursorPos = getNativeCursorPosition();

    // If cursor not within rect that we capture, then nothing to do here
    if (!rect.contains(cursorPos)) {
        return pixmap;
    }

    // now we can get the image and start processing
    auto xcbConn = QX11Info::connection();

    auto  cursorCookie = xcb_xfixes_get_cursor_image_unchecked(xcbConn);
    ScopedCPointer<xcb_xfixes_get_cursor_image_reply_t> cursorReply(xcb_xfixes_get_cursor_image_reply(xcbConn, cursorCookie, nullptr));
    if (cursorReply.isNull()) {
        return pixmap;
    }

    auto pixelData = xcb_xfixes_get_cursor_image_cursor_image(cursorReply.data());
    if (!pixelData) {
        return pixmap;
    }

    // process the image into a QImage
    QImage cursorImage = QImage((quint8*)pixelData,
                                cursorReply->width,
                                cursorReply->height,
                                QImage::Format_ARGB32_Premultiplied);

    // a small fix for the cursor position for fancier cursors
    cursorPos -= QPoint(cursorReply->xhot, cursorReply->yhot);

    // now we translate the cursor point to our screen rectangle
    cursorPos -= QPoint(rect.x(), rect.y());

    // and do the painting
    QPixmap blendedPixmap = pixmap;
    QPainter painter(&blendedPixmap);
    painter.drawImage(cursorPos, cursorImage);

    return blendedPixmap;
}
