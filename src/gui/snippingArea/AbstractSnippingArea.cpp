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

AbstractSnippingArea::AbstractSnippingArea(const QSharedPointer<IConfig> &config) :
	mConfig(config),
	mBackground(nullptr),
	mResizer(new SnippingAreaResizer(mConfig, this)),
	mSelector(new SnippingAreaSelector(mConfig, this)),
	mSelectorInfoText(new SnippingAreaSelectorInfoText(this)),
	mResizerInfoText(new SnippingAreaResizerInfoText(this)),
	mIsSwitchPressed(false),
	mTimer(new QTimer(this)),
	mUnselectedRegionAlpha(150)
{
    // Make the frame span across the screen and show above any other widget
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

	setMouseTracking(true);

    connect(mResizer, &SnippingAreaResizer::rectChanged, this, &AbstractSnippingArea::updateCapturedArea);
    connect(mResizer, &SnippingAreaResizer::cursorChanged, this, &AbstractSnippingArea::updateCursor);

	connect(mSelector, &SnippingAreaSelector::rectChanged, this, &AbstractSnippingArea::updateCapturedArea);
	connect(mSelector, &SnippingAreaSelector::cursorChanged, this, &AbstractSnippingArea::updateCursor);

	connect(mTimer, &QTimer::timeout, this, &AbstractSnippingArea::cancelSelection);

    connect(mConfig.data(), &IConfig::snippingAreaChangedChanged, this, &AbstractSnippingArea::updatePosition);

    updatePosition();
}

AbstractSnippingArea::~AbstractSnippingArea()
{
    delete mBackground;
    delete mResizer;
    delete mSelector;
    delete mSelectorInfoText;
    delete mResizerInfoText;
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

QRect AbstractSnippingArea::getCaptureArea() const
{
    auto offset = getPosition().toPoint();
    const QRect &anAuto = mCaptureArea.translated(-offset.x(), -offset.y());
    return anAuto;
}

void AbstractSnippingArea::showSnippingArea()
{
	startTimeout();
	mIsSwitchPressed = false;
    setFullScreen();
	mSelector->activate(getGeometry(), getGlobalCursorPosition());
	mUnselectedRegionAlpha = mConfig->snippingAreaTransparency();
	if(mConfig->showSnippingAreaInfoText()) {
		mSelectorInfoText->activate(getGeometry(), mConfig->allowResizingRectSelection());
	}
    grabKeyboardFocus();
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

    auto pos = event->pos();
    mResizer->handleMousePress(pos);
    mSelector->handleMousePress(pos);
}

void AbstractSnippingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    mResizer->handleMouseRelease();
    mSelector->handleMouseRelease();


    if(isResizerSwitchRequired() && !mResizer->isActive()) {
        switchToResizer(event->pos());
    } else if(mSelector->isActive()){
		finishSelection();
	}
}

void AbstractSnippingArea::mouseMoveEvent(QMouseEvent *event)
{
    auto pos = event->pos();
    mResizer->handleMouseMove(pos);
    mSelector->handleMouseMove(pos);
    mSelectorInfoText->handleMouseMove(pos);
    mResizerInfoText->handleMouseMove(pos);
    update();
    QWidget::mouseMoveEvent(event);
}

void AbstractSnippingArea::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (mResizer->isActive()) {
		finishSelection();
	}

	QWidget::mouseDoubleClickEvent(event);
}

bool AbstractSnippingArea::isResizerSwitchRequired() const
{
	bool allowResizingRectSelection = mConfig->allowResizingRectSelection();
	return (allowResizingRectSelection && !mIsSwitchPressed) || (!allowResizingRectSelection && mIsSwitchPressed);
}

void AbstractSnippingArea::switchToResizer(const QPointF &pos)
{
	mSelector->deactivate();
	mSelectorInfoText->deactivate();
	if(mConfig->showSnippingAreaInfoText()) {
		mResizerInfoText->activate(getGeometry());
	}
	mResizer->activate(mCaptureArea, pos);
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
	mSelectorInfoText->deactivate();
	mResizerInfoText->deactivate();
    releaseKeyboard(); // Issue #57
    return QWidget::close();
}

void AbstractSnippingArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

	auto geometry = getGeometry();
	if (!isBackgroundTransparent()) {
		painter.drawPixmap(geometry, *mBackground, mBackground->rect());
    }

	painter.setClipRegion(mClippingRegion);

    painter.setBrush(QColor(0, 0, 0, mUnselectedRegionAlpha));
	painter.drawRect(geometry);

	mResizer->paint(&painter);
	mSelector->paint(&painter);

	painter.setClipRect(geometry);

	mSelectorInfoText->paint(&painter);
	mResizerInfoText->paint(&painter);

    QWidget::paintEvent(event);
}

bool AbstractSnippingArea::isBackgroundTransparent() const
{
    return mBackground == nullptr;
}

QPoint AbstractSnippingArea::getGlobalCursorPosition() const
{
    return QCursor::pos();
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

	mSelector->handleKeyPress(event);
    mResizer->handleKeyPress(event);
	update();

    QWidget::keyPressEvent(event);
}

void AbstractSnippingArea::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Control) {
		mIsSwitchPressed = false;
	}

	mResizer->handleKeyRelease(event);

	QWidget::keyReleaseEvent(event);
}

void AbstractSnippingArea::cancelSelection()
{
	stopTimeout();
	closeSnippingArea();
	emit canceled();
}

void AbstractSnippingArea::updateCapturedArea(const QRectF &rect)
{
    mCaptureArea = rect.toRect();
	mClippingRegion = QRegion(getGeometry().toRect()).subtracted(QRegion(mCaptureArea));
}

void AbstractSnippingArea::finishSelection()
{
	stopTimeout();
	closeSnippingArea();
	mConfig->setLastRectArea(selectedRectArea());
	emit finished();
}

void AbstractSnippingArea::grabKeyboardFocus()
{
    QApplication::setActiveWindow(this);
    activateWindow();
    setFocus();
    grabKeyboard();
}

QPointF AbstractSnippingArea::getPosition() const
{
    return mPosition;
}

QRectF AbstractSnippingArea::getGeometry() const
{
    return { getPosition(), getSize() };
}

void AbstractSnippingArea::updateCursor(const QCursor &cursor)
{
	setCursor(cursor);
}

void AbstractSnippingArea::startTimeout()
{
    mTimer->start(60000);
}

void AbstractSnippingArea::stopTimeout()
{
	mTimer->stop();
}

void AbstractSnippingArea::updatePosition()
{
    if(mConfig->snippingAreaOffsetEnable()) {
        mPosition = mConfig->snippingAreaOffset();
    } else {
        mPosition = {};
    }
}
