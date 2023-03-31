/*
 * Copyright (C) 2023 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_IMAGEFROMSTDINPUTREADER_H
#define KSNIP_IMAGEFROMSTDINPUTREADER_H

#include <QByteArray>

#include <iostream>

#include "IImageFromStdInputReader.h"

class ImageFromStdInputReader : public IImageFromStdInputReader
{
public:
    ImageFromStdInputReader() = default;
    ~ImageFromStdInputReader() = default;
    QByteArray read() const override;
};

#endif //KSNIP_IMAGEFROMSTDINPUTREADER_H
