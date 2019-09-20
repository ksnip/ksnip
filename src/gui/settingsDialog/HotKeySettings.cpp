/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#include "HotKeySettings.h"

HotKeySettings::HotKeySettings(KsnipConfig *ksnipConfig)
{
	Q_ASSERT(ksnipConfig != nullptr);

	mConfig = ksnipConfig;

	initGui();
	loadConfig();
}

HotKeySettings::~HotKeySettings()
{
	delete mEnableGlobalHotKeys;
	delete mLayout;
}

void HotKeySettings::saveSettings()
{
	mConfig->setGlobalHotKeysEnabled(mEnableGlobalHotKeys->isChecked());
}

void HotKeySettings::initGui()
{
	mEnableGlobalHotKeys = new QCheckBox(this);
	mLayout = new QGridLayout(this);

	mEnableGlobalHotKeys->setText(tr("Enable Global HotKeys"));

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->setColumnStretch(0, 1);
	mLayout->addWidget(mEnableGlobalHotKeys, 0, 0);

	setTitle(tr("Global HotKeys"));
	setLayout(mLayout);
}

void HotKeySettings::loadConfig()
{
	mEnableGlobalHotKeys->setChecked(mConfig->globalHotKeysEnabled());
}
