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
    mIsFullScreenSizeSet(false),
    mIsMultipleScaledScreens(false)
{
    setWindowFlags(windowFlags() | Qt::Tool);
    
    mFullScreenRect = mWinWrapper.getFullScreenRect();

    setupScalingVariables();
}

QRect WinSnippingArea::selectedRectArea() const
{
    if(isBackgroundTransparent()) {
        auto topLeft = mapToGlobal(mCaptureArea.topLeft());
        auto bottomRight = mapToGlobal(mCaptureArea.bottomRight());
        return {topLeft, bottomRight};
    } else if (mIsMultipleScaledScreens) {
        auto xWithOffset = mCaptureArea.x() - mScaleOffset.x();
        auto yWithOffset = mCaptureArea.y() - mScaleOffset.y();
        return mHdpiScaler.scale({xWithOffset, yWithOffset, mCaptureArea.width(), mCaptureArea.height()});
    } else {
        return mHdpiScaler.scale(mCaptureArea);
    }
}

void WinSnippingArea::setFullScreen()
{
    /*
     * Workaround for Qt HiDPI issue, setting geometry more then once
     * enlarges the widget outside the size of the visible desktop. See #668.
     * Qt behaves differently in case of one or multiple scaled screens so
     * we utilise here different 'hacks' to fix the different use cases.
     * This part just be checked after upgrading to newer Qt version if it
     * can be simplified again in case the issue was fixed from Qt side.
     * See bug https://bugreports.qt.io/browse/QTBUG-94638
     */

    if(mIsMultipleScaledScreens) {
        setGeometry(QApplication::desktop()->geometry());
        QWidget::show();
        setGeometry(QApplication::desktop()->geometry());
    } else if(!mIsFullScreenSizeSet) {
            setGeometry(mFullScreenRect);
            mIsFullScreenSizeSet = true;
    }

    QWidget::show();
}

QRect WinSnippingArea::getSnippingAreaGeometry() const
{
    if(mIsMultipleScaledScreens) {
        return {mScaleOffset.x(), mScaleOffset.y(), mFullScreenRect.width() / 2, mFullScreenRect.height() / 2 };
    } else {
        return {0, 0, geometry().width(), geometry().height() };
    }
}

void WinSnippingArea::setupScalingVariables()
{
    auto scaledScreens = 0;
    auto screens = QApplication::screens();
    for(auto screen : screens) {
        auto screenGeometry = screen->geometry();
        
        if(screen->devicePixelRatio() > 1) {
            scaledScreens++;
        }

        if (screenGeometry.x() != 0) {
            mScaleOffset.setX(screenGeometry.x());
        }

        if (screenGeometry.y() != 0) {
            mScaleOffset.setY(screenGeometry.y());
        }
    }

    mScaleOffset.setX((mScaleOffset.x() - mFullScreenRect.x()) / mHdpiScaler.scaleFactor());
    mScaleOffset.setY((mScaleOffset.y() - mFullScreenRect.y()) / mHdpiScaler.scaleFactor());

    mIsMultipleScaledScreens = scaledScreens > 1;
}
