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

#ifndef KSNIP_OCRWINDOW_H
#define KSNIP_OCRWINDOW_H

#include <QTextEdit>
#include <QVBoxLayout>

#include "src/gui/modelessWindows/IModelessWindow.h"

class OcrWindow : public IModelessWindow
{
public:
	explicit OcrWindow(const QString &text, const QString &title);
	~OcrWindow() override = default;

protected:
	void closeEvent(QCloseEvent *event) override;

private:
	QTextEdit *mTextEdit;
	QVBoxLayout *mLayout;
};

#endif //KSNIP_OCRWINDOW_H
