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

#ifndef IMAGEGRABBER_H
#define IMAGEGRABBER_H

#include <QObject>
#include <QApplication>
#include <QPainter>
#include <QDesktopWidget>
#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>

class MainWindow;

class ImageGrabber : public QObject
{
public:
    enum CaptureMode { RectArea, FullScreen, CurrentScreen, ActiveWindow };

public:
    ImageGrabber(QWidget *);
    QPixmap grabImage(CaptureMode captureMode, bool capureMouse, QRect *rect = 0);
    QRect currectScreenRect();
    QRect fullScreenRect();
    QRect activeWindowRect();

private:
    QWidget *mParent;

    QPixmap grabRect(QRect rect, bool capureMouse);
    Window getToplevelParent(Display *display , Window window);
};

#endif // IMAGEGRABBER_H
