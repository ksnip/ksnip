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

#include "ImgurUploaderSettings.h"

ImgurUploaderSettings::ImgurUploaderSettings(KsnipConfig *ksnipConfig) :
	mConfig(ksnipConfig),
	mForceAnonymousCheckbox(new QCheckBox(this)),
	mDirectLinkToImageCheckbox(new QCheckBox(this)),
	mAlwaysCopyToClipboardCheckBox(new QCheckBox(this)),
	mOpenLinkInBrowserCheckbox(new QCheckBox(this)),
	mClientIdLineEdit(new QLineEdit(this)),
	mClientSecretLineEdit(new QLineEdit(this)),
	mPinLineEdit(new QLineEdit(this)),
	mBaseUrlLineEdit(new CustomLineEdit(this)),
	mUsernameLabel(new QLabel(this)),
	mBaseUrlLabel(new QLabel(this)),
	mGetPinButton(new QPushButton(this)),
	mGetTokenButton(new QPushButton(this)),
	mHistoryButton(new QPushButton(this)),
	mImgurWrapper(new ImgurWrapper(mConfig->imgurBaseUrl(), this)),
	mLayout(new QGridLayout(this))
{
	Q_ASSERT(mConfig != nullptr);

	initGui();
	loadConfig();
}

ImgurUploaderSettings::~ImgurUploaderSettings()
{
	delete mForceAnonymousCheckbox;
	delete mDirectLinkToImageCheckbox;
	delete mAlwaysCopyToClipboardCheckBox;
	delete mOpenLinkInBrowserCheckbox;
	delete mClientIdLineEdit;
	delete mClientSecretLineEdit;
	delete mPinLineEdit;
	delete mBaseUrlLineEdit;
	delete mUsernameLabel;
	delete mBaseUrlLabel;
	delete mGetPinButton;
	delete mGetTokenButton;
	delete mHistoryButton;
	delete mImgurWrapper;
	delete mLayout;
}

void ImgurUploaderSettings::saveSettings()
{
	mConfig->setImgurForceAnonymous(mForceAnonymousCheckbox->isChecked());
	mConfig->setImgurLinkDirectlyToImage(mDirectLinkToImageCheckbox->isChecked());
	mConfig->setImgurAlwaysCopyToClipboard(mAlwaysCopyToClipboardCheckBox->isChecked());
	mConfig->setImgurOpenLinkInBrowser(mOpenLinkInBrowserCheckbox->isChecked());
	mConfig->setImgurBaseUrl(mBaseUrlLineEdit->textOrPlaceholderText());
}

void ImgurUploaderSettings::initGui()
{
	connect(mImgurWrapper, &ImgurWrapper::tokenUpdated, this, &ImgurUploaderSettings::imgurTokenUpdated);
	connect(mImgurWrapper, &ImgurWrapper::error, this, &ImgurUploaderSettings::imgurTokenError);

	mForceAnonymousCheckbox->setText(tr("Force anonymous upload"));
	mOpenLinkInBrowserCheckbox->setText(tr("After uploading open Imgur link in default browser"));
	mDirectLinkToImageCheckbox->setText(tr("Link directly to image"));
	mAlwaysCopyToClipboardCheckBox->setText(tr("Always copy Imgur link to clipboard"));

	mBaseUrlLabel->setText(tr("Base Url:"));
	mBaseUrlLabel->setToolTip(tr("Base url that will be used for communication with Imgur.\n"
	                             "Changing requires restart."));

	mClientIdLineEdit->setPlaceholderText(tr("Client ID"));
	connect(mClientIdLineEdit, &QLineEdit::textChanged, this, &ImgurUploaderSettings::imgurClientEntered);

	mClientSecretLineEdit->setPlaceholderText(tr("Client Secret"));
	connect(mClientSecretLineEdit, &QLineEdit::textChanged, this, &ImgurUploaderSettings::imgurClientEntered);

	mPinLineEdit->setPlaceholderText(tr("PIN"));
	mPinLineEdit->setToolTip(tr("Enter imgur Pin which will be exchanged for a token."));
	connect(mPinLineEdit, &QLineEdit::textChanged, [this](const QString & text) {
		mGetTokenButton->setEnabled(text.length() > 8);
	});

	mBaseUrlLineEdit->setPlaceholderText(DefaultValues::ImgurBaseUrl);
	mBaseUrlLineEdit->setToolTip(mBaseUrlLabel->toolTip());

	mGetPinButton->setText(tr("Get PIN"));
	connect(mGetPinButton, &QPushButton::clicked, this, &ImgurUploaderSettings::requestImgurPin);
	mGetPinButton->setEnabled(false);

	mGetTokenButton->setText(tr("Get Token"));
	connect(mGetTokenButton, &QPushButton::clicked, this, &ImgurUploaderSettings::getImgurToken);
	mGetTokenButton->setEnabled(false);

	mHistoryButton->setText(tr("Imgur History"));
	connect(mHistoryButton, &QPushButton::clicked, this, &ImgurUploaderSettings::showImgurHistoryDialog);

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->setColumnMinimumWidth(0, 10);
	mLayout->addWidget(mForceAnonymousCheckbox, 0, 0, 1, 3);
	mLayout->addWidget(mOpenLinkInBrowserCheckbox, 1, 0, 1, 3);
	mLayout->addWidget(mDirectLinkToImageCheckbox, 2, 0, 1, 3);
	mLayout->addWidget(mAlwaysCopyToClipboardCheckBox, 3, 0, 1, 3);
	mLayout->setRowMinimumHeight(4, 15);
	mLayout->addWidget(mBaseUrlLabel, 5, 0, 1, 1);
	mLayout->addWidget(mBaseUrlLineEdit, 5, 1, 1, 2);
	mLayout->setRowMinimumHeight(6, 15);
	mLayout->addWidget(mUsernameLabel, 7, 0, 1, 3);
	mLayout->addWidget(mHistoryButton, 7, 3, 1, 1);
	mLayout->addWidget(mClientIdLineEdit, 8, 0, 1, 3);
	mLayout->addWidget(mClientSecretLineEdit, 9, 0, 1, 3);
	mLayout->addWidget(mGetPinButton, 9, 3, 1, 1);
	mLayout->addWidget(mPinLineEdit, 10, 0, 1, 3);
	mLayout->addWidget(mGetTokenButton, 10, 3, 1, 1);

	setTitle(tr("Imgur Uploader"));
	setLayout(mLayout);
}

void ImgurUploaderSettings::loadConfig()
{
	mForceAnonymousCheckbox->setChecked(mConfig->imgurForceAnonymous());
	mOpenLinkInBrowserCheckbox->setChecked(mConfig->imgurOpenLinkInBrowser());
	mDirectLinkToImageCheckbox->setChecked(mConfig->imgurLinkDirectlyToImage());
	mAlwaysCopyToClipboardCheckBox->setChecked(mConfig->imgurAlwaysCopyToClipboard());
	mBaseUrlLineEdit->setText(mConfig->imgurBaseUrl());

	mUsernameLabel->setText(tr("Username") + ": " + mConfig->imgurUsername());
	if(!mConfig->imgurClientId().isEmpty()) {
		mClientIdLineEdit->setPlaceholderText(mConfig->imgurClientId());
	}
}

/*
 * Based on the entered client id and client secret we create a pin request and open it up in the
 * default browser.
 */
void ImgurUploaderSettings::requestImgurPin()
{
	// Save client ID and Secret to config file
	mConfig->setImgurClientId(mClientIdLineEdit->text().toUtf8());
	mConfig->setImgurClientSecret(mClientSecretLineEdit->text().toUtf8());

	// Open the pin request in the default browser
	QDesktopServices::openUrl(mImgurWrapper->pinRequestUrl(mClientIdLineEdit->text()));

	// Cleanup line edits
	mClientIdLineEdit->setPlaceholderText(mClientIdLineEdit->text());
	mClientIdLineEdit->clear();

	mClientSecretLineEdit->clear();
}

/*
 * Request a new token from imgur.com when clicked.
 */
void ImgurUploaderSettings::getImgurToken()
{
	mImgurWrapper->getAccessToken(mPinLineEdit->text().toUtf8(),
	                              mConfig->imgurClientId(),
	                              mConfig->imgurClientSecret());
	mPinLineEdit->clear();
	qInfo("%s", qPrintable(tr("Waiting for imgur.com…")));
}

void ImgurUploaderSettings::imgurClientEntered(const QString&)
{
	mGetPinButton->setEnabled(!mClientIdLineEdit->text().isEmpty() && !mClientSecretLineEdit->text().isEmpty());
}

/*
 * We have received a new token from imgur.com, now we save it to config for
 * later use and inform the user about it.
 */
void ImgurUploaderSettings::imgurTokenUpdated(const QString& accessToken, const QString& refreshToken, const QString& username)
{
	mConfig->setImgurAccessToken(accessToken.toUtf8());
	mConfig->setImgurRefreshToken(refreshToken.toUtf8());
	mConfig->setImgurUsername(username);

	mUsernameLabel->setText(tr("Username:") + username);
	qInfo("%s", qPrintable(tr("Imgur.com token successfully updated.")));
}

/*
 * Something went wrong while requesting a new token, we write the message to
 * shell.
 */
void ImgurUploaderSettings::imgurTokenError(const QString& message)
{
	qCritical("SettingsDialog returned error: '%s'", qPrintable(message));
	qInfo("%s", qPrintable(tr("Imgur.com token update error.")));
}

void ImgurUploaderSettings::showImgurHistoryDialog()
{
	ImgurHistoryDialog dialog;
	dialog.exec();
}

