/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "SnippingAreaSettings.h"

SnippingAreaSettings::SnippingAreaSettings(const QSharedPointer<IConfig> &config, const QSharedPointer<IScaledSizeProvider> &scaledSizeProvider) :
	mConfig(config),
	mScaledSizeProvider(scaledSizeProvider),
	mFreezeImageWhileSnippingCheckbox(new QCheckBox(this)),
	mSnippingAreaRulersCheckbox(new QCheckBox(this)),
	mSnippingAreaPositionAndSizeInfoCheckbox(new QCheckBox(this)),
	mSnippingAreaMagnifyingGlassCheckbox(new QCheckBox(this)),
	mAllowResizingRectSelectionCheckbox(new QCheckBox(this)),
	mShowSnippingAreaInfoTextCheckbox(new QCheckBox(this)),
	mSnippingAreaOffsetEnabledCheckbox(new QCheckBox(this)),
	mSnippingCursorSizeLabel(new QLabel(this)),
	mSnippingCursorColorLabel(new QLabel(this)),
	mSnippingAdornerColorLabel(new QLabel(this)),
	mSnippingAreaTransparencyLabel(new QLabel(this)),
	mSnippingAreaOffsetXLabel(new QLabel(this)),
	mSnippingAreaOffsetYLabel(new QLabel(this)),
	mSnippingCursorSizeCombobox(new NumericComboBox(1, 2, 3)),
	mSnippingCursorColorButton(new ColorButton(this)),
	mSnippingAdornerColorButton(new ColorButton(this)),
	mSnippingAreaTransparencySpinBox(new QSpinBox(this)),
	mSnippingAreaOffsetXSpinBox(new QDoubleSpinBox(this)),
	mSnippingAreaOffsetYSpinBox(new QDoubleSpinBox(this)),
	mLayout(new QGridLayout(this))
{
	initGui();
	loadConfig();
}

SnippingAreaSettings::~SnippingAreaSettings()
{
	delete mSnippingCursorSizeCombobox;
}

void SnippingAreaSettings::saveSettings()
{
	mConfig->setFreezeImageWhileSnippingEnabled(mFreezeImageWhileSnippingCheckbox->isChecked());
	mConfig->setSnippingAreaMagnifyingGlassEnabled(mSnippingAreaMagnifyingGlassCheckbox->isChecked());
	mConfig->setSnippingAreaRulersEnabled(mSnippingAreaRulersCheckbox->isChecked());
	mConfig->setSnippingAreaPositionAndSizeInfoEnabled(mSnippingAreaPositionAndSizeInfoCheckbox->isChecked());
	mConfig->setAllowResizingRectSelection(mAllowResizingRectSelectionCheckbox->isChecked());
	mConfig->setShowSnippingAreaInfoText(mShowSnippingAreaInfoTextCheckbox->isChecked());
	mConfig->setSnippingCursorColor(mSnippingCursorColorButton->color());
	mConfig->setSnippingAdornerColor(mSnippingAdornerColorButton->color());
	mConfig->setSnippingCursorSize(mSnippingCursorSizeCombobox->value());
	mConfig->setSnippingAreaTransparency(mSnippingAreaTransparencySpinBox->value());
	mConfig->setSnippingAreaOffsetEnable(mSnippingAreaOffsetEnabledCheckbox->isChecked());
	mConfig->setSnippingAreaOffset({mSnippingAreaOffsetXSpinBox->value(), mSnippingAreaOffsetYSpinBox->value()});
}

void SnippingAreaSettings::initGui()
{
	auto const fixedButtonWidth = mScaledSizeProvider->scaledWidth(70);

	mFreezeImageWhileSnippingCheckbox->setText(tr("Freeze Image while snipping"));
	mFreezeImageWhileSnippingCheckbox->setToolTip(tr("When enabled will freeze the background while\n"
													 "selecting a rectangular region. It also changes\n"
													 "the behavior of delayed screenshots, with this\n"
													 "option enabled the delay happens before the\n"
													 "snipping area is shown and with the option disabled\n"
													 "the delay happens after the snipping area is shown.\n"
													 "This feature is always disabled for Wayland and always\n"
													 "enabled for MacOs."));
	connect(mFreezeImageWhileSnippingCheckbox, &QCheckBox::stateChanged, this, &SnippingAreaSettings::freezeImageWhileSnippingStateChanged);

	mSnippingAreaMagnifyingGlassCheckbox->setText(tr("Show magnifying glass on snipping area"));
	mSnippingAreaMagnifyingGlassCheckbox->setToolTip(tr("Show a magnifying glass which zooms into\n"
														"the background image. This option only works\n"
														"with 'Freeze Image while snipping' enabled."));

	mSnippingAreaRulersCheckbox->setText(tr("Show Snipping Area rulers"));
	mSnippingAreaRulersCheckbox->setToolTip(tr("Horizontal and vertical lines going from\n"
											   "desktop edges to cursor on snipping area."));

	mSnippingAreaPositionAndSizeInfoCheckbox->setText(tr("Show Snipping Area position and size info"));
	mSnippingAreaPositionAndSizeInfoCheckbox->setToolTip(tr("When left mouse button is not pressed the position\n"
															"is shown, when the mouse button is pressed,\n"
															"the size of the select area is shown left\n"
															"and above from the captured area."));

	mAllowResizingRectSelectionCheckbox->setText(tr("Allow resizing rect area selection by default"));
	mAllowResizingRectSelectionCheckbox->setToolTip(tr("When enabled will, after selecting a rect\n"
													   "area, allow resizing the selection. When\n"
													   "done resizing the selection can be confirmed\n"
													   "by pressing return."));

	mShowSnippingAreaInfoTextCheckbox->setText(tr("Show Snipping Area info text"));

	mSnippingCursorColorLabel->setText(tr("Snipping Area cursor color") + QLatin1String(":"));
	mSnippingCursorColorLabel->setToolTip(tr("Sets the color of the snipping area cursor."));
	mSnippingCursorColorButton->setMinimumWidth(fixedButtonWidth);
	mSnippingCursorColorButton->setToolTip(mSnippingCursorColorLabel->toolTip());

	mSnippingAdornerColorLabel->setText(tr("Snipping Area adorner color") + QLatin1String(":"));
	mSnippingAdornerColorLabel->setToolTip(tr("Sets the color of all adorner elements\n"
										        "on the snipping area."));
	mSnippingAdornerColorButton->setMinimumWidth(fixedButtonWidth);
	mSnippingAdornerColorButton->setToolTip(mSnippingAdornerColorLabel->toolTip());

	mSnippingCursorSizeLabel->setText(tr("Snipping Area cursor thickness") + QLatin1String(":"));
	mSnippingCursorSizeLabel->setToolTip(tr("Sets the thickness of the snipping area cursor."));
	mSnippingCursorSizeCombobox->setMinimumWidth(fixedButtonWidth);
	mSnippingCursorSizeCombobox->setToolTip(mSnippingCursorSizeLabel->toolTip());

	mSnippingAreaTransparencyLabel->setText(tr("Snipping Area Transparency"));
	mSnippingAreaTransparencyLabel->setToolTip(tr("Alpha for not selected region on snipping area.\n"
											   "Smaller number is more transparent."));
	mSnippingAreaTransparencySpinBox->setMinimum(0);
	mSnippingAreaTransparencySpinBox->setMaximum(200);
	mSnippingAreaTransparencySpinBox->setToolTip(mSnippingAreaTransparencyLabel->toolTip());
	mSnippingAreaTransparencySpinBox->setMinimumWidth(fixedButtonWidth);

    mSnippingAreaOffsetEnabledCheckbox->setText(tr("Enable Snipping Area offset"));
    mSnippingAreaOffsetEnabledCheckbox->setToolTip(tr("When enabled will apply the configured\n"
                                                        "offset to the Snipping Area position which\n"
                                                        "is required when the position is not\n"
                                                        "correctly calculated. This is sometimes\n"
                                                        "required with screen scaling enabled."));
    connect(mSnippingAreaOffsetEnabledCheckbox, &QCheckBox::stateChanged, this, &SnippingAreaSettings::snippingAreaOffsetEnableStateChanged);

    mSnippingAreaOffsetXLabel->setText(tr("X") + QLatin1String(":"));
    mSnippingAreaOffsetYLabel->setText(tr("Y") + QLatin1String(":"));

    mSnippingAreaOffsetXSpinBox->setMinimum(-9999);
    mSnippingAreaOffsetXSpinBox->setMaximum(9999);
    mSnippingAreaOffsetXSpinBox->setDecimals(2);

    mSnippingAreaOffsetYSpinBox->setMinimum(-9999);
    mSnippingAreaOffsetYSpinBox->setMaximum(9999);
	mSnippingAreaOffsetYSpinBox->setDecimals(2);

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->setColumnMinimumWidth(0, mScaledSizeProvider->scaledWidth(10));
    mLayout->setColumnMinimumWidth(1, mScaledSizeProvider->scaledWidth(30));
	mLayout->addWidget(mFreezeImageWhileSnippingCheckbox, 0, 0, 1, 5);
	mLayout->addWidget(mSnippingAreaMagnifyingGlassCheckbox, 1, 1, 1, 4);
	mLayout->addWidget(mSnippingAreaRulersCheckbox, 2, 0, 1, 5);
	mLayout->addWidget(mSnippingAreaPositionAndSizeInfoCheckbox, 3, 0, 1, 5);
	mLayout->addWidget(mAllowResizingRectSelectionCheckbox, 4, 0, 1, 5);
	mLayout->addWidget(mShowSnippingAreaInfoTextCheckbox, 5, 0, 1, 5);
	mLayout->setRowMinimumHeight(6, 15);
	mLayout->addWidget(mSnippingAdornerColorLabel, 7, 0, 1, 3);
	mLayout->addWidget(mSnippingAdornerColorButton, 7, 3, Qt::AlignLeft);
	mLayout->addWidget(mSnippingCursorColorLabel, 8, 0, 1, 3);
	mLayout->addWidget(mSnippingCursorColorButton, 8, 3, Qt::AlignLeft);
	mLayout->addWidget(mSnippingCursorSizeLabel, 9, 0, 1, 3);
	mLayout->addWidget(mSnippingCursorSizeCombobox, 9, 3, Qt::AlignLeft);
	mLayout->addWidget(mSnippingAreaTransparencyLabel, 10, 0, 1, 3);
	mLayout->addWidget(mSnippingAreaTransparencySpinBox, 10, 3, Qt::AlignLeft);
    mLayout->setRowMinimumHeight(11, 15);
	mLayout->addWidget(mSnippingAreaOffsetEnabledCheckbox, 12, 0, 1, 5);
	mLayout->addWidget(mSnippingAreaOffsetXLabel, 13, 1, 1, 1);
	mLayout->addWidget(mSnippingAreaOffsetXSpinBox, 13, 2, Qt::AlignLeft);
    mLayout->addWidget(mSnippingAreaOffsetYLabel, 14, 1, 1, 1);
    mLayout->addWidget(mSnippingAreaOffsetYSpinBox, 14, 2, Qt::AlignLeft);

	setTitle(tr("Snipping Area"));
	setLayout(mLayout);
}

void SnippingAreaSettings::loadConfig()
{
	mFreezeImageWhileSnippingCheckbox->setChecked(mConfig->freezeImageWhileSnippingEnabled());
	mFreezeImageWhileSnippingCheckbox->setEnabled(!mConfig->isFreezeImageWhileSnippingEnabledReadOnly());
	mSnippingAreaMagnifyingGlassCheckbox->setChecked(mConfig->snippingAreaMagnifyingGlassEnabled());
	mSnippingAreaMagnifyingGlassCheckbox->setEnabled(!mConfig->isSnippingAreaMagnifyingGlassEnabledReadOnly());
	mSnippingAreaRulersCheckbox->setChecked(mConfig->snippingAreaRulersEnabled());
	mSnippingAreaPositionAndSizeInfoCheckbox->setChecked(mConfig->snippingAreaPositionAndSizeInfoEnabled());
	mAllowResizingRectSelectionCheckbox->setChecked(mConfig->allowResizingRectSelection());
	mShowSnippingAreaInfoTextCheckbox->setChecked(mConfig->showSnippingAreaInfoText());
	mSnippingCursorColorButton->setColor(mConfig->snippingCursorColor());
	mSnippingAdornerColorButton->setColor(mConfig->snippingAdornerColor());
	mSnippingCursorSizeCombobox->setValue(mConfig->snippingCursorSize());
	mSnippingAreaTransparencySpinBox->setValue(mConfig->snippingAreaTransparency());
	mSnippingAreaOffsetEnabledCheckbox->setChecked(mConfig->snippingAreaOffsetEnable());
	mSnippingAreaOffsetXSpinBox->setValue(mConfig->snippingAreaOffset().x());
	mSnippingAreaOffsetYSpinBox->setValue(mConfig->snippingAreaOffset().y());

	freezeImageWhileSnippingStateChanged();
    snippingAreaOffsetEnableStateChanged();
}

void SnippingAreaSettings::freezeImageWhileSnippingStateChanged()
{
    mSnippingAreaMagnifyingGlassCheckbox->setEnabled(mFreezeImageWhileSnippingCheckbox->isChecked());
}

void SnippingAreaSettings::snippingAreaOffsetEnableStateChanged()
{
    auto isEnabled = mSnippingAreaOffsetEnabledCheckbox->isChecked();
    mSnippingAreaOffsetXLabel->setEnabled(isEnabled);
    mSnippingAreaOffsetYLabel->setEnabled(isEnabled);
    mSnippingAreaOffsetXSpinBox->setEnabled(isEnabled);
    mSnippingAreaOffsetYSpinBox->setEnabled(isEnabled);
}
