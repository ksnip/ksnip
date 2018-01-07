/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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

#include "NumberSequencer.h"

NumberSequencer* NumberSequencer::instance()
{
    static NumberSequencer instance;
    return &instance;
}

int NumberSequencer::getNumberAndIncrement()
{
    auto currentNumber = mSequenceNumber;
    setNextNumber(mSequenceNumber + 1);
    emit numberChanged(mSequenceNumber);
    return currentNumber;
}

int NumberSequencer::currentNumber()
{
    return mSequenceNumber;
}

void NumberSequencer::setNextNumber(int number)
{
    if (number > max()) {
        mSequenceNumber = min();
    } else if (number < min()) {
        mSequenceNumber = min();
    } else {
        mSequenceNumber = number;
    }
}

void NumberSequencer::resetNumber()
{
    mSequenceNumber = min();
}

int NumberSequencer::min() const
{
    return minValue;
}

int NumberSequencer::max() const
{
    return maxValue;
}
