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

KeySequenceToMacKeyCodeTranslator::KeySequenceToMacKeyCodeTranslator()
{
	mHotKeyMap = HotKeyMap::instance();
}

KeyCodeCombo KeySequenceToMacKeyCodeTranslator::map(const QKeySequence &keySequence) const
{
	auto sequenceString = keySequence.toString().toUpper();
	auto modifierString = sequenceString.section(QStringLiteral("+"), 0, -2);
	auto keyString = sequenceString.section(QStringLiteral("+"), -1, -1);

	auto modifier = getModifier(modifierString);
	auto key = getKey(keyString);

	return KeyCodeCombo(modifier, key);
}

unsigned int KeySequenceToMacKeyCodeTranslator::getModifier(const QString &modifierString) const
{
	unsigned int modifier = 0;
	return modifier;
}

unsigned int KeySequenceToMacKeyCodeTranslator::getKey(const QString &keyString) const
{
	auto key = mHotKeyMap->getKeyForString(keyString);
	return key;
}
