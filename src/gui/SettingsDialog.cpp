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

SettingsDialog::SettingsDialog(QWidget *parent)
    :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    mAlwaysCopyToClipboardCheckbox(new QCheckBox),
    mPromptToSaveBeforeExitCheckbox(new QCheckBox),
    mSaveKsnipPositionCheckbox(new QCheckBox),
    mSaveKsnipToolSelectionCheckbox(new QCheckBox),
    mCaptureOnStartupCheckbox(new QCheckBox),
    mCaptureCursorCheckbox(new QCheckBox),
    mUseInstantSaveCheckBox(new QCheckBox),
    mImgurForceAnonymousCheckbox(new QCheckBox),
    mImgurDirectLinkToImageCheckbox(new QCheckBox),
    mImgurAlwaysCopyToClipboardCheckBox(new QCheckBox),
    mImgurConfirmBeforeUploadCheckbox(new QCheckBox),
    mSmoothPathCheckbox(new QCheckBox),
    mItemShadowCheckbox(new QCheckBox),
    mCursorRulerCheckbox(new QCheckBox),
    mCursorInfoCheckbox(new QCheckBox),
    mSaveLocationLineEdit(new QLineEdit),
    mImgurClientIdLineEdit(new QLineEdit),
    mImgurClientSecretLineEdit(new QLineEdit),
    mImgurPinLineEdit(new QLineEdit),
    mSaveLocationLabel(new QLabel),
    mImgurUsernameLabel(new QLabel),
    mTextFontLabel(new QLabel),
    mNumberFontLabel(new QLabel),
    mSmoothFactorLabel(new QLabel),
    mSnippingCursorSizeLabel(new QLabel),
    mSnippingCursorColorLabel(new QLabel),
    mApplicationStyleLabel(new QLabel),
    mSmoothFactorCombobox(new NumericComboBox(1, 1, 15)),
    mSnippingCursorSizeCombobox(new NumericComboBox(1, 2, 3)),
    mTextFontCombobox(new QFontComboBox(this)),
    mNumberFontCombobox(new QFontComboBox(this)),
    mApplicationStyleCombobox(new QComboBox(this)),
    mBrowseButton(new QPushButton),
    mImgurGetPinButton(new QPushButton),
    mImgurGetTokenButton(new QPushButton),
    mOkButton(new QPushButton),
    mCancelButton(new QPushButton),
    mTextBoldButton(new QToolButton),
    mTextItalicButton(new QToolButton),
    mTextUnderlineButton(new QToolButton),
    mSnippingCursorColorButton(new ColorButton),
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
    delete mAlwaysCopyToClipboardCheckbox;
    delete mPromptToSaveBeforeExitCheckbox;
    delete mSaveKsnipPositionCheckbox;
    delete mSaveKsnipToolSelectionCheckbox;
    delete mCaptureOnStartupCheckbox;
    delete mCaptureCursorCheckbox;
    delete mUseInstantSaveCheckBox;
    delete mImgurForceAnonymousCheckbox;
    delete mImgurDirectLinkToImageCheckbox;
    delete mImgurAlwaysCopyToClipboardCheckBox;
    delete mImgurConfirmBeforeUploadCheckbox;
    delete mSmoothPathCheckbox;
    delete mItemShadowCheckbox;
    delete mCursorRulerCheckbox;
    delete mCursorInfoCheckbox;
    delete mSaveLocationLineEdit;
    delete mImgurClientIdLineEdit;
    delete mImgurClientSecretLineEdit;
    delete mImgurPinLineEdit;
    delete mSaveLocationLabel;
    delete mImgurUsernameLabel;
    delete mTextFontLabel;
    delete mNumberFontLabel;
    delete mSmoothFactorLabel;
    delete mSnippingCursorSizeLabel;
    delete mSnippingCursorColorLabel;
    delete mApplicationStyleLabel;
    delete mSmoothFactorCombobox;
    delete mSnippingCursorSizeCombobox;
    delete mTextFontCombobox;
    delete mNumberFontCombobox;
    delete mApplicationStyleCombobox;
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
    mUseInstantSaveCheckBox->setChecked(mConfig->useInstantSave());

    mImgurForceAnonymousCheckbox->setChecked(mConfig->imgurForceAnonymous());
    mImgurDirectLinkToImageCheckbox->setChecked(mConfig->imgurOpenLinkDirectlyToImage());
    mImgurAlwaysCopyToClipboardCheckBox->setChecked(mConfig->imgurAlwaysCopyToClipboard());
    mImgurConfirmBeforeUploadCheckbox->setChecked(mConfig->imgurConfirmBeforeUpload());

    mImgurUsernameLabel->setText(tr("Username") + ": " + mConfig->imgurUsername());
    if(!mConfig->imgurClientId().isEmpty()) {
        mImgurClientIdLineEdit->setPlaceholderText(mConfig->imgurClientId());
    }

    mCaptureCursorCheckbox->setChecked(mConfig->captureCursor());
    mCursorRulerCheckbox->setChecked(mConfig->cursorRulerEnabled());
    mCursorInfoCheckbox->setChecked(mConfig->cursorInfoEnabled());
    mSnippingCursorColorButton->setColor(mConfig->snippingCursorColor());
    mSnippingCursorSizeCombobox->setValue(mConfig->snippingCursorSize());

    mTextFontCombobox->setCurrentFont(mConfig->textFont());
    mTextBoldButton->setChecked(mConfig->textBold());
    mTextItalicButton->setChecked(mConfig->textItalic());
    mTextUnderlineButton->setChecked(mConfig->textUnderline());
    mNumberFontCombobox->setCurrentFont(mConfig->numberFont());
    mApplicationStyleCombobox->addItems(QStyleFactory::keys());
    mApplicationStyleCombobox->setCurrentText(mConfig->applicationStyle());
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
    mConfig->setUseInstantSave(mUseInstantSaveCheckBox->isChecked());
    mConfig->setApplicationStyle(mApplicationStyleCombobox->currentText());

    mConfig->setImgurForceAnonymous(mImgurForceAnonymousCheckbox->isChecked());
    mConfig->setImgurOpenLinkDirectlyToImage(mImgurDirectLinkToImageCheckbox->isChecked());
    mConfig->setImgurAlwaysCopyToClipboard(mImgurAlwaysCopyToClipboardCheckBox->isChecked());
    mConfig->setImgurConfirmBeforeUpload(mImgurConfirmBeforeUploadCheckbox->isChecked());

    mConfig->setCaptureCursor(mCaptureCursorCheckbox->isChecked());
    mConfig->setCursorRulerEnabled(mCursorRulerCheckbox->isChecked());
    mConfig->setCursorInfoEnabled(mCursorInfoCheckbox->isChecked());
    mConfig->setSnippingCursorColor(mSnippingCursorColorButton->color());
    mConfig->setSnippingCursorSize(mSnippingCursorSizeCombobox->value());

    mConfig->setSaveDirectory(FilenameFormatter::extractPath(mSaveLocationLineEdit->displayText()));
    mConfig->setSaveFilename(FilenameFormatter::extractFilename(mSaveLocationLineEdit->displayText()));
    mConfig->setSaveFormat(FilenameFormatter::extractFormat(mSaveLocationLineEdit->displayText()));

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
    mPromptToSaveBeforeExitCheckbox->setText(tr("Prompt to save before discarding unsaved changes"));
    mSaveKsnipPositionCheckbox->setText(tr("Save ksnip position on move and load on startup"));
    mSaveKsnipToolSelectionCheckbox->setText(tr("Save ksnip tool selection and load on startup"));
    mCaptureOnStartupCheckbox->setText(tr("Capture screenshot at startup with default mode"));
    mUseInstantSaveCheckBox->setText(tr("Instant save to default location without 'Save as' dialog"));
    mUseInstantSaveCheckBox->setToolTip(tr("When enabled, will not ask where to save a screenshot\n"
                                           "when saving, but will save instantly to default location."));

    mApplicationStyleLabel->setText(tr("Application Style") + QStringLiteral(":"));
    mApplicationStyleLabel->setToolTip(tr("Sets the application style which defines the look and feel of the GUI.\n"
                                          "Change requires ksnip restart to take effect."));
    mApplicationStyleCombobox->setToolTip(mApplicationStyleLabel->toolTip());
    mApplicationStyleCombobox->setFixedWidth(100);

    mSaveLocationLabel->setText(tr("Capture save location and filename") + QStringLiteral(":"));

    mSaveLocationLineEdit->setText(mConfig->saveDirectory() +
                                   mConfig->saveFilename() +
                                   mConfig->saveFormat());
    mSaveLocationLineEdit->setToolTip(tr("Filename can contain $Y, $M, $D for date, $h, $m, $s for time, or $T for time in hhmmss format."));

    mBrowseButton->setText(tr("Browse"));
    connect(mBrowseButton, &QPushButton::clicked, this, &SettingsDialog::chooseSaveDirectory);

    // Create Image Grabber Settings
    mCaptureCursorCheckbox->setText(tr("Capture mouse cursor on screenshot"));
    mCaptureCursorCheckbox->setToolTip(tr("Should mouse cursor be visible on\n"
                                          "screenshots."));
    mCursorRulerCheckbox->setText(tr("Show snipping cursor ruler"));
    mCursorRulerCheckbox->setToolTip(tr("Horizontal and vertical lines going from\n"
                                        "desktop corner to cursor on snipping area."));
    mCursorInfoCheckbox->setText(tr("Show cursor position info"));
    mCursorInfoCheckbox->setToolTip(tr("When left mouse is not pressed the position\n"
                                       "is show, when the mouse button is pressed,\n"
                                       "the size of the select area is shown left\n"
                                       "and right from the captured area."));
    mSnippingCursorColorLabel->setText(tr("Cursor Color") + QStringLiteral(":"));
    mSnippingCursorColorLabel->setToolTip(tr("Sets the color of the snipping area\n"
                                          "cursor. Change requires ksnip restart to\n"
                                          "take effect."));
    mSnippingCursorColorButton->setMinimumWidth(fixedButtonSize);
    mSnippingCursorColorButton->setToolTip(mSnippingCursorColorLabel->toolTip());
    mSnippingCursorSizeLabel->setText(tr("Cursor Thickness") + QStringLiteral(":"));
    mSnippingCursorSizeLabel->setToolTip(tr("Sets the thickness of the snipping area\n"
                                            "cursor. Change requires ksnip restart to\n"
                                            "take effect."));
    mSnippingCursorSizeCombobox->setMinimumWidth(fixedButtonSize);
    mSnippingCursorSizeCombobox->setToolTip(mSnippingCursorSizeLabel->toolTip());

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

    mTextBoldButton->setIcon(QIcon(QStringLiteral(":/bold")));
    mTextBoldButton->setToolTip(tr("Bold"));
    mTextBoldButton->setCheckable(true);

    mTextItalicButton->setIcon(QIcon(QStringLiteral(":/italic")));
    mTextItalicButton->setToolTip(tr("Italic"));
    mTextItalicButton->setCheckable(true);

    mTextUnderlineButton->setIcon(QIcon(QStringLiteral(":/underline")));
    mTextUnderlineButton->setToolTip(tr("Underline"));
    mTextUnderlineButton->setCheckable(true);

    mNumberFontLabel->setText(tr("Numbering Font") + QStringLiteral(":"));
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
    applicationGrid->addWidget(mAlwaysCopyToClipboardCheckbox, 0, 0, 1, 3);
    applicationGrid->addWidget(mPromptToSaveBeforeExitCheckbox, 1, 0, 1, 3);
    applicationGrid->addWidget(mSaveKsnipPositionCheckbox, 2, 0, 1, 3);
    applicationGrid->addWidget(mSaveKsnipToolSelectionCheckbox, 3, 0, 1, 3);
    applicationGrid->addWidget(mCaptureOnStartupCheckbox, 4, 0, 1, 3);
    applicationGrid->addWidget(mUseInstantSaveCheckBox, 5, 0, 1, 3);
    applicationGrid->setRowMinimumHeight(6, 15);
    applicationGrid->addWidget(mApplicationStyleLabel, 7, 0);
    applicationGrid->addWidget(mApplicationStyleCombobox, 7, 1, Qt::AlignLeft);
    applicationGrid->setRowMinimumHeight(8, 15);
    applicationGrid->addWidget(mSaveLocationLabel, 9, 0, 1, 3);
    applicationGrid->addWidget(mSaveLocationLineEdit, 10, 0, 1, 3);
    applicationGrid->addWidget(mBrowseButton, 10, 4);


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
    imageGrabberGrid->addWidget(mSnippingCursorColorLabel, 4, 0);
    imageGrabberGrid->addWidget(mSnippingCursorColorButton, 4, 1, Qt::AlignLeft);
    imageGrabberGrid->addWidget(mSnippingCursorSizeLabel, 5, 0);
    imageGrabberGrid->addWidget(mSnippingCursorSizeCombobox, 5, 1, Qt::AlignLeft);

    auto imageGrabberGrpBox = new QGroupBox(tr("Image Grabber"));
    imageGrabberGrpBox->setLayout(imageGrabberGrid);

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

    auto painterGrpBox = new QGroupBox(tr("Painter Settings"));
    painterGrpBox->setLayout(painterGrid);

    // Setup Push Button Layout
    auto buttonLayout = new QHBoxLayout;
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
 * shell and inform the user via statusbar.
 */
void SettingsDialog::imgurTokenError(const QString& message)
{
    qCritical("SettingsDialog returned error: '%s'", qPrintable(message));
    qInfo("%s", qPrintable(tr("Imgur.com token update error.")));
}

void SettingsDialog::chooseSaveDirectory()
{
    auto path = QFileDialog::getExistingDirectory(this,
                tr("Capture save location"),
                mConfig->saveDirectory());
    if(!path.isEmpty()) {
        auto filename = FilenameFormatter::extractFilename(mSaveLocationLineEdit->text());
        auto format = FilenameFormatter::extractFormat(mSaveLocationLineEdit->text());

        if(!filename.isEmpty()) {
            path.append(QLatin1Char('/')).append(filename);
        }

        if(!format.isEmpty()) {
            path.append(QLatin1Char('.')).append(format);
        }

        mSaveLocationLineEdit->setText(path);
    }
}
