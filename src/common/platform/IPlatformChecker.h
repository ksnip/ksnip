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

#ifndef KSNIP_IPLATFORMCHECKER_H
#define KSNIP_IPLATFORMCHECKER_H

class IPlatformChecker
{
public:
	explicit IPlatformChecker() = default;
	virtual ~IPlatformChecker() = default;

	virtual bool isX11() const = 0;
	virtual bool isWayland() const = 0;
	virtual bool isKde() const = 0;
	virtual bool isGnome() const = 0;
	virtual bool isSnap() const = 0;
	virtual int gnomeVersion() const = 0;
};

#endif //KSNIP_IPLATFORMCHECKER_H
