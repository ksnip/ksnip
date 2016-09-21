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

#include "SizeComboBox.h"

SizeComboBox::SizeComboBox ( int start, int increment, int steps, QWidget *parent ) : QComboBox ( parent )
{
    populateList(start, increment, steps);
}

//
// Public Functions
//
int SizeComboBox::size() const
{
    return itemData ( currentIndex() ).toInt();
}

void SizeComboBox::setSize ( int size )
{
    setCurrentIndex ( findData ( size ) );
}

//
// Private Functions
//
void SizeComboBox::populateList ( int start, int increment, int steps )
{
    for ( int i = 0; i < steps; i++ ) {
        addItem ( QString::number ( start + i * increment ), start + i * increment );
    }
}
