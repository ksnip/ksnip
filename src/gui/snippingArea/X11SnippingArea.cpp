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

X11SnippingArea::X11SnippingArea(const QSharedPointer<IConfig> &config) :
    AbstractSnippingArea(config),
	mScreenCountChanged(true)
{
	setWindowFlags(windowFlags() | Qt::Tool | Qt::X11BypassWindowManagerHint);

	connect(qGuiApp, &QGuiApplication::screenRemoved, [this]() { mScreenCountChanged = true; });
	connect(qGuiApp, &QGuiApplication::screenAdded, [this]() {	mScreenCountChanged = true;	});
}

QRect X11SnippingArea::selectedRectArea() const
{
    auto captureArea = getCaptureArea();

    if(isBackgroundTransparent()) {
		return captureArea;
	} else {
        return mHdpiScaler.scale(captureArea);
	}
}

void X11SnippingArea::setFullScreen()
{
    setFixedSize(QDesktopWidget().size());
    QWidget::showFullScreen();
}

QSizeF X11SnippingArea::getSize() const
{
    return mDesktopGeometry.size();
}

void X11SnippingArea::showSnippingArea()
{
	// Just after the screen count is changed the new screen is not positioned
	// correctly so our calculation is wrong. As a workaround we mark that we
	// need to recalculate the screen and calculate just before we show the
	// snipping area.
	if (mScreenCountChanged) {
		calculateDesktopGeometry();
		mScreenCountChanged = false;
	}

	AbstractSnippingArea::showSnippingArea();
}

void X11SnippingArea::calculateDesktopGeometry()
{
	mDesktopGeometry = QRectF();

	auto screens = QGuiApplication::screens();

	for(auto screen : screens) {
		auto scaleFactor = screen->devicePixelRatio();
		auto screenGeometry = screen->geometry();
		auto x = screenGeometry.x() / scaleFactor;
		auto y = screenGeometry.y() / scaleFactor;
		auto width = (qreal)screenGeometry.width();
		auto height = (qreal)screenGeometry.height();

        mDesktopGeometry = mDesktopGeometry.united({x, y, width, height});
	}
}
