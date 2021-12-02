/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#include "X11SnippingArea.h"

#include <QDebug>

X11SnippingArea::X11SnippingArea(const QSharedPointer<IConfig> &config) : AbstractSnippingArea(config)
{
	setWindowFlags(windowFlags() | Qt::Tool | Qt::X11BypassWindowManagerHint);

    qDebug("-----------------------");
	calculateDesktopGeometry();
}

QRect X11SnippingArea::selectedRectArea() const
{
	if(isBackgroundTransparent()) {
		return mCaptureArea;
	} else {
        auto xWithOffset = mCaptureArea.x() - mOffset.x();
        auto yWithOffset = mCaptureArea.y() - mOffset.y();
        auto rect = QRect(xWithOffset, yWithOffset, mCaptureArea.width(), mCaptureArea.height());
        return mHdpiScaler.scale(rect);
	}
}

void X11SnippingArea::setFullScreen()
{
    setFixedSize(QDesktopWidget().size());
    QWidget::showFullScreen();
}

QRect X11SnippingArea::getSnippingAreaGeometry() const
{
    return mDesktopGeometry;
}

void X11SnippingArea::calculateDesktopGeometry()
{
	auto screens = QGuiApplication::screens();
	for(auto screen : screens) {
		auto scaleFactor = screen->devicePixelRatio();
		auto screenGeometry = screen->geometry();
		int x = screenGeometry.x() / scaleFactor;
		int y = screenGeometry.y() / scaleFactor;
		auto width = screenGeometry.width();
		auto height = screenGeometry.height();

        qDebug() << "Screen:" << screen->name();
        qDebug() << "Screen Scaling: " << scaleFactor;
        qDebug() << "Screen Geometry: " << screenGeometry;
        qDebug() << "Screen virtual geometry" << screen->virtualGeometry();

        mDesktopGeometry = mDesktopGeometry.united({x, y, width, height});
	}

    qDebug() << "Global scale factor: " << mHdpiScaler.scaleFactor();
    qDebug() << "Desktop Geometry without offset: " << mDesktopGeometry;

    auto scaleFactor = mHdpiScaler.scaleFactor();
    if(scaleFactor >= 2) {
        auto firstScreenWidth = screens[0]->geometry().width();
        mOffset = QPoint(firstScreenWidth, 0);
    } else if(scaleFactor >= 1.75) {
        mOffset = QPoint((int)(1920 / scaleFactor), 0);
    } else if(scaleFactor >= 1.5) {
        auto firstScreenWidth = (qreal)screens[0]->geometry().width();
        mOffset = QPoint((int)((firstScreenWidth * scaleFactor) / 2 / scaleFactor), 0);
    } else {
        mOffset = QPoint(0, 0);
    }

    mDesktopGeometry = QRect(mOffset , mDesktopGeometry.size());

    qDebug() << "Desktop Geometry with offset: " << mDesktopGeometry;
    qDebug() << "Calculated Offset: " << mOffset;
    qDebug() << "Native Fullscreen: " << mX11Wrapper.getFullScreenRect();
    qDebug() << "Desktop Widget Geometry: " << QDesktopWidget().geometry();

}
