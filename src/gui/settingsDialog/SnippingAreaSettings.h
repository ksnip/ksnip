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

#ifndef KSNIP_SNIPPINGAREASETTINGS_H
#define KSNIP_SNIPPINGAREASETTINGS_H

#include <QGroupBox>
#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>
#include <QSpinBox>

#include "src/backend/config/KsnipConfig.h"
#include "src/widgets/ColorButton.h"
#include "src/widgets/NumericComboBox.h"
#include "src/common/provider/ScaledSizeProvider.h"

class SnippingAreaSettings : public QGroupBox
{
Q_OBJECT
public:
	explicit SnippingAreaSettings(KsnipConfig *config);
	~SnippingAreaSettings() override;
	void saveSettings();

private:
	QCheckBox *mFreezeImageWhileSnippingCheckbox;
	QCheckBox *mSnippingAreaRulersCheckbox;
	QCheckBox *mSnippingAreaPositionAndSizeInfoCheckbox;
	QCheckBox *mSnippingAreaMagnifyingGlassCheckbox;
	QCheckBox *mAllowResizingRectSelectionCheckbox;
	QCheckBox *mShowSnippingAreaInfoTextCheckbox;
	QLabel *mSnippingCursorSizeLabel;
	QLabel *mSnippingCursorColorLabel;
	QLabel *mSnippingAdornerColorLabel;
	QLabel *mSnippingAreaTransparencyLabel;
	ColorButton *mSnippingCursorColorButton;
	ColorButton *mSnippingAdornerColorButton;
	NumericComboBox *mSnippingCursorSizeCombobox;
	QSpinBox *mSnippingAreaTransparencySpinBox;
	QGridLayout *mLayout;
	KsnipConfig *mConfig;
	void initGui();
	void loadConfig();

private slots:
	void freezeImageWhileSnippingStateChanged();
};


#endif //KSNIP_SNIPPINGAREASETTINGS_H
