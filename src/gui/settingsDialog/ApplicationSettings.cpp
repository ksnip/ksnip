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
	delete mAlwaysCopyToClipboardCheckbox;
	delete mPromptToSaveBeforeExitCheckbox;
	delete mSaveKsnipPositionCheckbox;
	delete mSaveKsnipToolSelectionCheckbox;
	delete mCaptureOnStartupCheckbox;
	delete mUseInstantSaveCheckBox;
	delete mApplicationStyleLabel;
	delete mApplicationStyleCombobox;
	delete mSaveLocationLabel;
	delete mSaveLocationLineEdit;
	delete mBrowseButton;
	delete mLayout;
}

void ApplicationSettings::initGui()
{
	mAlwaysCopyToClipboardCheckbox = new QCheckBox(this);
	mPromptToSaveBeforeExitCheckbox = new QCheckBox(this);
	mSaveKsnipPositionCheckbox = new QCheckBox(this);
	mSaveKsnipToolSelectionCheckbox = new QCheckBox(this);
	mCaptureOnStartupCheckbox = new QCheckBox(this);
	mUseInstantSaveCheckBox = new QCheckBox(this);
	mApplicationStyleLabel = new QLabel(this);
	mApplicationStyleCombobox = new QComboBox(this);
	mSaveLocationLabel = new QLabel(this);
	mSaveLocationLineEdit = new QLineEdit(this);
	mBrowseButton = new QPushButton(this);
	mLayout = new QGridLayout;

	mAlwaysCopyToClipboardCheckbox->setText(tr("Always copy capture to clipboard"));
	mPromptToSaveBeforeExitCheckbox->setText(tr("Prompt to save before discarding unsaved changes"));
	mSaveKsnipPositionCheckbox->setText(tr("Save ksnip position on move and load on startup"));
	mSaveKsnipToolSelectionCheckbox->setText(tr("Save ksnip tool selection and load on startup"));
	mCaptureOnStartupCheckbox->setText(tr("Capture screenshot at startup with default mode"));
	mUseInstantSaveCheckBox->setText(tr("Instant save to default location without 'Save as' dialog"));
	mUseInstantSaveCheckBox->setToolTip(tr("When enabled, will not ask where to save a screenshot\n"
	                                       "when saving, but will save instantly to default location."));

	mApplicationStyleLabel->setText(tr("Application Style") + QStringLiteral(":"));
	mApplicationStyleLabel->setToolTip(tr("Sets the application style which defines the look and feel of the GUI.\n"
	                                      "Change requires ksnip restart to take effect."));
	mApplicationStyleCombobox->addItems(QStyleFactory::keys());
	mApplicationStyleCombobox->setToolTip(mApplicationStyleLabel->toolTip());
	mApplicationStyleCombobox->setFixedWidth(100);

	mSaveLocationLabel->setText(tr("Capture save location and filename") + QStringLiteral(":"));

	mSaveLocationLineEdit->setToolTip(tr("Filename can contain $Y, $M, $D for date, $h, $m, $s for time, or $T for time in hhmmss format."));

	mBrowseButton->setText(tr("Browse"));
	connect(mBrowseButton, &QPushButton::clicked, this, &ApplicationSettings::chooseSaveDirectory);

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->addWidget(mAlwaysCopyToClipboardCheckbox, 0, 0, 1, 3);
	mLayout->addWidget(mPromptToSaveBeforeExitCheckbox, 1, 0, 1, 3);
	mLayout->addWidget(mSaveKsnipPositionCheckbox, 2, 0, 1, 3);
	mLayout->addWidget(mSaveKsnipToolSelectionCheckbox, 3, 0, 1, 3);
	mLayout->addWidget(mCaptureOnStartupCheckbox, 4, 0, 1, 3);
	mLayout->addWidget(mUseInstantSaveCheckBox, 5, 0, 1, 3);
	mLayout->setRowMinimumHeight(6, 15);
	mLayout->addWidget(mApplicationStyleLabel, 7, 0);
	mLayout->addWidget(mApplicationStyleCombobox, 7, 1, Qt::AlignLeft);
	mLayout->setRowMinimumHeight(8, 15);
	mLayout->addWidget(mSaveLocationLabel, 9, 0, 1, 3);
	mLayout->addWidget(mSaveLocationLineEdit, 10, 0, 1, 3);
	mLayout->addWidget(mBrowseButton, 10, 4);

	setTitle(tr("Application Settings"));
	setLayout(mLayout);
}

void ApplicationSettings::loadConfig()
{
	mAlwaysCopyToClipboardCheckbox->setChecked(mConfig->alwaysCopyToClipboard());
	mPromptToSaveBeforeExitCheckbox->setChecked(mConfig->promptSaveBeforeExit());
	mSaveKsnipPositionCheckbox->setChecked(mConfig->savePosition());
	mSaveKsnipToolSelectionCheckbox->setChecked(mConfig->saveToolSelection());
	mCaptureOnStartupCheckbox->setChecked(mConfig->captureOnStartup());
	mUseInstantSaveCheckBox->setChecked(mConfig->useInstantSave());

	mApplicationStyleCombobox->setCurrentText(mConfig->applicationStyle());

	mSaveLocationLineEdit->setText(mConfig->saveDirectory() + mConfig->saveFilename() + mConfig->saveFormat());
}

void ApplicationSettings::saveSettings()
{
	mConfig->setAlwaysCopyToClipboard(mAlwaysCopyToClipboardCheckbox->isChecked());
	mConfig->setPromptSaveBeforeExit(mPromptToSaveBeforeExitCheckbox->isChecked());
	mConfig->setSavePosition(mSaveKsnipPositionCheckbox->isChecked());
	mConfig->setSaveToolSelection(mSaveKsnipToolSelectionCheckbox->isChecked());
	mConfig->setCaptureOnStartup(mCaptureOnStartupCheckbox->isChecked());
	mConfig->setUseInstantSave(mUseInstantSaveCheckBox->isChecked());

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
