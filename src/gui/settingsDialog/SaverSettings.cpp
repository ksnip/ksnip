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
	mSaveLocationLabel(new QLabel(this)),
	mSaveLocationLineEdit(new QLineEdit(this)),
	mBrowseButton(new QPushButton(this)),
	mLayout(new QGridLayout),
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
	delete mSaveLocationLabel;
	delete mSaveLocationLineEdit;
	delete mBrowseButton;
	delete mFileDialog;
}

void SaverSettings::initGui()
{
	mAutoSaveNewCapturesCheckbox->setText(tr("Automatically save new captures to default location"));
	mPromptToSaveBeforeExitCheckbox->setText(tr("Prompt to save before discarding unsaved changes"));

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

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->addWidget(mAutoSaveNewCapturesCheckbox, 0, 0, 1, 4);
	mLayout->addWidget(mPromptToSaveBeforeExitCheckbox, 1, 0, 1, 4);
	mLayout->addWidget(mRememberSaveDirectoryCheckbox, 2, 0, 1, 4);
	mLayout->setRowMinimumHeight(3, 15);
	mLayout->addWidget(mSaveLocationLabel, 4, 0, 1, 4);
	mLayout->addWidget(mSaveLocationLineEdit, 5, 0, 1, 4);
	mLayout->addWidget(mBrowseButton, 5, 4);

	setTitle(tr("Saver Settings"));
	setLayout(mLayout);
}

void SaverSettings::loadConfig()
{
	mAutoSaveNewCapturesCheckbox->setChecked(mConfig->autoSaveNewCaptures());
	mPromptToSaveBeforeExitCheckbox->setChecked(mConfig->promptSaveBeforeExit());
	mRememberSaveDirectoryCheckbox->setChecked(mConfig->rememberLastSaveDirectory());
	mSaveLocationLineEdit->setText(mConfig->saveDirectory() + mConfig->saveFilename() + QStringLiteral(".") + mConfig->saveFormat());
}

void SaverSettings::saveSettings()
{
	mConfig->setAutoSaveNewCaptures(mAutoSaveNewCapturesCheckbox->isChecked());
	mConfig->setPromptSaveBeforeExit(mPromptToSaveBeforeExitCheckbox->isChecked());
	mConfig->setRememberLastSaveDirectory(mRememberSaveDirectoryCheckbox->isChecked());
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
