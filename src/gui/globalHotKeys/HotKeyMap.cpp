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

#include "HotKeyMap.h"

HotKeyMap *HotKeyMap::instance()
{
	static HotKeyMap instance;
	return &instance;
}

HotKeyMap::HotKeyMap()
{
	// Numbers
	mKeyToStringMap[Qt::Key_0] = QStringLiteral("0");
	mKeyToStringMap[Qt::Key_1] = QStringLiteral("1");
	mKeyToStringMap[Qt::Key_2] = QStringLiteral("2");
	mKeyToStringMap[Qt::Key_3] = QStringLiteral("3");
	mKeyToStringMap[Qt::Key_4] = QStringLiteral("4");
	mKeyToStringMap[Qt::Key_5] = QStringLiteral("5");
	mKeyToStringMap[Qt::Key_6] = QStringLiteral("6");
	mKeyToStringMap[Qt::Key_7] = QStringLiteral("7");
	mKeyToStringMap[Qt::Key_8] = QStringLiteral("8");
	mKeyToStringMap[Qt::Key_9] = QStringLiteral("9");

	// Misc
	mKeyToStringMap[Qt::Key_Escape] = QStringLiteral("ESCAPE");
	mKeyToStringMap[Qt::Key_Backspace] = QStringLiteral("BACKSPACE");
	mKeyToStringMap[Qt::Key_Return] = QStringLiteral("RETURN");
	mKeyToStringMap[Qt::Key_Enter] = QStringLiteral("ENTER");
	mKeyToStringMap[Qt::Key_Insert] = QStringLiteral("INS");
	mKeyToStringMap[Qt::Key_Delete] = QStringLiteral("DEL");
	mKeyToStringMap[Qt::Key_Pause] = QStringLiteral("PAUSE");
	mKeyToStringMap[Qt::Key_Print] = QStringLiteral("PRINT");
	mKeyToStringMap[Qt::Key_Home] = QStringLiteral("HOME");
	mKeyToStringMap[Qt::Key_End] = QStringLiteral("END");
	mKeyToStringMap[Qt::Key_Left] = QStringLiteral("LEFT");
	mKeyToStringMap[Qt::Key_Up] = QStringLiteral("UP");
	mKeyToStringMap[Qt::Key_Right] = QStringLiteral("RIGHT");
	mKeyToStringMap[Qt::Key_Down] = QStringLiteral("DOWN");
	mKeyToStringMap[Qt::Key_PageUp] = QStringLiteral("PGUP");
	mKeyToStringMap[Qt::Key_PageDown] = QStringLiteral("PGDOWN");
	mKeyToStringMap[Qt::Key_Comma] = QStringLiteral(",");
	mKeyToStringMap[Qt::Key_Underscore] = QStringLiteral("_");
	mKeyToStringMap[Qt::Key_Minus] = QStringLiteral("-");
	mKeyToStringMap[Qt::Key_Period] = QStringLiteral(".");
	mKeyToStringMap[Qt::Key_Slash] = QStringLiteral("/");
	mKeyToStringMap[Qt::Key_Colon] = QStringLiteral(":");
	mKeyToStringMap[Qt::Key_Semicolon] = QStringLiteral(";");

	// F-Keys
	mKeyToStringMap[Qt::Key_F1] = QStringLiteral("F1");
	mKeyToStringMap[Qt::Key_F2] = QStringLiteral("F2");
	mKeyToStringMap[Qt::Key_F3] = QStringLiteral("F3");
	mKeyToStringMap[Qt::Key_F4] = QStringLiteral("F4");
	mKeyToStringMap[Qt::Key_F5] = QStringLiteral("F5");
	mKeyToStringMap[Qt::Key_F6] = QStringLiteral("F6");
	mKeyToStringMap[Qt::Key_F7] = QStringLiteral("F7");
	mKeyToStringMap[Qt::Key_F8] = QStringLiteral("F8");
	mKeyToStringMap[Qt::Key_F9] = QStringLiteral("F9");
	mKeyToStringMap[Qt::Key_F10] = QStringLiteral("F10");
	mKeyToStringMap[Qt::Key_F11] = QStringLiteral("F11");
	mKeyToStringMap[Qt::Key_F12] = QStringLiteral("F12");

	// Letters
	mKeyToStringMap[Qt::Key_A] = QStringLiteral("A");
	mKeyToStringMap[Qt::Key_B] = QStringLiteral("B");
	mKeyToStringMap[Qt::Key_C] = QStringLiteral("C");
	mKeyToStringMap[Qt::Key_D] = QStringLiteral("D");
	mKeyToStringMap[Qt::Key_E] = QStringLiteral("E");
	mKeyToStringMap[Qt::Key_F] = QStringLiteral("F");
	mKeyToStringMap[Qt::Key_G] = QStringLiteral("G");
	mKeyToStringMap[Qt::Key_H] = QStringLiteral("H");
	mKeyToStringMap[Qt::Key_I] = QStringLiteral("I");
	mKeyToStringMap[Qt::Key_J] = QStringLiteral("J");
	mKeyToStringMap[Qt::Key_K] = QStringLiteral("K");
	mKeyToStringMap[Qt::Key_L] = QStringLiteral("L");
	mKeyToStringMap[Qt::Key_M] = QStringLiteral("M");
	mKeyToStringMap[Qt::Key_N] = QStringLiteral("N");
	mKeyToStringMap[Qt::Key_O] = QStringLiteral("O");
	mKeyToStringMap[Qt::Key_P] = QStringLiteral("P");
	mKeyToStringMap[Qt::Key_Q] = QStringLiteral("Q");
	mKeyToStringMap[Qt::Key_R] = QStringLiteral("R");
	mKeyToStringMap[Qt::Key_S] = QStringLiteral("S");
	mKeyToStringMap[Qt::Key_T] = QStringLiteral("T");
	mKeyToStringMap[Qt::Key_U] = QStringLiteral("U");
	mKeyToStringMap[Qt::Key_V] = QStringLiteral("V");
	mKeyToStringMap[Qt::Key_W] = QStringLiteral("W");
	mKeyToStringMap[Qt::Key_X] = QStringLiteral("X");
	mKeyToStringMap[Qt::Key_Y] = QStringLiteral("Y");
	mKeyToStringMap[Qt::Key_Z] = QStringLiteral("Z");
}

Qt::Key HotKeyMap::getKeyForString(const QString &string) const
{
	return mKeyToStringMap.key(string);
}

QList<Qt::Key> HotKeyMap::getAllKeys() const
{
	return mKeyToStringMap.keys();
}
