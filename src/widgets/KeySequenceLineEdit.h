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

#ifndef KSNIP_KEYSEQUENCELINEEDIT_H
#define KSNIP_KEYSEQUENCELINEEDIT_H

#include <QLineEdit>
#include <QKeySequence>
#include <QKeyEvent>
#include <QApplication>

#include "src/gui/globalHotKeys/KeyHandlerFactory.h"
#include "src/gui/globalHotKeys/NativeKeyEventFilter.h"

class KeySequenceLineEdit : public QLineEdit
{
	Q_OBJECT
public:
	explicit KeySequenceLineEdit(QWidget *widget, const QList<Qt::Key> &allowedKeys);
	~KeySequenceLineEdit() override;
	QKeySequence value() const;
	void setValue(const QKeySequence &keySequence);
	void clear();

protected:
	void keyPressEvent(QKeyEvent *event) override;
	void keyReleaseEvent(QKeyEvent *event) override;
	void focusInEvent(QFocusEvent *event) override;
	void focusOutEvent(QFocusEvent *event) override;

private:
	QKeySequence mKeySequence;
	Qt::KeyboardModifiers mModifiers;
	Qt::Key mKey;
	QList<Qt::Key> mAllowedKeys;
	QList<QSharedPointer<NativeKeyEventFilter>> mSpecialKeyFilters;

	void updateText();
	void keyPressed(Qt::Key key);
	void setupSpecialKeyHandling();
	void updateKeySequence();
	void addSpecialKeyHandler(const QKeySequence &keySequence, Qt::Key key);
	Qt::Key getAllowedKey(const QKeyEvent *event) const;
	void removeSpecialKeyHandler();
};


#endif //KSNIP_KEYSEQUENCELINEEDIT_H
