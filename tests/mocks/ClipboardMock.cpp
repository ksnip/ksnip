/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "ClipboardMock.h"

QPixmap ClipboardMock::pixmap() const
{
	return QPixmap();
}

bool ClipboardMock::isPixmap() const
{
	return false;
}

void ClipboardMock::setImage(const QImage &image)
{
	mSetImage = image;
}

void ClipboardMock::setText(const QString &text)
{
	mSetText = text;
}

QString ClipboardMock::url() const
{
	return QString();
}

int ClipboardMock::setText_callCounter(const QString &text) const
{
	return -1;
}

int ClipboardMock::setImage_callCounter(const QImage &image) const
{
	return -1;
}

QImage ClipboardMock::setImage_set() const
{
	return mSetImage;
}

QString ClipboardMock::setText_get() const
{
	return mSetText;
}
