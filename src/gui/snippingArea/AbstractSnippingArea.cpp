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
	mResizer(new SnippingAreaResizer(mConfig, this)),
	mSelector(new SnippingAreaSelector(mConfig, this)),
	mInfoText(new SnippingAreaInfoText(this)),
	mIsSwitchPressed(false),
	mTimer(new QTimer(this))
{
    // Make the frame span across the screen and show above any other widget
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

	setMouseTracking(true);

    connect(mResizer, &SnippingAreaResizer::rectChanged, this, &AbstractSnippingArea::updateCapturedArea);
    connect(mResizer, &SnippingAreaResizer::cursorChanged, this, &AbstractSnippingArea::updateCursor);
	connect(mSelector, &SnippingAreaSelector::rectChanged, this, &AbstractSnippingArea::updateCapturedArea);
	connect(mSelector, &SnippingAreaSelector::cursorChanged, this, &AbstractSnippingArea::updateCursor);
	connect(mTimer, &QTimer::timeout, this, &AbstractSnippingArea::cancelSelection);
}

AbstractSnippingArea::~AbstractSnippingArea()
{
    delete mBackground;
    delete mResizer;
    delete mSelector;
    delete mInfoText;
    delete mTimer;
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
	startTimeout();
	mIsSwitchPressed = false;
    setFullScreen();
    QApplication::setActiveWindow(this);
	mSelector->activate(getSnippingAreaGeometry(), QCursor::pos());
	if(mConfig->showSnippingAreaInfoText()) {
		mInfoText->activate(getSnippingAreaGeometry(), mConfig->allowResizingRectSelection());
	}
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

    if(isResizerSwitchRequired() && !mResizer->isActive()) {
    	switchToResizer(event->pos());
    } else if(mSelector->isActive()){
		finishSelection();
	}
}

bool AbstractSnippingArea::isResizerSwitchRequired() const
{
	bool allowResizingRectSelection = mConfig->allowResizingRectSelection();
	return (allowResizingRectSelection && !mIsSwitchPressed) || (!allowResizingRectSelection && mIsSwitchPressed);
}

void AbstractSnippingArea::switchToResizer(QPoint point)
{
	mSelector->deactivate();
	mInfoText->deactivate();
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
	mInfoText->deactivate();
    releaseKeyboard(); // Issue #57
    return QWidget::close();
}

void AbstractSnippingArea::mouseMoveEvent(QMouseEvent *event)
{
    mResizer->handleMouseMove(event);
    mSelector->handleMouseMove(event);
    mInfoText->handleMouseMove(event->pos());
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

	mResizer->paint(&painter);
	mSelector->paint(&painter);

	painter.setClipRect(snippingAreaGeometry);

	mInfoText->paint(&painter);

    QWidget::paintEvent(event);
}

bool AbstractSnippingArea::isBackgroundTransparent() const
{
    return mBackground == nullptr;
}

void AbstractSnippingArea::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
		cancelSelection();
	} else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
		finishSelection();
	} else if (event->key() == Qt::Key_Control){
		mIsSwitchPressed = true;
	}

    QWidget::keyPressEvent(event);
}

void AbstractSnippingArea::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Control) {
		mIsSwitchPressed = false;
	}

	QWidget::keyReleaseEvent(event);
}

void AbstractSnippingArea::cancelSelection()
{
	stopTimeout();
	emit canceled();
	closeSnippingArea();
}

void AbstractSnippingArea::updateCapturedArea(const QRectF &rect)
{
    mCaptureArea = rect.toRect();
	mClippingRegion = QRegion(getSnippingAreaGeometry()).subtracted(QRegion(mCaptureArea));
}

void AbstractSnippingArea::finishSelection()
{
	stopTimeout();
	emit finished();
	mConfig->setLastRectArea(selectedRectArea());
	closeSnippingArea();
}

void AbstractSnippingArea::updateCursor(const QCursor &cursor)
{
	setCursor(cursor);
}

void AbstractSnippingArea::stopTimeout()
{
	mTimer->stop();
}

void AbstractSnippingArea::startTimeout()
{
	mTimer->start(60000);
}