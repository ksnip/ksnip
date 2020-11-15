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

ImageGrabberSettings::ImageGrabberSettings(KsnipConfig *config) :
	mCaptureCursorCheckbox(new QCheckBox(this)),
	mHideMainWindowDuringScreenshotCheckbox(new QCheckBox(this)),
	mShowMainWindowAfterTakingScreenshotCheckbox(new QCheckBox(this)),
	mForceGenericWaylandCheckbox(new QCheckBox(this)),
	mScaleGenericWaylandScreenshotsCheckbox(new QCheckBox(this)),
	mLayout(new QGridLayout(this)),
	mConfig(config)
{
	Q_ASSERT(mConfig != nullptr);

	initGui();
	loadConfig();
}

ImageGrabberSettings::~ImageGrabberSettings()
{
	delete mCaptureCursorCheckbox;
	delete mHideMainWindowDuringScreenshotCheckbox;
	delete mShowMainWindowAfterTakingScreenshotCheckbox;
	delete mForceGenericWaylandCheckbox;
	delete mScaleGenericWaylandScreenshotsCheckbox;
	delete mLayout;
}

void ImageGrabberSettings::saveSettings()
{
	mConfig->setHideMainWindowDuringScreenshot(mHideMainWindowDuringScreenshotCheckbox->isChecked());
	mConfig->setCaptureCursor(mCaptureCursorCheckbox->isChecked());
	mConfig->setShowMainWindowAfterTakingScreenshotEnabled(mShowMainWindowAfterTakingScreenshotCheckbox->isChecked());
	mConfig->setForceGenericWaylandEnabled(mForceGenericWaylandCheckbox->isChecked());
	mConfig->setScaleGenericWaylandScreenshots(mScaleGenericWaylandScreenshotsCheckbox->isChecked());
}

void ImageGrabberSettings::initGui()
{
	mCaptureCursorCheckbox->setText(tr("Capture mouse cursor on screenshot"));
	mCaptureCursorCheckbox->setToolTip(tr("Should mouse cursor be visible on\n"
	                                      "screenshots."));

	mShowMainWindowAfterTakingScreenshotCheckbox->setText(tr("Show Main Window after capturing screenshot"));
	mShowMainWindowAfterTakingScreenshotCheckbox->setToolTip(tr("Show Main Window after capturing a new screenshot\n"
															 	   "when the Main Window was hidden or minimized."));

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

	mHideMainWindowDuringScreenshotCheckbox->setText(tr("Hide Main Window during screenshot"));
	mHideMainWindowDuringScreenshotCheckbox->setToolTip(tr("Hide Main Window when capturing a new screenshot."));

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->setColumnMinimumWidth(0, 10);
	mLayout->addWidget(mCaptureCursorCheckbox, 0, 0, 1, 3);
	mLayout->addWidget(mShowMainWindowAfterTakingScreenshotCheckbox, 1, 0, 1, 3);
	mLayout->addWidget(mHideMainWindowDuringScreenshotCheckbox, 2, 0, 1, 3);
	mLayout->addWidget(mForceGenericWaylandCheckbox, 3, 0, 1, 3);
	mLayout->addWidget(mScaleGenericWaylandScreenshotsCheckbox, 4, 0, 1, 3);

	setTitle(tr("Image Grabber"));
	setLayout(mLayout);
}

void ImageGrabberSettings::loadConfig()
{
	mHideMainWindowDuringScreenshotCheckbox->setChecked(mConfig->hideMainWindowDuringScreenshot());
	mCaptureCursorCheckbox->setChecked(mConfig->captureCursor());
	mShowMainWindowAfterTakingScreenshotCheckbox->setChecked(mConfig->showMainWindowAfterTakingScreenshotEnabled());
	mForceGenericWaylandCheckbox->setChecked(mConfig->forceGenericWaylandEnabled());
	mForceGenericWaylandCheckbox->setEnabled(!mConfig->isForceGenericWaylandEnabledReadOnly());
	mScaleGenericWaylandScreenshotsCheckbox->setChecked(mConfig->scaleGenericWaylandScreenshotsEnabled());
	mScaleGenericWaylandScreenshotsCheckbox->setEnabled(!mConfig->isScaleGenericWaylandScreenshotEnabledReadOnly());
}
