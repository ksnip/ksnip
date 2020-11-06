/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#include "ApplicationSettings.h"

ApplicationSettings::ApplicationSettings(KsnipConfig *ksnipConfig) :
	mConfig(ksnipConfig),
	mAutoCopyToClipboardNewCapturesCheckbox(new QCheckBox(this)),
	mRememberPositionCheckbox(new QCheckBox(this)),
	mCaptureOnStartupCheckbox(new QCheckBox(this)),
	mUseTrayIconCheckBox(new QCheckBox(this)),
	mMinimizeToTrayCheckBox(new QCheckBox(this)),
	mCloseToTrayCheckBox(new QCheckBox(this)),
	mStartMinimizedToTrayCheckBox(new QCheckBox(this)),
	mUseTabsCheckbox(new QCheckBox(this)),
	mAutoHideTabsCheckbox(new QCheckBox(this)),
	mUseSingleInstanceCheckBox(new QCheckBox(this)),
	mApplicationStyleLabel(new QLabel(this)),
	mApplicationStyleCombobox(new QComboBox(this)),
	mLayout(new QGridLayout)
{
	Q_ASSERT(mConfig != nullptr);

	initGui();
	loadConfig();
}

ApplicationSettings::~ApplicationSettings()
{
	delete mAutoCopyToClipboardNewCapturesCheckbox;
	delete mRememberPositionCheckbox;
	delete mCaptureOnStartupCheckbox;
	delete mUseTrayIconCheckBox;
	delete mUseTabsCheckbox;
	delete mAutoHideTabsCheckbox;
	delete mMinimizeToTrayCheckBox;
	delete mCloseToTrayCheckBox;
	delete mStartMinimizedToTrayCheckBox;
	delete mUseSingleInstanceCheckBox;
	delete mApplicationStyleLabel;
	delete mApplicationStyleCombobox;
	delete mLayout;
}

void ApplicationSettings::initGui()
{
	mAutoCopyToClipboardNewCapturesCheckbox->setText(tr("Automatically copy new captures to clipboard"));
	mRememberPositionCheckbox->setText(tr("Remember position on move and load on startup"));
	mCaptureOnStartupCheckbox->setText(tr("Capture screenshot at startup with default mode"));
	mUseTrayIconCheckBox->setText(tr("Use Tray Icon"));
	mUseTrayIconCheckBox->setToolTip(tr("When enabled will add a Tray Icon to the TaskBar if the OS Window Manager supports it.\n"
									       "Change requires restart."));
	mMinimizeToTrayCheckBox->setText(tr("Minimize to Tray"));
	mStartMinimizedToTrayCheckBox->setText(tr("Start Minimized to Tray"));
	mCloseToTrayCheckBox->setText(tr("Close to Tray"));

	mUseTabsCheckbox->setText(tr("Use Tabs"));
	mUseTabsCheckbox->setToolTip(tr("Change requires restart."));

	mAutoHideTabsCheckbox->setText(tr("Auto Hide Tabs"));
	mAutoHideTabsCheckbox->setToolTip(tr("Hide Tabbar when only one Tab is used."));

	mUseSingleInstanceCheckBox->setText(tr("Run ksnip as single instance"));
	mUseSingleInstanceCheckBox->setToolTip(tr("Enabling this option will allow only one ksnip instance to run,\n"
										         "all other instances started after the first will pass its\n"
				                                 "arguments to the first and close. Changing this option requires\n"
									             "a new start of all instances."));

	connect(mUseTrayIconCheckBox, &QCheckBox::stateChanged, this, &ApplicationSettings::useTrayIconChanged);
	connect(mUseTabsCheckbox, &QCheckBox::stateChanged, this, &ApplicationSettings::useTabsChanged);

	mApplicationStyleLabel->setText(tr("Application Style") + QStringLiteral(":"));
	mApplicationStyleLabel->setToolTip(tr("Sets the application style which defines the look and feel of the GUI.\n"
	                                      "Change requires ksnip restart to take effect."));
	mApplicationStyleCombobox->addItems(QStyleFactory::keys());
	mApplicationStyleCombobox->setToolTip(mApplicationStyleLabel->toolTip());
	mApplicationStyleCombobox->setFixedWidth(100);

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->setColumnMinimumWidth(0, 10);
	mLayout->addWidget(mAutoCopyToClipboardNewCapturesCheckbox, 0, 0, 1, 4);
	mLayout->addWidget(mRememberPositionCheckbox, 1, 0, 1, 4);
	mLayout->addWidget(mCaptureOnStartupCheckbox, 2, 0, 1, 4);
	mLayout->addWidget(mUseTrayIconCheckBox, 3, 0, 1, 4);
	mLayout->addWidget(mStartMinimizedToTrayCheckBox, 4, 1, 1, 3);
	mLayout->addWidget(mMinimizeToTrayCheckBox, 5, 1, 1, 3);
	mLayout->addWidget(mCloseToTrayCheckBox, 6, 1, 1, 3);
	mLayout->addWidget(mUseTabsCheckbox, 7, 0, 1, 4);
	mLayout->addWidget(mAutoHideTabsCheckbox, 8, 1, 1, 3);
	mLayout->addWidget(mUseSingleInstanceCheckBox, 9, 0, 1, 4);
	mLayout->setRowMinimumHeight(10, 15);
	mLayout->addWidget(mApplicationStyleLabel, 11, 0, 1, 2);
	mLayout->addWidget(mApplicationStyleCombobox, 11, 2, Qt::AlignLeft);

	setTitle(tr("Application Settings"));
	setLayout(mLayout);
}

void ApplicationSettings::loadConfig()
{
	mAutoCopyToClipboardNewCapturesCheckbox->setChecked(mConfig->autoCopyToClipboardNewCaptures());
	mRememberPositionCheckbox->setChecked(mConfig->rememberPosition());
	mCaptureOnStartupCheckbox->setChecked(mConfig->captureOnStartup());
	mUseTrayIconCheckBox->setChecked(mConfig->useTrayIcon());
	mMinimizeToTrayCheckBox->setChecked(mConfig->minimizeToTray());
	mStartMinimizedToTrayCheckBox->setChecked(mConfig->startMinimizedToTray());
	mCloseToTrayCheckBox->setChecked(mConfig->closeToTray());
	mUseTabsCheckbox->setChecked(mConfig->useTabs());
	mAutoHideTabsCheckbox->setChecked(mConfig->autoHideTabs());
	mUseSingleInstanceCheckBox->setChecked(mConfig->useSingleInstance());
	mApplicationStyleCombobox->setCurrentText(mConfig->applicationStyle());

	useTrayIconChanged();
	useTabsChanged();
}

void ApplicationSettings::saveSettings()
{
	mConfig->setAutoCopyToClipboardNewCaptures(mAutoCopyToClipboardNewCapturesCheckbox->isChecked());
	mConfig->setRememberPosition(mRememberPositionCheckbox->isChecked());
	mConfig->setCaptureOnStartup(mCaptureOnStartupCheckbox->isChecked());
	mConfig->setUseTrayIcon(mUseTrayIconCheckBox->isChecked());
	mConfig->setMinimizeToTray(mMinimizeToTrayCheckBox->isChecked());
	mConfig->setStartMinimizedToTray(mStartMinimizedToTrayCheckBox->isChecked());
	mConfig->setCloseToTray(mCloseToTrayCheckBox->isChecked());
	mConfig->setUseSingleInstance(mUseSingleInstanceCheckBox->isChecked());
	mConfig->setUseTabs(mUseTabsCheckbox->isChecked());
	mConfig->setAutoHideTabs(mAutoHideTabsCheckbox->isChecked());
	mConfig->setApplicationStyle(mApplicationStyleCombobox->currentText());
}

void ApplicationSettings::useTrayIconChanged()
{
	mMinimizeToTrayCheckBox->setEnabled(mUseTrayIconCheckBox->isChecked());
	mCloseToTrayCheckBox->setEnabled(mUseTrayIconCheckBox->isChecked());
	mStartMinimizedToTrayCheckBox->setEnabled(mUseTrayIconCheckBox->isChecked());
}

void ApplicationSettings::useTabsChanged()
{
	mAutoHideTabsCheckbox->setEnabled(mUseTabsCheckbox->isChecked());
}
