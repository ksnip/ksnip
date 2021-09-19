/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "FtpUploaderSettings.h"

FtpUploaderSettings::FtpUploaderSettings(KsnipConfig *config) :
	mConfig(config),
	mLayout(new QGridLayout(this)),
	mForceAnonymousUploadCheckBox(new QCheckBox(this)),
	mUrlLabel(new QLabel(this)),
	mUsernameLabel(new QLabel(this)),
	mPasswordLabel(new QLabel(this)),
	mUrlLineEdit(new QLineEdit(this)),
	mUsernameLineEdit(new QLineEdit(this)),
	mPasswordLineEdit(new QLineEdit(this))
{
	initGui();
	loadConfig();
}

void FtpUploaderSettings::saveSettings()
{
	mConfig->setFtpUploadForceAnonymous(mForceAnonymousUploadCheckBox->isChecked());
	mConfig->setFtpUploadUrl(mUrlLineEdit->text());
	mConfig->setFtpUploadUsername(mUsernameLineEdit->text());
	mConfig->setFtpUploadPassword(mPasswordLineEdit->text());
}

void FtpUploaderSettings::initGui()
{
	mForceAnonymousUploadCheckBox->setText(tr("Force anonymous upload."));

	mUrlLabel->setText(tr("Url") + QLatin1String(":"));

	mUsernameLabel->setText(tr("Username") + QLatin1String(":"));

	mPasswordLabel->setText(tr("Password") + QLatin1String(":"));
	mPasswordLineEdit->setEchoMode(QLineEdit::Password);

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->addWidget(mForceAnonymousUploadCheckBox, 0, 0, 1, 3);
	mLayout->setRowMinimumHeight(1, 15);
	mLayout->addWidget(mUrlLabel, 2, 0, 1, 1);
	mLayout->addWidget(mUrlLineEdit, 2, 1, 1, 2);
	mLayout->setRowMinimumHeight(3, 15);
	mLayout->addWidget(mUsernameLabel, 4, 0, 1, 1);
	mLayout->addWidget(mUsernameLineEdit, 4, 1, 1, 1);
	mLayout->addWidget(mPasswordLabel, 5, 0, 1, 1);
	mLayout->addWidget(mPasswordLineEdit, 5, 1, 1, 1);

	setTitle(tr("FTP Uploader"));
	setLayout(mLayout);
}

void FtpUploaderSettings::loadConfig()
{
	mForceAnonymousUploadCheckBox->setChecked(mConfig->ftpUploadForceAnonymous());
	mUrlLineEdit->setText(mConfig->ftpUploadUrl());
	mUsernameLineEdit->setText(mConfig->ftpUploadUsername());
	mPasswordLineEdit->setText(mConfig->ftpUploadPassword());
}
