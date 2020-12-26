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
	mUseTabsCheckbox(new QCheckBox(this)),
	mAutoHideTabsCheckbox(new QCheckBox(this)),
	mUseSingleInstanceCheckBox(new QCheckBox(this)),
	mAutoHideDocksCheckBox(new QCheckBox(this)),
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
	delete mUseTabsCheckbox;
	delete mAutoHideTabsCheckbox;
	delete mUseSingleInstanceCheckBox;
	delete mAutoHideDocksCheckBox;
	delete mApplicationStyleLabel;
	delete mApplicationStyleCombobox;
	delete mLayout;
}

void ApplicationSettings::initGui()
{
	mAutoCopyToClipboardNewCapturesCheckbox->setText(tr("Automatically copy new captures to clipboard"));
	mRememberPositionCheckbox->setText(tr("Remember Main Window position on move and load on startup"));
	mCaptureOnStartupCheckbox->setText(tr("Capture screenshot at startup with default mode"));

	mUseTabsCheckbox->setText(tr("Use Tabs"));
	mUseTabsCheckbox->setToolTip(tr("Change requires restart."));

	mAutoHideTabsCheckbox->setText(tr("Auto hide Tabs"));
	mAutoHideTabsCheckbox->setToolTip(tr("Hide Tabbar when only one Tab is used."));

	mUseSingleInstanceCheckBox->setText(tr("Run ksnip as single instance"));
	mUseSingleInstanceCheckBox->setToolTip(tr("Enabling this option will allow only one ksnip instance to run,\n"
										         "all other instances started after the first will pass its\n"
				                                 "arguments to the first and close. Changing this option requires\n"
									             "a new start of all instances."));

	mAutoHideDocksCheckBox->setText(tr("Auto hide Docks"));
	mAutoHideDocksCheckBox->setToolTip(tr("On startup hide Toolbar and Annotation Settings.\n"
									   		"Docks visibility can be toggled with the Tab Key."));

	connect(mUseTabsCheckbox, &QCheckBox::stateChanged, this, &ApplicationSettings::useTabsChanged);

	mApplicationStyleLabel->setText(tr("Application Style") + QLatin1String(":"));
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
	mLayout->addWidget(mUseTabsCheckbox, 3, 0, 1, 4);
	mLayout->addWidget(mAutoHideTabsCheckbox, 4, 1, 1, 3);
	mLayout->addWidget(mUseSingleInstanceCheckBox, 5, 0, 1, 4);
	mLayout->addWidget(mAutoHideDocksCheckBox, 6, 0, 1, 4);
	mLayout->setRowMinimumHeight(7, 15);
	mLayout->addWidget(mApplicationStyleLabel, 8, 0, 1, 2);
	mLayout->addWidget(mApplicationStyleCombobox, 8, 2, Qt::AlignLeft);

	setTitle(tr("Application Settings"));
	setLayout(mLayout);
}

void ApplicationSettings::loadConfig()
{
	mAutoCopyToClipboardNewCapturesCheckbox->setChecked(mConfig->autoCopyToClipboardNewCaptures());
	mRememberPositionCheckbox->setChecked(mConfig->rememberPosition());
	mCaptureOnStartupCheckbox->setChecked(mConfig->captureOnStartup());
	mUseTabsCheckbox->setChecked(mConfig->useTabs());
	mAutoHideTabsCheckbox->setChecked(mConfig->autoHideTabs());
	mUseSingleInstanceCheckBox->setChecked(mConfig->useSingleInstance());
	mAutoHideDocksCheckBox->setChecked(mConfig->autoHideDocks());
	mApplicationStyleCombobox->setCurrentText(mConfig->applicationStyle());

	useTabsChanged();
}

void ApplicationSettings::saveSettings()
{
	mConfig->setAutoCopyToClipboardNewCaptures(mAutoCopyToClipboardNewCapturesCheckbox->isChecked());
	mConfig->setRememberPosition(mRememberPositionCheckbox->isChecked());
	mConfig->setCaptureOnStartup(mCaptureOnStartupCheckbox->isChecked());
	mConfig->setUseSingleInstance(mUseSingleInstanceCheckBox->isChecked());
	mConfig->setUseTabs(mUseTabsCheckbox->isChecked());
	mConfig->setAutoHideTabs(mAutoHideTabsCheckbox->isChecked());
	mConfig->setAutoHideDocks(mAutoHideDocksCheckBox->isChecked());
	mConfig->setApplicationStyle(mApplicationStyleCombobox->currentText());
}

void ApplicationSettings::useTabsChanged()
{
	mAutoHideTabsCheckbox->setEnabled(mUseTabsCheckbox->isChecked());
}
