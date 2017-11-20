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
}

void SettingsPickerConfigurator::setup(SettingsPicker* settingsPicker, Painter::Modes mode)
{
    settingsPicker->clearPopup();

    switch (mode) {
    case Painter::Pen:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupColorGrid(true, false, true);
        settingsPicker->addPopupSizeSlider(1, 10, 1);
        settingsPicker->setColor(mConfig->penColor());
        settingsPicker->setSize(mConfig->penSize());
        break;
    case Painter::Marker:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupColorGrid(false, false, false);
        settingsPicker->insertColor("yellow");
        settingsPicker->insertColor("blue");
        settingsPicker->insertColor("cyan");
        settingsPicker->insertColor("orange");
        settingsPicker->insertColor("red");
        settingsPicker->addPopupSizeSlider(10, 30, 2);
        settingsPicker->setColor(mConfig->markerColor());
        settingsPicker->setSize(mConfig->markerSize());
        break;
    case Painter::Rect:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupColorGrid(true, true, true);
        settingsPicker->addPopupSizeSlider(1, 10, 1);
        settingsPicker->setColor(mConfig->rectColor());
        settingsPicker->setSize(mConfig->rectSize());
        settingsPicker->setFill(mConfig->rectFill());
        break;
    case Painter::Ellipse:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupColorGrid(true, true, true);
        settingsPicker->addPopupSizeSlider(1, 10, 1);
        settingsPicker->setColor(mConfig->ellipseColor());
        settingsPicker->setSize(mConfig->ellipseSize());
        settingsPicker->setFill(mConfig->ellipseFill());
        break;
    case Painter::Line:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupColorGrid(true, false, true);
        settingsPicker->addPopupSizeSlider(1, 10, 1);
        settingsPicker->setColor(mConfig->lineColor());
        settingsPicker->setSize(mConfig->lineSize());
        break;
    case Painter::Arrow:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupColorGrid(true, false, true);
        settingsPicker->addPopupSizeSlider(1, 5, 1);
        settingsPicker->setColor(mConfig->arrowColor());
        settingsPicker->setSize(mConfig->arrowSize());
        break;
    case Painter::Text:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupColorGrid(true, false, true);
        settingsPicker->addPopupSizeSlider(10, 20, 1);
        settingsPicker->setColor(mConfig->textColor());
        settingsPicker->setSize(mConfig->textSize());
        break;
    case Painter::Number:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupColorGrid(true, false, true);
        settingsPicker->addPopupSizeSlider(10, 50, 5);
        settingsPicker->setColor(mConfig->numberColor());
        settingsPicker->setSize(mConfig->numberSize());
        break;
    case Painter::Erase:
        settingsPicker->setEnabled(true);
        settingsPicker->addPopupSizeSlider(1, 10, 1);
        settingsPicker->setSize(mConfig->eraseSize());
        break;
    case Painter::Move:
    case Painter::Select:
        settingsPicker->setEnabled(false);
        break;
    }
}
