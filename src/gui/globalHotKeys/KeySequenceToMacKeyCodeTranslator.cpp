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

#include "KeySequenceToMacKeyCodeTranslator.h"

#include <Carbon/Carbon.h>

KeySequenceToMacKeyCodeTranslator::KeySequenceToMacKeyCodeTranslator()
{
	mHotKeyMap = HotKeyMap::instance();
}

KeyCodeCombo KeySequenceToMacKeyCodeTranslator::map(const QKeySequence &keySequence) const
{
	auto sequenceString = keySequence.toString().toUpper();
	auto modifierString = sequenceString.section(QLatin1String("+"), 0, -2);
	auto keyString = sequenceString.section(QLatin1String("+"), -1, -1);

	auto modifier = getModifier(modifierString);
	auto key = getKey(keyString);

	return KeyCodeCombo(modifier, key);
}

unsigned int KeySequenceToMacKeyCodeTranslator::getModifier(const QString &modifierString) const
{
	// Qt swaps Ctrl and Meta on macOS: Ctrl is the Command key and Meta is
	// the Control key. The portable text of the key sequence uses the Qt names.
	unsigned int modifier = 0;
	if (modifierString.contains(QLatin1String("SHIFT"))) {
		modifier |= shiftKey;
	}
	if (modifierString.contains(QLatin1String("ALT"))) {
		modifier |= optionKey;
	}
	if (modifierString.contains(QLatin1String("CTRL"))) {
		modifier |= cmdKey;
	}
	if (modifierString.contains(QLatin1String("META"))) {
		modifier |= controlKey;
	}

	return modifier;
}

unsigned int KeySequenceToMacKeyCodeTranslator::getKey(const QString &keyString) const
{
	auto key = mHotKeyMap->getKeyForString(keyString);
	switch (key) {
		case Qt::Key_A: return kVK_ANSI_A;
		case Qt::Key_B: return kVK_ANSI_B;
		case Qt::Key_C: return kVK_ANSI_C;
		case Qt::Key_D: return kVK_ANSI_D;
		case Qt::Key_E: return kVK_ANSI_E;
		case Qt::Key_F: return kVK_ANSI_F;
		case Qt::Key_G: return kVK_ANSI_G;
		case Qt::Key_H: return kVK_ANSI_H;
		case Qt::Key_I: return kVK_ANSI_I;
		case Qt::Key_J: return kVK_ANSI_J;
		case Qt::Key_K: return kVK_ANSI_K;
		case Qt::Key_L: return kVK_ANSI_L;
		case Qt::Key_M: return kVK_ANSI_M;
		case Qt::Key_N: return kVK_ANSI_N;
		case Qt::Key_O: return kVK_ANSI_O;
		case Qt::Key_P: return kVK_ANSI_P;
		case Qt::Key_Q: return kVK_ANSI_Q;
		case Qt::Key_R: return kVK_ANSI_R;
		case Qt::Key_S: return kVK_ANSI_S;
		case Qt::Key_T: return kVK_ANSI_T;
		case Qt::Key_U: return kVK_ANSI_U;
		case Qt::Key_V: return kVK_ANSI_V;
		case Qt::Key_W: return kVK_ANSI_W;
		case Qt::Key_X: return kVK_ANSI_X;
		case Qt::Key_Y: return kVK_ANSI_Y;
		case Qt::Key_Z: return kVK_ANSI_Z;
		case Qt::Key_0: return kVK_ANSI_0;
		case Qt::Key_1: return kVK_ANSI_1;
		case Qt::Key_2: return kVK_ANSI_2;
		case Qt::Key_3: return kVK_ANSI_3;
		case Qt::Key_4: return kVK_ANSI_4;
		case Qt::Key_5: return kVK_ANSI_5;
		case Qt::Key_6: return kVK_ANSI_6;
		case Qt::Key_7: return kVK_ANSI_7;
		case Qt::Key_8: return kVK_ANSI_8;
		case Qt::Key_9: return kVK_ANSI_9;
		case Qt::Key_F1: return kVK_F1;
		case Qt::Key_F2: return kVK_F2;
		case Qt::Key_F3: return kVK_F3;
		case Qt::Key_F4: return kVK_F4;
		case Qt::Key_F5: return kVK_F5;
		case Qt::Key_F6: return kVK_F6;
		case Qt::Key_F7: return kVK_F7;
		case Qt::Key_F8: return kVK_F8;
		case Qt::Key_F9: return kVK_F9;
		case Qt::Key_F10: return kVK_F10;
		case Qt::Key_F11: return kVK_F11;
		case Qt::Key_F12: return kVK_F12;
		case Qt::Key_Return: return kVK_Return;
		case Qt::Key_Enter: return kVK_ANSI_KeypadEnter;
		case Qt::Key_Escape: return kVK_Escape;
		case Qt::Key_Backspace: return kVK_Delete;
		case Qt::Key_Delete: return kVK_ForwardDelete;
		case Qt::Key_Left: return kVK_LeftArrow;
		case Qt::Key_Right: return kVK_RightArrow;
		case Qt::Key_Up: return kVK_UpArrow;
		case Qt::Key_Down: return kVK_DownArrow;
		case Qt::Key_Home: return kVK_Home;
		case Qt::Key_End: return kVK_End;
		case Qt::Key_PageUp: return kVK_PageUp;
		case Qt::Key_PageDown: return kVK_PageDown;
		case Qt::Key_Comma: return kVK_ANSI_Comma;
		case Qt::Key_Period: return kVK_ANSI_Period;
		case Qt::Key_Slash: return kVK_ANSI_Slash;
		case Qt::Key_Minus: return kVK_ANSI_Minus;
		case Qt::Key_Underscore: return kVK_ANSI_Minus;
		case Qt::Key_Semicolon: return kVK_ANSI_Semicolon;
		case Qt::Key_Colon: return kVK_ANSI_Semicolon;
		default: return InvalidKey; // e.g. Print, Pause and Insert do not exist on Mac keyboards
	}
}
