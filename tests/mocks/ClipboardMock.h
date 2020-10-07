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

#ifndef KSNIP_CLIPBOARDMOCK_H
#define KSNIP_CLIPBOARDMOCK_H

#include <QPixmap>
#include <QImage>

#include "src/gui/clipboard/IClipboard.h"

class ClipboardMock : public IClipboard
{
Q_OBJECT
public:
	explicit ClipboardMock() = default;
	~ClipboardMock() override = default;
	QPixmap pixmap() const override;
	bool isPixmap() const override;
	void setImage(const QImage &image) override;
	void setText(const QString &text) override;
	QString url() const override;

	// Mock Methods
	int setText_callCounter(const QString &text) const;
	int setImage_callCounter(const QImage &image) const;
	QImage setImage_set() const;
	QString setText_get() const;

private:
	QImage mSetImage;
	QString mSetText;
};


#endif //KSNIP_CLIPBOARDMOCK_H
