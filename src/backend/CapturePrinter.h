/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_CAPTUREPRINTER_H
#define KSNIP_CAPTUREPRINTER_H

#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPainter>

class CapturePrinter : public QObject
{
Q_OBJECT
public:
	explicit CapturePrinter(QWidget *parent);
	~CapturePrinter() override = default;
	void print(const QImage &image, const QString &defaultPath);
	void printPreview(const QImage &image, const QString &defaultPath);

private:
	QWidget *mParent;

private slots:
	void printCapture(const QImage &image, QPrinter *p);
};

#endif //KSNIP_CAPTUREPRINTER_H
