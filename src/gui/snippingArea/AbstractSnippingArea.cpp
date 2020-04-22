/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */

#include "AbstractSnippingArea.h"

AbstractSnippingArea::AbstractSnippingArea()
	: mCursorFactory(new CursorFactory()),
	  mConfig(KsnipConfigProvider::instance()),
	  mBackground(nullptr)
{
    // Make the frame span across the screen and show above any other widget
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    QScopedPointer<QCursor> cursor(mCursorFactory->createSnippingCursor());
    QWidget::setCursor(*cursor);
}

AbstractSnippingArea::~AbstractSnippingArea()
{
    delete mCursorFactory;
    delete mBackground;
}

void AbstractSnippingArea::showWithoutBackground()
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    clearBackgroundImage();
    showSnippingArea();
}

void AbstractSnippingArea::showWithBackground(const QPixmap &background)
{
    setAttribute(Qt::WA_TranslucentBackground, false);
    setBackgroundImage(background);
    showSnippingArea();
}

void AbstractSnippingArea::showSnippingArea()
{
    init();
    setFullScreen();
    QApplication::setActiveWindow(this);
    updateAdorner();
	setFocus();
    grabKeyboard(); // Issue #57
}

void AbstractSnippingArea::setBackgroundImage(const QPixmap &background)
{
    clearBackgroundImage();
    mBackground = new QPixmap(background);
	mAdorner.setBackgroundImage(mBackground);
}

void AbstractSnippingArea::clearBackgroundImage()
{
    delete mBackground;
	mBackground = nullptr;
	mAdorner.setBackgroundImage(nullptr);
}

void AbstractSnippingArea::init()
{
	auto rulersEnabled = mConfig->snippingAreaRulersEnabled();
	auto positionAndSizeInfoEnabled = mConfig->snippingAreaPositionAndSizeInfoEnabled();
	auto magnifyingGlassEnabled = mConfig->snippingAreaMagnifyingGlassEnabled();
	auto freezeImageWhileSnippingEnabled = mConfig->freezeImageWhileSnippingEnabled();
	mAdorner.setRulersEnabled(rulersEnabled);
	mAdorner.setPositionAndSizeInfoEnabled(positionAndSizeInfoEnabled);
	mAdorner.setMagnifyingGlassEnabled(magnifyingGlassEnabled && freezeImageWhileSnippingEnabled);
	setMouseTracking(rulersEnabled || positionAndSizeInfoEnabled || magnifyingGlassEnabled);
	setMouseIsDown(false);
}

void AbstractSnippingArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    mMouseDownPosition = getMousePosition();
    updateCapturedArea();
	setMouseIsDown(true);
}

void AbstractSnippingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

	setMouseIsDown(false);
	finishSelection();
}

QPixmap AbstractSnippingArea::background() const
{
	Q_ASSERT(!isBackgroundTransparent());
	return *mBackground;
}

bool AbstractSnippingArea::closeSnippingArea()
{
    releaseKeyboard(); // Issue #57
    return QWidget::close();
}

void AbstractSnippingArea::mouseMoveEvent(QMouseEvent *event)
{
    if (mMouseIsDown) {
        updateCapturedArea();
    }
    updateAdorner();
    update();
    QWidget::mouseMoveEvent(event);
}

void AbstractSnippingArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

	auto snippingAreaGeometry = getSnippingAreaGeometry();
	if (!isBackgroundTransparent()) {
		painter.drawPixmap(snippingAreaGeometry, *mBackground);
    }

    if (mMouseIsDown) {
	    painter.setClipRegion(mClippingRegion);
    }

    painter.setBrush(QColor(0, 0, 0, 150));
	painter.drawRect(snippingAreaGeometry);

	mAdorner.draw(painter);

    if (mMouseIsDown) {
        painter.setPen(QPen(Qt::red, 4, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        painter.drawRect(mCaptureArea);
    }

    QWidget::paintEvent(event);
}

bool AbstractSnippingArea::isBackgroundTransparent() const
{
    return mBackground == nullptr;
}

void AbstractSnippingArea::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        emit canceled();
        closeSnippingArea();
    }
    QWidget::keyPressEvent(event);
}

void AbstractSnippingArea::updateCapturedArea()
{
    auto currentMousePosition = getMousePosition();
    mCaptureArea = QRect(mMouseDownPosition, currentMousePosition).normalized();
	mClippingRegion = QRegion(getSnippingAreaGeometry()).subtracted(QRegion(mCaptureArea));
}

void AbstractSnippingArea::setMouseIsDown(bool isDown)
{
	mMouseIsDown = isDown;
	mAdorner.setMouseDown(isDown);
}

void AbstractSnippingArea::updateAdorner()
{
    auto snippingAreaGeometry = getSnippingAreaGeometry();
    auto currentMousePosition = getMousePosition();
	mAdorner.update(currentMousePosition, snippingAreaGeometry, mCaptureArea);
}

void AbstractSnippingArea::finishSelection()
{
	emit finished();
	mConfig->setLastRectArea(selectedRectArea());
	closeSnippingArea();
}
