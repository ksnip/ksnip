/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "X11KeyHandler.h"

#include <xcb/xcb.h>
#include <X11/Xlib.h>

X11KeyHandler::X11KeyHandler()
{
	mFixedModifiers = { 0, Mod2Mask, LockMask, (Mod2Mask | LockMask)};
}

X11KeyHandler::~X11KeyHandler()
{
	unregisterKey();
}

bool X11KeyHandler::registerKey(const QKeySequence &keySequence)
{
	qDebug("Global Hotkey: Trying to register Hotkey");
	auto display = QX11Info::display();
	if(!display) {
		qDebug("Global Hotkey: No Display Found");
		return false;
	}

	mKeyCodeCombo = mKeyCodeMapper.map(keySequence);
	for(auto fixedModifier : mFixedModifiers) {
		XGrabKey(display, mKeyCodeCombo.key, mKeyCodeCombo.modifier | fixedModifier, DefaultRootWindow(display), true, GrabModeAsync, GrabModeAsync);
	}

	XSync(display, False);
	qDebug("Global Hotkey: Hotkey registered %s + %s", qPrintable(QString::number(mKeyCodeCombo.modifier)), qPrintable(qPrintable(QString::number(mKeyCodeCombo.key))));
	return true;
}

bool X11KeyHandler::isKeyPressed(void *message)
{
	auto genericEvent = static_cast<xcb_generic_event_t *>(message);
//	qDebug("Global Hotkey: Native event occurred");
	if (genericEvent->response_type == XCB_KEY_PRESS) {
		auto keyEvent = static_cast<xcb_key_press_event_t *>(message);
		qDebug("Global Hotkey: Hotkey pressed %s + %s", qPrintable(QString::number(keyEvent->state)), qPrintable(qPrintable(QString::number(keyEvent->detail))));
		auto isMatch = keyEvent->detail == mKeyCodeCombo.key && keyEvent->state == mKeyCodeCombo.modifier;
		if(isMatch) {
			qDebug("We have a match");
		}
		return isMatch;
	}
//	qDebug("Global Hotkey: Event was not Hotkey");
	return false;
}

void X11KeyHandler::unregisterKey() const
{
	qDebug("Global Hotkey: Trying to unregister Hotkey");
	auto display = QX11Info::display();
	if(!display) {
		qDebug("Global Hotkey: No Display Found");
		return;
	}

	for(auto fixedModifier : mFixedModifiers) {
		XUngrabKey(display, mKeyCodeCombo.key, mKeyCodeCombo.modifier | fixedModifier, DefaultRootWindow(display));
	}

	XSync(display, False);

	qDebug("Global Hotkey: Hotkey unregistered %s + %s", qPrintable(QString::number(mKeyCodeCombo.modifier)), qPrintable(qPrintable(QString::number(mKeyCodeCombo.key))));
}
