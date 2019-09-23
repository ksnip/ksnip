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

	mKeyCodeCombo = mKeyCodeMapper.map(keySequence);
	XGrabKey(display, mKeyCodeCombo.key, mKeyCodeCombo.modifier, DefaultRootWindow(display), true, GrabModeAsync, GrabModeAsync);

	XSync(display, False);
	return true;
}

bool X11KeyHandler::isKeyPressed(void *message)
{
	auto genericEvent = static_cast<xcb_generic_event_t *>(message);
	if (genericEvent->response_type == XCB_KEY_PRESS) {
		auto keyEvent = static_cast<xcb_key_press_event_t *>(message);
		return keyEvent->detail == mKeyCodeCombo.key && keyEvent->state == mKeyCodeCombo.modifier;
	}
	return false;
}

void X11KeyHandler::unregisterKey() const
{
	auto display = QX11Info::display();
	if(!display) {
		return;
	}

	XUngrabKey(display, mKeyCodeCombo.key, mKeyCodeCombo.modifier, DefaultRootWindow(display));
	XSync(display, False);
}
