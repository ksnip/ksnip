/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "SettingsPickerColorItem.h"

SettingsPickerColorItem::SettingsPickerColorItem(const QColor& color,
        const QString& text,
        QWidget* parent) :
    QFrame(parent), mColor(color), mText(text), mSelected(false)
{
    setToolTip(mText);
    setFixedWidth(24);
    setFixedHeight(21);
}

QColor SettingsPickerColorItem::color() const
{
    return mColor;
}

QString SettingsPickerColorItem::text() const
{
    return mText;
}

bool SettingsPickerColorItem::isSelected() const
{
    return mSelected;
}

void SettingsPickerColorItem::setSelected(bool selected)
{
    mSelected = selected;
    update();
}

void SettingsPickerColorItem::setColor(const QColor& color, const QString& text)
{
    mColor = color;
    mText = text;
    setToolTip(mText);
    update();
}

void SettingsPickerColorItem::mouseMoveEvent(QMouseEvent* event)
{
    setFocus();
    update();
}

void SettingsPickerColorItem::mouseReleaseEvent(QMouseEvent* event)
{
    mSelected = true;
    emit selected();
}

void SettingsPickerColorItem::mousePressEvent(QMouseEvent* event)
{
    setFocus();
    update();
}

void SettingsPickerColorItem::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    auto w = width();            // width of cell in pixels
    auto h = height();           // height of cell in pixels

    p.setPen(QPen(Qt::gray, 0, Qt::SolidLine));

    if (mSelected) {
        p.drawRect(1, 1, w - 3, h - 3);
    }

    p.setPen(QPen(Qt::black, 0, Qt::SolidLine));
    p.drawRect(3, 3, w - 7, h - 7);
    p.fillRect(QRect(4, 4, w - 8, h - 8), QBrush(mColor));

    if (hasFocus()) {
        p.drawRect(0, 0, w - 1, h - 1);
    }
}
