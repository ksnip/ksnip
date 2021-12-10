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

WinSnippingArea::WinSnippingArea(const QSharedPointer<IConfig> &config) :
    AbstractSnippingArea(config),
    mIsFullScreenSizeSet(false),
    mIsMultipleScaledScreens(false)
{
    setWindowFlags(windowFlags() | Qt::Tool);

    connect(qGuiApp, &QGuiApplication::screenRemoved, this, &WinSnippingArea::init);
    connect(qGuiApp, &QGuiApplication::screenAdded, this, &WinSnippingArea::init);

    init();
}

QRect WinSnippingArea::selectedRectArea() const
{
    auto captureArea = getCaptureArea();

    if(isBackgroundTransparent()) {
        auto topLeft = mapToGlobal(captureArea.topLeft());
        auto bottomRight = mapToGlobal(captureArea.bottomRight());
        return {topLeft, bottomRight};
    } else {
        return mHdpiScaler.scale(captureArea);
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

    if (mIsMultipleScaledScreens) {
        setGeometry(QApplication::desktop()->geometry());
        QWidget::show();
        setGeometry(QApplication::desktop()->geometry());
    } else if (!mIsFullScreenSizeSet) {
        setGeometry(mFullScreenRect);
        mIsFullScreenSizeSet = true;
    }

    QWidget::show();
}

QSizeF WinSnippingArea::getSize() const
{
    if (mIsMultipleScaledScreens) {
        return { static_cast<double>(mFullScreenRect.width()) / 2, static_cast<double>(mFullScreenRect.height()) / 2 };
    } else {
        return { static_cast<double>(geometry().width()), static_cast<double>(geometry().height()) };
    }
}

QPoint WinSnippingArea::getGlobalCursorPosition() const
{
    return mapFromGlobal(AbstractSnippingArea::getGlobalCursorPosition());
}

void WinSnippingArea::setupScalingVariables()
{
    auto scaledScreens = 0;
    auto screens = QApplication::screens();
    for (auto screen : screens) {
        auto screenGeometry = screen->geometry();
        
        if(screen->devicePixelRatio() > 1) {
            scaledScreens++;
        }

        if (screenGeometry.x() != 0) {
            mScalePosition.setX(screenGeometry.x());
        }

        if (screenGeometry.y() != 0) {
            mScalePosition.setY(screenGeometry.y());
        }
    }

    mScalePosition.setX((mScalePosition.x() - mFullScreenRect.x()) / mHdpiScaler.scaleFactor());
    mScalePosition.setY((mScalePosition.y() - mFullScreenRect.y()) / mHdpiScaler.scaleFactor());

    mIsMultipleScaledScreens = scaledScreens > 1;
}

void WinSnippingArea::init()
{
    mIsFullScreenSizeSet = false;

    mFullScreenRect = mWinWrapper.getFullScreenRect();
    setupScalingVariables();
}

QPointF WinSnippingArea::getPosition() const
{
    if (mIsMultipleScaledScreens) {
        return mScalePosition;
    } else {
        return AbstractSnippingArea::getPosition();
    }
}
