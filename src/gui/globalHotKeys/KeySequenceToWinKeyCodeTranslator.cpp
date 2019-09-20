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

#include "KeySequenceToWinKeyCodeTranslator.h"

KeySequenceToWinKeyCodeTranslator::KeySequenceToWinKeyCodeTranslator()
{
	mHotKeyMap = HotKeyMap::instance();
}

WinKeyCodeCombo KeySequenceToWinKeyCodeTranslator::map(const QKeySequence &keySequence) const
{
	auto sequenceString = keySequence.toString().toUpper();
	auto modifierString = sequenceString.section(QStringLiteral("+"), 0, -2);
	auto keyString = sequenceString.section(QStringLiteral("+"), -1, -1);

	auto modifier = getModifier(modifierString);
	auto key = getKey(keyString);

	return WinKeyCodeCombo(modifier, key);
}

unsigned int KeySequenceToWinKeyCodeTranslator::getModifier(const QString &modifierString) const
{
	unsigned int modifier = 0;
	if (modifierString.contains(QStringLiteral("SHIFT"))) {
		modifier |= MOD_SHIFT;
	}
	if (modifierString.contains(QStringLiteral("ALT"))) {
		modifier |= MOD_ALT;
	}
	if (modifierString.contains(QStringLiteral("CTRL"))) {
		modifier |= MOD_CONTROL;
	}

	modifier |= 0x4000;

	return modifier;
}

unsigned int KeySequenceToWinKeyCodeTranslator::getKey(const QString &keyString) const
{
	return mHotKeyMap->getKeyForString(keyString);
}
