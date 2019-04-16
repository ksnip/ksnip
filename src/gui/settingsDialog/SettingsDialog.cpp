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

	mSmoothPathCheckbox(new QCheckBox),
	mItemShadowCheckbox(new QCheckBox),
	mTextFontLabel(new QLabel),
	mNumberFontLabel(new QLabel),
	mSmoothFactorLabel(new QLabel),
	mSmoothFactorCombobox(new NumericComboBox(1, 1, 15)),
	mTextFontCombobox(new QFontComboBox(this)),
	mNumberFontCombobox(new QFontComboBox(this)),
	mOkButton(new QPushButton),
	mCancelButton(new QPushButton),
	mTextBoldButton(new QToolButton),
	mTextItalicButton(new QToolButton),
	mTextUnderlineButton(new QToolButton),
	mListWidget(new QListWidget),
	mStackedLayout(new QStackedLayout),
	mConfig(KsnipConfig::instance())
{
    setWindowTitle(QApplication::applicationName() + QStringLiteral(" - ") + tr("Settings"));

    initGui();

    loadSettings();

    connect(mListWidget, &QListWidget::itemSelectionChanged, [this]() {
        mStackedLayout->setCurrentIndex(mListWidget->currentRow());
    });
}

SettingsDialog::~SettingsDialog()
{
    delete mSmoothPathCheckbox;
    delete mItemShadowCheckbox;
    delete mTextFontLabel;
    delete mNumberFontLabel;
    delete mSmoothFactorLabel;
    delete mSmoothFactorCombobox;
    delete mTextFontCombobox;
    delete mNumberFontCombobox;
    delete mOkButton;
    delete mCancelButton;
    delete mTextBoldButton;
    delete mTextItalicButton;
    delete mTextUnderlineButton;
    delete mListWidget;
    delete mStackedLayout;
}

void SettingsDialog::loadSettings()
{
    mTextFontCombobox->setCurrentFont(mConfig->textFont());
    mTextBoldButton->setChecked(mConfig->textBold());
    mTextItalicButton->setChecked(mConfig->textItalic());
    mTextUnderlineButton->setChecked(mConfig->textUnderline());
    mNumberFontCombobox->setCurrentFont(mConfig->numberFont());
    mItemShadowCheckbox->setChecked(mConfig->itemShadowEnabled());
    mSmoothPathCheckbox->setChecked(mConfig->smoothPathEnabled());
    mSmoothFactorCombobox->setValue(mConfig->smoothFactor());
	smoothPathCheckboxClicked(mConfig->smoothPathEnabled());
}

void SettingsDialog::saveSettings()
{
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
    mImgurUploaderSettings->saveSettings();
}

void SettingsDialog::initGui()
{
    auto const fixedButtonSize = 100;

    // Create Painter Settings
    mItemShadowCheckbox->setText(tr("Paint Item Shadows"));
    mItemShadowCheckbox->setToolTip(tr("When enabled, paint items cast shadows."));

    mSmoothPathCheckbox->setText(tr("Smooth Painter Paths"));
    mSmoothPathCheckbox->setToolTip(tr("When enabled smooths out pen and\n"
                                       "marker paths after finished drawing."));
    connect(mSmoothPathCheckbox, &QCheckBox::clicked, this, &SettingsDialog::smoothPathCheckboxClicked);

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
	mImgurUploaderSettings = new ImgurUploaderSettings(mConfig);

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
    mStackedLayout->addWidget(mImgurUploaderSettings);
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

void SettingsDialog::smoothPathCheckboxClicked(bool checked)
{
    mSmoothFactorLabel->setEnabled(checked);
    mSmoothFactorCombobox->setEnabled(checked);
}
