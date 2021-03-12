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

#ifndef KSNIP_IIMAGEPATHSTORAGE_H
#define KSNIP_IIMAGEPATHSTORAGE_H

#include <QString>

class IImagePathStorage
{
public:
	virtual ~IImagePathStorage() = default;
	virtual void store(const QString &value, int index) = 0;
	virtual QString load(int index) = 0;
	virtual int count() = 0;
};

#endif //KSNIP_IIMAGEPATHSTORAGE_H
