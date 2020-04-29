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

#include "CapturePrinter.h"

CapturePrinter::CapturePrinter(QWidget *parent) : mParent(parent)
{
	Q_ASSERT(mParent != nullptr);
}

void CapturePrinter::print(const QImage &image, const QString &defaultPath)
{
    QPrinter printer;
    printer.setOutputFileName(defaultPath);
    printer.setOutputFormat(QPrinter::NativeFormat);
    QPrintDialog printDialog(&printer, mParent);

    if (printDialog.exec() == QDialog::Accepted) {
	    printCapture(image, &printer);
    }
}

void CapturePrinter::printCapture(const QImage &image, QPrinter *p)
{
    QPainter painter;
    painter.begin(p);
    auto xScale = p->pageRect().width() / double(image.width());
    auto yScale = p->pageRect().height() / double(image.height());
    auto scale = qMin(xScale, yScale);
    painter.translate(p->paperRect().x() + p->pageRect().width() / 2,
                      p->paperRect().y() + p->pageRect().height() / 2);
    painter.scale(scale, scale);
    painter.translate(-image.width() / 2, -image.height() / 2);
    painter.drawImage(QPoint(0, 0), image);
    painter.end();
}

void CapturePrinter::printPreview(const QImage &image, const QString &defaultPath)
{
    QPrinter printer;
    printer.setOutputFileName(defaultPath);
    printer.setOutputFormat(QPrinter::NativeFormat);
    QPrintPreviewDialog printDialog(&printer, mParent, Qt::Window | Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
	connect(&printDialog, &QPrintPreviewDialog::paintRequested, [this, image](QPrinter *p)
	{
		printCapture(image, p);
	});
    printDialog.exec();
}
