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

#include "SnippingAreaResizerInfoText.h"

SnippingAreaResizerInfoText::SnippingAreaResizerInfoText(QObject *parent) :
	AbstractSnippingAreaInfoText(parent)
{
}

void SnippingAreaResizerInfoText::updateInfoText()
{
	QStringList infoTextLines = {
			tr("Resize selected rect using the handles or move it by dragging the selection."),
			tr("Use arrow keys to move the selection."),
			tr("Use arrow keys while pressing CTRL to move top left handle."),
			tr("Use arrow keys while pressing ALT to move bottom right handle."),
			tr("Confirm selection by pressing ENTER/RETURN or abort by pressing ESC."),
			tr("This message can be disabled via settings.")
	};

	setInfoText(infoTextLines);
}
