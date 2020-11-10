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

AbstractSnippingArea::AbstractSnippingArea() :
	mConfig(KsnipConfigProvider::instance()),
	mBackground(nullptr),
	mResizer(new SnippingAreaResizer(this)),
	mSelector(new SnippingAreaSelector(mConfig, this))
{
    // Make the frame span across the screen and show above any other widget
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

	setMouseTracking(true);

    connect(mResizer, &SnippingAreaResizer::rectChanged, this, &AbstractSnippingArea::updateCapturedArea);
    connect(mResizer, &SnippingAreaResizer::cursorChanged, this, &AbstractSnippingArea::updateCursor);
	connect(mSelector, &SnippingAreaSelector::rectChanged, this, &AbstractSnippingArea::updateCapturedArea);
	connect(mSelector, &SnippingAreaSelector::cursorChanged, this, &AbstractSnippingArea::updateCursor);
}

AbstractSnippingArea::~AbstractSnippingArea()
{
    delete mBackground;
    delete mResizer;
    delete mSelector;
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
    setFullScreen();
    QApplication::setActiveWindow(this);
	mSelector->activate(getSnippingAreaGeometry(), QCursor::pos());
	setFocus();
    grabKeyboard(); // Issue #57
}

void AbstractSnippingArea::setBackgroundImage(const QPixmap &background)
{
    clearBackgroundImage();
    mBackground = new QPixmap(background);
	mSelector->setBackgroundImage(mBackground);
}

void AbstractSnippingArea::clearBackgroundImage()
{
    delete mBackground;
	mBackground = nullptr;
	mSelector->setBackgroundImage(nullptr);
}

void AbstractSnippingArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    mResizer->handleMousePress(event);
    mSelector->handleMousePress(event);
}

void AbstractSnippingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    mResizer->handleMouseRelease(event);
    mSelector->handleMouseRelease(event);

    if(mConfig->allowResizingRectCapture()) {
		if (!mResizer->isActive()){
			switchToResizer(event->pos());
		}
    } else {
		finishSelection();
	}
}

void AbstractSnippingArea::switchToResizer(QPoint point)
{
	mSelector->deactivate();
	mResizer->activate(mCaptureArea, point);
	update();
}

QPixmap AbstractSnippingArea::background() const
{
	Q_ASSERT(!isBackgroundTransparent());
	return *mBackground;
}

bool AbstractSnippingArea::closeSnippingArea()
{
	mSelector->deactivate();
	mResizer->deactivate();
    releaseKeyboard(); // Issue #57
    return QWidget::close();
}

void AbstractSnippingArea::mouseMoveEvent(QMouseEvent *event)
{
    mResizer->handleMouseMove(event);
    mSelector->handleMouseMove(event);
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

	painter.setClipRegion(mClippingRegion);

    painter.setBrush(QColor(0, 0, 0, 150));
	painter.drawRect(snippingAreaGeometry);

	painter.setClipRect(snippingAreaGeometry);

	mResizer->paint(&painter);
	mSelector->paint(&painter);

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

	if (event->key() == Qt::Key_Return) {
		finishSelection();
	}
    QWidget::keyPressEvent(event);
}

void AbstractSnippingArea::updateCapturedArea(const QRectF &rect)
{
    mCaptureArea = rect.toRect();
	mClippingRegion = QRegion(getSnippingAreaGeometry()).subtracted(QRegion(mCaptureArea));
}

void AbstractSnippingArea::finishSelection()
{
	emit finished();
	mConfig->setLastRectArea(selectedRectArea());
	closeSnippingArea();
}

void AbstractSnippingArea::updateCursor(const QCursor &cursor)
{
	setCursor(cursor);
}
