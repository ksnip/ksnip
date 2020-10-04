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

#include "SaverSettings.h"

SaverSettings::SaverSettings(KsnipConfig *ksnipConfig) :
	mConfig(ksnipConfig),
	mAutoSaveNewCapturesCheckbox(new QCheckBox(this)),
	mPromptToSaveBeforeExitCheckbox(new QCheckBox(this)),
	mRememberSaveDirectoryCheckbox(new QCheckBox(this)),
	mSaveQualityDefaultRadioButton(new QRadioButton(this)),
	mSaveQualityFactorRadioButton(new QRadioButton(this)),
	mSaveLocationLabel(new QLabel(this)),
	mSaveLocationLineEdit(new QLineEdit(this)),
	mBrowseButton(new QPushButton(this)),
	mSaveQualityFactorSpinBox(new CustomSpinBox(0, 100, this)),
	mLayout(new QGridLayout),
	mSaveQualityLayout(new QGridLayout),
	mSaveQualityGroupBox(new QGroupBox(this)),
	mFileDialog(FileDialogAdapterFactory::create())
{
	Q_ASSERT(mConfig != nullptr);

	initGui();
	loadConfig();
}

SaverSettings::~SaverSettings()
{
	delete mAutoSaveNewCapturesCheckbox;
	delete mPromptToSaveBeforeExitCheckbox;
	delete mRememberSaveDirectoryCheckbox;
	delete mSaveQualityDefaultRadioButton;
	delete mSaveQualityFactorRadioButton;
	delete mSaveLocationLabel;
	delete mSaveLocationLineEdit;
	delete mBrowseButton;
	delete mSaveQualityGroupBox;
	delete mFileDialog;
}

void SaverSettings::initGui()
{
	mAutoSaveNewCapturesCheckbox->setText(tr("Automatically save new captures to default location"));
	mPromptToSaveBeforeExitCheckbox->setText(tr("Prompt to save before discarding unsaved changes"));

	mSaveQualityDefaultRadioButton->setText(tr("Default"));
	mSaveQualityFactorRadioButton->setText(tr("Factor"));
	mSaveQualityFactorRadioButton->setToolTip(tr("Specify 0 to obtain small compressed files, 100 for large uncompressed files.\n"
											        "Not all image formats support the full range, JPEG does."));

	mSaveQualityFactorSpinBox->setToolTip(mSaveQualityFactorRadioButton->toolTip());

	mSaveQualityGroupBox->setTitle(tr("Save Quality"));

	mRememberSaveDirectoryCheckbox->setText(tr("Remember last Save Directory"));
	mRememberSaveDirectoryCheckbox->setToolTip(tr("When enabled will overwrite the save directory stored in settings\n"
												  "with the latest save directory, for every save."));

	mSaveLocationLabel->setText(tr("Capture save location and filename") + QStringLiteral(":"));

	mSaveLocationLineEdit->setToolTip(tr("Supported Formats are JPG, PNG and BMP. If no format provided, PNG will be used as default.\n"
									         "Filename can contain following wildcards:\n"
									         "- $Y, $M, $D for date, $h, $m, $s for time, or $T for time in hhmmss format.\n"
		                                     "- Multiple consecutive # for counter. #### will result in 0001, next capture would be 0002."));

	mBrowseButton->setText(tr("Browse"));
	connect(mBrowseButton, &QPushButton::clicked, this, &SaverSettings::chooseSaveDirectory);

	mSaveQualityLayout->addWidget(mSaveQualityDefaultRadioButton, 0, 0, 1, 1);
	mSaveQualityLayout->addWidget(mSaveQualityFactorRadioButton, 1, 0, 1, 1);
	mSaveQualityLayout->addWidget(mSaveQualityFactorSpinBox, 1, 1, 1, 1);
	mSaveQualityLayout->setColumnStretch(2, 1);

	mSaveQualityGroupBox->setLayout(mSaveQualityLayout);

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->addWidget(mAutoSaveNewCapturesCheckbox, 0, 0, 1, 4);
	mLayout->addWidget(mPromptToSaveBeforeExitCheckbox, 1, 0, 1, 4);
	mLayout->addWidget(mRememberSaveDirectoryCheckbox, 2, 0, 1, 4);
	mLayout->setRowMinimumHeight(3, 15);
	mLayout->addWidget(mSaveQualityGroupBox, 4, 0, 1, 4);
	mLayout->setRowMinimumHeight(5, 15);
	mLayout->addWidget(mSaveLocationLabel, 6, 0, 1, 4);
	mLayout->addWidget(mSaveLocationLineEdit, 7, 0, 1, 3);
	mLayout->addWidget(mBrowseButton, 7, 3);

	setTitle(tr("Saver Settings"));
	setLayout(mLayout);
}

void SaverSettings::loadConfig()
{
	mAutoSaveNewCapturesCheckbox->setChecked(mConfig->autoSaveNewCaptures());
	mPromptToSaveBeforeExitCheckbox->setChecked(mConfig->promptSaveBeforeExit());
	mRememberSaveDirectoryCheckbox->setChecked(mConfig->rememberLastSaveDirectory());
	mSaveQualityFactorSpinBox->setValue(mConfig->saveQualityFactor());
	mSaveQualityDefaultRadioButton->setChecked(mConfig->saveQualityMode() == SaveQualityMode::Default);
	mSaveQualityFactorRadioButton->setChecked(mConfig->saveQualityMode() == SaveQualityMode::Factor);
	mSaveLocationLineEdit->setText(mConfig->saveDirectory() + mConfig->saveFilename() + QStringLiteral(".") + mConfig->saveFormat());
}

void SaverSettings::saveSettings()
{
	mConfig->setAutoSaveNewCaptures(mAutoSaveNewCapturesCheckbox->isChecked());
	mConfig->setPromptSaveBeforeExit(mPromptToSaveBeforeExitCheckbox->isChecked());
	mConfig->setRememberLastSaveDirectory(mRememberSaveDirectoryCheckbox->isChecked());
	mConfig->setSaveQualityMode(getSaveQualityMode());
	mConfig->setSaveQualityFactor(mSaveQualityFactorSpinBox->value());
	mConfig->setSaveDirectory(PathHelper::extractParentDirectory(mSaveLocationLineEdit->displayText()));
	mConfig->setSaveFilename(PathHelper::extractFilename(mSaveLocationLineEdit->displayText()));
	mConfig->setSaveFormat(PathHelper::extractFormat(mSaveLocationLineEdit->displayText()));
}

void SaverSettings::chooseSaveDirectory()
{
	auto path = mFileDialog->getExistingDirectory(this, tr("Capture save location"), mConfig->saveDirectory());
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

SaveQualityMode SaverSettings::getSaveQualityMode()
{
	return mSaveQualityDefaultRadioButton->isChecked() ? SaveQualityMode::Default : SaveQualityMode::Factor;
}
