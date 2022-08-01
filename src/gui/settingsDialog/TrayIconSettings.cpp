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

/**
 * @brief ...
 *
 * @param captureModes p_captureModes:...
 * @param config p_config:...
 */
/**
 * @brief ...
 *
 * @param captureModes p_captureModes:...
 * @param config ${p_config:...}
 */
TrayIconSettings::TrayIconSettings(const QList<CaptureModes> &captureModes, const QSharedPointer<IConfig> &config) :
	mConfig(config),
	mUseTrayIconCheckBox(new QCheckBox(this)),
	mMinimizeToTrayCheckBox(new QCheckBox(this)),
	mCloseToTrayCheckBox(new QCheckBox(this)),
	mTrayIconNotificationsCheckBox(new QCheckBox(this)),
	mUsePlatformSpecificNotificationServiceCheckBox(new QCheckBox(this)),
	mStartMinimizedToTrayCheckBox(new QCheckBox(this)),
	// fields for setting the default action when clicking the tray icon
	mDefaultActionCaptureModeCombobox(new QComboBox(this)),
	mDefaultActionShowEditorRadioButton(new QRadioButton(this)),
	mDefaultActionCaptureRadioButton(new QRadioButton(this)),
	mDefaultActionGroupBox(new QGroupBox(this)),
	mDefaultActionLayout(new QGridLayout),
	// fields for setting the tray icon image
	mTrayIconDefaultRadioButton(new QRadioButton(this)),
	mTrayIconCustomRadioButton(new QRadioButton(this)),
	mTrayIconCustomFileSelectButton(new QPushButton(this)),
	mTrayIconLineEdit(new QLineEdit(this)),
	mTrayIconGroupBox(new QGroupBox(this)),
	mTrayIconLayout(new QGridLayout),

	mLayout(new QGridLayout)
{
	Q_ASSERT(mConfig != nullptr);

	initGui();
	populateDefaultActionCaptureModeCombobox(captureModes);

	loadConfig();
}

void TrayIconSettings::saveSettings()
{
	mConfig->setUseTrayIcon(mUseTrayIconCheckBox->isChecked());
	mConfig->setMinimizeToTray(mMinimizeToTrayCheckBox->isChecked());
	mConfig->setStartMinimizedToTray(mStartMinimizedToTrayCheckBox->isChecked());
	mConfig->setCloseToTray(mCloseToTrayCheckBox->isChecked());
	mConfig->setTrayIconNotificationsEnabled(mTrayIconNotificationsCheckBox->isChecked());
	mConfig->setPlatformSpecificNotificationServiceEnabled(mUsePlatformSpecificNotificationServiceCheckBox->isChecked());
	mConfig->setDefaultTrayIconActionMode(selectedTrayIconDefaultActionMode());
	mConfig->setDefaultTrayIconCaptureMode(mDefaultActionCaptureModeCombobox->currentData().value<CaptureModes>());

	mConfig->setCustomTrayIconImageFile(mTrayIconLineEdit->displayText());
	mConfig->setCustomTrayIconImage(mTrayIconCustomRadioButton->isChecked());
	mConfig->setCustomTrayIconImageFile(mTrayIconLineEdit->displayText());
}

void TrayIconSettings::initGui()
{
	mUseTrayIconCheckBox->setText(tr("Use Tray Icon"));
	mUseTrayIconCheckBox->setToolTip(tr("When enabled will add a Tray Icon to the TaskBar if the OS Window Manager supports it.\n"
										"Change requires restart."));
	mMinimizeToTrayCheckBox->setText(tr("Minimize to Tray"));
	mStartMinimizedToTrayCheckBox->setText(tr("Start Minimized to Tray"));
	mCloseToTrayCheckBox->setText(tr("Close to Tray"));
	mTrayIconNotificationsCheckBox->setText(tr("Display Tray Icon notifications"));
	mUsePlatformSpecificNotificationServiceCheckBox->setText(tr("Use platform specific notification service"));
	mUsePlatformSpecificNotificationServiceCheckBox->setToolTip(tr("When enabled will use try to use platform specific notification\n"
																   "service when such exists. Change requires restart to take effect."));

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

	mTrayIconDefaultRadioButton->setText(tr("Use Default Icon Image"));
	mTrayIconCustomRadioButton->setText(tr("Choose Custom Icon Image"));
	mTrayIconLineEdit->setPlaceholderText("valid images are *.png *.jpg *.bmp and *.svg");
	mTrayIconCustomFileSelectButton->setText(tr("Select an Image"));

	connect(mTrayIconCustomFileSelectButton, &QPushButton::clicked, this, &TrayIconSettings::selectCustomImage);
	// needed since we disable or enable file select based on this radio
	connect(mTrayIconCustomRadioButton, &QRadioButton::clicked, this, &TrayIconSettings::useTrayIconChanged);
	connect(mTrayIconDefaultRadioButton, &QRadioButton::clicked, this, &TrayIconSettings::useTrayIconChanged);

	auto warnRequiresRestart = [this]() {
		auto title = tr("Required Reload");
		auto message = tr("Selecting a new image for the tray icon requires restarting the program to take effect");
		auto messageBox = QMessageBox::warning(this, title, message);
	};

	connect(mTrayIconCustomRadioButton, &QRadioButton::clicked, this, warnRequiresRestart);

	mTrayIconLayout->addWidget(mTrayIconDefaultRadioButton, 0, 0, 1, 3);
	mTrayIconLayout->addWidget(mTrayIconCustomRadioButton, 0, 3, 1, 1);
	mTrayIconLayout->addWidget(mTrayIconLineEdit, 1, 0, 1, 3);
	mTrayIconLayout->addWidget(mTrayIconCustomFileSelectButton, 1, 3, 1, 1);
	mTrayIconLayout->setColumnStretch(1, 3);

	mTrayIconGroupBox->setTitle(tr("Tray Icon Image Settings"));
	mTrayIconGroupBox->setToolTip(tr("Use the default tray icon image, or select your own"));
	mTrayIconGroupBox->setLayout(mTrayIconLayout);

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->setColumnMinimumWidth(0, 10);
	mLayout->addWidget(mUseTrayIconCheckBox, 0, 0, 1, 4);
	mLayout->setRowMinimumHeight(1, 5);
	mLayout->addWidget(mStartMinimizedToTrayCheckBox, 2, 0, 1, 4);
	mLayout->addWidget(mMinimizeToTrayCheckBox, 3, 0, 1, 4);
	mLayout->addWidget(mCloseToTrayCheckBox, 4, 0, 1, 4);
	mLayout->addWidget(mTrayIconNotificationsCheckBox, 5, 0, 1, 4);
	mLayout->addWidget(mUsePlatformSpecificNotificationServiceCheckBox, 6, 0, 1, 4);
	mLayout->addWidget(mDefaultActionGroupBox, 7, 0, 1, 4);
	mLayout->addWidget(mTrayIconGroupBox, 8, 0, 1, 4);

	setTitle(tr("Tray Icon Settings"));
	setLayout(mLayout);
}

void TrayIconSettings::selectCustomImage()
{
	auto imageFileName = QFileDialog::getOpenFileName(
		this,
    	tr("Select Custom Tray Icon Image"),
		QDir::homePath(),
		tr("Image Files (*.png *.jpg *.bmp, *.svg)")
	);

	if(!imageFileName.isEmpty()) {
		mTrayIconLineEdit->setText(imageFileName);
	}
}

void TrayIconSettings::loadConfig()
{
	mUseTrayIconCheckBox->setChecked(mConfig->useTrayIcon());
	mMinimizeToTrayCheckBox->setChecked(mConfig->minimizeToTray());
	mStartMinimizedToTrayCheckBox->setChecked(mConfig->startMinimizedToTray());
	mCloseToTrayCheckBox->setChecked(mConfig->closeToTray());
	mTrayIconNotificationsCheckBox->setChecked(mConfig->trayIconNotificationsEnabled());
	mUsePlatformSpecificNotificationServiceCheckBox->setChecked(mConfig->platformSpecificNotificationServiceEnabled());
	mDefaultActionShowEditorRadioButton->setChecked(mConfig->defaultTrayIconActionMode() == TrayIconDefaultActionMode::ShowEditor);
	mDefaultActionCaptureRadioButton->setChecked(mConfig->defaultTrayIconActionMode() == TrayIconDefaultActionMode::Capture);
	mDefaultActionCaptureModeCombobox->setCurrentIndex(indexOfSelectedCaptureMode());

	mTrayIconCustomRadioButton->setChecked(mConfig->useCustomTrayIconImage());
	mTrayIconDefaultRadioButton->setChecked(!mConfig->useCustomTrayIconImage());
	mTrayIconLineEdit->setText(mConfig->customTrayIconImageFile());

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
		const auto label = EnumTranslator::instance()->toTranslatedString(captureMode);
		mDefaultActionCaptureModeCombobox->addItem(label, static_cast<int>(captureMode));
	}
}

void TrayIconSettings::useTrayIconChanged()
{
	const auto trayIconEnabled = mUseTrayIconCheckBox->isChecked();
	mMinimizeToTrayCheckBox->setEnabled(trayIconEnabled);
	mCloseToTrayCheckBox->setEnabled(trayIconEnabled);
	mTrayIconNotificationsCheckBox->setEnabled(trayIconEnabled);
	mUsePlatformSpecificNotificationServiceCheckBox->setEnabled(trayIconEnabled);
	mStartMinimizedToTrayCheckBox->setEnabled(trayIconEnabled);
	mDefaultActionCaptureModeCombobox->setEnabled(trayIconEnabled);
	mDefaultActionShowEditorRadioButton->setEnabled(trayIconEnabled);
	mDefaultActionCaptureRadioButton->setEnabled(trayIconEnabled);

	mTrayIconDefaultRadioButton->setEnabled(trayIconEnabled);
	mTrayIconCustomRadioButton->setEnabled(trayIconEnabled);
	// conditionally show these two if the "custom image" radio is selected
	mTrayIconLineEdit->setEnabled(trayIconEnabled && mTrayIconCustomRadioButton->isChecked());
	mTrayIconCustomFileSelectButton->setEnabled(trayIconEnabled && mTrayIconCustomRadioButton->isChecked());
}
