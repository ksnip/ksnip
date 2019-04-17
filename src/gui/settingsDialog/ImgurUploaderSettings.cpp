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

#include "ImgurUploaderSettings.h"

ImgurUploaderSettings::ImgurUploaderSettings(KsnipConfig *ksnipConfig)
{
	Q_ASSERT(ksnipConfig != nullptr);

	mConfig = ksnipConfig;

	initGui();
	loadConfig();
}

ImgurUploaderSettings::~ImgurUploaderSettings()
{
	delete mImgurForceAnonymousCheckbox;
	delete mImgurDirectLinkToImageCheckbox;
	delete mImgurAlwaysCopyToClipboardCheckBox;
	delete mImgurConfirmBeforeUploadCheckbox;
	delete mImgurClientIdLineEdit;
	delete mImgurClientSecretLineEdit;
	delete mImgurPinLineEdit;
	delete mImgurUsernameLabel;
	delete mImgurGetPinButton;
	delete mImgurGetTokenButton;
	delete mImgurHistoryButton;
	delete mImgurUploader;
	delete mLayout;
}

void ImgurUploaderSettings::saveSettings()
{
	mConfig->setImgurForceAnonymous(mImgurForceAnonymousCheckbox->isChecked());
	mConfig->setImgurOpenLinkDirectlyToImage(mImgurDirectLinkToImageCheckbox->isChecked());
	mConfig->setImgurAlwaysCopyToClipboard(mImgurAlwaysCopyToClipboardCheckBox->isChecked());
	mConfig->setImgurConfirmBeforeUpload(mImgurConfirmBeforeUploadCheckbox->isChecked());
}

void ImgurUploaderSettings::initGui()
{
	mImgurForceAnonymousCheckbox = new QCheckBox(this);
	mImgurDirectLinkToImageCheckbox = new QCheckBox(this);
	mImgurAlwaysCopyToClipboardCheckBox = new QCheckBox(this);
	mImgurConfirmBeforeUploadCheckbox = new QCheckBox(this);
	mImgurClientIdLineEdit = new QLineEdit(this);
	mImgurClientSecretLineEdit = new QLineEdit(this);
	mImgurPinLineEdit = new QLineEdit(this);
	mImgurUsernameLabel = new QLabel(this);
	mImgurGetPinButton = new QPushButton(this);
	mImgurGetTokenButton = new QPushButton(this);
	mImgurHistoryButton = new QPushButton(this);
	mImgurUploader = new ImgurUploader(this);
	mLayout = new QGridLayout(this);

	connect(mImgurUploader, &ImgurUploader::tokenUpdated, this, &ImgurUploaderSettings::imgurTokenUpdated);
	connect(mImgurUploader, &ImgurUploader::error, this, &ImgurUploaderSettings::imgurTokenError);

	mImgurForceAnonymousCheckbox->setText(tr("Force anonymous upload"));
	mImgurDirectLinkToImageCheckbox->setText(tr("Open link directly to image"));
	mImgurAlwaysCopyToClipboardCheckBox->setText(tr("Always copy Imgur link to clipboard"));
	mImgurConfirmBeforeUploadCheckbox->setText(tr("Ask for confirmation before uploading"));

	mImgurClientIdLineEdit->setPlaceholderText(tr("Client ID"));
	connect(mImgurClientIdLineEdit, &QLineEdit::textChanged, this, &ImgurUploaderSettings::imgurClientEntered);

	mImgurClientSecretLineEdit->setPlaceholderText(tr("Client Secret"));
	connect(mImgurClientSecretLineEdit, &QLineEdit::textChanged, this, &ImgurUploaderSettings::imgurClientEntered);

	mImgurPinLineEdit->setPlaceholderText(tr("PIN"));
	mImgurPinLineEdit->setToolTip(tr("Enter imgur Pin which will be exchanged for a token."));
	connect(mImgurPinLineEdit, &QLineEdit::textChanged, [this](const QString & text) {
		mImgurGetTokenButton->setEnabled(text.length() > 8);
	});

	mImgurGetPinButton->setText(tr("Get PIN"));
	connect(mImgurGetPinButton, &QPushButton::clicked, this, &ImgurUploaderSettings::requestImgurPin);
	mImgurGetPinButton->setEnabled(false);

	mImgurGetTokenButton->setText(tr("Get Token"));
	connect(mImgurGetTokenButton, &QPushButton::clicked, this, &ImgurUploaderSettings::getImgurToken);
	mImgurGetTokenButton->setEnabled(false);

	mImgurHistoryButton->setText(tr("Imgur History"));
	connect(mImgurHistoryButton, &QPushButton::clicked, this, &ImgurUploaderSettings::showImgurHistoryDialog);

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->setColumnStretch(0, 1);
	mLayout->addWidget(mImgurForceAnonymousCheckbox, 0, 0);
	mLayout->addWidget(mImgurDirectLinkToImageCheckbox, 1, 0);
	mLayout->addWidget(mImgurAlwaysCopyToClipboardCheckBox, 2, 0);
	mLayout->addWidget(mImgurConfirmBeforeUploadCheckbox, 3, 0);
	mLayout->setRowMinimumHeight(4, 15);
	mLayout->addWidget(mImgurUsernameLabel, 5, 0);
	mLayout->addWidget(mImgurHistoryButton, 5, 3);
	mLayout->addWidget(mImgurClientIdLineEdit, 6, 0);
	mLayout->addWidget(mImgurClientSecretLineEdit, 7, 0);
	mLayout->addWidget(mImgurGetPinButton, 7, 3);
	mLayout->addWidget(mImgurPinLineEdit, 8, 0);
	mLayout->addWidget(mImgurGetTokenButton, 8, 3);

	setTitle(tr("Imgur Uploader"));
	setLayout(mLayout);
}

void ImgurUploaderSettings::loadConfig()
{
	mImgurForceAnonymousCheckbox->setChecked(mConfig->imgurForceAnonymous());
	mImgurDirectLinkToImageCheckbox->setChecked(mConfig->imgurOpenLinkDirectlyToImage());
	mImgurAlwaysCopyToClipboardCheckBox->setChecked(mConfig->imgurAlwaysCopyToClipboard());
	mImgurConfirmBeforeUploadCheckbox->setChecked(mConfig->imgurConfirmBeforeUpload());

	mImgurUsernameLabel->setText(tr("Username") + ": " + mConfig->imgurUsername());
	if(!mConfig->imgurClientId().isEmpty()) {
		mImgurClientIdLineEdit->setPlaceholderText(mConfig->imgurClientId());
	}
}

/*
 * Based on the entered client id and client secret we create a pin request and open it up in the
 * default browser.
 */
void ImgurUploaderSettings::requestImgurPin()
{
	// Save client ID and Secret to config file
	mConfig->setImgurClientId(mImgurClientIdLineEdit->text().toUtf8());
	mConfig->setImgurClientSecret(mImgurClientSecretLineEdit->text().toUtf8());

	// Open the pin request in the default browser
	QDesktopServices::openUrl(mImgurUploader->pinRequestUrl(mImgurClientIdLineEdit->text()));

	// Cleanup line edits
	mImgurClientIdLineEdit->setPlaceholderText(mImgurClientIdLineEdit->text());
	mImgurClientIdLineEdit->clear();

	mImgurClientSecretLineEdit->clear();
}

/*
 * Request a new token from imgur.com when clicked.
 */
void ImgurUploaderSettings::getImgurToken()
{
	mImgurUploader->getAccessToken(mImgurPinLineEdit->text().toUtf8(),
	                               mConfig->imgurClientId(),
	                               mConfig->imgurClientSecret());
	mImgurPinLineEdit->clear();
	qInfo("%s", qPrintable(tr("Waiting for imgur.com...")));
}

void ImgurUploaderSettings::imgurClientEntered(const QString&)
{
	mImgurGetPinButton->setEnabled(!mImgurClientIdLineEdit->text().isEmpty() && !mImgurClientSecretLineEdit->text().isEmpty());
}

/*
 * We have received a new token from imgur.com, now we save it to config for
 * later use and inform the user about it.
 */
void ImgurUploaderSettings::imgurTokenUpdated(const QString& accessToken,
                                       const QString& refreshTocken,
                                       const QString& username)
{
	mConfig->setImgurAccessToken(accessToken.toUtf8());
	mConfig->setImgurRefreshToken(refreshTocken.toUtf8());
	mConfig->setImgurUsername(username);

	mImgurUsernameLabel->setText(tr("Username:") + username);
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
