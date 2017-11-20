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

#ifndef SETTINGSPICKER_H
#define SETTINGSPICKER_H

#include <QDesktopWidget>
#include <QToolButton>

#include "SettingsPickerPopup.h"

class SettingsPicker : public QToolButton
{
    Q_OBJECT

public:
    SettingsPicker(QWidget *parent = 0, int columns = -1);
    void insertColor(const QColor &color, const QString &text = QString::null, int index = -1);
    QColor color() const;
    void setColor(const QColor &color);
    bool fill() const;
    void setFill(bool fill);
    int size() const;
    void setSize(int size);
    void addPopupColorGrid(bool colorDialog = true,
                           bool fillCheckbox = true,
                           bool standardColor = true);
    void addPopupSizeSlider(int  min, int  max, int  interval);
    void insertStandardColor();
    void clearPopup();

public slots:
    void updateColor(const QColor &color);
    void updateFill(bool fill);
    void updateSize(int size);

signals:
    void colorChanged(const QColor &);
    void fillChanged(bool);
    void sizeChanged(int);

private slots:
    void buttonPressed();
    void popupClosed();

private:
    SettingsPickerPopup *mPopup;
};

#endif // SETTINGSPICKER_H
