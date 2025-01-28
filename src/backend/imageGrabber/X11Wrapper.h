/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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

#ifndef X11WRAPPER_H
#define X11WRAPPER_H

#include <xcb/xfixes.h>
#include <QtGlobal>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtGui/private/qtx11extras_p.h>
#else
#include <QX11Info>
#endif

#include "src/common/dtos/CursorDto.h"

class X11Wrapper
{
public:
	X11Wrapper() = default;
	~X11Wrapper() = default;
    virtual bool isCompositorActive() const;
    virtual QRect getFullScreenRect() const;
    virtual QRect getActiveWindowRect() const;
	virtual CursorDto getCursorWithPosition() const;

protected:
	QPoint getNativeCursorPosition() const;
    QRect getWindowRect(xcb_window_t window) const;
    xcb_window_t getActiveWindowId() const;
};

/*
 * QScopedPointer class overwritten to free pointers that need to be freed by
 * free() instead of delete.
 */
template <typename T>
class ScopedCPointer : public QScopedPointer<T, QScopedPointerPodDeleter>
{
public:
	explicit ScopedCPointer(T *p = 0) : QScopedPointer<T, QScopedPointerPodDeleter>(p) {}
};

#endif // X11WRAPPER_H
