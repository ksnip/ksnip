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

#include "KeySequenceToX11KeyCodeTranslator.h"

#include <X11/Xutil.h>

KeySequenceToX11KeyCodeTranslator::KeySequenceToX11KeyCodeTranslator()
{
	mHotKeyMap = HotKeyMap::instance();
}

KeyCodeCombo KeySequenceToX11KeyCodeTranslator::map(const QKeySequence &keySequence) const
{
	auto sequenceString = keySequence.toString().toUpper();
	auto modifierString = sequenceString.section(QStringLiteral("+"), 0, -2);
	auto keyString = sequenceString.section(QStringLiteral("+"), -1, -1);

	auto modifier = getModifier(modifierString);
	auto key = getKey(keyString);

	return KeyCodeCombo(modifier, key);
}

unsigned int KeySequenceToX11KeyCodeTranslator::getModifier(const QString &modifierString) const
{
	unsigned int modifier = 0;
	if (modifierString.contains(QStringLiteral("SHIFT"))) {
		modifier |= ShiftMask;
	}
	if (modifierString.contains(QStringLiteral("ALT"))) {
		modifier |= Mod1Mask;
	}
	if (modifierString.contains(QStringLiteral("CTRL"))) {
		modifier |= ControlMask;
	}
	if (modifierString.contains(QStringLiteral("META"))) {
		modifier |= Mod4Mask;
	}

	return modifier;
}

unsigned int KeySequenceToX11KeyCodeTranslator::getKey(const QString &keyString) const
{
	auto display = QX11Info::display();
	auto keyCode = getKeyCode(keyString);
	return XKeysymToKeycode(display, keyCode);
}

unsigned int KeySequenceToX11KeyCodeTranslator::getKeyCode(const QString &keyString) const
{
	auto key = mHotKeyMap->getKeyForString(keyString);
	switch (key) {
		case Qt::Key_F1:
			return XK_F1;
		case Qt::Key_F2:
			return XK_F2;
		case Qt::Key_F3:
			return XK_F3;
		case Qt::Key_F4:
			return XK_F4;
		case Qt::Key_F5:
			return XK_F5;
		case Qt::Key_F6:
			return XK_F6;
		case Qt::Key_F7:
			return XK_F7;
		case Qt::Key_F8:
			return XK_F8;
		case Qt::Key_F9:
			return XK_F9;
		case Qt::Key_F10:
			return XK_F10;
		case Qt::Key_F11:
			return XK_F11;
		case Qt::Key_F12:
			return XK_F12;
		case Qt::Key_Delete:
			return XK_Delete;
		case Qt::Key_Insert:
			return XK_Insert;
		case Qt::Key_Print:
			return XK_Print;
		case Qt::Key_Left:
			return XK_Left;
		case Qt::Key_Up:
			return XK_Up;
		case Qt::Key_Right:
			return XK_Right;
		case Qt::Key_Down:
			return XK_Down;
		case Qt::Key_PageDown:
			return XK_Page_Down;
		case Qt::Key_PageUp:
			return XK_Page_Up;
		default:
			return key;
	}
}
