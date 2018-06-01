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

#include "SettingsPickerConfigurator.h"

SettingsPickerConfigurator::SettingsPickerConfigurator()
{
    mConfig = KsnipConfig::instance();
    mNumberSequencer = NumberSequencer::instance();
}

void SettingsPickerConfigurator::setup(SettingsPicker* settingsPicker, PaintMode mode)
{
    settingsPicker->clearPopup();

    switch (mode) {
    case PaintMode::Pen:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupColorGrid(true, false, true);
        settingsPicker->addPopupSizeSlider(1, 10, 1);
            settingsPicker->setColor(mConfig->toolColor(PaintMode::Pen));
        settingsPicker->setSize(mConfig->toolSize(PaintMode::Pen));
        break;
    case PaintMode::Marker:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupColorGrid(false, false, false);
        settingsPicker->insertColor("yellow");
        settingsPicker->insertColor("blue");
        settingsPicker->insertColor("cyan");
        settingsPicker->insertColor("orange");
        settingsPicker->insertColor("red");
        settingsPicker->addPopupSizeSlider(10, 30, 2);
            settingsPicker->setColor(mConfig->toolColor(PaintMode::Marker));
        settingsPicker->setSize(mConfig->toolSize(PaintMode::Marker));
        break;
    case PaintMode::Rect:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupColorGrid(true, true, true);
        settingsPicker->addPopupSizeSlider(1, 10, 1);
            settingsPicker->setColor(mConfig->toolColor(PaintMode::Rect));
        settingsPicker->setSize(mConfig->toolSize(PaintMode::Rect));
        settingsPicker->setFill(mConfig->toolFill(PaintMode::Rect));
        break;
    case PaintMode::Ellipse:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupColorGrid(true, true, true);
        settingsPicker->addPopupSizeSlider(1, 10, 1);
            settingsPicker->setColor(mConfig->toolColor(PaintMode::Ellipse));
        settingsPicker->setSize(mConfig->toolSize(PaintMode::Ellipse));
        settingsPicker->setFill(mConfig->toolFill(PaintMode::Ellipse));
        break;
    case PaintMode::Line:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupColorGrid(true, false, true);
        settingsPicker->addPopupSizeSlider(1, 10, 1);
            settingsPicker->setColor(mConfig->toolColor(PaintMode::Line));
        settingsPicker->setSize(mConfig->toolSize(PaintMode::Line));
        break;
    case PaintMode::Arrow:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupColorGrid(true, false, true);
        settingsPicker->addPopupSizeSlider(1, 5, 1);
            settingsPicker->setColor(mConfig->toolColor(PaintMode::Arrow));
        settingsPicker->setSize(mConfig->toolSize(PaintMode::Arrow));
        break;
    case PaintMode::Text:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupColorGrid(true, false, true);
        settingsPicker->addPopupSizeSlider(10, 20, 1);
            settingsPicker->setColor(mConfig->toolColor(PaintMode::Text));
        settingsPicker->setSize(mConfig->toolSize(PaintMode::Text));
        break;
    case PaintMode::Number:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupColorGrid(true, false, true);
        settingsPicker->addPopupSizeSlider(10, 50, 5);
        settingsPicker->addPopupNumberPicker(mNumberSequencer->min(), mNumberSequencer->max());
            settingsPicker->setColor(mConfig->toolColor(PaintMode::Number));
        settingsPicker->setSize(mConfig->toolSize(PaintMode::Number));
        connect(mNumberSequencer, &NumberSequencer::numberChanged, settingsPicker, &SettingsPicker::updateNumber);
        connect(settingsPicker, &SettingsPicker::numberSelected, mNumberSequencer, &NumberSequencer::setNextNumber);
        break;
    case PaintMode::Erase:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupSizeSlider(1, 10, 1);
        settingsPicker->setSize(mConfig->toolSize(PaintMode::Erase));
        break;
    case PaintMode::Select:
        settingsPicker->setEnabled(false);
        break;
    }
}
