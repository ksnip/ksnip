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

#include "ImageGrabber.h"

ImageGrabber::ImageGrabber(QWidget* parent) : QObject()
{
    mParent = parent;
}

//
// Public Functions
//

QPixmap ImageGrabber::grabImage(CaptureMode captureMode, bool capureMouse, QRect* rect)
{
    switch (captureMode) {
    case RectArea:
        if (!rect) {
            qCritical("ImageGrabber::grabImage: No rect provided but it was expected.");
            return 0;
        }

        return grabRect(*rect, capureMouse);

    case FullScreen:
        return grabRect(fullScreenRect(), capureMouse);

    case CurrentScreen:
        return grabRect(currectScreenRect(), capureMouse);

    case ActiveWindow:
        return grabRect(activeWindowRect(), capureMouse);

    default:
        qCritical("ImageGrabber::grabImage: Unknown CaptureMode provided.");
        return 0;
    }
}

/*
 * Returns the rect of the screen where the mouse cursor is currently located
 */
QRect ImageGrabber::currectScreenRect()
{
    unsigned short int screen = QApplication::desktop()->screenNumber(QCursor::pos());
    return QApplication::desktop()->screenGeometry(screen);
}

/*
 * Returns a rect covering the full screen, including several windows.
 */
QRect ImageGrabber::fullScreenRect()
{
    return QApplication::desktop()->screen()->geometry();
}

/*
 * Get the position and size of the current top window which has focus.
 */
QRect ImageGrabber::activeWindowRect()
{

    Display* display = XOpenDisplay(NULL);
    Window focusWindow, parentOfFocusedWindow;
    XWindowAttributes attrributes;
    int revert;

    XGetInputFocus(display, &focusWindow, &revert);
    parentOfFocusedWindow = getToplevelParent(display, focusWindow);

    if (!parentOfFocusedWindow) {
        qCritical("ImageGrabber::getActiveWindowRect: Unable to get window, returning screen.");
        return currectScreenRect();
    }

    XGetWindowAttributes(display, parentOfFocusedWindow, &attrributes);
    return QRect(attrributes.x, attrributes.y, attrributes.width, attrributes.height);
}

//
// Private Functions
//
QPixmap ImageGrabber::grabRect(QRect rect, bool capureMouse)
{
    QPixmap screenshot = QPixmap::grabWindow(QApplication::desktop()->winId(),
                         rect.topLeft().x(),
                         rect.topLeft().y(),
                         rect.width(),
                         rect.height());

    // Check if we should draw the cursor on the capture.
    if (rect.contains(QCursor::pos()) && capureMouse) {

        QPoint mousePos = QCursor::pos() - rect.topLeft();

        XFixesCursorImage* xfcursorImage = XFixesGetCursorImage(XOpenDisplay(NULL));

        // Converting long to uint as just using long on a 64bit system doesn't work out
        uint* uintCursor = (uint*)malloc((xfcursorImage->width * xfcursorImage->height) * sizeof(uint));
        for (int i = 0; i <= (xfcursorImage->width * xfcursorImage->height); i++) {
            uintCursor[i] = xfcursorImage->pixels[i];
        }

        // Create image of cursor
        QImage mouseCursor((uchar*)uintCursor, xfcursorImage->width,
                           xfcursorImage->height, QImage::Format_ARGB32_Premultiplied);

        // Cursor offset
        mousePos = mousePos - QPoint(xfcursorImage->xhot, xfcursorImage->yhot);

        // Draw the cursor image on the screenshot
        QPainter p(&screenshot);
        p.drawImage(mousePos, mouseCursor);

        free(uintCursor);
    }

    return screenshot;
}

/*
 * The returned top window can consist of several "windows", therefor this function is used
 * to find the child window that is currently at the top. Credit goes to Doug from StackOverflow:
 * http://stackoverflow.com/questions/3909713/xlib-xgetwindowattributes-always-returns-1x1
 */
Window ImageGrabber::getToplevelParent(Display* display, Window window)
{
    Window parentWindow;
    Window rootWindow;
    Window* childrenWindows;
    unsigned int numberOfChildren;

    while (1) {
        if (XQueryTree(display, window, &rootWindow, &parentWindow, &childrenWindows,
                       &numberOfChildren) == 0) {
            qCritical("ImageGrabber::getToplevelParent: XQueryTree Error");
            return 0;
        }

        if (childrenWindows) {
            XFree(childrenWindows);
        }

        if (window == rootWindow || parentWindow == rootWindow) {
            return window;
        } else {
            window = parentWindow;
        }
    }
}
