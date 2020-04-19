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

ApplicationSettings::ApplicationSettings(KsnipConfig *ksnipConfig)
{
	Q_ASSERT(ksnipConfig != nullptr);

	mConfig = ksnipConfig;

	initGui();
	loadConfig();
}

ApplicationSettings::~ApplicationSettings()
{
	delete mAutoCopyToClipboardNewCapturesCheckbox;
	delete mAutoSaveNewCapturesCheckbox;
	delete mPromptToSaveBeforeExitCheckbox;
	delete mSaveKsnipPositionCheckbox;
	delete mSaveKsnipToolSelectionCheckbox;
	delete mCaptureOnStartupCheckbox;
	delete mUseTrayIconCheckBox;
	delete mAutoHideTabsCheckbox;
	delete mMinimizeToTrayCheckBox;
	delete mCloseToTrayCheckBox;
	delete mStartMinimizedToTrayCheckBox;
	delete mApplicationStyleLabel;
	delete mApplicationStyleCombobox;
	delete mSaveLocationLabel;
	delete mSaveLocationLineEdit;
	delete mBrowseButton;
	delete mLayout;
}

void ApplicationSettings::initGui()
{
	mAutoCopyToClipboardNewCapturesCheckbox = new QCheckBox(this);
	mAutoSaveNewCapturesCheckbox = new QCheckBox(this);
	mPromptToSaveBeforeExitCheckbox = new QCheckBox(this);
	mSaveKsnipPositionCheckbox = new QCheckBox(this);
	mSaveKsnipToolSelectionCheckbox = new QCheckBox(this);
	mCaptureOnStartupCheckbox = new QCheckBox(this);
	mUseTrayIconCheckBox = new QCheckBox(this);
	mMinimizeToTrayCheckBox = new QCheckBox(this);
	mCloseToTrayCheckBox = new QCheckBox(this);
	mStartMinimizedToTrayCheckBox = new QCheckBox(this);
	mAutoHideTabsCheckbox = new QCheckBox(this);
	mApplicationStyleLabel = new QLabel(this);
	mApplicationStyleCombobox = new QComboBox(this);
	mSaveLocationLabel = new QLabel(this);
	mSaveLocationLineEdit = new QLineEdit(this);
	mBrowseButton = new QPushButton(this);
	mLayout = new QGridLayout;

	mAutoCopyToClipboardNewCapturesCheckbox->setText(tr("Automatically copy new captures to clipboard"));
	mAutoSaveNewCapturesCheckbox->setText(tr("Automatically save new captures to default location"));
	mPromptToSaveBeforeExitCheckbox->setText(tr("Prompt to save before discarding unsaved changes"));
	mSaveKsnipPositionCheckbox->setText(tr("Save ksnip position on move and load on startup"));
	mSaveKsnipToolSelectionCheckbox->setText(tr("Save ksnip tool selection and load on startup"));
	mCaptureOnStartupCheckbox->setText(tr("Capture screenshot at startup with default mode"));
	mUseTrayIconCheckBox->setText(tr("Use Tray Icon"));
	mUseTrayIconCheckBox->setToolTip(tr("When enabled will add a Tray Icon to the TaskBar if the OS Window Manager supports it.\n"
									       "Change requires restart."));
	mMinimizeToTrayCheckBox->setText(tr("Minimize to Tray"));
	mStartMinimizedToTrayCheckBox->setText(tr("Start Minimized to Tray."));
	mCloseToTrayCheckBox->setText(tr("Close to Tray"));

	mAutoHideTabsCheckbox->setText(tr("Auto Hide Tabs"));
	mAutoHideTabsCheckbox->setToolTip(tr("Hide Tabbar when only on Tab is used."));

	connect(mUseTrayIconCheckBox, &QCheckBox::stateChanged, this, &ApplicationSettings::useTrayIconChanged);

	mApplicationStyleLabel->setText(tr("Application Style") + QStringLiteral(":"));
	mApplicationStyleLabel->setToolTip(tr("Sets the application style which defines the look and feel of the GUI.\n"
	                                      "Change requires ksnip restart to take effect."));
	mApplicationStyleCombobox->addItems(QStyleFactory::keys());
	mApplicationStyleCombobox->setToolTip(mApplicationStyleLabel->toolTip());
	mApplicationStyleCombobox->setFixedWidth(ScaledSizeProvider::getScaledWidth(100));

	mSaveLocationLabel->setText(tr("Capture save location and filename") + QStringLiteral(":"));

	mSaveLocationLineEdit->setToolTip(tr("Filename can contain $Y, $M, $D for date, $h, $m, $s for time, or $T for time in hhmmss format."));

	mBrowseButton->setText(tr("Browse"));
	connect(mBrowseButton, &QPushButton::clicked, this, &ApplicationSettings::chooseSaveDirectory);

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->setColumnMinimumWidth(0, ScaledSizeProvider::getScaledWidth(10));
	mLayout->addWidget(mAutoCopyToClipboardNewCapturesCheckbox, 0, 0, 1, 4);
	mLayout->addWidget(mAutoSaveNewCapturesCheckbox, 1, 0, 1, 4);
	mLayout->addWidget(mPromptToSaveBeforeExitCheckbox, 2, 0, 1, 4);
	mLayout->addWidget(mSaveKsnipPositionCheckbox, 3, 0, 1, 4);
	mLayout->addWidget(mSaveKsnipToolSelectionCheckbox, 4, 0, 1, 4);
	mLayout->addWidget(mCaptureOnStartupCheckbox, 5, 0, 1, 4);
	mLayout->addWidget(mUseTrayIconCheckBox, 6, 0, 1, 4);
	mLayout->addWidget(mStartMinimizedToTrayCheckBox, 7, 1, 1, 3);
	mLayout->addWidget(mMinimizeToTrayCheckBox, 8, 1, 1, 3);
	mLayout->addWidget(mCloseToTrayCheckBox, 9, 1, 1, 3);
	mLayout->addWidget(mAutoHideTabsCheckbox, 10, 0, 1, 4);
	mLayout->setRowMinimumHeight(11, 15);
	mLayout->addWidget(mApplicationStyleLabel, 12, 0, 1, 2);
	mLayout->addWidget(mApplicationStyleCombobox, 12, 2, Qt::AlignLeft);
	mLayout->setRowMinimumHeight(13, 15);
	mLayout->addWidget(mSaveLocationLabel, 14, 0, 1, 4);
	mLayout->addWidget(mSaveLocationLineEdit, 15, 0, 1, 4);
	mLayout->addWidget(mBrowseButton, 15, 4);

	setTitle(tr("Application Settings"));
	setLayout(mLayout);
}

void ApplicationSettings::loadConfig()
{
	mAutoCopyToClipboardNewCapturesCheckbox->setChecked(mConfig->autoCopyToClipboardNewCaptures());
	mAutoSaveNewCapturesCheckbox->setChecked(mConfig->autoSaveNewCaptures());
	mPromptToSaveBeforeExitCheckbox->setChecked(mConfig->promptSaveBeforeExit());
	mSaveKsnipPositionCheckbox->setChecked(mConfig->savePosition());
	mSaveKsnipToolSelectionCheckbox->setChecked(mConfig->saveToolSelection());
	mCaptureOnStartupCheckbox->setChecked(mConfig->captureOnStartup());
	mUseTrayIconCheckBox->setChecked(mConfig->useTrayIcon());
	mMinimizeToTrayCheckBox->setChecked(mConfig->minimizeToTray());
	mStartMinimizedToTrayCheckBox->setChecked(mConfig->startMinimizedToTray());
	mCloseToTrayCheckBox->setChecked(mConfig->closeToTray());
	mAutoHideTabsCheckbox->setChecked(mConfig->autoHideTabs());

	useTrayIconChanged();

	mApplicationStyleCombobox->setCurrentText(mConfig->applicationStyle());

	mSaveLocationLineEdit->setText(mConfig->saveDirectory() + mConfig->saveFilename() + mConfig->saveFormat());
}

void ApplicationSettings::saveSettings()
{
	mConfig->setAutoCopyToClipboardNewCaptures(mAutoCopyToClipboardNewCapturesCheckbox->isChecked());
	mConfig->setAutoSaveNewCaptures(mAutoSaveNewCapturesCheckbox->isChecked());
	mConfig->setPromptSaveBeforeExit(mPromptToSaveBeforeExitCheckbox->isChecked());
	mConfig->setSavePosition(mSaveKsnipPositionCheckbox->isChecked());
	mConfig->setSaveToolSelection(mSaveKsnipToolSelectionCheckbox->isChecked());
	mConfig->setCaptureOnStartup(mCaptureOnStartupCheckbox->isChecked());
	mConfig->setUseTrayIcon(mUseTrayIconCheckBox->isChecked());
	mConfig->setMinimizeToTray(mMinimizeToTrayCheckBox->isChecked());
	mConfig->setStartMinimizedToTray(mStartMinimizedToTrayCheckBox->isChecked());
	mConfig->setCloseToTray(mCloseToTrayCheckBox->isChecked());
	mConfig->setAutoHideTabs(mAutoHideTabsCheckbox->isChecked());

	mConfig->setApplicationStyle(mApplicationStyleCombobox->currentText());

	mConfig->setSaveDirectory(PathHelper::extractPath(mSaveLocationLineEdit->displayText()));
	mConfig->setSaveFilename(PathHelper::extractFilename(mSaveLocationLineEdit->displayText()));
	mConfig->setSaveFormat(PathHelper::extractFormat(mSaveLocationLineEdit->displayText()));
}

void ApplicationSettings::chooseSaveDirectory()
{
	auto path = QFileDialog::getExistingDirectory(this, tr("Capture save location"), mConfig->saveDirectory());
	if(!path.isEmpty()) {
		auto filename = PathHelper::extractFilename(mSaveLocationLineEdit->text());
		auto format = PathHelper::extractFormat(mSaveLocationLineEdit->text());

		if(!filename.isEmpty()) {
			path.append(QLatin1Char('/')).append(filename);
		}

		if(!format.isEmpty()) {
			path.append(QLatin1Char('.')).append(format);
		}

		mSaveLocationLineEdit->setText(path);
	}
}

void ApplicationSettings::useTrayIconChanged()
{
	mMinimizeToTrayCheckBox->setEnabled(mUseTrayIconCheckBox->isChecked());
	mCloseToTrayCheckBox->setEnabled(mUseTrayIconCheckBox->isChecked());
	mStartMinimizedToTrayCheckBox->setEnabled(mUseTrayIconCheckBox->isChecked());
}
