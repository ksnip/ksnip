/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
 *
 */


#include "CustomToolButton.h"

CustomToolButton::CustomToolButton(QWidget* parent) : QToolButton(parent)
{
    setPopupMode(QToolButton::MenuButtonPopup);
    QObject::connect(this, SIGNAL(triggered(QAction*)), this, SLOT(setDefaultAction(QAction*)));
}

//
// Public Functions
//

/*
 * Function used to set main button text, overriding the usual behavior where the text of the
 * selected action is set
 */
void CustomToolButton::setButtonText(const QString& text)
{
    buttonText = text;
    QToolButton::setText(text);
}

//
// Public Slots
//

/*
 * Overriding setDefaultAction function to prevent changing of text when a new action is selected,
 * the main text on the button is supposed to stay the same.
 */
void CustomToolButton::setDefaultAction(QAction* action)
{
    QToolButton::setDefaultAction(action);
    setText(buttonText);
}

void CustomToolButton::trigger()
{
    if (defaultAction() != 0) {
        defaultAction()->trigger();
    }
}
