/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "KeySequenceToMacKeyCodeTranslatorTests.h"

#include <Carbon/Carbon.h>

#include "src/gui/globalHotKeys/KeySequenceToMacKeyCodeTranslator.h"

#include "tests/utils/TestRunner.h"

void KeySequenceToMacKeyCodeTranslatorTests::Map_Should_ReturnCommandModifier_When_SequenceContainsCtrl()
{
	// arrange
	KeySequenceToMacKeyCodeTranslator translator;

	// act
	auto result = translator.map(QKeySequence(Qt::CTRL | Qt::Key_R));

	// assert
	QCOMPARE(result.modifier, static_cast<unsigned int>(cmdKey));
	QCOMPARE(result.key, static_cast<unsigned int>(kVK_ANSI_R));
}

void KeySequenceToMacKeyCodeTranslatorTests::Map_Should_ReturnControlModifier_When_SequenceContainsMeta()
{
	// arrange
	KeySequenceToMacKeyCodeTranslator translator;

	// act
	auto result = translator.map(QKeySequence(Qt::META | Qt::Key_R));

	// assert
	QCOMPARE(result.modifier, static_cast<unsigned int>(controlKey));
}

void KeySequenceToMacKeyCodeTranslatorTests::Map_Should_ReturnOptionAndShiftModifiers_When_SequenceContainsAltAndShift()
{
	// arrange
	KeySequenceToMacKeyCodeTranslator translator;

	// act
	auto result = translator.map(QKeySequence(Qt::ALT | Qt::SHIFT | Qt::Key_F));

	// assert
	QCOMPARE(result.modifier, static_cast<unsigned int>(optionKey | shiftKey));
	QCOMPARE(result.key, static_cast<unsigned int>(kVK_ANSI_F));
}

void KeySequenceToMacKeyCodeTranslatorTests::Map_Should_ReturnNoModifier_When_SequenceHasOnlyKey()
{
	// arrange
	KeySequenceToMacKeyCodeTranslator translator;

	// act
	auto result = translator.map(QKeySequence(Qt::Key_F5));

	// assert
	QCOMPARE(result.modifier, 0u);
	QCOMPARE(result.key, static_cast<unsigned int>(kVK_F5));
}

void KeySequenceToMacKeyCodeTranslatorTests::Map_Should_ReturnVirtualKeyCode_When_KeyIsLetterNumberOrFunctionKey()
{
	// arrange
	KeySequenceToMacKeyCodeTranslator translator;

	// act
	auto letter = translator.map(QKeySequence(Qt::CTRL | Qt::Key_Z));
	auto number = translator.map(QKeySequence(Qt::CTRL | Qt::Key_4));
	auto functionKey = translator.map(QKeySequence(Qt::CTRL | Qt::Key_F12));

	// assert
	QCOMPARE(letter.key, static_cast<unsigned int>(kVK_ANSI_Z));
	QCOMPARE(number.key, static_cast<unsigned int>(kVK_ANSI_4));
	QCOMPARE(functionKey.key, static_cast<unsigned int>(kVK_F12));
}

void KeySequenceToMacKeyCodeTranslatorTests::Map_Should_ReturnInvalidKey_When_KeyHasNoMacEquivalent()
{
	// arrange
	KeySequenceToMacKeyCodeTranslator translator;

	// act
	auto result = translator.map(QKeySequence(Qt::CTRL | Qt::Key_Print));

	// assert
	QCOMPARE(result.key, KeySequenceToMacKeyCodeTranslator::InvalidKey);
}

TEST_MAIN(KeySequenceToMacKeyCodeTranslatorTests)
