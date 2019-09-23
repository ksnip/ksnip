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

	return modifier;
}

unsigned int KeySequenceToX11KeyCodeTranslator::getKey(const QString &keyString) const
{
	auto display = QX11Info::display();
	auto key = mHotKeyMap->getKeyForString(keyString);
	return XKeysymToKeycode(display, key);
}
