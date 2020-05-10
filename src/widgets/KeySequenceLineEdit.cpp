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

#include "KeySequenceLineEdit.h"

KeySequenceLineEdit::KeySequenceLineEdit(QWidget *widget, const QList<Qt::Key> &allowedKeys) : QLineEdit(widget)
{
	mAllowedKeys = allowedKeys;
}

KeySequenceLineEdit::~KeySequenceLineEdit()
{
	mSpecialKeyFilters.clear();
}

void KeySequenceLineEdit::keyPressEvent(QKeyEvent *event)
{
	mModifiers = event->modifiers();
	mKey = getAllowedKey(event);
	updateKeySequence();
}

Qt::Key KeySequenceLineEdit::getAllowedKey(const QKeyEvent *event) const
{
	return mAllowedKeys.contains(static_cast<Qt::Key>(event->key())) ? static_cast<Qt::Key>(event->key()) : Qt::Key_unknown;
}

void KeySequenceLineEdit::updateKeySequence()
{
	mKeySequence = mKey == Qt::Key_unknown ? QKeySequence(mModifiers) : QKeySequence(mModifiers + mKey);
	updateText();
}

void KeySequenceLineEdit::keyReleaseEvent(QKeyEvent *event)
{
	mModifiers = Qt::NoModifier;
	mKey = Qt::Key_unknown;
	QWidget::keyReleaseEvent(event);
}

void KeySequenceLineEdit::updateText()
{
	setText(mKeySequence.toString());
}

QKeySequence KeySequenceLineEdit::value() const
{
	return mKeySequence;
}

void KeySequenceLineEdit::clear()
{
	mKeySequence = QKeySequence();
	updateText();
}

void KeySequenceLineEdit::setValue(const QKeySequence &keySequence)
{
	mKeySequence = keySequence;
	updateText();
}

void KeySequenceLineEdit::focusInEvent(QFocusEvent *event)
{
	setupSpecialKeyHandling();
	QLineEdit::focusInEvent(event);
}

void KeySequenceLineEdit::focusOutEvent(QFocusEvent *event)
{
	removeSpecialKeyHandler();
	QLineEdit::focusOutEvent(event);
}

void KeySequenceLineEdit::removeSpecialKeyHandler()
{
	for(const auto& keyFilter : mSpecialKeyFilters) {
		QApplication::instance()->removeNativeEventFilter(keyFilter.data());
	}
	mSpecialKeyFilters.clear();
}

void KeySequenceLineEdit::keyPressed(Qt::Key key)
{
	mKey = key;
	updateKeySequence();
}

void KeySequenceLineEdit::setupSpecialKeyHandling()
{
	addSpecialKeyHandler(Qt::Key_Print, Qt::Key_Print);
	addSpecialKeyHandler(Qt::CTRL + Qt::Key_Print, Qt::Key_Print);
	addSpecialKeyHandler(Qt::ALT + Qt::Key_Print, Qt::Key_Print);
	addSpecialKeyHandler(Qt::SHIFT + Qt::Key_Print, Qt::Key_Print);
	addSpecialKeyHandler(Qt::CTRL + Qt::ALT + Qt::Key_Print, Qt::Key_Print);
	addSpecialKeyHandler(Qt::CTRL + Qt::SHIFT + Qt::Key_Print, Qt::Key_Print);
	addSpecialKeyHandler(Qt::ALT + Qt::SHIFT + Qt::Key_Print, Qt::Key_Print);
	addSpecialKeyHandler(Qt::CTRL + Qt::ALT + Qt::SHIFT + Qt::Key_Print, Qt::Key_Print);
}

void KeySequenceLineEdit::addSpecialKeyHandler(const QKeySequence &keySequence, Qt::Key key)
{
	auto keyHandler = KeyHandlerFactory::create();
	keyHandler->registerKey(keySequence);
	auto keyFilter = QSharedPointer<NativeKeyEventFilter>(new NativeKeyEventFilter(keyHandler));
	connect(keyFilter.data(), &NativeKeyEventFilter::triggered, [this, key]() { keyPressed(key); });
	mSpecialKeyFilters.append(keyFilter);
	QApplication::instance()->installNativeEventFilter(keyFilter.data());
}
