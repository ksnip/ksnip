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
    mCaptureOnStartupCheckbox(new QCheckBox),
    mCaptureCursorCheckbox(new QCheckBox),
    mImgurForceAnonymousCheckbox(new QCheckBox),
    mImgurDirectLinkToImageCheckbox(new QCheckBox),
    mImgurAlwaysCopyToClipboardCheckBox(new QCheckBox),
    mSmoothPathCheckbox(new QCheckBox),
    mItemShadowCheckbox(new QCheckBox),
    mCursorRulerCheckbox(new QCheckBox),
    mCursorInfoCheckbox(new QCheckBox),
    mSaveLocationLineEdit(new QLineEdit),
    mImgurClientIdLineEdit(new QLineEdit),
    mImgurClientSecretLineEdit(new QLineEdit),
    mImgurPinLineEdit(new QLineEdit),
    mCaptureDelayLabel(new QLabel),
    mSaveLocationLabel(new QLabel),
    mImgurUsernameLabel(new QLabel),
    mTextFontLabel(new QLabel),
    mNumberFontLabel(new QLabel),
    mSmoothFactorLabel(new QLabel),
    mSnippingCursorSizeLabel(new QLabel),
    mSnippingCursorColorLabel(new QLabel),
    mCaptureDelayCombobox(new NumericComboBox(0, 1, 11)),
    mSmoothFactorCombobox(new NumericComboBox(1, 1, 15)),
    mSnippingCursorSizeCombobox(new NumericComboBox(1, 2, 3)),
    mTextFontCombobox(new QFontComboBox(this)),
    mNumberFontCombobox(new QFontComboBox(this)),
    mBrowseButton(new QPushButton),
    mImgurGetPinButton(new QPushButton),
    mImgurGetTokenButton(new QPushButton),
    mOkButton(new QPushButton),
    mCancelButton(new QPushButton),
    mTextBoldButton(new QPushButton),
    mTextItalicButton(new QPushButton),
    mTextUnderlineButton(new QPushButton),
    mSnippingCursorColorButton(new ColorButton),
    mImgurUploader(new ImgurUploader),
    mListWidget(new QListWidget),
    mStackedLayout(new QStackedLayout),
    mConfig(KsnipConfig::instance())
{
    setWindowTitle(QApplication::applicationName() + " - " + tr("Settings"));

    initGui();

    loadSettings();

    connect(mImgurUploader, &ImgurUploader::tokenUpdated,
            this, &SettingsDialog::imgurTokenUpdated);
    connect(mImgurUploader, &ImgurUploader::error,
            this, &SettingsDialog::imgurTokenError);
    connect(mListWidget, &QListWidget::itemSelectionChanged, [this]() {
        mStackedLayout->setCurrentIndex(mListWidget->currentRow());
    });
}

SettingsDialog::~SettingsDialog()
{
    delete mAlwaysCopyToClipboardCheckbox;
    delete mPromptToSaveBeforeExitCheckbox;
    delete mSaveKsnipPositionCheckbox;
    delete mSaveKsnipToolSelectionCheckbox;
    delete mCaptureOnStartupCheckbox;
    delete mCaptureCursorCheckbox;
    delete mImgurForceAnonymousCheckbox;
    delete mImgurDirectLinkToImageCheckbox;
    delete mImgurAlwaysCopyToClipboardCheckBox;
    delete mSmoothPathCheckbox;
    delete mItemShadowCheckbox;
    delete mCursorRulerCheckbox;
    delete mCursorInfoCheckbox;
    delete mSaveLocationLineEdit;
    delete mImgurClientIdLineEdit;
    delete mImgurClientSecretLineEdit;
    delete mImgurPinLineEdit;
    delete mCaptureDelayLabel;
    delete mSaveLocationLabel;
    delete mImgurUsernameLabel;
    delete mTextFontLabel;
    delete mNumberFontLabel;
    delete mSmoothFactorLabel;
    delete mSnippingCursorSizeLabel;
    delete mSnippingCursorColorLabel;
    delete mCaptureDelayCombobox;
    delete mSmoothFactorCombobox;
    delete mSnippingCursorSizeCombobox;
    delete mTextFontCombobox;
    delete mNumberFontCombobox;
    delete mBrowseButton;
    delete mImgurGetPinButton;
    delete mImgurGetTokenButton;
    delete mOkButton;
    delete mCancelButton;
    delete mTextBoldButton;
    delete mTextItalicButton;
    delete mTextUnderlineButton;
    delete mSnippingCursorColorButton;
    delete mImgurUploader;
    delete mListWidget;
    delete mStackedLayout;
}

void SettingsDialog::loadSettings()
{
    mAlwaysCopyToClipboardCheckbox->setChecked(mConfig->alwaysCopyToClipboard());
    mPromptToSaveBeforeExitCheckbox->setChecked(mConfig->promptSaveBeforeExit());
    mSaveKsnipPositionCheckbox->setChecked(mConfig->saveKsnipPosition());
    mSaveKsnipToolSelectionCheckbox->setChecked(mConfig->saveKsnipToolSelection());
    mCaptureOnStartupCheckbox->setChecked(mConfig->captureOnStartup());

    mImgurForceAnonymousCheckbox->setChecked(mConfig->imgurForceAnonymous());
    mImgurDirectLinkToImageCheckbox->setChecked(mConfig->imgurOpenLinkDirectlyToImage());
    mImgurAlwaysCopyToClipboardCheckBox->setChecked(mConfig->imgurAlwaysCopyToClipboard());

    mImgurUsernameLabel->setText(tr("Username") + ": " + mConfig->imgurUsername());
    if (!mConfig->imgurClientId().isEmpty()) {
        mImgurClientIdLineEdit->setPlaceholderText(mConfig->imgurClientId());
    }

    mCaptureCursorCheckbox->setChecked(mConfig->captureCursor());
    mCaptureDelayCombobox->setValue(mConfig->captureDelay() / 1000);
    mCursorRulerCheckbox->setChecked(mConfig->cursorRulerEnabled());
    mCursorInfoCheckbox->setChecked(mConfig->cursorInfoEnabled());
    mSnippingCursorColorButton->setColor(mConfig->snippingCursorColor());
    mSnippingCursorSizeCombobox->setValue(mConfig->snippingCursorSize());

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
    mConfig->setAlwaysCopyToClipboard(mAlwaysCopyToClipboardCheckbox->isChecked());
    mConfig->setPromptSaveBeforeExit(mPromptToSaveBeforeExitCheckbox->isChecked());
    mConfig->setSaveKsnipPosition(mSaveKsnipPositionCheckbox->isChecked());
    mConfig->setSaveKsnipToolSelection(mSaveKsnipToolSelectionCheckbox->isChecked());
    mConfig->setCaptureOnStartup(mCaptureOnStartupCheckbox->isChecked());

    mConfig->setImgurForceAnonymous(mImgurForceAnonymousCheckbox->isChecked());
    mConfig->setImgurOpenLinkDirectlyToImage(mImgurDirectLinkToImageCheckbox->isChecked());
    mConfig->setImgurAlwaysCopyToClipboard(mImgurAlwaysCopyToClipboardCheckBox->isChecked());

    mConfig->setCaptureCursor(mCaptureCursorCheckbox->isChecked());
    mConfig->setCaptureDelay(mCaptureDelayCombobox->value() * 1000);
    mConfig->setCursorRulerEnabled(mCursorRulerCheckbox->isChecked());
    mConfig->setCursorInfoEnabled(mCursorInfoCheckbox->isChecked());
    mConfig->setSnippingCursorColor(mSnippingCursorColorButton->color());
    mConfig->setSnippingCursorSize(mSnippingCursorSizeCombobox->value());

    mConfig->setSaveDirectory(StringFormattingHelper::extractPath(mSaveLocationLineEdit->displayText()));
    mConfig->setSaveFilename(StringFormattingHelper::extractFilename(mSaveLocationLineEdit->displayText()));
    mConfig->setSaveFormat(StringFormattingHelper::extractFormat(mSaveLocationLineEdit->displayText()));

    mConfig->setTextFont(mTextFontCombobox->currentFont());
    mConfig->setTextBold(mTextBoldButton->isChecked());
    mConfig->setTextItalic(mTextItalicButton->isChecked());
    mConfig->setTextUnderline(mTextUnderlineButton->isChecked());

    mConfig->setNumberFont(mNumberFontCombobox->currentFont());

    mConfig->setItemShadowEnabled(mItemShadowCheckbox->isChecked());

    mConfig->setSmoothPathEnabled(mSmoothPathCheckbox->isChecked());
    mConfig->setSmoothFactor(mSmoothFactorCombobox->value());
}

void SettingsDialog::initGui()
{
    auto const fixedButtonSize = 100;

    // Create Application Settings
    mAlwaysCopyToClipboardCheckbox->setText(tr("Always copy capture to clipboard"));
    mPromptToSaveBeforeExitCheckbox->setText(tr("Prompt to save before exiting ksnip"));
    mSaveKsnipPositionCheckbox->setText(tr("Save ksnip position on move and load on startup"));
    mSaveKsnipToolSelectionCheckbox->setText(tr("Save ksnip tool selection and load on startup"));
    mCaptureOnStartupCheckbox->setText(tr("Capture screenshot at startup with default mode"));

    mSaveLocationLabel->setText(tr("Capture save location and filename") + ":");

    mSaveLocationLineEdit->setText(mConfig->saveDirectory() +
                                   mConfig->saveFilename() +
                                   mConfig->saveFormat());
    mSaveLocationLineEdit->setToolTip(tr("Filename can contain $Y, $M, $D for date and $T for time."));

    mBrowseButton->setText(tr("Browse"));
    connect(mBrowseButton, &QPushButton::clicked, [this]() {
        mSaveLocationLineEdit->setText(QFileDialog::getOpenFileName(this,
                                       tr("Capture save location"),
                                       mConfig->saveDirectory() +
                                       mConfig->saveFilename() +
                                       mConfig->saveFormat(),
                                       tr("All")));
    });

    // Create Image Grabber Settings
    mCaptureCursorCheckbox->setText(tr("Capture mouse cursor on screenshot"));
    mCaptureCursorCheckbox->setToolTip(tr("Should mouse cursor be visible on\n"
                                          "screenshots."));
    mCaptureDelayLabel->setText(tr("Delay (sec)") + ":");
    mCaptureDelayLabel->setToolTip(tr("Sets the delay between triggering a capture\n"
                                      "and the moment when the capture is taken, in\n"
                                      "seconds."));
    mCaptureDelayCombobox->setToolTip(mCaptureDelayLabel->toolTip());
    mCaptureDelayCombobox->setMinimumWidth(fixedButtonSize);
    mCursorRulerCheckbox->setText(tr("Show snipping cursor ruler"));
    mCursorRulerCheckbox->setToolTip(tr("Horizontal and vertical lines going from\n"
                                        "desktop corner to cursor on snipping area."));
    mCursorInfoCheckbox->setText(tr("Show cursor position info"));
    mCursorInfoCheckbox->setToolTip(tr("When left mouse is not pressed the position\n"
                                       "is show, when the mouse button is pressed,\n"
                                       "the size of the select area is shown left\n"
                                       "and right from the captured area."));
    mSnippingCursorColorLabel->setText(tr("Cursor Color") + ":");
    mSnippingCursorColorLabel->setToolTip(tr("Sets the color of the snipping area\n"
                                             "cursor. Change requires ksnip restart to\n"
                                             "take effect."));
    mSnippingCursorColorButton->setMinimumWidth(fixedButtonSize);
    mSnippingCursorColorButton->setToolTip(mSnippingCursorColorLabel->toolTip());
    mSnippingCursorSizeLabel->setText(tr("Cursor Thickness") + ":");
    mSnippingCursorSizeLabel->setToolTip(tr("Sets the thickness of the snipping area\n"
                                            "cursor. Change requires ksnip restart to\n"
                                            "take effect."));
    mSnippingCursorSizeCombobox->setMinimumWidth(fixedButtonSize);
    mSnippingCursorSizeCombobox->setToolTip(mSnippingCursorSizeLabel->toolTip());

    // Create Imgur Uploader Settings
    mImgurForceAnonymousCheckbox->setText(tr("Force anonymous upload"));
    mImgurDirectLinkToImageCheckbox->setText(tr("Open link directly to image"));
    mImgurAlwaysCopyToClipboardCheckBox->setText(tr("Always copy Imgur link to clipboard"));

    mImgurClientIdLineEdit->setPlaceholderText(tr("Client ID"));
    connect(mImgurClientIdLineEdit, &QLineEdit::textChanged,
            this, &SettingsDialog::imgurClientEntered);

    mImgurClientSecretLineEdit->setPlaceholderText(tr("Client Secret"));
    connect(mImgurClientSecretLineEdit, &QLineEdit::textChanged,
            this, &SettingsDialog::imgurClientEntered);

    mImgurPinLineEdit->setPlaceholderText(tr("PIN"));
    mImgurPinLineEdit->setToolTip(tr("Enter imgur Pin which will be exchanged for a token."));
    connect(mImgurPinLineEdit, &QLineEdit::textChanged, [this](const QString & text) {
        if (text.length() > 8) {
            mImgurGetTokenButton->setEnabled(true);
        } else {
            mImgurGetTokenButton->setEnabled(false);
        }
    });

    mImgurGetPinButton->setText(tr("Get PIN"));
    connect(mImgurGetPinButton, &QPushButton::clicked,
            this, &SettingsDialog::getPinButtonClicked);
    mImgurGetPinButton->setEnabled(false);

    mImgurGetTokenButton->setText(tr("Get Token"));
    connect(mImgurGetTokenButton, &QPushButton::clicked,
            this, &SettingsDialog::getTokenButtonClicked);
    mImgurGetTokenButton->setEnabled(false);

    // Create Painter Settings
    mItemShadowCheckbox->setText(tr("Paint Item Shadows"));
    mItemShadowCheckbox->setToolTip(tr("When enabled, paint items cast shadows."));

    mSmoothPathCheckbox->setText(tr("Smooth Painter Paths"));
    mSmoothPathCheckbox->setToolTip(tr("When enabled smooths out pen and\n"
                                       "marker paths after finished drawing."));
    connect(mSmoothPathCheckbox, &QCheckBox::clicked,
            this, &SettingsDialog::smootPathCheckboxClicked);

    mSmoothFactorLabel->setText(tr("Smooth Factor") + ":");
    mSmoothFactorLabel->setToolTip(tr("Increasing the smooth factor will decrease\n"
                                      "precision for pen and marker but will\n"
                                      "make them more smooth."));
    mSmoothFactorCombobox->setMinimumWidth(fixedButtonSize);
    mSmoothFactorCombobox->setToolTip(mSmoothFactorLabel->toolTip());

    mTextFontLabel->setText(tr("Text Font") + ":");
    mTextFontLabel->setToolTip(tr("Sets the font for the Text Paint Item."));
    mTextFontCombobox->setToolTip(mTextFontLabel->toolTip());
    mTextFontCombobox->setEditable(false);

    // Setting the button to same square size as the height of the combobox
    auto size = mTextFontCombobox->minimumSizeHint().height();

    mTextBoldButton->setText(tr("B"));
    mTextBoldButton->setToolTip(tr("Bold"));
    mTextBoldButton->setCheckable(true);
    mTextBoldButton->setFixedSize(size, size);
    mTextBoldButton->setStyleSheet("QPushButton { font-size: 18pt; font-weight: bold; }");

    mTextItalicButton->setText(tr("I"));
    mTextItalicButton->setToolTip(tr("Italic"));
    mTextItalicButton->setCheckable(true);
    mTextItalicButton->setFixedSize(size, size);
    mTextItalicButton->setStyleSheet("QPushButton { font-size: 18pt; font-style: italic; }");

    mTextUnderlineButton->setText(tr("U"));
    mTextUnderlineButton->setToolTip(tr("Underline"));
    mTextUnderlineButton->setCheckable(true);
    mTextUnderlineButton->setFixedSize(size, size);
    mTextUnderlineButton->setStyleSheet("QPushButton { font-size: 18pt; text-decoration: underline; }");

    mNumberFontLabel->setText(tr("Numbering Font") + ":");
    mNumberFontLabel->setToolTip(tr("Sets the font for the Numbering Paint Item."));
    mNumberFontCombobox->setToolTip(mNumberFontLabel->toolTip());
    mNumberFontCombobox->setEditable(false);

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

    // Setup Application Settings Layout
    auto applicationGrid = new QGridLayout;
    applicationGrid->setAlignment(Qt::AlignTop);
    applicationGrid->setColumnStretch(0, 1);
    applicationGrid->addWidget(mAlwaysCopyToClipboardCheckbox, 0, 0);
    applicationGrid->addWidget(mPromptToSaveBeforeExitCheckbox, 1, 0);
    applicationGrid->addWidget(mSaveKsnipPositionCheckbox, 2, 0);
    applicationGrid->addWidget(mSaveKsnipToolSelectionCheckbox, 3, 0);
    applicationGrid->addWidget(mCaptureOnStartupCheckbox, 4, 0);
    applicationGrid->setRowMinimumHeight(5, 15);
    applicationGrid->addWidget(mSaveLocationLabel, 6, 0);
    applicationGrid->addWidget(mSaveLocationLineEdit, 7, 0);
    applicationGrid->addWidget(mBrowseButton, 7, 3);

    auto applicationGrpBox = new QGroupBox(tr("Application Settings"));
    applicationGrpBox->setLayout(applicationGrid);

    // Setup Image Grabber Layout
    auto imageGrabberGrid = new QGridLayout;
    imageGrabberGrid->setAlignment(Qt::AlignTop);
    imageGrabberGrid->setColumnStretch(1, 1);
    imageGrabberGrid->addWidget(mCaptureCursorCheckbox, 0, 0, 1, 2);
    imageGrabberGrid->addWidget(mCursorRulerCheckbox, 1, 0, 1, 2);
    imageGrabberGrid->addWidget(mCursorInfoCheckbox, 2, 0, 1, 2);
    imageGrabberGrid->setRowMinimumHeight(3, 15);
    imageGrabberGrid->addWidget(mCaptureDelayLabel, 4, 0);
    imageGrabberGrid->addWidget(mCaptureDelayCombobox, 4, 1, Qt::AlignLeft);
    imageGrabberGrid->setRowMinimumHeight(5, 15);
    imageGrabberGrid->addWidget(mSnippingCursorColorLabel, 6, 0);
    imageGrabberGrid->addWidget(mSnippingCursorColorButton, 6, 1, Qt::AlignLeft);
    imageGrabberGrid->addWidget(mSnippingCursorSizeLabel, 7, 0);
    imageGrabberGrid->addWidget(mSnippingCursorSizeCombobox, 7, 1, Qt::AlignLeft);

    auto imageGrabberGrpBox = new QGroupBox(tr("Image Grabber"));
    imageGrabberGrpBox->setLayout(imageGrabberGrid);

    // Setup Imgur Uploader Layout
    auto imgurUploaderGrid = new QGridLayout;
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

    auto painterGrpBox = new QGroupBox(tr("Painter Settings"));
    painterGrpBox->setLayout(painterGrid);

    // Setup Push Button Layout
    auto buttonLayout = new QHBoxLayout;
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

void SettingsDialog::smootPathCheckboxClicked(bool checked)
{
    mSmoothFactorLabel->setEnabled(checked);
    mSmoothFactorCombobox->setEnabled(checked);
}

void SettingsDialog::imgurClientEntered(const QString&)
{
    if (!mImgurClientIdLineEdit->text().isEmpty() && !mImgurClientSecretLineEdit->text().isEmpty()) {
        mImgurGetPinButton->setEnabled(true);
    } else {
        mImgurGetPinButton->setEnabled(false);
    }
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

    mImgurUsernameLabel->setText(tr("Username") + ": " + username);
    mParent->statusBar()->showMessage(tr("Imgur.com token successfully updated."), 3000);
}

/*
 * Something went wrong while requesting a new token, we write the message to
 * shell and inform the user via statusbar.
 */
void SettingsDialog::imgurTokenError(const QString& message)
{
    qCritical("SettingsDialog returned error: '%s'", qPrintable(message));
    mParent->statusBar()->showMessage(tr("Imgur.com token update error."), 3000);
}
