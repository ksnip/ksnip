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

#include "WidgetVisibilityHandler.h"

WidgetVisibilityHandler::WidgetVisibilityHandler(QWidget *widget) :
	mWidget(widget),
	mSelectedWindowState(Qt::WindowActive),
	mWindowStateChangeLock(false),
	mWasMinimized(false)
{

}

void WidgetVisibilityHandler::hide()
{
	mWidget->hide();
}

void WidgetVisibilityHandler::makeInvisible()
{
	mWindowStateChangeLock = true;
	setVisible(false);
	mWidget->showMinimized();
}

void WidgetVisibilityHandler::minimize()
{
	mWidget->showMinimized();
}

void WidgetVisibilityHandler::restoreVisibility()
{
	setVisible(true);

	if(!mWasMinimized) {
		showWidget();
	} else {
		mWidget->showMinimized();
	}

	mWindowStateChangeLock = false;
}

void WidgetVisibilityHandler::enforceVisible()
{
	setVisible(true);
	showWidget();
	mWindowStateChangeLock = false;
}

bool WidgetVisibilityHandler::isMaximized()
{
	return mSelectedWindowState == Qt::WindowMaximized;
}

void WidgetVisibilityHandler::updateState()
{
	if(!mWindowStateChangeLock) {
		if(mWidget->isMaximized()) {
			mSelectedWindowState = Qt::WindowMaximized;
		} else if(mWidget->isActiveWindow()){
			mSelectedWindowState = Qt::WindowActive;
		}

		mWasMinimized = mWidget->isMinimized();
	}
}

void WidgetVisibilityHandler::setVisible(bool isVisible)
{
	if(isVisible) {
		mWidget->setWindowOpacity(1.0);
	} else {
		mWidget->setWindowOpacity(0.0);
	}
}

void WidgetVisibilityHandler::showWidget()
{
	mWidget->setWindowState(mSelectedWindowState);
	mWidget->activateWindow();
	mWidget->raise();
	mWidget->show();
}
