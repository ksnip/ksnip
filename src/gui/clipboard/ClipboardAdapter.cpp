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

#include "ClipboardAdapter.h"

ClipboardAdapter::ClipboardAdapter() :
	mClipboard(QGuiApplication::clipboard())
{
	connect(mClipboard, &QClipboard::changed, this, &ClipboardAdapter::selectionChanged);
}

QPixmap ClipboardAdapter::pixmap() const
{
	auto pixmap = mClipboard->pixmap();

	if(pixmap.isNull()) {
		pixmap = QPixmap(url());
	}
	return pixmap;
}

QString ClipboardAdapter::url() const
{
	return FileUrlHelper::parse(mClipboard->text());
}

bool ClipboardAdapter::isPixmap() const
{
	return !pixmap().isNull();
}

void ClipboardAdapter::setImage(const QImage &image)
{
	mClipboard->setImage(image);
}

void ClipboardAdapter::selectionChanged(QClipboard::Mode mode) const
{
	if(mode == QClipboard::Mode::Clipboard) {
		emit changed(isPixmap());
	}
}

void ClipboardAdapter::setText(const QString &text)
{
	mClipboard->setText(text);
}
