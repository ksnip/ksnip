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

AnnotationSettings::AnnotationSettings(const QSharedPointer<IConfig> &config, const QSharedPointer<IScaledSizeProvider> &scaledSizeProvider) :
	mSmoothPathCheckbox(new QCheckBox(this)),
	mRememberToolSelectionCheckBox(new QCheckBox(this)),
	mSwitchToSelectToolAfterDrawingItemCheckBox(new QCheckBox(this)),
	mNumberToolSeedChangeUpdatesAllItemsCheckBox(new QCheckBox(this)),
	mSelectItemAfterDrawingCheckBox(new QCheckBox(this)),
	mIsControlsWidgetVisibleCheckBox(new QCheckBox(this)),
	mSmoothFactorLabel(new QLabel(this)),
	mCanvasColorLabel(new QLabel(this)),
	mSmoothFactorCombobox(new NumericComboBox(1, 1, 15)),
	mCanvasColorButton(new ColorButton(this)),
	mLayout(new QGridLayout(this)),
	mConfig(config),
	mScaledSizeProvider(scaledSizeProvider)
{
    initGui();
    loadConfig();
}

AnnotationSettings::~AnnotationSettings()
{
    delete mSmoothFactorCombobox;
}

void AnnotationSettings::saveSettings()
{
    mConfig->setSmoothPathEnabled(mSmoothPathCheckbox->isChecked());
    mConfig->setSmoothFactor(mSmoothFactorCombobox->value());
    mConfig->setRememberToolSelection(mRememberToolSelectionCheckBox->isChecked());
    mConfig->setSwitchToSelectToolAfterDrawingItem(mSwitchToSelectToolAfterDrawingItemCheckBox->isChecked());
	mConfig->setNumberToolSeedChangeUpdatesAllItems(mNumberToolSeedChangeUpdatesAllItemsCheckBox->isChecked());
	mConfig->setSelectItemAfterDrawing(mSelectItemAfterDrawingCheckBox->isChecked());
	mConfig->setIsControlsWidgetVisible(mIsControlsWidgetVisibleCheckBox->isChecked());
	mConfig->setCanvasColor(mCanvasColorButton->color());
}

void AnnotationSettings::initGui()
{
    auto const fixedButtonWidth = mScaledSizeProvider->scaledWidth(100);

    mRememberToolSelectionCheckBox->setText(tr("Remember annotation tool selection and load on startup"));

    mSwitchToSelectToolAfterDrawingItemCheckBox->setText(tr("Switch to Select Tool after drawing Item"));
	connect(mSwitchToSelectToolAfterDrawingItemCheckBox, &QCheckBox::clicked, this, &AnnotationSettings::switchToSelectToolAfterDrawingItemCheckBoxClicked);

	mSelectItemAfterDrawingCheckBox->setText(tr("Select Item after drawing"));
	mSelectItemAfterDrawingCheckBox->setToolTip(tr("With this option enabled the item gets selected after\n"
												      "being created, allowing changing settings."));

    mNumberToolSeedChangeUpdatesAllItemsCheckBox->setText(tr("Number Tool Seed change updates all Number Items"));
    mNumberToolSeedChangeUpdatesAllItemsCheckBox->setToolTip(tr("Disabling this option causes changes of the number tool\n"
																"seed to affect only new items but not existing items.\n"
																"Disabling this option allows having duplicate numbers."));

	mIsControlsWidgetVisibleCheckBox->setText(tr("Show Controls Widget"));
	mIsControlsWidgetVisibleCheckBox->setToolTip(tr("The Controls Widget contains the Undo/Redo,\n"
											     "Crop, Scale, Rotate and Modify Canvas buttons."));

	mSmoothPathCheckbox->setText(tr("Smooth Painter Paths"));
    mSmoothPathCheckbox->setToolTip(tr("When enabled smooths out pen and\n"
                                       "marker paths after finished drawing."));
    connect(mSmoothPathCheckbox, &QCheckBox::clicked, this, &AnnotationSettings::smoothPathCheckBoxClicked);

    mSmoothFactorLabel->setText(tr("Smooth Factor") + QLatin1String(":"));
    mSmoothFactorLabel->setToolTip(tr("Increasing the smooth factor will decrease\n"
                                      "precision for pen and marker but will\n"
                                      "make them more smooth."));
    mSmoothFactorCombobox->setMinimumWidth(fixedButtonWidth);
    mSmoothFactorCombobox->setToolTip(mSmoothFactorLabel->toolTip());

	mCanvasColorLabel->setText(tr("Canvas Color") + QLatin1String(":"));
	mCanvasColorLabel->setToolTip(tr("Default Canvas background color for annotation area.\n"
								  	 	"Changing color affects only new annotation areas."));
	mCanvasColorButton->setMinimumWidth(fixedButtonWidth);
	mCanvasColorButton->setShowAlphaChannel(true);

    mLayout->setAlignment(Qt::AlignTop);
    mLayout->setColumnMinimumWidth(0, 10);
    mLayout->addWidget(mRememberToolSelectionCheckBox, 0, 0, 1, 6);
    mLayout->addWidget(mSwitchToSelectToolAfterDrawingItemCheckBox, 1, 0, 1, 6);
    mLayout->addWidget(mSelectItemAfterDrawingCheckBox, 2, 1, 1, 5);
    mLayout->addWidget(mNumberToolSeedChangeUpdatesAllItemsCheckBox, 3, 0, 1, 6);
    mLayout->addWidget(mIsControlsWidgetVisibleCheckBox, 4, 0, 1, 6);
    mLayout->addWidget(mSmoothPathCheckbox, 5, 0, 1, 6);
    mLayout->addWidget(mSmoothFactorLabel, 6, 1, 1, 3);
    mLayout->addWidget(mSmoothFactorCombobox, 7, 3, 1,3, Qt::AlignLeft);
    mLayout->setRowMinimumHeight(7, 15);
    mLayout->addWidget(mCanvasColorLabel, 8, 0, 1, 2);
    mLayout->addWidget(mCanvasColorButton, 8, 3, 1,3, Qt::AlignLeft);

    setTitle(tr("Annotator Settings"));
    setLayout(mLayout);
}

void AnnotationSettings::loadConfig()
{
    mSmoothPathCheckbox->setChecked(mConfig->smoothPathEnabled());
    mSmoothFactorCombobox->setValue(mConfig->smoothFactor());
    mRememberToolSelectionCheckBox->setChecked(mConfig->rememberToolSelection());
    mSwitchToSelectToolAfterDrawingItemCheckBox->setChecked(mConfig->switchToSelectToolAfterDrawingItem());
    mNumberToolSeedChangeUpdatesAllItemsCheckBox->setChecked(mConfig->numberToolSeedChangeUpdatesAllItems());
	mSelectItemAfterDrawingCheckBox->setChecked(mConfig->selectItemAfterDrawing());
	mIsControlsWidgetVisibleCheckBox->setChecked(mConfig->isControlsWidgetVisible());
    mCanvasColorButton->setColor(mConfig->canvasColor());
	smoothPathCheckBoxClicked(mConfig->smoothPathEnabled());
	switchToSelectToolAfterDrawingItemCheckBoxClicked(mConfig->switchToSelectToolAfterDrawingItem());
}

void AnnotationSettings::smoothPathCheckBoxClicked(bool checked)
{
    mSmoothFactorLabel->setEnabled(checked);
    mSmoothFactorCombobox->setEnabled(checked);
}

void AnnotationSettings::switchToSelectToolAfterDrawingItemCheckBoxClicked(bool checked)
{
	mSelectItemAfterDrawingCheckBox->setEnabled(checked);
}
