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

#include "PinWindowHandler.h"

PinWindowHandler::PinWindowHandler(QWidget *parent) :
	QObject(parent),
	mParent(parent)
{
}

PinWindowHandler::~PinWindowHandler()
{
	mPinWindows.clear();
}

void PinWindowHandler::add(const QPixmap &pixmap)
{
	auto titel = tr("Pin Window %1").arg(QString::number(mPinWindows.count() + 1));
	auto pinWindow = QSharedPointer<PinWindow>(new PinWindow(pixmap, titel));
	pinWindow->show();
	mPinWindows.append(pinWindow);
}

void PinWindowHandler::close()
{
	auto caller = dynamic_cast<PinWindow*>(sender());
	caller->hide();
	for(const auto& pinWindow : mPinWindows){
		if(pinWindow.data() == caller) {
			mPinWindows.removeAll(pinWindow);
			break;
		}
	}
}

void PinWindowHandler::closeAll()
{
	for(const auto& pinWindow : mPinWindows){
		pinWindow->hide();
	}
	mPinWindows.clear();
}

void PinWindowHandler::closeOther()
{
	auto caller = dynamic_cast<PinWindow*>(sender());
}
