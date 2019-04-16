/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
	mImgurForceAnonymousCheckbox(new QCheckBox),
	mImgurDirectLinkToImageCheckbox(new QCheckBox),
	mImgurAlwaysCopyToClipboardCheckBox(new QCheckBox),
	mImgurConfirmBeforeUploadCheckbox(new QCheckBox),
	mSmoothPathCheckbox(new QCheckBox),
	mItemShadowCheckbox(new QCheckBox),
	mImgurClientIdLineEdit(new QLineEdit),
	mImgurClientSecretLineEdit(new QLineEdit),
	mImgurPinLineEdit(new QLineEdit),
	mImgurUsernameLabel(new QLabel),
	mTextFontLabel(new QLabel),
	mNumberFontLabel(new QLabel),
	mSmoothFactorLabel(new QLabel),
	mSmoothFactorCombobox(new NumericComboBox(1, 1, 15)),
	mTextFontCombobox(new QFontComboBox(this)),
	mNumberFontCombobox(new QFontComboBox(this)),
	mImgurGetPinButton(new QPushButton),
	mImgurGetTokenButton(new QPushButton),
	mOkButton(new QPushButton),
	mCancelButton(new QPushButton),
	mImgurHistoryButton(new QPushButton),
	mTextBoldButton(new QToolButton),
	mTextItalicButton(new QToolButton),
	mTextUnderlineButton(new QToolButton),
	mImgurUploader(new ImgurUploader),
	mListWidget(new QListWidget),
	mStackedLayout(new QStackedLayout),
	mConfig(KsnipConfig::instance())
{
    setWindowTitle(QApplication::applicationName() + QStringLiteral(" - ") + tr("Settings"));

    initGui();

    loadSettings();

    connect(mImgurUploader, &ImgurUploader::tokenUpdated, this, &SettingsDialog::imgurTokenUpdated);
    connect(mImgurUploader, &ImgurUploader::error, this, &SettingsDialog::imgurTokenError);
    connect(mListWidget, &QListWidget::itemSelectionChanged, [this]() {
        mStackedLayout->setCurrentIndex(mListWidget->currentRow());
    });
}

SettingsDialog::~SettingsDialog()
{
    delete mImgurForceAnonymousCheckbox;
    delete mImgurDirectLinkToImageCheckbox;
    delete mImgurAlwaysCopyToClipboardCheckBox;
    delete mImgurConfirmBeforeUploadCheckbox;
    delete mSmoothPathCheckbox;
    delete mItemShadowCheckbox;
    delete mImgurClientIdLineEdit;
    delete mImgurClientSecretLineEdit;
    delete mImgurPinLineEdit;
    delete mImgurUsernameLabel;
    delete mTextFontLabel;
    delete mNumberFontLabel;
    delete mSmoothFactorLabel;
    delete mSmoothFactorCombobox;
    delete mTextFontCombobox;
    delete mNumberFontCombobox;
    delete mImgurGetPinButton;
    delete mImgurGetTokenButton;
    delete mOkButton;
    delete mCancelButton;
	delete mImgurHistoryButton;
    delete mTextBoldButton;
    delete mTextItalicButton;
    delete mTextUnderlineButton;
    delete mImgurUploader;
    delete mListWidget;
    delete mStackedLayout;
}

void SettingsDialog::loadSettings()
{
    mImgurForceAnonymousCheckbox->setChecked(mConfig->imgurForceAnonymous());
    mImgurDirectLinkToImageCheckbox->setChecked(mConfig->imgurOpenLinkDirectlyToImage());
    mImgurAlwaysCopyToClipboardCheckBox->setChecked(mConfig->imgurAlwaysCopyToClipboard());
    mImgurConfirmBeforeUploadCheckbox->setChecked(mConfig->imgurConfirmBeforeUpload());

    mImgurUsernameLabel->setText(tr("Username") + ": " + mConfig->imgurUsername());
    if(!mConfig->imgurClientId().isEmpty()) {
        mImgurClientIdLineEdit->setPlaceholderText(mConfig->imgurClientId());
    }

    mTextFontCombobox->setCurrentFont(mConfig->textFont());
    mTextBoldButton->setChecked(mConfig->textBold());
    mTextItalicButton->setChecked(mConfig->textItalic());
    mTextUnderlineButton->setChecked(mConfig->textUnderline());
    mNumberFontCombobox->setCurrentFont(mConfig->numberFont());
    mItemShadowCheckbox->setChecked(mConfig->itemShadowEnabled());
    mSmoothPathCheckbox->setChecked(mConfig->smoothPathEnabled());
    mSmoothFactorCombobox->setValue(mConfig->smoothFactor());
    smootPathCheckboxClicked(mConfig->smoothPathEnabled());
}

void SettingsDialog::saveSettings()
{
    mConfig->setImgurForceAnonymous(mImgurForceAnonymousCheckbox->isChecked());
    mConfig->setImgurOpenLinkDirectlyToImage(mImgurDirectLinkToImageCheckbox->isChecked());
    mConfig->setImgurAlwaysCopyToClipboard(mImgurAlwaysCopyToClipboardCheckBox->isChecked());
    mConfig->setImgurConfirmBeforeUpload(mImgurConfirmBeforeUploadCheckbox->isChecked());

    mConfig->setTextFont(mTextFontCombobox->currentFont());
    mConfig->setTextBold(mTextBoldButton->isChecked());
    mConfig->setTextItalic(mTextItalicButton->isChecked());
    mConfig->setTextUnderline(mTextUnderlineButton->isChecked());
    mConfig->setNumberFont(mNumberFontCombobox->currentFont());
    mConfig->setItemShadowEnabled(mItemShadowCheckbox->isChecked());
    mConfig->setSmoothPathEnabled(mSmoothPathCheckbox->isChecked());
    mConfig->setSmoothFactor(mSmoothFactorCombobox->value());

    mApplicationSettings->saveSettings();
    mImageGrabberSettings->saveSettings();
}

void SettingsDialog::initGui()
{
    auto const fixedButtonSize = 100;

    // Create Imgur Uploader Settings
    mImgurForceAnonymousCheckbox->setText(tr("Force anonymous upload"));
    mImgurDirectLinkToImageCheckbox->setText(tr("Open link directly to image"));
    mImgurAlwaysCopyToClipboardCheckBox->setText(tr("Always copy Imgur link to clipboard"));
    mImgurConfirmBeforeUploadCheckbox->setText(tr("Ask for confirmation before uploading"));

    mImgurClientIdLineEdit->setPlaceholderText(tr("Client ID"));
    connect(mImgurClientIdLineEdit, &QLineEdit::textChanged, this, &SettingsDialog::imgurClientEntered);

    mImgurClientSecretLineEdit->setPlaceholderText(tr("Client Secret"));
    connect(mImgurClientSecretLineEdit, &QLineEdit::textChanged, this, &SettingsDialog::imgurClientEntered);

    mImgurPinLineEdit->setPlaceholderText(tr("PIN"));
    mImgurPinLineEdit->setToolTip(tr("Enter imgur Pin which will be exchanged for a token."));
    connect(mImgurPinLineEdit, &QLineEdit::textChanged, [this](const QString & text) {
        mImgurGetTokenButton->setEnabled(text.length() > 8);
    });

    mImgurGetPinButton->setText(tr("Get PIN"));
    connect(mImgurGetPinButton, &QPushButton::clicked, this, &SettingsDialog::requestImgurPin);
    mImgurGetPinButton->setEnabled(false);

    mImgurGetTokenButton->setText(tr("Get Token"));
    connect(mImgurGetTokenButton, &QPushButton::clicked, this, &SettingsDialog::getImgurToken);
    mImgurGetTokenButton->setEnabled(false);

	mImgurHistoryButton->setText(tr("Imgur History"));
	connect(mImgurHistoryButton, &QPushButton::clicked, this, &SettingsDialog::showImgurHistoryDialog);

    // Create Painter Settings
    mItemShadowCheckbox->setText(tr("Paint Item Shadows"));
    mItemShadowCheckbox->setToolTip(tr("When enabled, paint items cast shadows."));

    mSmoothPathCheckbox->setText(tr("Smooth Painter Paths"));
    mSmoothPathCheckbox->setToolTip(tr("When enabled smooths out pen and\n"
                                       "marker paths after finished drawing."));
    connect(mSmoothPathCheckbox, &QCheckBox::clicked, this, &SettingsDialog::smootPathCheckboxClicked);

    mSmoothFactorLabel->setText(tr("Smooth Factor") + QStringLiteral(":"));
    mSmoothFactorLabel->setToolTip(tr("Increasing the smooth factor will decrease\n"
                                      "precision for pen and marker but will\n"
                                      "make them more smooth."));
    mSmoothFactorCombobox->setMinimumWidth(fixedButtonSize);
    mSmoothFactorCombobox->setToolTip(mSmoothFactorLabel->toolTip());

    mTextFontLabel->setText(tr("Text Font") + QStringLiteral(":"));
    mTextFontLabel->setToolTip(tr("Sets the font for the Text Paint Item."));
    mTextFontCombobox->setToolTip(mTextFontLabel->toolTip());
    mTextFontCombobox->setEditable(false);

	mTextBoldButton->setIcon(IconLoader::load(QStringLiteral("bold.svg")));
    mTextBoldButton->setToolTip(tr("Bold"));
    mTextBoldButton->setCheckable(true);

	mTextItalicButton->setIcon(IconLoader::load(QStringLiteral("italic.svg")));
    mTextItalicButton->setToolTip(tr("Italic"));
    mTextItalicButton->setCheckable(true);

	mTextUnderlineButton->setIcon(IconLoader::load(QStringLiteral("underline.svg")));
    mTextUnderlineButton->setToolTip(tr("Underline"));
    mTextUnderlineButton->setCheckable(true);

    mNumberFontLabel->setText(tr("Numbering Font") + QStringLiteral(":"));
    mNumberFontLabel->setToolTip(tr("Sets the font for the Numbering Paint Item."));
    mNumberFontCombobox->setToolTip(mNumberFontLabel->toolTip());
    mNumberFontCombobox->setEditable(false);

	mApplicationSettings = new ApplicationSettings(mConfig);
	mImageGrabberSettings = new ImageGrabberSettings(mConfig);

    // Create Push Buttons
    mOkButton->setText(tr("OK"));
    connect(mOkButton, &QPushButton::clicked, [this]() {
        saveSettings();
        close();
    });

    mCancelButton->setText(tr("Cancel"));
    connect(mCancelButton, &QPushButton::clicked, [this]() {
        close();
    });

    // Setup Imgur Uploader Layout
    auto imgurUploaderGrid = new QGridLayout;
    imgurUploaderGrid->setAlignment(Qt::AlignTop);
    imgurUploaderGrid->setColumnStretch(0, 1);
    imgurUploaderGrid->addWidget(mImgurForceAnonymousCheckbox, 0, 0);
    imgurUploaderGrid->addWidget(mImgurDirectLinkToImageCheckbox, 1, 0);
    imgurUploaderGrid->addWidget(mImgurAlwaysCopyToClipboardCheckBox, 2, 0);
    imgurUploaderGrid->addWidget(mImgurConfirmBeforeUploadCheckbox, 3, 0);
    imgurUploaderGrid->setRowMinimumHeight(4, 15);
    imgurUploaderGrid->addWidget(mImgurUsernameLabel, 5, 0);
	imgurUploaderGrid->addWidget(mImgurHistoryButton, 5, 3);
    imgurUploaderGrid->addWidget(mImgurClientIdLineEdit, 6, 0);
    imgurUploaderGrid->addWidget(mImgurClientSecretLineEdit, 7, 0);
    imgurUploaderGrid->addWidget(mImgurGetPinButton, 7, 3);
    imgurUploaderGrid->addWidget(mImgurPinLineEdit, 8, 0);
    imgurUploaderGrid->addWidget(mImgurGetTokenButton, 8, 3);

    auto imgurUploaderGrpBox = new QGroupBox(tr("Imgur Uploader"));
    imgurUploaderGrpBox->setLayout(imgurUploaderGrid);

    // Setup Painter Layout
    auto painterGrid = new QGridLayout;
    painterGrid->setAlignment(Qt::AlignTop);
    painterGrid->setColumnStretch(1, 1);
    painterGrid->addWidget(mItemShadowCheckbox, 0, 0, 1, 2);
    painterGrid->setRowMinimumHeight(1, 15);
    painterGrid->addWidget(mSmoothPathCheckbox, 2, 0, 1, 2);
    painterGrid->addWidget(mSmoothFactorLabel, 3, 0);
    painterGrid->addWidget(mSmoothFactorCombobox, 3, 1, Qt::AlignLeft);
    painterGrid->setRowMinimumHeight(4, 15);
    painterGrid->addWidget(mTextFontLabel, 5, 0);
    painterGrid->addWidget(mTextFontCombobox, 5, 1);
    painterGrid->addWidget(mTextBoldButton, 5, 2);
    painterGrid->addWidget(mTextItalicButton, 5, 3);
    painterGrid->addWidget(mTextUnderlineButton, 5, 4);
    painterGrid->addWidget(mNumberFontLabel, 6, 0);
    painterGrid->addWidget(mNumberFontCombobox, 6, 1);
    painterGrid->setRowMinimumHeight(7, 15);

	auto painterGroupBox = new QGroupBox(tr("Painter Settings"));
	painterGroupBox->setLayout(painterGrid);

    // Setup Push Button Layout
    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(mOkButton);
    buttonLayout->addWidget(mCancelButton);
    buttonLayout->setAlignment(Qt::AlignRight);

    // Populate Stacked layout and listview
    mStackedLayout->addWidget(mApplicationSettings);
    mStackedLayout->addWidget(mImageGrabberSettings);
    mStackedLayout->addWidget(imgurUploaderGrpBox);
	mStackedLayout->addWidget(painterGroupBox);

    mListWidget->addItem(tr("Application"));
    mListWidget->addItem(tr("Image Grabber"));
    mListWidget->addItem(tr("Imgur Uploader"));
    mListWidget->addItem(tr("Painter"));
    mListWidget->setCurrentRow(0);
    mListWidget->setFixedWidth(mListWidget->sizeHintForColumn(0) + 20);

    // Setup Main Window Layout
    auto listAndStackLayout = new QHBoxLayout;
    listAndStackLayout->addWidget(mListWidget);
    listAndStackLayout->addLayout(mStackedLayout);

    auto mainLayout = new QVBoxLayout();
    mainLayout->addLayout(listAndStackLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

/*
 * Based on the entered client id and client secret we create a pin request and open it up in the
 * default browser.
 */
void SettingsDialog::requestImgurPin()
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
void SettingsDialog::getImgurToken()
{
    mImgurUploader->getAccessToken(mImgurPinLineEdit->text().toUtf8(),
                                   mConfig->imgurClientId(),
                                   mConfig->imgurClientSecret());
    mImgurPinLineEdit->clear();
    qInfo("%s", qPrintable(tr("Waiting for imgur.com...")));
}

void SettingsDialog::smootPathCheckboxClicked(bool checked)
{
    mSmoothFactorLabel->setEnabled(checked);
    mSmoothFactorCombobox->setEnabled(checked);
}

void SettingsDialog::imgurClientEntered(const QString&)
{
    mImgurGetPinButton->setEnabled(!mImgurClientIdLineEdit->text().isEmpty() && !mImgurClientSecretLineEdit->text().isEmpty());
}

/*
 * We have received a new token from imgur.com, now we save it to config for
 * later use and inform the user about it.
 */
void SettingsDialog::imgurTokenUpdated(const QString& accessToken,
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
void SettingsDialog::imgurTokenError(const QString& message)
{
    qCritical("SettingsDialog returned error: '%s'", qPrintable(message));
    qInfo("%s", qPrintable(tr("Imgur.com token update error.")));
}

void SettingsDialog::showImgurHistoryDialog()
{
	ImgurHistoryDialog dialog;
	dialog.exec();
}
