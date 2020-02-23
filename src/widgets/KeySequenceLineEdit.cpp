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

#include "KeySequenceLineEdit.h"

KeySequenceLineEdit::KeySequenceLineEdit(QWidget *widget, const QList<Qt::Key> &allowedKeys) : QLineEdit(widget)
{
	mAllowedKeys = allowedKeys;

	setupPrintKeyHandling();
}

KeySequenceLineEdit::~KeySequenceLineEdit()
{
	delete mPrintKeyHandler;
	delete mNativeKeyFilter;
}

void KeySequenceLineEdit::keyPressEvent(QKeyEvent *event)
{
	mModifiers = event->modifiers();

	if(mAllowedKeys.contains(static_cast<Qt::Key>(event->key()))) {
		mKey = static_cast<Qt::Key>(event->key());
	} else {
		mKey = Qt::Key_unknown;
	}

	updateKeySequence();
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

void KeySequenceLineEdit::setValue(const QKeySequence &keySequence)
{
	mKeySequence = keySequence;
	updateText();
}

void KeySequenceLineEdit::focusInEvent(QFocusEvent *event)
{
	QApplication::instance()->installNativeEventFilter(mNativeKeyFilter);

	QLineEdit::focusInEvent(event);
}

void KeySequenceLineEdit::focusOutEvent(QFocusEvent *event)
{
	QApplication::instance()->removeNativeEventFilter(mNativeKeyFilter);

	QLineEdit::focusOutEvent(event);
}

void KeySequenceLineEdit::printKeyPressed()
{
	mKey = Qt::Key_Print;
	updateKeySequence();
}

void KeySequenceLineEdit::setupPrintKeyHandling()
{
	mPrintKeyHandler = KeyHandlerFactory::create();
	mPrintKeyHandler->registerKey(Qt::Key_Print);
	mNativeKeyFilter = new NativeKeyEventFilter(mPrintKeyHandler);
	connect(mNativeKeyFilter, &NativeKeyEventFilter::triggered, this, &KeySequenceLineEdit::printKeyPressed);
}
