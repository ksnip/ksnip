/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#include "CustomSpinBox.h"

CustomSpinBox::CustomSpinBox(int min, int max, QWidget* parent) :
    QSpinBox(parent)
{
    setMinimum(min);
    setMaximum(max);
    setWrapping(false);

    connect(this, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &CustomSpinBox::valueChanged);
}

int CustomSpinBox::value() const
{
    return QSpinBox::value();
}

void CustomSpinBox::setValue(int value)
{
    // Don't emit valueChanged signal values set via this method
    blockSignals(true);

    QSpinBox::setValue(value);

    blockSignals(false);
}
