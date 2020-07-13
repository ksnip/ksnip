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
	mDropShadowEffect(new QGraphicsDropShadowEffect(this))
{
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setModal(false);
	setWindowTitle(title);

	mCentralWidget->setPixmap(pixmap);
	mLayout->addWidget(mCentralWidget);

	auto margin = 15;
	setContentsMargins(margin, margin, margin, margin);

	mDropShadowEffect->setColor(QColor(160,160,160));
	mDropShadowEffect->setBlurRadius(margin * 2);
	mDropShadowEffect->setOffset(0);
	setGraphicsEffect(mDropShadowEffect);
}

PinWindow::~PinWindow()
{
	delete mLayout;
	delete mCentralWidget;
}
