/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef KSNIP_SETTINGSDIALOG_H
#define KSNIP_SETTINGSDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QFontComboBox>
#include <QListWidget>
#include <QGroupBox>
#include <QStackedLayout>
#include <QApplication>
#include <QToolButton>

#include "ApplicationSettings.h"
#include "ImageGrabberSettings.h"
#include "ImgurUploaderSettings.h"
#include "src/widgets/NumericComboBox.h"
#include "src/widgets/ColorButton.h"
#include "backend/config/KsnipConfig.h"
#include "src/common/formatter/FilenameFormatter.h"
#include "src/common/loader/IconLoader.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog() override;

private:
    QCheckBox       *mSmoothPathCheckbox;
    QCheckBox       *mItemShadowCheckbox;
    QLabel          *mTextFontLabel;
    QLabel          *mNumberFontLabel;
    QLabel          *mSmoothFactorLabel;
    NumericComboBox *mSmoothFactorCombobox;
    QFontComboBox   *mTextFontCombobox;
    QFontComboBox   *mNumberFontCombobox;
    QPushButton     *mOkButton;
    QPushButton     *mCancelButton;
    QToolButton     *mTextBoldButton;
    QToolButton     *mTextItalicButton;
    QToolButton     *mTextUnderlineButton;


	ApplicationSettings *mApplicationSettings;
	ImageGrabberSettings *mImageGrabberSettings;
	ImgurUploaderSettings *mImgurUploaderSettings;
    QListWidget *mListWidget;
    QStackedLayout *mStackedLayout;
    KsnipConfig *mConfig;

    void loadSettings();
    void saveSettings();
    void initGui();

private slots:
	void smoothPathCheckboxClicked(bool checked);
};

#endif // KSNIP_SETTINGSDIALOG_H
