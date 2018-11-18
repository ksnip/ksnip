/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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
 */

#include "AbstractImageGrabber.h"

AbstractImageGrabber::AbstractImageGrabber(AbstractSnippingArea *snippingArea) : mSnippingArea(snippingArea)
{
    Q_ASSERT(snippingArea != nullptr);
}

AbstractImageGrabber::~AbstractImageGrabber()
{
    delete mSnippingArea;
}

bool AbstractImageGrabber::isCaptureModeSupported(CaptureModes captureMode) const
{
    return mSupportedCaptureModes.contains(captureMode);
}

QList<CaptureModes> AbstractImageGrabber::supportedCaptureModes() const
{
    return mSupportedCaptureModes;
}

/*
 * Returns the rect of the screen where the mouse cursor is currently located
 */
QRect AbstractImageGrabber::currectScreenRect() const
{
    auto screen = QApplication::desktop()->screenNumber(QCursor::pos());
    return QApplication::desktop()->screenGeometry(screen);
}

void AbstractImageGrabber::openSnippingArea()
{
    initSnippingArea();
    mSnippingArea->showWithoutBackground();
}

void AbstractImageGrabber::openSnippingAreaWithBackground(const QPixmap& background)
{
    initSnippingArea();
    mSnippingArea->showWithBackground(background);
}

QRect AbstractImageGrabber::selectedSnippingAreaRect() const
{
    return mSnippingArea->selectedRectArea();
}

void AbstractImageGrabber::initSnippingArea()
{
    connect(mSnippingArea, &AbstractSnippingArea::finished, [this]()
    {
        QTimer::singleShot(mCaptureDelay, this, &AbstractImageGrabber::grab);
    });
    connect(mSnippingArea, &AbstractSnippingArea::canceled, this, &AbstractImageGrabber::canceled);
}
