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

ImageGrabberSettings::ImageGrabberSettings(const QSharedPointer<IConfig> &config) :
		mCaptureCursorCheckbox(new QCheckBox(this)),
		mHideMainWindowDuringScreenshotCheckbox(new QCheckBox(this)),
		mShowMainWindowAfterTakingScreenshotCheckbox(new QCheckBox(this)),
		mForceGenericWaylandCheckbox(new QCheckBox(this)),
		mScaleGenericWaylandScreenshotsCheckbox(new QCheckBox(this)),
		mImplicitCaptureDelayLabel(new QLabel(this)),
		mImplicitCaptureDelaySpinBox(new CustomSpinBox(0, 2000, this)),
		mLayout(new QGridLayout(this)),
		mConfig(config)
{
	Q_ASSERT(mConfig != nullptr);

	initGui();
	loadConfig();
}

void ImageGrabberSettings::saveSettings()
{
	mConfig->setHideMainWindowDuringScreenshot(mHideMainWindowDuringScreenshotCheckbox->isChecked());
	mConfig->setCaptureCursor(mCaptureCursorCheckbox->isChecked());
	mConfig->setShowMainWindowAfterTakingScreenshotEnabled(mShowMainWindowAfterTakingScreenshotCheckbox->isChecked());
	mConfig->setForceGenericWaylandEnabled(mForceGenericWaylandCheckbox->isChecked());
	mConfig->setScaleGenericWaylandScreenshots(mScaleGenericWaylandScreenshotsCheckbox->isChecked());
	mConfig->setImplicitCaptureDelay(mImplicitCaptureDelaySpinBox->value());
}

void ImageGrabberSettings::initGui()
{
	mCaptureCursorCheckbox->setText(tr("Capture mouse cursor on screenshot"));
	mCaptureCursorCheckbox->setToolTip(tr("Should mouse cursor be visible on\n"
	                                      "screenshots."));

	mShowMainWindowAfterTakingScreenshotCheckbox->setText(tr("Show Main Window after capturing screenshot"));
	mShowMainWindowAfterTakingScreenshotCheckbox->setToolTip(tr("Show Main Window after capturing a new screenshot\n"
															 	   "when the Main Window was hidden or minimize."));

    mForceGenericWaylandCheckbox->setText(tr("Force Generic Wayland (xdg-desktop-portal) Screenshot"));
    mForceGenericWaylandCheckbox->setToolTip(tr("GNOME and KDE Plasma support their own Wayland\n"
                                                   "and the Generic XDG-DESKTOP-PORTAL screenshots.\n"
                                                   "Enabling this option will force KDE Plasma and\n"
                                                   "GNOME to use the XDG-DESKTOP-PORTAL screenshots.\n"
                                                   "Change in this option require a ksnip restart."));

    mScaleGenericWaylandScreenshotsCheckbox->setText(tr("Scale Generic Wayland (xdg-desktop-portal) Screenshots"));
    mScaleGenericWaylandScreenshotsCheckbox->setToolTip(tr("Generic Wayland implementations that use\n"
                                                              "XDG-DESKTOP-PORTAL handle screen scaling\n"
                                                              "differently. Enabling this option will\n"
                                                              "determine the current screen scaling and\n"
                                                              "apply that to the screenshot in ksnip."));

	mHideMainWindowDuringScreenshotCheckbox->setText(tr("Hide Main Window during screenshot"));
	mHideMainWindowDuringScreenshotCheckbox->setToolTip(tr("Hide Main Window when capturing a new screenshot."));

	mImplicitCaptureDelayLabel->setText(tr("Implicit capture delay") + QLatin1String(":"));
	mImplicitCaptureDelayLabel->setToolTip(tr("This delay is used when no delay was selected in\n"
												  "the UI, it allows ksnip to hide before taking\n"
												  "a screenshot. This value is not applied when\n"
												  "ksnip was already minimized. Reducing this value\n"
												  "can have the effect that ksnip's main window is\n"
												  "visible on the screenshot."));

	mImplicitCaptureDelaySpinBox->setSuffix(QLatin1String("ms"));
	mImplicitCaptureDelaySpinBox->setToolTip(mImplicitCaptureDelayLabel->toolTip());
	mImplicitCaptureDelaySpinBox->setSingleStep(10);

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->setColumnMinimumWidth(0, 10);
	mLayout->addWidget(mCaptureCursorCheckbox, 0, 0, 1, 3);
	mLayout->addWidget(mShowMainWindowAfterTakingScreenshotCheckbox, 1, 0, 1, 3);
	mLayout->addWidget(mHideMainWindowDuringScreenshotCheckbox, 2, 0, 1, 3);
	mLayout->addWidget(mForceGenericWaylandCheckbox, 3, 0, 1, 3);
	mLayout->addWidget(mScaleGenericWaylandScreenshotsCheckbox, 4, 0, 1, 3);
	mLayout->setRowMinimumHeight(5, 15);
	mLayout->addWidget(mImplicitCaptureDelayLabel, 6, 0, 1, 1);
	mLayout->addWidget(mImplicitCaptureDelaySpinBox, 6, 1, Qt::AlignLeft);

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
	mImplicitCaptureDelaySpinBox->setValue(mConfig->implicitCaptureDelay());
}
