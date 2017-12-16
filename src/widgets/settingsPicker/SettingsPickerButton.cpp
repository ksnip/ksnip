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

#include "SettingsPickerButton.h"

SettingsPickerButton::SettingsPickerButton(QWidget* parent) : QFrame(parent)
{
    setFrameStyle(StyledPanel);
}

void SettingsPickerButton::mousePressEvent(QMouseEvent*)
{
    setFrameShadow(Sunken);
    update();
}

void SettingsPickerButton::mouseMoveEvent(QMouseEvent*)
{
    setFocus();
    update();
}

void SettingsPickerButton::mouseReleaseEvent(QMouseEvent*)
{
    setFrameShadow(Raised);
    repaint();
    emit clicked();
}

void SettingsPickerButton::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down
            || event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        qApp->sendEvent(parent(), event);
    } else if (event->key() == Qt::Key_Enter
               || event->key() == Qt::Key_Space || event->key() == Qt::Key_Return) {
        setFrameShadow(Sunken);
        update();
    } else {
        QFrame::keyPressEvent(event);
    }
}

void SettingsPickerButton::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down
            || event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        qApp->sendEvent(parent(), event);
    } else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Space
               || event->key() == Qt::Key_Return) {
        setFrameShadow(Raised);
        repaint();
        emit clicked();
    } else {
        QFrame::keyReleaseEvent(event);
    }
}

void SettingsPickerButton::focusInEvent(QFocusEvent* event)
{
    setFrameShadow(Raised);
    update();
    QFrame::focusOutEvent(event);
}

void SettingsPickerButton::focusOutEvent(QFocusEvent* event)
{
    setFrameShadow(Raised);
    update();
    QFrame::focusOutEvent(event);
}

void SettingsPickerButton::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.fillRect(contentsRect(), palette().button());

    auto r = rect();
    auto offset = frameShadow() == Sunken ? 1 : 0;

    QPen pen(palette().buttonText(), 1);
    painter.setPen(pen);

    painter.drawRect(r.center().x() + offset - 4, r.center().y() + offset, 1, 1);
    painter.drawRect(r.center().x() + offset    , r.center().y() + offset, 1, 1);
    painter.drawRect(r.center().x() + offset + 4, r.center().y() + offset, 1, 1);
    if (hasFocus()) {
        painter.setPen(QPen(Qt::black, 0, Qt::SolidLine));
        painter.drawRect(0, 0, width() - 1, height() - 1);
    }

    painter.end();
}
