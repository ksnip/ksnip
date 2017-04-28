/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

/*
 * blendCursorImage() and getNativeCursorPosition() functions have been taken
 * from KDE Spectacle X11ImageGrabber and slightly modified to fit this
 * implementation.
 */

#include "ImageGrabber.h"

ImageGrabber::ImageGrabber() : QObject()
{
}

//
// Public Functions
//

QPixmap ImageGrabber::grabImage(CaptureMode captureMode, bool capureMouse, const QRect* rect) const
{
    switch (captureMode) {
    case RectArea:
        if (!rect) {
            qCritical("ImageGrabber::grabImage: No rect provided but it was expected.");
            return QPixmap();
        }

        return grabRect(*rect, capureMouse);

    case FullScreen:
        return grabRect(fullScreenRect(), capureMouse);

    case CurrentScreen:
        return grabRect(currectScreenRect(), capureMouse);

    case ActiveWindow: {
        xcb_window_t wId = getActiveWindow();
        if (wId == 0) {
            qWarning("ImageGrabber::getActiveWindow: Found no window with focus");
            return grabRect(currectScreenRect(), capureMouse);
        }
        return grabRect(getWindowRect(wId), capureMouse);
    }
    default:
        qCritical("ImageGrabber::grabImage: Unknown CaptureMode provided.");
        return QPixmap();
    }
}

/*
 * Returns the rect of the screen where the mouse cursor is currently located
 */
QRect ImageGrabber::currectScreenRect() const
{
    auto screen = QApplication::desktop()->screenNumber(QCursor::pos());
    return QApplication::desktop()->screenGeometry(screen);
}

/*
 * Returns a rect covering the full screen, including several monitors.
 */
QRect ImageGrabber::fullScreenRect() const
{
    xcb_window_t rootWindow = QX11Info::appRootWindow();
    return getWindowRect(rootWindow);
}

//
// Private Functions
//
QPixmap ImageGrabber::grabRect(const QRect& rect, bool capureMouse) const
{
    auto screen = QGuiApplication::primaryScreen();
    QPixmap screenshot = screen->grabWindow(QApplication::desktop()->winId(),
                                            rect.topLeft().x(),
                                            rect.topLeft().y(),
                                            rect.width(),
                                            rect.height());

    // If requested, add cursor image to screenshot
    if (capureMouse) {
        screenshot = blendCursorImage(screenshot, rect);
    }

    return screenshot;
}

xcb_window_t ImageGrabber::getActiveWindow() const
{
    xcb_query_tree_cookie_t treeCookie;
    auto connection = QX11Info::connection();
    ScopedCPointer<xcb_get_input_focus_reply_t> focusReply(xcb_get_input_focus_reply(connection, xcb_get_input_focus(connection), nullptr));

    auto window = focusReply->focus;
    while (1) {
        treeCookie = xcb_query_tree_unchecked(connection, window);
        ScopedCPointer<xcb_query_tree_reply_t> treeReply(xcb_query_tree_reply(connection, treeCookie, nullptr));
        if (!treeReply) {
            return 0;
        }
        if (window == treeReply->root || treeReply->parent == treeReply->root) {
            return window;
        } else {
            window = treeReply->parent;
        }
    }
}

/*
 * Return geometry rect for provided window id. If window id 0, returns a null
 * QRect.
 */
QRect ImageGrabber::getWindowRect(xcb_window_t window) const
{
    // In case of window id 0 return empty rect
    if (window == 0) {
        return QRect();
    }

    auto connection = QX11Info::connection();
    auto geomCookie = xcb_get_geometry_unchecked(connection, window);
    ScopedCPointer<xcb_get_geometry_reply_t> geomReply(xcb_get_geometry_reply(connection, geomCookie, nullptr));

    return QRect(geomReply->x, geomReply->y, geomReply->width, geomReply->height);
}

// Note: x, y, width and height are measured in device pixels
QPixmap ImageGrabber::blendCursorImage(const QPixmap& pixmap, const QRect& rect) const
{
    auto cursorPos = getNativeCursorPosition();

    if (!rect.contains(cursorPos)) {
        return pixmap;
    }

    // now we can get the image and start processing

    auto xcbConn = QX11Info::connection();

    auto  cursorCookie = xcb_xfixes_get_cursor_image_unchecked(xcbConn);
    ScopedCPointer<xcb_xfixes_get_cursor_image_reply_t>  cursorReply(xcb_xfixes_get_cursor_image_reply(xcbConn, cursorCookie, nullptr));
    if (cursorReply.isNull()) {
        return pixmap;
    }

    quint32* pixelData = xcb_xfixes_get_cursor_image_cursor_image(cursorReply.data());
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

QPoint ImageGrabber::getNativeCursorPosition() const
{
    // QCursor::pos() is not used because it requires additional calculations.
    // Its value is the offset to the origin of the current screen is in
    // device-independent pixels while the origin itself uses native pixels.

    auto xcbConn = QX11Info::connection();
    auto pointerCookie = xcb_query_pointer_unchecked(xcbConn, QX11Info::appRootWindow());
    ScopedCPointer<xcb_query_pointer_reply_t> pointerReply(xcb_query_pointer_reply(xcbConn, pointerCookie, nullptr));

    return QPoint(pointerReply->root_x, pointerReply->root_y);
}
