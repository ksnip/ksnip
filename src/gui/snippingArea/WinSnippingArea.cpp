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

#include "WinSnippingArea.h"

WinSnippingArea::WinSnippingArea() : AbstractSnippingArea()
{
    setWindowFlags(windowFlags() | Qt::Tool);
}

QRect WinSnippingArea::selectedRectArea() const
{
    if(isBackgroundTransparent()) {
        auto topLeft = mapToGlobal(mCaptureArea.topLeft());
        auto bottomRight = mapToGlobal(mCaptureArea.bottomRight());
        return {topLeft, bottomRight};
    } else {
        return mCaptureArea;
    }
}

void WinSnippingArea::setFullScreen()
{
    auto fullScreenRect = getFullScreenRect();
    setGeometry(fullScreenRect);
    QWidget::show();
}

QPoint WinSnippingArea::getMousePosition() const
{
    return mapFromGlobal(QCursor::pos());
}

QRect WinSnippingArea::getSnippingAreaGeometry() const
{
    auto snippingAreaGeometry = geometry();
    return {mapFromGlobal(snippingAreaGeometry.topLeft()), mapFromGlobal(snippingAreaGeometry.bottomRight())};
}

QRect WinSnippingArea::getFullScreenRect() const
{
    QRect fullScreenRect;
    auto screenCount = QDesktopWidget().screenCount();
    for(int i = 0; i < screenCount; i++) {
        auto screenRect = QDesktopWidget().screenGeometry(i);
		fullScreenRect = fullScreenRect.united(screenRect);
    }

    return fullScreenRect;
}
