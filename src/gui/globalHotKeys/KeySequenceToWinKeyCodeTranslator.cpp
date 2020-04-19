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

#include "KeySequenceToWinKeyCodeTranslator.h"

KeySequenceToWinKeyCodeTranslator::KeySequenceToWinKeyCodeTranslator()
{
	mHotKeyMap = HotKeyMap::instance();
}

KeyCodeCombo KeySequenceToWinKeyCodeTranslator::map(const QKeySequence &keySequence) const
{
	auto sequenceString = keySequence.toString().toUpper();
	auto modifierString = sequenceString.section(QStringLiteral("+"), 0, -2);
	auto keyString = sequenceString.section(QStringLiteral("+"), -1, -1);

	auto modifier = getModifier(modifierString);
	auto key = getKey(keyString);

	return KeyCodeCombo(modifier, key);
}

unsigned int KeySequenceToWinKeyCodeTranslator::getModifier(const QString &modifierString) const
{
	unsigned int modifier = MOD_NOREPEAT;
	if (modifierString.contains(QStringLiteral("SHIFT"))) {
		modifier |= MOD_SHIFT;
	}
	if (modifierString.contains(QStringLiteral("ALT"))) {
		modifier |= MOD_ALT;
	}
	if (modifierString.contains(QStringLiteral("CTRL"))) {
		modifier |= MOD_CONTROL;
	}

	return modifier;
}

unsigned int KeySequenceToWinKeyCodeTranslator::getKey(const QString &keyString) const
{
	auto key = mHotKeyMap->getKeyForString(keyString);
	switch (key) {
		case Qt::Key_F1:
			return VK_F1;
		case Qt::Key_F2:
			return VK_F2;
		case Qt::Key_F3:
			return VK_F3;
		case Qt::Key_F4:
			return VK_F4;
		case Qt::Key_F5:
			return VK_F5;
		case Qt::Key_F6:
			return VK_F6;
		case Qt::Key_F7:
			return VK_F7;
		case Qt::Key_F8:
			return VK_F8;
		case Qt::Key_F9:
			return VK_F9;
		case Qt::Key_F10:
			return VK_F10;
		case Qt::Key_F11:
			return VK_F11;
		case Qt::Key_F12:
			return VK_F12;
		case Qt::Key_Escape:
			return VK_ESCAPE;
		case Qt::Key_Backspace:
			return VK_BACK;
		case Qt::Key_Return:
		case Qt::Key_Enter:
			return VK_RETURN;
		case Qt::Key_Insert:
			return VK_INSERT;
		case Qt::Key_Delete:
			return VK_DELETE;
		case Qt::Key_Pause:
			return VK_PAUSE;
		case Qt::Key_Print:
			return VK_SNAPSHOT;
		case Qt::Key_Home:
			return VK_HOME;
		case Qt::Key_End:
			return VK_END;
		case Qt::Key_Left:
			return VK_LEFT;
		case Qt::Key_Up:
			return VK_UP;
		case Qt::Key_Right:
			return VK_RIGHT;
		case Qt::Key_Down:
			return VK_DOWN;
		case Qt::Key_PageUp:
			return VK_PRIOR;
		case Qt::Key_PageDown:
			return VK_NEXT;
		case Qt::Key_Comma:
		case Qt::Key_Semicolon:
			return VK_OEM_COMMA;
		case Qt::Key_Minus:
		case Qt::Key_Underscore:
			return VK_OEM_MINUS;
		case Qt::Key_Period:
		case Qt::Key_Colon:
			return VK_OEM_PERIOD;
		default:
			return key;
	}
}
