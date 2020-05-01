/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

/*
 * Inspired by Skycoder42`s QHotKey implementation https://github.com/Skycoder42/QHotkey/blob/master/QHotkey/qhotkey_x11.cpp
 */

#include "X11KeyHandler.h"

#include "X11ErrorLogger.h"

X11KeyHandler::X11KeyHandler() :
	mFixedModifiers({ 0, Mod2Mask, LockMask, (Mod2Mask | LockMask)})
{
}

X11KeyHandler::~X11KeyHandler()
{
	unregisterKey();
}

bool X11KeyHandler::registerKey(const QKeySequence &keySequence)
{
	auto display = QX11Info::display();
	if(!display) {
		return false;
	}

	X11ErrorLogger x11ErrorLogger;
	mKeyCodeCombo = mKeyCodeMapper.map(keySequence);
	for(auto fixedModifier : mFixedModifiers) {
		GrabKey(display, fixedModifier);
	}

	XSync(display, False);
	return true;
}

bool X11KeyHandler::isKeyPressed(void *message)
{
	auto genericEvent = static_cast<xcb_generic_event_t *>(message);
	if (genericEvent->response_type == XCB_KEY_PRESS) {
		auto keyEvent = static_cast<xcb_key_press_event_t *>(message);

		for(auto fixedModifier : mFixedModifiers) {
			if(isMatching(keyEvent, fixedModifier)) {
				return true;
			}
		}
	}
	return false;
}

bool X11KeyHandler::isMatching(const xcb_key_press_event_t *keyEvent, unsigned int fixedModifier) const
{ return keyEvent->detail == mKeyCodeCombo.key && keyEvent->state == (mKeyCodeCombo.modifier | fixedModifier); }

void X11KeyHandler::unregisterKey() const
{
	auto display = QX11Info::display();
	if(!display) {
		return;
	}

	X11ErrorLogger x11ErrorLogger;
	for(auto fixedModifier : mFixedModifiers) {
		UngrabKey(display, fixedModifier);
	}

	XSync(display, False);
}

void X11KeyHandler::GrabKey(Display *display, unsigned int fixedModifier) const
{
	XGrabKey(display, mKeyCodeCombo.key, mKeyCodeCombo.modifier | fixedModifier, DefaultRootWindow(display), true, GrabModeAsync, GrabModeAsync);
}

void X11KeyHandler::UngrabKey(Display *display, unsigned int fixedModifier) const
{
	XUngrabKey(display, mKeyCodeCombo.key, mKeyCodeCombo.modifier | fixedModifier, DefaultRootWindow(display));
}
