/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "ModelessWindowHandler.h"

ModelessWindowHandler::ModelessWindowHandler(const QSharedPointer<IModelessWindowCreator> &windowCreator) :
	QObject(nullptr),
	mWindowCreator(windowCreator)
{
}

ModelessWindowHandler::~ModelessWindowHandler()
{
	mModelessWindows.clear();
}

void ModelessWindowHandler::add(const QPixmap &pixmap)
{
	auto modelessWindow = CreateModelessWindow(pixmap);
	modelessWindow->show();
	mModelessWindows.append(modelessWindow);
}

QSharedPointer<IModelessWindow> ModelessWindowHandler::CreateModelessWindow(const QPixmap &pixmap) const
{
	auto windowId = mModelessWindows.count() + 1;
	auto modelessWindow = mWindowCreator->create(pixmap, windowId);
	connect(modelessWindow.data(), &IModelessWindow::closeRequest, this, &ModelessWindowHandler::closeRequested);
	connect(modelessWindow.data(), &IModelessWindow::closeOtherRequest, this, &ModelessWindowHandler::closeOtherRequested);
	connect(modelessWindow.data(), &IModelessWindow::closeAllRequest, this, &ModelessWindowHandler::closeAllRequested);

	return modelessWindow;
}

void ModelessWindowHandler::closeRequested()
{
	auto caller = dynamic_cast<IModelessWindow*>(sender());
	caller->hide();
	for(const auto& modelessWindow : mModelessWindows){
		if (modelessWindow.data() == caller) {
			mModelessWindows.removeOne(modelessWindow);
			break;
		}
	}
}

void ModelessWindowHandler::closeAllRequested()
{
	for(const auto& modelessWindow : mModelessWindows){
		modelessWindow->hide();
	}
	mModelessWindows.clear();
}

void ModelessWindowHandler::closeOtherRequested()
{
	auto caller = dynamic_cast<IModelessWindow*>(sender());
	for (auto iterator = mModelessWindows.begin(); iterator != mModelessWindows.end(); ++iterator) {
		if(iterator->data() != caller) {
			iterator->data()->hide();
			mModelessWindows.removeOne(*iterator);
		}
	}
}