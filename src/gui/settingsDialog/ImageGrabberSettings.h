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

#ifndef KSNIP_IMAGEGRABBERSETTINGS_H
#define KSNIP_IMAGEGRABBERSETTINGS_H

#include <QGroupBox>
#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>

#include "src/backend/config/KsnipConfig.h"
#include "src/widgets/ColorButton.h"
#include "src/widgets/NumericComboBox.h"

class ImageGrabberSettings : public QGroupBox
{
	Q_OBJECT
public:
	explicit ImageGrabberSettings(KsnipConfig *ksnipConfig);
	~ImageGrabberSettings() override;
	void saveSettings();

private:
	QCheckBox *mCaptureCursorCheckbox;
	QCheckBox *mFreezeImageWhileSnippingCheckbox;
	QCheckBox *mSnippingAreaRulersCheckbox;
	QCheckBox *mSnippingAreaPositionAndSizeInfoCheckbox;
	QCheckBox *mSnippingAreaMagnifyingGlassCheckbox;
	QCheckBox *mForceGenericWaylandCheckbox;
	QCheckBox *mScaleGenericWaylandScreenshotsCheckbox;
	QLabel *mSnippingCursorSizeLabel;
	QLabel *mSnippingCursorColorLabel;
	ColorButton *mSnippingCursorColorButton;
	NumericComboBox *mSnippingCursorSizeCombobox;
	QGridLayout *mLayout;

	KsnipConfig *mConfig;

	void initGui();
	void loadConfig();

private slots:
	void freezeImageWhileSnippingStateChanged();
};

#endif //KSNIP_IMAGEGRABBERSETTINGS_H
