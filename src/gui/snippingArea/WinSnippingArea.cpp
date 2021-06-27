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

WinSnippingArea::WinSnippingArea() :
        AbstractSnippingArea(),
        mIsFullScreenSizeSet(false)
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
        return mHdpiScaler.scale(mCaptureArea);
    }
}

void WinSnippingArea::setFullScreen()
{
    auto rect = mWinWrapper.getFullScreenRect();

    // Workaround for Qt HiDPI issue, setting geometry more then once
    // enlarges the widget outside the size of the visible desktop. See #668.
    if(!mIsFullScreenSizeSet) {
        setGeometry(rect);
        mIsFullScreenSizeSet = true;
    }

    QWidget::show();
}

QRect WinSnippingArea::getSnippingAreaGeometry() const
{
    auto geometrySize = geometry().size();
    return {0, 0, geometrySize.width(), geometrySize.height() };
}
