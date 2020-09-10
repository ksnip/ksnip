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

#ifndef KSNIP_ANNOTATIONSETTINGS_H
#define KSNIP_ANNOTATIONSETTINGS_H

#include <QGroupBox>
#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>
#include <QFontComboBox>
#include <QToolButton>
#include <QPushButton>

#include "src/backend/config/KsnipConfig.h"
#include "src/backend/WatermarkImageLoader.h"
#include "src/widgets/NumericComboBox.h"
#include "src/common/loader/IconLoader.h"
#include "src/gui/operations/UpdateWatermarkOperation.h"

class AnnotationSettings : public QGroupBox
{
	Q_OBJECT
public:
    explicit AnnotationSettings(KsnipConfig *config);
    ~AnnotationSettings() override;
    void saveSettings();

private:
    QCheckBox *mSmoothPathCheckbox;
    QCheckBox *mItemShadowCheckbox;
    QCheckBox *mRotateWatermarkCheckbox;
	QCheckBox *mRememberToolSelectionCheckbox;
	QLabel *mTextFontLabel;
    QLabel *mNumberFontLabel;
    QLabel *mSmoothFactorLabel;
    QLabel *mWatermarkImageLabel;
    NumericComboBox *mSmoothFactorCombobox;
    QFontComboBox *mTextFontCombobox;
    QFontComboBox *mNumberFontCombobox;
    QToolButton *mTextBoldButton;
    QToolButton *mTextItalicButton;
    QToolButton *mTextUnderlineButton;
    QPushButton *mUpdateWatermarkImageButton;
    QGridLayout *mLayout;
    KsnipConfig *mConfig;
    WatermarkImageLoader mWatermarkImageLoader;

    void initGui();
    void loadConfig();

private slots:
    void smoothPathCheckboxClicked(bool checked);
	void updateWatermarkImageClicked();
};

#endif //KSNIP_ANNOTATIONSETTINGS_H
