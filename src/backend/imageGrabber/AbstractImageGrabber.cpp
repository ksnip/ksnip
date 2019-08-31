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
	connectSnippingAreaCancel();
}

AbstractImageGrabber::~AbstractImageGrabber()
{
    delete mSnippingArea;
}

void AbstractImageGrabber::grabImage(CaptureModes captureMode, bool captureCursor, int delay, bool freezeImageWhileSnipping)
{
	mCaptureCursor = captureCursor;
	mCaptureDelay = mDelayHandler.getDelay(delay);
	mFreezeImageWhileSnipping = freezeImageWhileSnipping;

	if (isCaptureModeSupported(captureMode)) {
		mCaptureMode = captureMode;
	} else {
		qWarning("Unsupported Capture Mode selected, falling back to full screen.");
		mCaptureMode = CaptureModes::FullScreen;
	}

	if (isRectAreaCaptureWithoutBackground()) {
		openSnippingAreaWithoutBackground();
	} else {
		QTimer::singleShot(mCaptureDelay, this, &AbstractImageGrabber::prepareGrab);
	}
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
QRect AbstractImageGrabber::currentScreenRect() const
{
    auto screen = QApplication::desktop()->screenNumber(QCursor::pos());
    return QApplication::desktop()->screenGeometry(screen);
}

void AbstractImageGrabber::addSupportedCaptureMode(CaptureModes captureMode)
{
	mSupportedCaptureModes.append(captureMode);
}

void AbstractImageGrabber::openSnippingAreaWithoutBackground()
{
	connectSnippingAreaFinish();
    mSnippingArea->showWithoutBackground();
}

void AbstractImageGrabber::openSnippingAreaWithBackground(const QPixmap& background)
{
	connectSnippingAreaFinish();
    mSnippingArea->showWithBackground(background);
}

QRect AbstractImageGrabber::selectedSnippingAreaRect() const
{
    return mSnippingArea->selectedRectArea();
}

QPixmap AbstractImageGrabber::snippingAreaBackground() const
{
	return mSnippingArea->background();
}

QPixmap AbstractImageGrabber::getScreenshotFromRect(const QRect &rect) const
{
	auto screen = QGuiApplication::primaryScreen();
	auto windowId = QApplication::desktop()->winId();
	auto rectPosition = rect.topLeft();
	return screen->grabWindow(windowId, rectPosition.x(), rectPosition.y(), rect.width(), rect.height());
}

QPixmap AbstractImageGrabber::getScreenshot() const
{
	if (isRectAreaCaptureWithBackground()) {
		return snippingAreaBackground().copy(mCaptureRect);
	} else {
		return getScreenshotFromRect(mCaptureRect);
	}
}

void AbstractImageGrabber::setCaptureRectFromCorrectSource()
{
	if (mCaptureMode == CaptureModes::RectArea) {
		mCaptureRect = selectedSnippingAreaRect();
	} else if (mCaptureMode == CaptureModes::FullScreen) {
		mCaptureRect = fullScreenRect();
	} else if (mCaptureMode == CaptureModes::CurrentScreen) {
		mCaptureRect = currentScreenRect();
	} else if (mCaptureMode == CaptureModes::ActiveWindow) {
		mCaptureRect = activeWindowRect();
		if (mCaptureRect.isNull()) {
			qWarning("ImageGrabber::getActiveWindow: Found no window with focus.");
			mCaptureRect = currentScreenRect();
		}
	}
}

bool AbstractImageGrabber::isSnippingAreaBackgroundTransparent() const
{
	return !mFreezeImageWhileSnipping;
}

void AbstractImageGrabber::prepareGrab()
{
	if (isRectAreaCaptureWithBackground()) {
		openSnippingArea();
	} else {
		grab();
	}
}

void AbstractImageGrabber::grab()
{
	setCaptureRectFromCorrectSource();
	CaptureDto capture(getScreenshot());

	if (shouldCaptureCursor()) {
		capture.cursor = getCursorRelativeToScreenshot();
	}
	emit finished(capture);
}

CursorDto AbstractImageGrabber::getCursorRelativeToScreenshot() const
{
	auto cursor = getCursorImageWithPositionFromCorrectSource();
	if(mCaptureRect.contains(cursor.position)) {
		cursor.position -= mCaptureRect.topLeft();
		return cursor;
	}
	return {};
}

bool AbstractImageGrabber::shouldCaptureCursor() const
{
	return mCaptureCursor && !(mCaptureMode == CaptureModes::RectArea && mCaptureDelay <= mDelayHandler.minDelayInMs());
}

void AbstractImageGrabber::openSnippingArea()
{
	if (isSnippingAreaBackgroundTransparent()) {
		openSnippingAreaWithoutBackground();
	} else {
		auto screenRect = fullScreenRect();
		auto background = getScreenshotFromRect(screenRect);
		mStoredCursorImageWithPosition = getCursorWithPosition();
		openSnippingAreaWithBackground(background);
	}
}

void AbstractImageGrabber::connectSnippingAreaCancel()
{
    connect(mSnippingArea, &AbstractSnippingArea::canceled, this, &AbstractImageGrabber::canceled);
}

void AbstractImageGrabber::connectSnippingAreaFinish()
{
	disconnectSnippingAreaFinish();

	if (isSnippingAreaBackgroundTransparent()) {
		connect(mSnippingArea, &AbstractSnippingArea::finished, [this]()
		{
			QTimer::singleShot(mCaptureDelay, this, &AbstractImageGrabber::grab);
		});
	} else {
		connect(mSnippingArea, &AbstractSnippingArea::finished, this, &AbstractImageGrabber::grab);
	}
}

void AbstractImageGrabber::disconnectSnippingAreaFinish()
{
	disconnect(mSnippingArea, &AbstractSnippingArea::finished, nullptr, nullptr);
}

CursorDto AbstractImageGrabber::getCursorImageWithPositionFromCorrectSource() const
{
	return isRectAreaCaptureWithBackground() ? mStoredCursorImageWithPosition : getCursorWithPosition();
}

bool AbstractImageGrabber::isRectAreaCaptureWithBackground() const
{
	return mCaptureMode == CaptureModes::RectArea && !isSnippingAreaBackgroundTransparent();
}

bool AbstractImageGrabber::isRectAreaCaptureWithoutBackground() const
{
	return mCaptureMode == CaptureModes::RectArea && isSnippingAreaBackgroundTransparent();
}
