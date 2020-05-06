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

#include "ScriptUploaderSettings.h"

ScriptUploaderSettings::ScriptUploaderSettings(KsnipConfig *ksnipConfig) :
	mConfig(ksnipConfig),
	mLayout(new QGridLayout(this)),
	mCopyOutputToClipboardCheckbox(new QCheckBox(this)),
	mCopyOutputAfterLabel(new QLabel(this)),
	mCopyOutputBeforeLabel(new QLabel(this)),
	mScriptPathLabel(new QLabel(this)),
	mCopyOutputAfterLineEdit(new QLineEdit(this)),
	mCopyOutputBeforeLineEdit(new QLineEdit(this)),
	mUploadScriptPathLineEdit(new QLineEdit(this)),
	mBrowseButton(new QPushButton(this))
{
	initGui();
	loadConfig();
}

ScriptUploaderSettings::~ScriptUploaderSettings()
{
	delete mLayout;
	delete mCopyOutputToClipboardCheckbox;
	delete mCopyOutputAfterLabel;
	delete mCopyOutputBeforeLabel;
	delete mScriptPathLabel;
	delete mCopyOutputAfterLineEdit;
	delete mCopyOutputBeforeLineEdit;
	delete mUploadScriptPathLineEdit;
	delete mBrowseButton;
}

void ScriptUploaderSettings::saveSettings()
{
	mConfig->setUploadScriptCopyOutputToClipboard(mCopyOutputToClipboardCheckbox->isChecked());
	mConfig->setUploadScriptCopyOutputAfter(mCopyOutputAfterLineEdit->text());
	mConfig->setUploadScriptCopyOutputBefore(mCopyOutputBeforeLineEdit->text());
	mConfig->setUploadScriptPath(mUploadScriptPathLineEdit->text());
}

void ScriptUploaderSettings::initGui()
{
	mCopyOutputToClipboardCheckbox->setText(tr("Copy script output to clipboard"));
	connect(mCopyOutputToClipboardCheckbox, &QCheckBox::stateChanged, this, &ScriptUploaderSettings::copyToClipboardChanged);

	mCopyOutputAfterLabel->setText(tr("After:"));
	mCopyOutputAfterLabel->setToolTip(tr("Only output following this string will be copied to clipboard, excluding that string.\n"
									         "If omitted, everything from start will be copied."));

	mCopyOutputAfterLineEdit->setToolTip(mCopyOutputAfterLabel->toolTip());


	mCopyOutputBeforeLabel->setText(tr("Before:"));
	mCopyOutputBeforeLabel->setToolTip(tr("Only output before this string will be copied to clipboard, excluding that string.\n"
	                                          "If omitted, everything up to the end will be copied."));

	mCopyOutputBeforeLineEdit->setToolTip(mCopyOutputBeforeLabel->toolTip());

	mScriptPathLabel->setText(tr("Script: "));

	mBrowseButton->setText(tr("Browse"));
	connect(mBrowseButton, &QPushButton::clicked, this, &ScriptUploaderSettings::ShowScriptSelectionDialog);

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->setColumnMinimumWidth(0, ScaledSizeProvider::getScaledWidth(10));
	mLayout->addWidget(mCopyOutputToClipboardCheckbox, 0, 0, 1, 3);
	mLayout->addWidget(mCopyOutputAfterLabel, 1, 1, 1, 1);
	mLayout->addWidget(mCopyOutputAfterLineEdit, 1, 2, 1, 1);
	mLayout->addWidget(mCopyOutputBeforeLabel, 2, 1, 1, 1);
	mLayout->addWidget(mCopyOutputBeforeLineEdit, 2, 2, 1, 1);
	mLayout->addWidget(mScriptPathLabel, 3, 0, 1, 1);
	mLayout->addWidget(mUploadScriptPathLineEdit, 3, 1, 1, 2);
	mLayout->addWidget(mBrowseButton, 3, 3, 1, 1);

	setTitle(tr("Script Uploader"));
	setLayout(mLayout);
}

void ScriptUploaderSettings::loadConfig()
{
	mCopyOutputToClipboardCheckbox->setChecked(mConfig->uploadScriptCopyOutputToClipboard());
	mCopyOutputAfterLineEdit->setText(mConfig->uploadScriptCopyOutputAfter());
	mCopyOutputBeforeLineEdit->setText(mConfig->uploadScriptCopyOutputBefore());
	mUploadScriptPathLineEdit->setText(mConfig->uploadScriptPath());

	copyToClipboardChanged();
}

void ScriptUploaderSettings::ShowScriptSelectionDialog()
{
	auto path = QFileDialog::getOpenFileName(this, tr("Select Upload Script"), mConfig->uploadScriptPath());
	if(PathHelper::isPathValid(path)) {
		mUploadScriptPathLineEdit->setText(path);
	}
}

void ScriptUploaderSettings::copyToClipboardChanged()
{
	auto enabled = mCopyOutputToClipboardCheckbox->isChecked();
	mCopyOutputAfterLabel->setEnabled(enabled);
	mCopyOutputAfterLineEdit->setEnabled(enabled);
	mCopyOutputBeforeLabel->setEnabled(enabled);
	mCopyOutputBeforeLineEdit->setEnabled(enabled);
}
