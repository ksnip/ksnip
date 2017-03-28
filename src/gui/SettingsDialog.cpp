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

SettingsDialog::SettingsDialog(MainWindow* parent) :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    mParent(parent),
    mAlwaysCopyToClipboardCheckbox(new QCheckBox),
    mPromptToSaveBeforeExitCheckbox(new QCheckBox),
    mSaveKsnipPositionCheckbox(new QCheckBox),
    mSaveKsnipToolSelectionCheckbox(new QCheckBox),
    mCaptureMouseCheckbox(new QCheckBox),
    mImgurForceAnonymousCheckbox(new QCheckBox),
    mImgurDirectLinkToImageCheckbox(new QCheckBox),
    mImgurAlwaysCopyToClipboardCheckBox(new QCheckBox),
    mSmoothPathCheckbox(new QCheckBox),
    mSaveLocationLineEdit(new QLineEdit),
    mImgurClientIdLineEdit(new QLineEdit),
    mImgurClientSecretLineEdit(new QLineEdit),
    mImgurPinLineEdit(new QLineEdit),
    mCaptureDelayLabel(new QLabel),
    mSaveLocationLabel(new QLabel),
    mImgurUsernameLabel(new QLabel),
    mTextFontLabel(new QLabel),
    mSmoothFactorLabel(new QLabel),
    mCaptureDelayCombobox(new NumericComboBox(0, 1, 11)),
    mSmoothFactorCombobox(new NumericComboBox(1, 1, 15)),
    mTextFontCombobox(new QFontComboBox(this)),
    mBrowseButton(new QPushButton),
    mImgurGetPinButton(new QPushButton),
    mImgurGetTokenButton(new QPushButton),
    mOkButton(new QPushButton),
    mCancelButton(new QPushButton),
    mTextBoldButton(new QPushButton),
    mTextItalicButton(new QPushButton),
    mTextUnderlineButton(new QPushButton),
    mImgurUploader(new ImgurUploader),
    mListWidget(new QListWidget),
    mStackedLayout(new QStackedLayout)
{
    mConfig = KsnipConfig::instance();
    setWindowTitle(QApplication::applicationName() + " - " + tr("Settings"));

    initGui();

    loadSettings();

    connect(mImgurUploader, SIGNAL(tokenUpdated(QString, QString, QString)),
            this, SLOT(imgurTokenUpdated(QString, QString, QString)));
    connect(mImgurUploader, SIGNAL(error(QString)), this, SLOT(imgurTokenError(QString)));
    connect(mListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(listSelectionChanged()));
}

//
// Private Functions
//
void SettingsDialog::loadSettings()
{
    mAlwaysCopyToClipboardCheckbox->setChecked(mConfig->alwaysCopyToClipboard());
    mPromptToSaveBeforeExitCheckbox->setChecked(mConfig->promptSaveBeforeExit());
    mSaveKsnipPositionCheckbox->setChecked(mConfig->saveKsnipPosition());
    mSaveKsnipToolSelectionCheckbox->setChecked(mConfig->saveKsnipToolSelection());

    mCaptureMouseCheckbox->setChecked(mConfig->captureMouse());

    mImgurForceAnonymousCheckbox->setChecked(mConfig->imgurForceAnonymous());
    mImgurDirectLinkToImageCheckbox->setChecked(mConfig->imgurOpenLinkDirectlyToImage());
    mImgurAlwaysCopyToClipboardCheckBox->setChecked(mConfig->imgurAlwaysCopyToClipboard());

    mImgurUsernameLabel->setText(tr("Username") + ": " + mConfig->imgurUsername());
    if (!mConfig->imgurClientId().isEmpty()) {
        mImgurClientIdLineEdit->setPlaceholderText(mConfig->imgurClientId());
    }
    mCaptureDelayCombobox->setValue(mConfig->captureDelay() / 1000);

    mTextFontCombobox->setCurrentFont(mConfig->textFont());
    mTextBoldButton->setChecked(mConfig->textBold());
    mTextItalicButton->setChecked(mConfig->textItalic());
    mTextUnderlineButton->setChecked(mConfig->textUnderline());

    mSmoothPathCheckbox->setChecked(mConfig->smoothPath());
    mSmoothFactorCombobox->setValue(mConfig->smoothFactor());
    smootPathCheckboxClicked(mConfig->smoothPath());
}

void SettingsDialog::saveSettings()
{
    mConfig->setAlwaysCopyToClipboard(mAlwaysCopyToClipboardCheckbox->isChecked());
    mConfig->setPromptSaveBeforeExit(mPromptToSaveBeforeExitCheckbox->isChecked());
    mConfig->setSaveKsnipPosition(mSaveKsnipPositionCheckbox->isChecked());
    mConfig->setSaveKsnipToolSelection(mSaveKsnipToolSelectionCheckbox->isChecked());

    mConfig->setCaptureMouse(mCaptureMouseCheckbox->isChecked());

    mConfig->setImgurForceAnonymous(mImgurForceAnonymousCheckbox->isChecked());
    mConfig->setImgurOpenLinkDirectlyToImage(mImgurDirectLinkToImageCheckbox->isChecked());
    mConfig->setImgurAlwaysCopyToClipboard(mImgurAlwaysCopyToClipboardCheckBox->isChecked());

    mConfig->setCaptureDelay(mCaptureDelayCombobox->value() * 1000);
    mConfig->setSaveDirectory(StringManip::extractPath(mSaveLocationLineEdit->displayText()));
    mConfig->setSaveFilename(StringManip::extractFilename(mSaveLocationLineEdit->displayText()));
    mConfig->setSaveFormat(StringManip::extractFormat(mSaveLocationLineEdit->displayText()));

    mConfig->setTextFont(mTextFontCombobox->currentFont());
    mConfig->setTextBold(mTextBoldButton->isChecked());
    mConfig->setTextItalic(mTextItalicButton->isChecked());
    mConfig->setTextUnderline(mTextUnderlineButton->isChecked());

    mConfig->setSmoothPath(mSmoothPathCheckbox->isChecked());
    mConfig->setSmoothFactor(mSmoothFactorCombobox->value());
}

void SettingsDialog::initGui()
{
    // Create Application Settings
    mAlwaysCopyToClipboardCheckbox->setText(tr("Always copy capture to clipboard."));
    mPromptToSaveBeforeExitCheckbox->setText(tr("Prompt to save before exiting ksnip."));
    mSaveKsnipPositionCheckbox->setText(tr("Save ksnip position on move and load on startup."));
    mSaveKsnipToolSelectionCheckbox->setText(tr("Save ksnip tool selection and "
            "load on startup."));

    mSaveLocationLabel->setText(tr("Capture save location and filename") + ":");

    mSaveLocationLineEdit->setText(mConfig->saveDirectory() +
                                   mConfig->saveFilename() +
                                   mConfig->saveFormat());
    mSaveLocationLineEdit->setToolTip(tr("Filename can contain $Y, $M, $D for date and $T for time."));

    mBrowseButton->setText(tr("Browse"));
    connect(mBrowseButton, SIGNAL(clicked()), this, SLOT(browseButtonClicked()));

    // Create Image Grabber Settings
    mCaptureMouseCheckbox->setText(tr("Capture mouse cursor on screenshot."));
    mCaptureDelayLabel->setText(tr("Delay (sec)") + ":");

    // Create Imgur Uploader Settings
    mImgurForceAnonymousCheckbox->setText(tr("Force anonymous upload."));
    mImgurDirectLinkToImageCheckbox->setText(tr("Open link directly to image."));
    mImgurAlwaysCopyToClipboardCheckBox->setText(tr("Always copy Imgur link to clipboard."));

    mImgurClientIdLineEdit->setPlaceholderText(tr("Client ID"));
    connect(mImgurClientIdLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(imgurClientEntered(QString)));

    mImgurClientSecretLineEdit->setPlaceholderText(tr("Client Secret"));
    connect(mImgurClientSecretLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(imgurClientEntered(QString)));

    mImgurPinLineEdit->setPlaceholderText(tr("PIN"));
    mImgurPinLineEdit->setToolTip(tr("Enter imgur Pin which will be exchanged for a token."));
    connect(mImgurPinLineEdit, SIGNAL(textChanged(QString)), SLOT(imgurPinEntered(QString)));

    mImgurGetPinButton->setText(tr("Get PIN"));
    connect(mImgurGetPinButton, SIGNAL(clicked()), SLOT(getPinButtonClicked()));
    mImgurGetPinButton->setEnabled(false);

    mImgurGetTokenButton->setText(tr("Get Token"));
    connect(mImgurGetTokenButton, SIGNAL(clicked()), SLOT(getTokenButtonClicked()));
    mImgurGetTokenButton->setEnabled(false);

    // Create Painter Settings
    mSmoothPathCheckbox->setText(tr("Smooth Paths"));
    mSmoothPathCheckbox->setToolTip(tr("When enabled smooths out pen and \n"
                                       "marker paths after finished drawing."));
    connect(mSmoothPathCheckbox, SIGNAL(clicked(bool)), SLOT(smootPathCheckboxClicked(bool)));

    mSmoothFactorLabel->setText(tr("Smooth Factor") + ":");
    mSmoothFactorLabel->setToolTip(tr("Increasing the smooth factor will decrease\n"
                                      "precisions for pen and marker but will \n"
                                      "make them more smooth."));
    mSmoothFactorCombobox->setToolTip(mSmoothFactorLabel->toolTip());

    mTextFontLabel->setText(tr("Text Font") + ":");
    mTextFontCombobox->setEditable(false);

    // Setting the button to same square size as the height of the combobox
    int wh = mTextFontCombobox->minimumSizeHint().height();

    mTextBoldButton->setText(tr("B"));
    mTextBoldButton->setToolTip(tr("Bold"));
    mTextBoldButton->setCheckable(true);
    mTextBoldButton->setFixedSize(wh, wh);
    mTextBoldButton->setStyleSheet("QPushButton { font-size: 18pt; font-weight: bold; }");

    mTextItalicButton->setText(tr("I"));
    mTextItalicButton->setToolTip(tr("Italic"));
    mTextItalicButton->setCheckable(true);
    mTextItalicButton->setFixedSize(wh, wh);
    mTextItalicButton->setStyleSheet("QPushButton { font-size: 18pt; font-style: italic; }");

    mTextUnderlineButton->setText(tr("U"));
    mTextUnderlineButton->setToolTip(tr("Underline"));
    mTextUnderlineButton->setCheckable(true);
    mTextUnderlineButton->setFixedSize(wh, wh);
    mTextUnderlineButton->setStyleSheet("QPushButton { font-size: 18pt; text-decoration: underline; }");

    // Create Push Buttons
    mOkButton->setText(tr("OK"));
    connect(mOkButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));

    mCancelButton->setText(tr("Cancel"));
    connect(mCancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));

    // Setup Application Settings Layout
    QGridLayout* applicationGrid = new QGridLayout;
    applicationGrid->setAlignment(Qt::AlignTop);
    applicationGrid->setColumnStretch(0, 1);
    applicationGrid->addWidget(mAlwaysCopyToClipboardCheckbox, 0, 0);
    applicationGrid->addWidget(mPromptToSaveBeforeExitCheckbox, 1, 0);
    applicationGrid->addWidget(mSaveKsnipPositionCheckbox, 2, 0);
    applicationGrid->addWidget(mSaveKsnipToolSelectionCheckbox, 3, 0);
    applicationGrid->setRowMinimumHeight(4, 15);
    applicationGrid->addWidget(mSaveLocationLabel, 5, 0);
    applicationGrid->addWidget(mSaveLocationLineEdit, 6, 0);
    applicationGrid->addWidget(mBrowseButton, 6, 3);

    QGroupBox* applicationGrpBox = new QGroupBox(tr("Application Settings"));
    applicationGrpBox->setLayout(applicationGrid);

    // Setup Image Grabber Layout
    QGridLayout* imageGrabberGrid = new QGridLayout;
    imageGrabberGrid->setAlignment(Qt::AlignTop);
    imageGrabberGrid->setColumnStretch(1, 1);
    imageGrabberGrid->addWidget(mCaptureMouseCheckbox, 0, 0, 1, 2);
    imageGrabberGrid->setRowMinimumHeight(1, 15);
    imageGrabberGrid->addWidget(mCaptureDelayLabel, 2, 0);
    imageGrabberGrid->addWidget(mCaptureDelayCombobox, 2, 1);

    QGroupBox* imageGrabberGrpBox = new QGroupBox(tr("Image Grabber"));
    imageGrabberGrpBox->setLayout(imageGrabberGrid);

    // Setup Imgur Uploader Layout
    QGridLayout* imgurUploaderGrid = new QGridLayout;
    imgurUploaderGrid->setAlignment(Qt::AlignTop);
    imgurUploaderGrid->setColumnStretch(0, 1);
    imgurUploaderGrid->addWidget(mImgurForceAnonymousCheckbox, 0, 0);
    imgurUploaderGrid->addWidget(mImgurDirectLinkToImageCheckbox, 1, 0);
    imgurUploaderGrid->addWidget(mImgurAlwaysCopyToClipboardCheckBox, 2, 0);
    imgurUploaderGrid->setRowMinimumHeight(3, 15);
    imgurUploaderGrid->addWidget(mImgurUsernameLabel, 4, 0);
    imgurUploaderGrid->addWidget(mImgurClientIdLineEdit, 5, 0);
    imgurUploaderGrid->addWidget(mImgurClientSecretLineEdit, 6, 0);
    imgurUploaderGrid->addWidget(mImgurGetPinButton, 6, 3);
    imgurUploaderGrid->addWidget(mImgurPinLineEdit, 7, 0);
    imgurUploaderGrid->addWidget(mImgurGetTokenButton, 7, 3);

    QGroupBox* imgurUploaderGrpBox = new QGroupBox(tr("Imgur Uploader"));
    imgurUploaderGrpBox->setLayout(imgurUploaderGrid);

    // Setup Painter Layout
    QGridLayout* painterGrid = new QGridLayout;
    painterGrid->setAlignment(Qt::AlignTop);
    painterGrid->setColumnStretch(1, 1);
    painterGrid->addWidget(mSmoothPathCheckbox, 0, 0);
    painterGrid->addWidget(mSmoothFactorLabel, 1, 0);
    painterGrid->addWidget(mSmoothFactorCombobox, 1, 1);
    painterGrid->setRowMinimumHeight(2, 15);
    painterGrid->addWidget(mTextFontLabel, 3, 0);
    painterGrid->addWidget(mTextFontCombobox, 3, 1);
    painterGrid->addWidget(mTextBoldButton, 3, 2);
    painterGrid->addWidget(mTextItalicButton, 3, 3);
    painterGrid->addWidget(mTextUnderlineButton, 3, 4);

    QGroupBox* painterGrpBox = new QGroupBox(tr("Painter Settings"));
    painterGrpBox->setLayout(painterGrid);

    // Setup Push Button Layout
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(mOkButton);
    buttonLayout->addWidget(mCancelButton);
    buttonLayout->setAlignment(Qt::AlignRight);

    // Populate Stacked layout and listview
    mStackedLayout->addWidget(applicationGrpBox);
    mStackedLayout->addWidget(imageGrabberGrpBox);
    mStackedLayout->addWidget(imgurUploaderGrpBox);
    mStackedLayout->addWidget(painterGrpBox);

    mListWidget->addItem(tr("Application"));
    mListWidget->addItem(tr("Image Grabber"));
    mListWidget->addItem(tr("Imgur Uploader"));
    mListWidget->addItem(tr("Painter"));
    mListWidget->setFixedWidth(mListWidget->sizeHintForColumn(0) + 20);

    // Setup Main Window Layout
    QHBoxLayout* listAndStackLayout = new QHBoxLayout;
    listAndStackLayout->addWidget(mListWidget);
    listAndStackLayout->addLayout(mStackedLayout);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(listAndStackLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

//
// Public Slots
//
void SettingsDialog::browseButtonClicked()
{
    mSaveLocationLineEdit->setText(QFileDialog::getOpenFileName(this,
                                   tr("Capture save location"),
                                   mConfig->saveDirectory() +
                                   mConfig->saveFilename() +
                                   mConfig->saveFormat(),
                                   tr("All")));
}

/*
 * Based on the entered client id and client secret we create a pin request and open it up in the
 * default browser.
 */
void SettingsDialog::getPinButtonClicked()
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
void SettingsDialog::getTokenButtonClicked()
{
    mImgurUploader->getAccessToken(mImgurPinLineEdit->text().toUtf8(),
                                   mConfig->imgurClientId(),
                                   mConfig->imgurClientSecret());
    mImgurPinLineEdit->clear();
    mParent->statusBar()->showMessage(tr("Waiting for imgur.com..."));
}

void SettingsDialog::okButtonClicked()
{
    saveSettings();
    close();
}

/*
 * Called when the list view selection has changed, it will change the selected stacked layout
 * providing the effect of switching between the different settings option
 */
void SettingsDialog::listSelectionChanged()
{
    mStackedLayout->setCurrentIndex(mListWidget->currentRow());
}

void SettingsDialog::cancelButtonClicked()
{
    close();
}

void SettingsDialog::smootPathCheckboxClicked(bool checked)
{
    mSmoothFactorLabel->setEnabled(checked);
    mSmoothFactorCombobox->setEnabled(checked);
}

void SettingsDialog::imgurPinEntered(const QString &text)
{
    if (text.length() > 8) {
        mImgurGetTokenButton->setEnabled(true);
    } else {
        mImgurGetTokenButton->setEnabled(false);
    }
}

void SettingsDialog::imgurClientEntered(const QString &text)
{
    if (!mImgurClientIdLineEdit->text().isEmpty() && !mImgurClientSecretLineEdit->text().isEmpty()) {
        mImgurGetPinButton->setEnabled(true);
    } else {
        mImgurGetPinButton->setEnabled(false);
    }
}

/*
 * We have received a new token from imgur.com, now we save it to config for later use and inform
 * the user about it.
 */
void SettingsDialog::imgurTokenUpdated(const QString &accessToken, const QString &refreshTocken,
                                       const QString &username)
{
    mConfig->setImgurAccessToken(accessToken.toUtf8());
    mConfig->setImgurRefreshToken(refreshTocken.toUtf8());
    mConfig->setImgurUsername(username);

    mImgurUsernameLabel->setText(tr("Username") + ": " + username);
    mParent->statusBar()->showMessage(tr("Imgur.com token successfully updated."), 3000);
}

/*
 * Something went wrong while requesting a new token, we write the message to shell and inform the
 * user via statusbar.
 */
void SettingsDialog::imgurTokenError(const QString &message)
{
    qCritical("SettingsDialog returned error: '%s'", qPrintable(message));
    mParent->statusBar()->showMessage(tr("Imgur.com token update error."), 3000);
}
