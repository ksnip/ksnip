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

#include <iostream>

CustomToolButton::CustomToolButton(QWidget* parent) : QToolButton(parent)
{
    setPopupMode(QToolButton::MenuButtonPopup);
    QObject::connect(this, SIGNAL(triggered(QAction*)), this, SLOT(setDefaultAction(QAction*)));
}

void CustomToolButton::setMenu(QMenu *menu)
{
    /* 
     * When a new menu is added to this button, check the size of all it's actions in order to
     * to have width set to the largest of them, preventing change in size when switching between
     * the different tools. The integer that is added to the value is to account for the drop down
     * arrow on the right side, which we don't have with normal buttons.
     */
    setMinimumWidth(getLargestWidth(menu->actions()) + 30 );
    QToolButton::setMenu(menu);
}

/*
 * Get the largest width of all actions provided in the Qlist and return this value. QActions have 
 * no own width, therefor use a temporary dummy button. 
 */
int CustomToolButton::getLargestWidth(QList<QAction*> list)
{
    QToolButton *tmpButton = new QToolButton;
    int largestWidth;
    
    for (int i = 0; i < list.count(); i++)
    {
        tmpButton->setText(list.at(i)->text());
        tmpButton->setIcon(list.at(i)->icon());
        tmpButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        
        if( tmpButton->sizeHint().width() > largestWidth)
            largestWidth = tmpButton->sizeHint().width();
    }
    
    delete tmpButton;
    
    return largestWidth;
}


