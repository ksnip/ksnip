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
	mTrayIconNotificationsCheckBox(new QCheckBox(this)),
	mDefaultActionCaptureModeCombobox(new QComboBox(this)),
	mStartMinimizedToTrayCheckBox(new QCheckBox(this)),
	mDefaultActionShowEditorRadioButton(new QRadioButton(this)),
	mDefaultActionCaptureRadioButton(new QRadioButton(this)),
	mDefaultActionGroupBox(new QGroupBox(this)),
	mDefaultActionLayout(new QGridLayout),
	mLayout(new QGridLayout)
{
	Q_ASSERT(mConfig != nullptr);

	initGui();
	populateDefaultActionCaptureModeCombobox(captureModes);

	loadConfig();
}

TrayIconSettings::~TrayIconSettings()
{
	delete mUseTrayIconCheckBox;
	delete mMinimizeToTrayCheckBox;
	delete mCloseToTrayCheckBox;
	delete mTrayIconNotificationsCheckBox;
	delete mDefaultActionCaptureModeCombobox;
	delete mStartMinimizedToTrayCheckBox;
	delete mDefaultActionShowEditorRadioButton;
	delete mDefaultActionCaptureRadioButton;
	delete mDefaultActionGroupBox;
}

void TrayIconSettings::saveSettings()
{
	mConfig->setUseTrayIcon(mUseTrayIconCheckBox->isChecked());
	mConfig->setMinimizeToTray(mMinimizeToTrayCheckBox->isChecked());
	mConfig->setStartMinimizedToTray(mStartMinimizedToTrayCheckBox->isChecked());
	mConfig->setCloseToTray(mCloseToTrayCheckBox->isChecked());
	mConfig->setTrayIconNotificationsEnabled(mTrayIconNotificationsCheckBox->isChecked());
	mConfig->setDefaultTrayIconActionMode(selectedTrayIconDefaultActionMode());
	mConfig->setDefaultTrayIconCaptureMode(mDefaultActionCaptureModeCombobox->currentData().value<CaptureModes>());
}

void TrayIconSettings::initGui()
{
	mUseTrayIconCheckBox->setText(tr("Use Tray Icon"));
	mUseTrayIconCheckBox->setToolTip(tr("When enabled will add a Tray Icon to the TaskBar if the OS Window Manager supports it.\n"
										"Change requires restart."));
	mMinimizeToTrayCheckBox->setText(tr("Minimize to Tray"));
	mStartMinimizedToTrayCheckBox->setText(tr("Start Minimized to Tray"));
	mCloseToTrayCheckBox->setText(tr("Close to Tray"));
	mTrayIconNotificationsCheckBox->setText(tr("Display Tray icon notifications"));

	connect(mUseTrayIconCheckBox, &QCheckBox::stateChanged, this, &TrayIconSettings::useTrayIconChanged);

	mDefaultActionShowEditorRadioButton->setText(tr("Show Editor"));
	mDefaultActionCaptureRadioButton->setText(tr("Capture") + QLatin1String(":"));

	mDefaultActionLayout->addWidget(mDefaultActionShowEditorRadioButton, 0, 0, 1, 1);
	mDefaultActionLayout->addWidget(mDefaultActionCaptureRadioButton, 1, 0, 1, 1);
	mDefaultActionLayout->addWidget(mDefaultActionCaptureModeCombobox, 1, 1, 1, 1);
	mDefaultActionLayout->setColumnStretch(2, 1);

	mDefaultActionGroupBox->setTitle(tr("Default Tray Icon action"));
	mDefaultActionGroupBox->setToolTip(tr("Default Action that is triggered by left clicking the tray icon."));
	mDefaultActionGroupBox->setLayout(mDefaultActionLayout);

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->setColumnMinimumWidth(0, 10);
	mLayout->addWidget(mUseTrayIconCheckBox, 0, 0, 1, 4);
	mLayout->setRowMinimumHeight(1, 5);
	mLayout->addWidget(mStartMinimizedToTrayCheckBox, 2, 0, 1, 4);
	mLayout->addWidget(mMinimizeToTrayCheckBox, 3, 0, 1, 4);
	mLayout->addWidget(mCloseToTrayCheckBox, 4, 0, 1, 4);
	mLayout->addWidget(mTrayIconNotificationsCheckBox, 5, 0, 1, 4);
	mLayout->addWidget(mDefaultActionGroupBox, 6, 0, 1, 4);

	setTitle(tr("Tray Icon Settings"));
	setLayout(mLayout);
}

void TrayIconSettings::loadConfig()
{
	mUseTrayIconCheckBox->setChecked(mConfig->useTrayIcon());
	mMinimizeToTrayCheckBox->setChecked(mConfig->minimizeToTray());
	mStartMinimizedToTrayCheckBox->setChecked(mConfig->startMinimizedToTray());
	mCloseToTrayCheckBox->setChecked(mConfig->closeToTray());
	mTrayIconNotificationsCheckBox->setChecked(mConfig->trayIconNotificationsEnabled());
	mDefaultActionShowEditorRadioButton->setChecked(mConfig->defaultTrayIconActionMode() == TrayIconDefaultActionMode::ShowEditor);
	mDefaultActionCaptureRadioButton->setChecked(mConfig->defaultTrayIconActionMode() == TrayIconDefaultActionMode::Capture);
	mDefaultActionCaptureModeCombobox->setCurrentIndex(indexOfSelectedCaptureMode());

	useTrayIconChanged();
}

int TrayIconSettings::indexOfSelectedCaptureMode() const
{
	return mDefaultActionCaptureModeCombobox->findData(QVariant::fromValue(mConfig->defaultTrayIconCaptureMode()));
}

TrayIconDefaultActionMode TrayIconSettings::selectedTrayIconDefaultActionMode() const
{
	return mDefaultActionShowEditorRadioButton->isChecked() ? TrayIconDefaultActionMode::ShowEditor : TrayIconDefaultActionMode::Capture;
}

void TrayIconSettings::populateDefaultActionCaptureModeCombobox(const QList<CaptureModes> &captureModes)
{
	for (auto captureMode: captureModes) {
		const auto label = EnumTranslator::instance()->toString(captureMode);
		mDefaultActionCaptureModeCombobox->addItem(label, static_cast<int>(captureMode));
	}
}

void TrayIconSettings::useTrayIconChanged()
{
	const auto trayIconEnabled = mUseTrayIconCheckBox->isChecked();
	mMinimizeToTrayCheckBox->setEnabled(trayIconEnabled);
	mCloseToTrayCheckBox->setEnabled(trayIconEnabled);
	mTrayIconNotificationsCheckBox->setEnabled(trayIconEnabled);
	mStartMinimizedToTrayCheckBox->setEnabled(trayIconEnabled);
	mDefaultActionCaptureModeCombobox->setEnabled(trayIconEnabled);
	mDefaultActionShowEditorRadioButton->setEnabled(trayIconEnabled);
	mDefaultActionCaptureRadioButton->setEnabled(trayIconEnabled);
}
