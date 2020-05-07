/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "UploaderSettings.h"

UploaderSettings::UploaderSettings(KsnipConfig *ksnipConfig) :
	mConfig(ksnipConfig),
	mConfirmBeforeUploadCheckbox(new QCheckBox(this)),
	mUploaderTypeComboBox(new QComboBox(this)),
	mUploaderTypeLabel(new QLabel(this)),
	mLayout(new QGridLayout(this))
{
	initGui();
	loadConfig();
}

UploaderSettings::~UploaderSettings()
{
	delete mConfirmBeforeUploadCheckbox;
	delete mUploaderTypeComboBox;
	delete mUploaderTypeLabel;
}

void UploaderSettings::saveSettings()
{
	mConfig->setConfirmBeforeUpload(mConfirmBeforeUploadCheckbox->isChecked());
	mConfig->setUploaderType(static_cast<UploaderType>(mUploaderTypeComboBox->currentData().toInt()));
}

void UploaderSettings::initGui()
{
	mConfirmBeforeUploadCheckbox->setText(tr("Ask for confirmation before uploading"));

	mUploaderTypeLabel->setText(tr("Uploader Type:"));

	mUploaderTypeComboBox->addItem(tr("Imgur"), static_cast<int>(UploaderType::Imgur));
	mUploaderTypeComboBox->addItem(tr("Script"), static_cast<int>(UploaderType::Script));

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->addWidget(mConfirmBeforeUploadCheckbox, 0, 0, 1, 3);
	mLayout->setRowMinimumHeight(1, 15);
	mLayout->addWidget(mUploaderTypeLabel, 2, 0, 1, 1);
	mLayout->addWidget(mUploaderTypeComboBox, 2, 1, 1, 1);

	setTitle(tr("Uploader"));
	setLayout(mLayout);
}

void UploaderSettings::loadConfig()
{
	mConfirmBeforeUploadCheckbox->setChecked(mConfig->confirmBeforeUpload());
	mUploaderTypeComboBox->setCurrentIndex(mUploaderTypeComboBox->findData(static_cast<int>(mConfig->uploaderType())));
}
