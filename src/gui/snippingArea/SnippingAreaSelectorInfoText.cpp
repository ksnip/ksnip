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

#include "SnippingAreaSelectorInfoText.h"

SnippingAreaSelectorInfoText::SnippingAreaSelectorInfoText(QObject *parent) :
	AbstractSnippingAreaInfoText(parent),
	mIsResizingDefault(false)
{
}

void SnippingAreaSelectorInfoText::updateInfoText()
{
	auto resizeAfterSelection = tr("Hold CTRL pressed to resize selection after selecting.");
	auto dontResizeAfterSelection = tr("Hold CTRL pressed to prevent resizing after selecting.");

	QStringList infoTextLines = {
			tr("Click and Drag to select a rectangular area or press ESC to quit."),
			mIsResizingDefault ? dontResizeAfterSelection : resizeAfterSelection,
			tr("Operation will be canceled after 60 sec when no selection made."),
			tr("This message can be disabled via settings.")
	};

	setInfoText(infoTextLines);
}

void SnippingAreaSelectorInfoText::activate(const QRectF &snippingAreaGeometry, bool isResizingDefault)
{
	mIsResizingDefault = isResizingDefault;
	AbstractSnippingAreaInfoText::activate(snippingAreaGeometry);
}
