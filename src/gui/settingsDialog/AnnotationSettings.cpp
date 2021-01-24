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

#include "AnnotationSettings.h"

AnnotationSettings::AnnotationSettings(KsnipConfig *config) :
	mSmoothPathCheckbox(new QCheckBox(this)),
	mItemShadowCheckbox(new QCheckBox(this)),
	mRememberToolSelectionCheckbox(new QCheckBox(this)),
	mSwitchToSelectToolAfterDrawingItemCheckbox(new QCheckBox(this)),
	mNumberToolSeedChangeUpdatesAllItemsCheckbox(new QCheckBox(this)),
	mTextFontLabel(new QLabel(this)),
	mNumberFontLabel(new QLabel(this)),
	mSmoothFactorLabel(new QLabel(this)),
	mCanvasColorLabel(new QLabel(this)),
	mSmoothFactorCombobox(new NumericComboBox(1, 1, 15)),
	mTextFontCombobox(new QFontComboBox(this)),
	mNumberFontCombobox(new QFontComboBox(this)),
	mTextBoldButton(new QToolButton(this)),
	mTextItalicButton(new QToolButton(this)),
	mTextUnderlineButton(new QToolButton(this)),
	mCanvasColorButton(new ColorButton(this)),
	mLayout(new QGridLayout(this)),
	mConfig(config)
{
    Q_ASSERT(mConfig != nullptr);

    mConfig = config;

    initGui();
    loadConfig();
}

AnnotationSettings::~AnnotationSettings()
{
    delete mSmoothPathCheckbox;
    delete mItemShadowCheckbox;
    delete mRememberToolSelectionCheckbox;
    delete mSwitchToSelectToolAfterDrawingItemCheckbox;
    delete mNumberToolSeedChangeUpdatesAllItemsCheckbox;
    delete mTextFontLabel;
    delete mNumberFontLabel;
    delete mSmoothFactorLabel;
    delete mCanvasColorLabel;
    delete mSmoothFactorCombobox;
    delete mTextFontCombobox;
    delete mNumberFontCombobox;
    delete mTextBoldButton;
    delete mTextItalicButton;
    delete mTextUnderlineButton;
    delete mCanvasColorButton;
    delete mLayout;
}

void AnnotationSettings::saveSettings()
{
    mConfig->setTextFont(mTextFontCombobox->currentFont());
    mConfig->setTextBold(mTextBoldButton->isChecked());
    mConfig->setTextItalic(mTextItalicButton->isChecked());
    mConfig->setTextUnderline(mTextUnderlineButton->isChecked());
    mConfig->setNumberFont(mNumberFontCombobox->currentFont());
    mConfig->setItemShadowEnabled(mItemShadowCheckbox->isChecked());
    mConfig->setSmoothPathEnabled(mSmoothPathCheckbox->isChecked());
    mConfig->setSmoothFactor(mSmoothFactorCombobox->value());
    mConfig->setRememberToolSelection(mRememberToolSelectionCheckbox->isChecked());
    mConfig->setSwitchToSelectToolAfterDrawingItem(mSwitchToSelectToolAfterDrawingItemCheckbox->isChecked());
	mConfig->setNumberToolSeedChangeUpdatesAllItems(mNumberToolSeedChangeUpdatesAllItemsCheckbox->isChecked());
	mConfig->setCanvasColor(mCanvasColorButton->color());
}

void AnnotationSettings::initGui()
{
    auto const fixedButtonWidth = ScaledSizeProvider::scaledWidth(100);

    mRememberToolSelectionCheckbox->setText(tr("Remember annotation tool selection and load on startup"));

    mSwitchToSelectToolAfterDrawingItemCheckbox->setText(tr("Switch to Select Tool after drawing Item"));

    mNumberToolSeedChangeUpdatesAllItemsCheckbox->setText(tr("Number Tool Seed change updates all Number Items"));
    mNumberToolSeedChangeUpdatesAllItemsCheckbox->setToolTip(tr("Disabling this option causes changes of the number tool\n"
																"seed to affect only new items but not existing items.\n"
																"Disabling this option allows having duplicate numbers."));

    mItemShadowCheckbox->setText(tr("Paint Item Shadows"));
    mItemShadowCheckbox->setToolTip(tr("When enabled, paint items cast shadows."));

    mSmoothPathCheckbox->setText(tr("Smooth Painter Paths"));
    mSmoothPathCheckbox->setToolTip(tr("When enabled smooths out pen and\n"
                                       "marker paths after finished drawing."));
    connect(mSmoothPathCheckbox, &QCheckBox::clicked, this, &AnnotationSettings::smoothPathCheckboxClicked);

    mSmoothFactorLabel->setText(tr("Smooth Factor") + QLatin1String(":"));
    mSmoothFactorLabel->setToolTip(tr("Increasing the smooth factor will decrease\n"
                                      "precision for pen and marker but will\n"
                                      "make them more smooth."));
    mSmoothFactorCombobox->setMinimumWidth(fixedButtonWidth);
    mSmoothFactorCombobox->setToolTip(mSmoothFactorLabel->toolTip());

    mTextFontLabel->setText(tr("Text Font") + QLatin1String(":"));
    mTextFontLabel->setToolTip(tr("Sets the font for the Text Paint Item."));
    mTextFontCombobox->setToolTip(mTextFontLabel->toolTip());
    mTextFontCombobox->setEditable(false);

    mTextBoldButton->setIcon(IconLoader::loadForTheme(QLatin1String("bold.svg")));
    mTextBoldButton->setToolTip(tr("Bold"));
    mTextBoldButton->setCheckable(true);

    mTextItalicButton->setIcon(IconLoader::loadForTheme(QLatin1String("italic.svg")));
    mTextItalicButton->setToolTip(tr("Italic"));
    mTextItalicButton->setCheckable(true);

    mTextUnderlineButton->setIcon(IconLoader::loadForTheme(QLatin1String("underline.svg")));
    mTextUnderlineButton->setToolTip(tr("Underline"));
    mTextUnderlineButton->setCheckable(true);

    mNumberFontLabel->setText(tr("Numbering Font") + QLatin1String(":"));
    mNumberFontLabel->setToolTip(tr("Sets the font for the Numbering Paint Item."));
    mNumberFontCombobox->setToolTip(mNumberFontLabel->toolTip());
    mNumberFontCombobox->setEditable(false);

	mCanvasColorLabel->setText(tr("Canvas Color") + QLatin1String(":"));
	mCanvasColorLabel->setToolTip(tr("Default Canvas background color for annotation area.\n"
								  	 	"Changing color affects only new annotation areas."));
	mCanvasColorButton->setMinimumWidth(fixedButtonWidth);
	mCanvasColorButton->setShowAlphaChannel(true);

    mLayout->setAlignment(Qt::AlignTop);
    mLayout->setColumnMinimumWidth(0, 10);
    mLayout->addWidget(mRememberToolSelectionCheckbox, 0, 0, 1, 6);
    mLayout->addWidget(mItemShadowCheckbox, 1, 0, 1, 6);
    mLayout->addWidget(mSwitchToSelectToolAfterDrawingItemCheckbox, 2, 0, 1, 6);
    mLayout->addWidget(mNumberToolSeedChangeUpdatesAllItemsCheckbox, 3, 0, 1, 6);
    mLayout->addWidget(mSmoothPathCheckbox, 4, 0, 1, 6);
    mLayout->addWidget(mSmoothFactorLabel, 5, 1, 1, 3);
    mLayout->addWidget(mSmoothFactorCombobox, 5, 3, 1,3, Qt::AlignLeft);
    mLayout->setRowMinimumHeight(6, 15);
    mLayout->addWidget(mTextFontLabel, 7, 0, 1, 2);
    mLayout->addWidget(mTextFontCombobox, 7, 3);
    mLayout->addWidget(mTextBoldButton, 7, 4);
    mLayout->addWidget(mTextItalicButton, 7, 5);
    mLayout->addWidget(mTextUnderlineButton, 7, 6);
    mLayout->addWidget(mNumberFontLabel, 8, 0, 1, 2);
    mLayout->addWidget(mNumberFontCombobox, 8, 3);
	mLayout->setRowMinimumHeight(9, 15);
    mLayout->addWidget(mCanvasColorLabel, 10, 0, 1, 2);
    mLayout->addWidget(mCanvasColorButton, 10, 3, 1,3, Qt::AlignLeft);
    mLayout->setRowMinimumHeight(11, 15);

    setTitle(tr("Annotator Settings"));
    setLayout(mLayout);
}

void AnnotationSettings::loadConfig()
{
    mTextFontCombobox->setCurrentFont(mConfig->textFont());
    mTextBoldButton->setChecked(mConfig->textBold());
    mTextItalicButton->setChecked(mConfig->textItalic());
    mTextUnderlineButton->setChecked(mConfig->textUnderline());
    mNumberFontCombobox->setCurrentFont(mConfig->numberFont());
    mItemShadowCheckbox->setChecked(mConfig->itemShadowEnabled());
    mSmoothPathCheckbox->setChecked(mConfig->smoothPathEnabled());
    mSmoothFactorCombobox->setValue(mConfig->smoothFactor());
    mRememberToolSelectionCheckbox->setChecked(mConfig->rememberToolSelection());
    mSwitchToSelectToolAfterDrawingItemCheckbox->setChecked(mConfig->switchToSelectToolAfterDrawingItem());
    mNumberToolSeedChangeUpdatesAllItemsCheckbox->setChecked(mConfig->numberToolSeedChangeUpdatesAllItems());
    mCanvasColorButton->setColor(mConfig->canvasColor());
    smoothPathCheckboxClicked(mConfig->smoothPathEnabled());
}

void AnnotationSettings::smoothPathCheckboxClicked(bool checked)
{
    mSmoothFactorLabel->setEnabled(checked);
    mSmoothFactorCombobox->setEnabled(checked);
}
