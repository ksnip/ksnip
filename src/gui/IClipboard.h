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

#ifndef KSNIP_ICLIPBOARD_H
#define KSNIP_ICLIPBOARD_H

#include <QObject>

class IClipboard : public QObject
{
	Q_OBJECT
public:
	explicit IClipboard() = default;
	~IClipboard() override = default;
	virtual QPixmap pixmap() const = 0;
	virtual bool isPixmap() const = 0;
	virtual void setImage(const QImage &image) = 0;
	virtual void setText(const QString &text) = 0;
	virtual QString url() const = 0;

signals:
	void changed(bool isPixmap) const;
};

#endif //KSNIP_ICLIPBOARD_H
