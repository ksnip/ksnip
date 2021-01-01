/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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

#include "ColorButton.h"

ColorButton::ColorButton(QWidget* parent) :
	QPushButton(parent),
	mShowAlphaChannel(false)
{
    connect(this, &ColorButton::clicked, this, &ColorButton::openDialog);
	setIconSize(QSize(48, iconSize().height()));
}

QColor ColorButton::color() const
{
    return mColor;
}

void ColorButton::setColor(const QColor& color)
{
    mColor = color;
    auto pixmapIcon = createPixmapFromColor(mColor);
    setIcon(pixmapIcon);
    setToolTip(mShowAlphaChannel ? mColor.name(QColor::HexArgb) : mColor.name());
}

void ColorButton::setShowAlphaChannel(bool enabled)
{
	mShowAlphaChannel = enabled;
}

QPixmap ColorButton::createPixmapFromColor(const QColor& color)
{
	QImage tiledBackground(QSize(10, 10), QImage::Format_ARGB32_Premultiplied);
	tiledBackground.fill(Qt::white);
	QPainter tiledBackgroundPainter(&tiledBackground);
	tiledBackgroundPainter.setPen(Qt::NoPen);
	tiledBackgroundPainter.setBrush(Qt::gray);
	tiledBackgroundPainter.drawRect(0, 0, 5, 5);
	tiledBackgroundPainter.drawRect(5, 5, 10, 10);

	QPixmap pixmap(iconSize());
	QPainter pixmapPainter(&pixmap);
	pixmapPainter.setPen(Qt::gray);
	pixmapPainter.setBrush(tiledBackground);
	pixmapPainter.drawRect(0,0, iconSize().width() - 1, iconSize().height() - 1);
	pixmapPainter.setBrush(color);
	pixmapPainter.drawRect(0,0, iconSize().width() - 1, iconSize().height() - 1);
	return pixmap;
}

void ColorButton::openDialog()
{
	QFlags<QColorDialog::ColorDialogOption> options;

	if(mShowAlphaChannel) {
		options |= QColorDialog::ShowAlphaChannel;
	}

	auto color = QColorDialog::getColor(mColor, parentWidget(), QString(), options);
	
	if (mShowAlphaChannel) 
	if (color.isValid() && color != mColor) {
		setColor(color);
	}
}
