/*
 * Copyright (C) 2022 Damir Porobic <damir.porobic@gmx.com>
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

#include "ProcessIndicator.h"

ProcessIndicator::ProcessIndicator(QWidget *parent) :
	QLabel(parent),
	mBaseText(tr("Processing")),
	mAnimationCharacter("."),
	mTimer(new QTimer(this)),
	mDotCount(0)
{
	setText(mBaseText);
	setFixedSize(100, 50);
}

void ProcessIndicator::start()
{
	connect(mTimer, &QTimer::timeout, this, &ProcessIndicator::tick);
	mTimer->start(500);
}

void ProcessIndicator::stop()
{
	mTimer->stop();
}

void ProcessIndicator::tick()
{
	mDotCount = ++mDotCount % 4;
	auto text = mBaseText + mAnimationCharacter.repeated(mDotCount);
	setText(text);
}
