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
	mRememberToolSelectionCheckbox(new QCheckBox(this)),
	mSwitchToSelectToolAfterDrawingItemCheckbox(new QCheckBox(this)),
	mNumberToolSeedChangeUpdatesAllItemsCheckbox(new QCheckBox(this)),
	mSmoothFactorLabel(new QLabel(this)),
	mCanvasColorLabel(new QLabel(this)),
	mSmoothFactorCombobox(new NumericComboBox(1, 1, 15)),
	mCanvasColorButton(new ColorButton(this)),
	mLayout(new QGridLayout(this)),
	mConfig(config)
{
    Q_ASSERT(mConfig != nullptr);

    initGui();
    loadConfig();
}

AnnotationSettings::~AnnotationSettings()
{
    delete mSmoothPathCheckbox;
    delete mRememberToolSelectionCheckbox;
    delete mSwitchToSelectToolAfterDrawingItemCheckbox;
    delete mNumberToolSeedChangeUpdatesAllItemsCheckbox;
    delete mSmoothFactorLabel;
    delete mCanvasColorLabel;
    delete mSmoothFactorCombobox;
    delete mCanvasColorButton;
    delete mLayout;
}

void AnnotationSettings::saveSettings()
{
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

	mCanvasColorLabel->setText(tr("Canvas Color") + QLatin1String(":"));
	mCanvasColorLabel->setToolTip(tr("Default Canvas background color for annotation area.\n"
								  	 	"Changing color affects only new annotation areas."));
	mCanvasColorButton->setMinimumWidth(fixedButtonWidth);
	mCanvasColorButton->setShowAlphaChannel(true);

    mLayout->setAlignment(Qt::AlignTop);
    mLayout->setColumnMinimumWidth(0, 10);
    mLayout->addWidget(mRememberToolSelectionCheckbox, 0, 0, 1, 6);
    mLayout->addWidget(mSwitchToSelectToolAfterDrawingItemCheckbox, 1, 0, 1, 6);
    mLayout->addWidget(mNumberToolSeedChangeUpdatesAllItemsCheckbox, 2, 0, 1, 6);
    mLayout->addWidget(mSmoothPathCheckbox, 3, 0, 1, 6);
    mLayout->addWidget(mSmoothFactorLabel, 4, 1, 1, 3);
    mLayout->addWidget(mSmoothFactorCombobox, 4, 3, 1,3, Qt::AlignLeft);
    mLayout->setRowMinimumHeight(5, 15);
    mLayout->addWidget(mCanvasColorLabel, 6, 0, 1, 2);
    mLayout->addWidget(mCanvasColorButton, 6, 3, 1,3, Qt::AlignLeft);

    setTitle(tr("Annotator Settings"));
    setLayout(mLayout);
}

void AnnotationSettings::loadConfig()
{
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
