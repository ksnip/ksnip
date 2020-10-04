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

#include "ImageGrabberSettings.h"

ImageGrabberSettings::ImageGrabberSettings(KsnipConfig *ksnipConfig) :
    mCaptureCursorCheckbox(new QCheckBox(this)),
    mFreezeImageWhileSnippingCheckbox(new QCheckBox(this)),
    mSnippingAreaRulersCheckbox(new QCheckBox(this)),
    mSnippingAreaPositionAndSizeInfoCheckbox(new QCheckBox(this)),
    mSnippingAreaMagnifyingGlassCheckbox(new QCheckBox(this)),
    mForceGenericWaylandCheckbox(new QCheckBox(this)),
    mScaleGenericWaylandScreenshotsCheckbox(new QCheckBox(this)),
    mSnippingCursorSizeLabel(new QLabel(this)),
    mSnippingCursorColorLabel(new QLabel(this)),
    mSnippingCursorSizeCombobox(new NumericComboBox(1, 2, 3)),
    mSnippingCursorColorButton(new ColorButton(this)),
    mLayout(new QGridLayout(this)),
    mConfig(ksnipConfig)
{
	Q_ASSERT(mConfig != nullptr);

	initGui();
	loadConfig();
}

ImageGrabberSettings::~ImageGrabberSettings()
{
	delete mCaptureCursorCheckbox;
	delete mFreezeImageWhileSnippingCheckbox;
	delete mSnippingAreaRulersCheckbox;
	delete mSnippingAreaPositionAndSizeInfoCheckbox;
	delete mSnippingAreaMagnifyingGlassCheckbox;
	delete mForceGenericWaylandCheckbox;
	delete mScaleGenericWaylandScreenshotsCheckbox;
	delete mSnippingCursorSizeLabel;
	delete mSnippingCursorColorLabel;
	delete mSnippingCursorColorButton;
	delete mSnippingCursorSizeCombobox;
	delete mLayout;
}

void ImageGrabberSettings::saveSettings()
{
	mConfig->setFreezeImageWhileSnippingEnabled(mFreezeImageWhileSnippingCheckbox->isChecked());
	mConfig->setSnippingAreaMagnifyingGlassEnabled(mSnippingAreaMagnifyingGlassCheckbox->isChecked());
	mConfig->setCaptureCursor(mCaptureCursorCheckbox->isChecked());
    mConfig->setSnippingAreaRulersEnabled(mSnippingAreaRulersCheckbox->isChecked());
	mConfig->setSnippingAreaPositionAndSizeInfoEnabled(mSnippingAreaPositionAndSizeInfoCheckbox->isChecked());
	mConfig->setForceGenericWaylandEnabled(mForceGenericWaylandCheckbox->isChecked());
	mConfig->setScaleGenericWaylandScreenshots(mScaleGenericWaylandScreenshotsCheckbox->isChecked());
	mConfig->setSnippingCursorColor(mSnippingCursorColorButton->color());
	mConfig->setSnippingCursorSize(mSnippingCursorSizeCombobox->value());
}

void ImageGrabberSettings::initGui()
{
	auto const fixedButtonSize = 70;

	mCaptureCursorCheckbox->setText(tr("Capture mouse cursor on screenshot"));
	mCaptureCursorCheckbox->setToolTip(tr("Should mouse cursor be visible on\n"
	                                      "screenshots."));
	mFreezeImageWhileSnippingCheckbox->setText(tr("Freeze Image while snipping"));
	mFreezeImageWhileSnippingCheckbox->setToolTip(tr("When enabled will freeze the background while\n"
	                                                 "selecting a rectangular region. It also changes\n"
	                                                 "the behavior of delayed screenshots, with this\n"
	                                                 "option enabled the delay happens before the\n"
	                                                 "snipping area is shown and with the option disabled\n"
	                                                 "the delay happens after the snipping area is shown.\n"
	                                                 "This feature is always disabled for Wayland and always\n"
	                                                 "enabled for MacOs."));
	connect(mFreezeImageWhileSnippingCheckbox, &QCheckBox::stateChanged, this, &ImageGrabberSettings::freezeImageWhileSnippingStateChanged);

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

    mForceGenericWaylandCheckbox->setText(tr("Force Generic Wayland Screenshot"));
    mForceGenericWaylandCheckbox->setToolTip(tr("GNOME and KDE Plasma support their own Wayland\n"
                                                   "and the Generic XDG-DESKTOP-PORTAL screenshots.\n"
                                                   "Enabling this option will force KDE Plasma and\n"
                                                   "GNOME to use the XDG-DESKTOP-PORTAL screenshots.\n"
                                                   "Change in this option require a ksnip restart."));

    mScaleGenericWaylandScreenshotsCheckbox->setText(tr("Scale Generic Wayland Screenshots"));
    mScaleGenericWaylandScreenshotsCheckbox->setToolTip(tr("Generic Wayland implementations that use\n"
                                                              "XDG-DESKTOP-PORTAL handle screen scaling\n"
                                                              "differently. Enabling this option will\n"
                                                              "determine the current screen scaling and\n"
                                                              "apply that to the screenshot in ksnip."));

	mSnippingCursorColorLabel->setText(tr("Snipping Area cursor color") + QLatin1Literal(":"));
	mSnippingCursorColorLabel->setToolTip(tr("Sets the color of the snipping area\n"
	                                         "cursor. Change requires ksnip restart to\n"
	                                         "take effect."));
	mSnippingCursorColorButton->setMinimumWidth(fixedButtonSize);
	mSnippingCursorColorButton->setToolTip(mSnippingCursorColorLabel->toolTip());
	mSnippingCursorSizeLabel->setText(tr("Snipping Area cursor thickness") + QLatin1Literal(":"));
	mSnippingCursorSizeLabel->setToolTip(tr("Sets the thickness of the snipping area\n"
	                                        "cursor. Change requires ksnip restart to\n"
	                                        "take effect."));
	mSnippingCursorSizeCombobox->setMinimumWidth(fixedButtonSize);
	mSnippingCursorSizeCombobox->setToolTip(mSnippingCursorSizeLabel->toolTip());

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->setColumnMinimumWidth(0, 10);
	mLayout->addWidget(mCaptureCursorCheckbox, 0, 0, 1, 3);
	mLayout->addWidget(mFreezeImageWhileSnippingCheckbox, 1, 0, 1, 3);
	mLayout->addWidget(mSnippingAreaMagnifyingGlassCheckbox, 2, 1, 1, 3);
	mLayout->addWidget(mSnippingAreaRulersCheckbox, 3, 0, 1, 3);
	mLayout->addWidget(mSnippingAreaPositionAndSizeInfoCheckbox, 4, 0, 1, 3);
	mLayout->addWidget(mForceGenericWaylandCheckbox, 5, 0, 1, 3);
	mLayout->addWidget(mScaleGenericWaylandScreenshotsCheckbox, 6, 0, 1, 3);
	mLayout->setRowMinimumHeight(7, 15);
	mLayout->addWidget(mSnippingCursorColorLabel, 8, 0, 1, 2);
	mLayout->addWidget(mSnippingCursorColorButton, 8, 2, Qt::AlignLeft);
	mLayout->addWidget(mSnippingCursorSizeLabel, 9, 0, 1, 2);
	mLayout->addWidget(mSnippingCursorSizeCombobox, 9, 2, Qt::AlignLeft);

	setTitle(tr("Image Grabber"));
	setLayout(mLayout);
}

void ImageGrabberSettings::freezeImageWhileSnippingStateChanged()
{
	mSnippingAreaMagnifyingGlassCheckbox->setEnabled(mFreezeImageWhileSnippingCheckbox->isChecked());
}

void ImageGrabberSettings::loadConfig()
{
	mFreezeImageWhileSnippingCheckbox->setChecked(mConfig->freezeImageWhileSnippingEnabled());
	mFreezeImageWhileSnippingCheckbox->setEnabled(!mConfig->isFreezeImageWhileSnippingEnabledReadOnly());
	mSnippingAreaMagnifyingGlassCheckbox->setChecked(mConfig->snippingAreaMagnifyingGlassEnabled());
	mSnippingAreaMagnifyingGlassCheckbox->setEnabled(!mConfig->isSnippingAreaMagnifyingGlassEnabledReadOnly());
	mCaptureCursorCheckbox->setChecked(mConfig->captureCursor());
	mSnippingAreaRulersCheckbox->setChecked(mConfig->snippingAreaRulersEnabled());
	mSnippingAreaPositionAndSizeInfoCheckbox->setChecked(mConfig->snippingAreaPositionAndSizeInfoEnabled());
    mForceGenericWaylandCheckbox->setChecked(mConfig->forceGenericWaylandEnabled());
    mForceGenericWaylandCheckbox->setEnabled(!mConfig->isForceGenericWaylandEnabledReadOnly());
    mScaleGenericWaylandScreenshotsCheckbox->setChecked(mConfig->scaleGenericWaylandScreenshotsEnabled());
    mScaleGenericWaylandScreenshotsCheckbox->setEnabled(!mConfig->isScaleGenericWaylandScreenshotEnabledReadOnly());
	mSnippingCursorColorButton->setColor(mConfig->snippingCursorColor());
	mSnippingCursorSizeCombobox->setValue(mConfig->snippingCursorSize());

	freezeImageWhileSnippingStateChanged();
}
