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
	mStopOnStdErrCheckbox(new QCheckBox(this)),
	mCopyOutputFilterLabel(new QLabel(this)),
	mScriptPathLabel(new QLabel(this)),
	mCopyOutputFilterLineEdit(new QLineEdit(this)),
	mUploadScriptPathLineEdit(new QLineEdit(this)),
	mBrowseButton(new QPushButton(this)),
	mFileDialog(FileDialogAdapterFactory::create())
{
	initGui();
	loadConfig();
}

ScriptUploaderSettings::~ScriptUploaderSettings()
{
	delete mLayout;
	delete mCopyOutputToClipboardCheckbox;
	delete mStopOnStdErrCheckbox;
	delete mCopyOutputFilterLabel;
	delete mScriptPathLabel;
	delete mCopyOutputFilterLineEdit;
	delete mUploadScriptPathLineEdit;
	delete mBrowseButton;
}

void ScriptUploaderSettings::saveSettings()
{
	mConfig->setUploadScriptStopOnStdErr(mStopOnStdErrCheckbox->isChecked());
	mConfig->setUploadScriptCopyOutputToClipboard(mCopyOutputToClipboardCheckbox->isChecked());
	mConfig->setUploadScriptCopyOutputFilter(mCopyOutputFilterLineEdit->text());
	mConfig->setUploadScriptPath(mUploadScriptPathLineEdit->text());
}

void ScriptUploaderSettings::initGui()
{
	mStopOnStdErrCheckbox->setText(tr("Stop when upload script writes to StdErr"));
	mStopOnStdErrCheckbox->setToolTip(tr("Marks the upload as failed when script writes to StdErr.\n"
									        "Without this setting errors in the script will be unnoticed."));

	mCopyOutputToClipboardCheckbox->setText(tr("Copy script output to clipboard"));
	connect(mCopyOutputToClipboardCheckbox, &QCheckBox::stateChanged, this, &ScriptUploaderSettings::copyToClipboardChanged);

	mCopyOutputFilterLabel->setText(tr("Filter:"));
	mCopyOutputFilterLabel->setToolTip(tr("RegEx Expression. Only copy to clipboard what matches the RegEx Expression.\n"
									         "When omitted, everything is copied."));

	mCopyOutputFilterLineEdit->setToolTip(mCopyOutputFilterLabel->toolTip());

	mScriptPathLabel->setText(tr("Script:"));
	mScriptPathLabel->setToolTip(tr("Path to script that will be called for uploading. During upload the script will be called\n"
								 "with the path to a temporary png file as a single argument."));

	mUploadScriptPathLineEdit->setToolTip(mScriptPathLabel->toolTip());

	mBrowseButton->setText(tr("Browse"));
	connect(mBrowseButton, &QPushButton::clicked, this, &ScriptUploaderSettings::ShowScriptSelectionDialog);

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->setColumnMinimumWidth(0, 10);
	mLayout->addWidget(mStopOnStdErrCheckbox, 0, 0, 1, 3);
	mLayout->addWidget(mCopyOutputToClipboardCheckbox, 1, 0, 1, 3);
	mLayout->addWidget(mCopyOutputFilterLabel, 2, 1, 1, 1);
	mLayout->addWidget(mCopyOutputFilterLineEdit, 2, 2, 1, 1);
	mLayout->addWidget(mScriptPathLabel, 3, 0, 1, 1);
	mLayout->addWidget(mUploadScriptPathLineEdit, 3, 1, 1, 2);
	mLayout->addWidget(mBrowseButton, 3, 3, 1, 1);

	setTitle(tr("Script Uploader"));
	setLayout(mLayout);
}

void ScriptUploaderSettings::loadConfig()
{
	mStopOnStdErrCheckbox->setChecked(mConfig->uploadScriptStopOnStdErr());
	mCopyOutputToClipboardCheckbox->setChecked(mConfig->uploadScriptCopyOutputToClipboard());
	mCopyOutputFilterLineEdit->setText(mConfig->uploadScriptCopyOutputFilter());
	mUploadScriptPathLineEdit->setText(mConfig->uploadScriptPath());

	copyToClipboardChanged();
}

void ScriptUploaderSettings::ShowScriptSelectionDialog()
{
	auto path = mFileDialog->getOpenFileName(this, tr("Select Upload Script"), mConfig->uploadScriptPath());
	if(PathHelper::isPathValid(path)) {
		mUploadScriptPathLineEdit->setText(path);
	}
}

void ScriptUploaderSettings::copyToClipboardChanged()
{
	auto enabled = mCopyOutputToClipboardCheckbox->isChecked();
	mCopyOutputFilterLabel->setEnabled(enabled);
	mCopyOutputFilterLineEdit->setEnabled(enabled);
}
