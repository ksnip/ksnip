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
	mKeyToStringMap[Qt::Key_0] = QLatin1String("0");
	mKeyToStringMap[Qt::Key_1] = QLatin1String("1");
	mKeyToStringMap[Qt::Key_2] = QLatin1String("2");
	mKeyToStringMap[Qt::Key_3] = QLatin1String("3");
	mKeyToStringMap[Qt::Key_4] = QLatin1String("4");
	mKeyToStringMap[Qt::Key_5] = QLatin1String("5");
	mKeyToStringMap[Qt::Key_6] = QLatin1String("6");
	mKeyToStringMap[Qt::Key_7] = QLatin1String("7");
	mKeyToStringMap[Qt::Key_8] = QLatin1String("8");
	mKeyToStringMap[Qt::Key_9] = QLatin1String("9");

	// Misc
	mKeyToStringMap[Qt::Key_Escape] = QLatin1String("ESCAPE");
	mKeyToStringMap[Qt::Key_Backspace] = QLatin1String("BACKSPACE");
	mKeyToStringMap[Qt::Key_Return] = QLatin1String("RETURN");
	mKeyToStringMap[Qt::Key_Enter] = QLatin1String("ENTER");
	mKeyToStringMap[Qt::Key_Insert] = QLatin1String("INS");
	mKeyToStringMap[Qt::Key_Delete] = QLatin1String("DEL");
	mKeyToStringMap[Qt::Key_Pause] = QLatin1String("PAUSE");
	mKeyToStringMap[Qt::Key_Print] = QLatin1String("PRINT");
	mKeyToStringMap[Qt::Key_Home] = QLatin1String("HOME");
	mKeyToStringMap[Qt::Key_End] = QLatin1String("END");
	mKeyToStringMap[Qt::Key_Left] = QLatin1String("LEFT");
	mKeyToStringMap[Qt::Key_Up] = QLatin1String("UP");
	mKeyToStringMap[Qt::Key_Right] = QLatin1String("RIGHT");
	mKeyToStringMap[Qt::Key_Down] = QLatin1String("DOWN");
	mKeyToStringMap[Qt::Key_PageUp] = QLatin1String("PGUP");
	mKeyToStringMap[Qt::Key_PageDown] = QLatin1String("PGDOWN");
	mKeyToStringMap[Qt::Key_Comma] = QLatin1String(",");
	mKeyToStringMap[Qt::Key_Underscore] = QLatin1String("_");
	mKeyToStringMap[Qt::Key_Minus] = QLatin1String("-");
	mKeyToStringMap[Qt::Key_Period] = QLatin1String(".");
	mKeyToStringMap[Qt::Key_Slash] = QLatin1String("/");
	mKeyToStringMap[Qt::Key_Colon] = QLatin1String(":");
	mKeyToStringMap[Qt::Key_Semicolon] = QLatin1String(";");

	// F-Keys
	mKeyToStringMap[Qt::Key_F1] = QLatin1String("F1");
	mKeyToStringMap[Qt::Key_F2] = QLatin1String("F2");
	mKeyToStringMap[Qt::Key_F3] = QLatin1String("F3");
	mKeyToStringMap[Qt::Key_F4] = QLatin1String("F4");
	mKeyToStringMap[Qt::Key_F5] = QLatin1String("F5");
	mKeyToStringMap[Qt::Key_F6] = QLatin1String("F6");
	mKeyToStringMap[Qt::Key_F7] = QLatin1String("F7");
	mKeyToStringMap[Qt::Key_F8] = QLatin1String("F8");
	mKeyToStringMap[Qt::Key_F9] = QLatin1String("F9");
	mKeyToStringMap[Qt::Key_F10] = QLatin1String("F10");
	mKeyToStringMap[Qt::Key_F11] = QLatin1String("F11");
	mKeyToStringMap[Qt::Key_F12] = QLatin1String("F12");

	// Letters
	mKeyToStringMap[Qt::Key_A] = QLatin1String("A");
	mKeyToStringMap[Qt::Key_B] = QLatin1String("B");
	mKeyToStringMap[Qt::Key_C] = QLatin1String("C");
	mKeyToStringMap[Qt::Key_D] = QLatin1String("D");
	mKeyToStringMap[Qt::Key_E] = QLatin1String("E");
	mKeyToStringMap[Qt::Key_F] = QLatin1String("F");
	mKeyToStringMap[Qt::Key_G] = QLatin1String("G");
	mKeyToStringMap[Qt::Key_H] = QLatin1String("H");
	mKeyToStringMap[Qt::Key_I] = QLatin1String("I");
	mKeyToStringMap[Qt::Key_J] = QLatin1String("J");
	mKeyToStringMap[Qt::Key_K] = QLatin1String("K");
	mKeyToStringMap[Qt::Key_L] = QLatin1String("L");
	mKeyToStringMap[Qt::Key_M] = QLatin1String("M");
	mKeyToStringMap[Qt::Key_N] = QLatin1String("N");
	mKeyToStringMap[Qt::Key_O] = QLatin1String("O");
	mKeyToStringMap[Qt::Key_P] = QLatin1String("P");
	mKeyToStringMap[Qt::Key_Q] = QLatin1String("Q");
	mKeyToStringMap[Qt::Key_R] = QLatin1String("R");
	mKeyToStringMap[Qt::Key_S] = QLatin1String("S");
	mKeyToStringMap[Qt::Key_T] = QLatin1String("T");
	mKeyToStringMap[Qt::Key_U] = QLatin1String("U");
	mKeyToStringMap[Qt::Key_V] = QLatin1String("V");
	mKeyToStringMap[Qt::Key_W] = QLatin1String("W");
	mKeyToStringMap[Qt::Key_X] = QLatin1String("X");
	mKeyToStringMap[Qt::Key_Y] = QLatin1String("Y");
	mKeyToStringMap[Qt::Key_Z] = QLatin1String("Z");
}

Qt::Key HotKeyMap::getKeyForString(const QString &string) const
{
	return mKeyToStringMap.key(string);
}

QList<Qt::Key> HotKeyMap::getAllKeys() const
{
	return mKeyToStringMap.keys();
}
