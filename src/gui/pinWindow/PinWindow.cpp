/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "PinWindow.h"

PinWindow::PinWindow(const QPixmap &pixmap, const QString &title) :
	QDialog(nullptr),
	mLayout(new QVBoxLayout(this)),
	mCentralWidget(new QLabel(this)),
	mDropShadowEffect(new QGraphicsDropShadowEffect(this)),
	mMargin(10),
	mMinSize(50),
	mImage(pixmap),
	mIsMoving(false)
{
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::CoverWindow);
	setAttribute(Qt::WA_TranslucentBackground);
	setModal(false);
	setWindowTitle(title);
	setAttribute(Qt::WA_DeleteOnClose);
	setMouseTracking(true);

	mCentralWidget->setPixmap(mImage);
	mLayout->addWidget(mCentralWidget);

	setContentsMargins(mMargin, mMargin, mMargin, mMargin);

	addDropShadow();
}

PinWindow::~PinWindow()
{
	delete mLayout;
	delete mCentralWidget;
	delete mDropShadowEffect;
}

void PinWindow::addDropShadow()
{
	mDropShadowEffect->setColor(QColor(160, 160, 160));
	mDropShadowEffect->setBlurRadius(mMargin * 2);
	mDropShadowEffect->setOffset(0);
	setGraphicsEffect(mDropShadowEffect);
}

void PinWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
	Q_UNUSED(event)
	emit close();
}

void PinWindow::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) {
		mIsMoving = true;
		mMoveOffset = event->globalPos() - pos();
	}
	QWidget::mousePressEvent(event);
}

void PinWindow::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) {
		mIsMoving = false;
		mMoveOffset = {};
	}
	QWidget::mouseReleaseEvent(event);
}

void PinWindow::mouseMoveEvent(QMouseEvent *event)
{
	if(mIsMoving) {
		move(event->globalPos() - mMoveOffset);
	}
	QWidget::mouseMoveEvent(event);
}

void PinWindow::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Escape) {
		emit close();
	}
}

void PinWindow::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu;
	menu.addAction(tr("Close"), this, &PinWindow::closeRequest);
	menu.addAction(tr("Close Other"), this, &PinWindow::closeOtherRequest);
	menu.addAction(tr("Close All"), this, &PinWindow::closeAllRequest);
	menu.exec(event->globalPos());
}

void PinWindow::enterEvent(QEvent *event)
{
	mDropShadowEffect->setBlurRadius(mDropShadowEffect->blurRadius() + 4);
	QWidget::enterEvent(event);
}

void PinWindow::leaveEvent(QEvent *event)
{
	mDropShadowEffect->setBlurRadius(mDropShadowEffect->blurRadius() - 4);
	QWidget::leaveEvent(event);
}

void PinWindow::wheelEvent(QWheelEvent *event)
{
	auto delta = event->delta() / 10;
	auto scaledSize = QSize(mCentralWidget->width() + delta, mCentralWidget->height() + delta);

	if(scaledSize.width() > mMinSize && scaledSize.height() > mMinSize) {
		auto scaledImage = mImage.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		mCentralWidget->setPixmap(scaledImage);
		adjustSize();
	}
}
