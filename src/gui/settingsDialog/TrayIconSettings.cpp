/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "TrayIconSettings.h"

TrayIconSettings::TrayIconSettings(KsnipConfig *config, const QList<CaptureModes> &captureModes) :
	mConfig(config),
	mUseTrayIconCheckBox(new QCheckBox(this)),
	mMinimizeToTrayCheckBox(new QCheckBox(this)),
	mCloseToTrayCheckBox(new QCheckBox(this)),
	mDefaultTrayLeftClickActionLabel(new QLabel(this)),
	mDefaultTrayLeftClickActionCombobox(new QComboBox(this)),
	mStartMinimizedToTrayCheckBox(new QCheckBox(this)),
	mLayout(new QGridLayout)
{
	Q_ASSERT(mConfig != nullptr);

	initGui();
	populateTrayLeftClickActionCombobox(captureModes);

	loadConfig();
}

TrayIconSettings::~TrayIconSettings()
{
	delete mUseTrayIconCheckBox;
	delete mMinimizeToTrayCheckBox;
	delete mCloseToTrayCheckBox;
	delete mDefaultTrayLeftClickActionLabel;
	delete mDefaultTrayLeftClickActionCombobox;
	delete mStartMinimizedToTrayCheckBox;
}

void TrayIconSettings::saveSettings()
{
	mConfig->setUseTrayIcon(mUseTrayIconCheckBox->isChecked());
	mConfig->setMinimizeToTray(mMinimizeToTrayCheckBox->isChecked());
	mConfig->setStartMinimizedToTray(mStartMinimizedToTrayCheckBox->isChecked());
	mConfig->setCloseToTray(mCloseToTrayCheckBox->isChecked());
	mConfig->setDefaultTrayIconAction(mDefaultTrayLeftClickActionCombobox->currentData().toInt());
}

void TrayIconSettings::initGui()
{
	mUseTrayIconCheckBox->setText(tr("Use Tray Icon"));
	mUseTrayIconCheckBox->setToolTip(tr("When enabled will add a Tray Icon to the TaskBar if the OS Window Manager supports it.\n"
										"Change requires restart."));
	mMinimizeToTrayCheckBox->setText(tr("Minimize to Tray"));
	mStartMinimizedToTrayCheckBox->setText(tr("Start Minimized to Tray"));
	mCloseToTrayCheckBox->setText(tr("Close to Tray"));
	mDefaultTrayLeftClickActionLabel->setText(tr("Default left-click on Tray Icon action"));
	mDefaultTrayLeftClickActionCombobox->setToolTip(tr("Default action performed when left-clicking Tray Icon"));

	connect(mUseTrayIconCheckBox, &QCheckBox::stateChanged, this, &TrayIconSettings::useTrayIconChanged);

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->setColumnMinimumWidth(0, 10);
	mLayout->addWidget(mUseTrayIconCheckBox, 0, 0, 1, 4);
	mLayout->setRowMinimumHeight(1, 10);
	mLayout->addWidget(mStartMinimizedToTrayCheckBox, 2, 0, 1, 4);
	mLayout->addWidget(mMinimizeToTrayCheckBox, 3, 0, 1, 4);
	mLayout->addWidget(mCloseToTrayCheckBox, 4, 0, 1, 4);
	mLayout->addWidget(mDefaultTrayLeftClickActionLabel, 5, 0, 1, 1);
	mLayout->addWidget(mDefaultTrayLeftClickActionCombobox, 5, 1, 1, 1);

	setTitle(tr("Tray Icon Settings"));
	setLayout(mLayout);
}

void TrayIconSettings::loadConfig()
{
	mUseTrayIconCheckBox->setChecked(mConfig->useTrayIcon());
	mMinimizeToTrayCheckBox->setChecked(mConfig->minimizeToTray());
	mStartMinimizedToTrayCheckBox->setChecked(mConfig->startMinimizedToTray());
	mCloseToTrayCheckBox->setChecked(mConfig->closeToTray());
	setTrayLeftClickActionComboboxValue(mConfig->defaultTrayIconAction());

	useTrayIconChanged();
}

void TrayIconSettings::populateTrayLeftClickActionCombobox(const QList<CaptureModes> &captureModes)
{
	mDefaultTrayLeftClickActionCombobox->addItem(tr("Show Editor"), -1);
	for (auto captureMode: captureModes) {
		const auto label = EnumTranslator::instance()->toString(captureMode);
		mDefaultTrayLeftClickActionCombobox->addItem(label, static_cast<int>(captureMode));
	}
}

void TrayIconSettings::setTrayLeftClickActionComboboxValue(int action)
{
	const auto index = mDefaultTrayLeftClickActionCombobox->findData(action);
	if (index >= 0) {
		mDefaultTrayLeftClickActionCombobox->setCurrentIndex(index);
	}
}

void TrayIconSettings::useTrayIconChanged()
{
	mMinimizeToTrayCheckBox->setEnabled(mUseTrayIconCheckBox->isChecked());
	mCloseToTrayCheckBox->setEnabled(mUseTrayIconCheckBox->isChecked());
	mStartMinimizedToTrayCheckBox->setEnabled(mUseTrayIconCheckBox->isChecked());
	mDefaultTrayLeftClickActionCombobox->setEnabled(mUseTrayIconCheckBox->isChecked());
}
