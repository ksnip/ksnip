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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

#include "MainWindow.h"
#include "src/widgets/ColorComboBox.h"
#include "src/widgets/NumericComboBox.h"
#include "src/backend/KsnipConfig.h"
#include "src/backend/StringManip.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    SettingsDialog ( MainWindow *parent = 0 );

public slots:
    void browseButtonClicked();
    void okButtonClicked();
    void cancelButtonClicked();

private:
    MainWindow      *mParent;
    QVBoxLayout     *mMainLayout;
    QGroupBox       *mApplicationSettingsGroupbox;
    QGroupBox       *mImageGrabberGroupbox;
    QGroupBox       *mPenSettingsGroupbox;
    QGroupBox       *mMarkerSettingsGroupbox;
    QGridLayout     *mApplicationSettingsLayout;
    QGridLayout     *mImageGrabberLayout;
    QGridLayout     *mPenSettingsLayout;
    QGridLayout     *mMarkerSettingsLayout;
    QHBoxLayout     *mButtonLayout;
    QCheckBox       *mAlwaysCopyToClipboardCheckbox;
    QCheckBox       *mPromptToSaveBeforeExitCheckbox;
    QCheckBox       *mSaveKsnipPositionCheckbox;
    QCheckBox       *mSaveKsnipToolSelectionCheckbox;
    QLineEdit       *mSaveLocationLineEdit;
    QLabel          *mCaptureDelayLabel;
    QLabel          *mSaveLocationLabel;
    QLabel          *mPenColorLabel;
    QLabel          *mPenSizeLabel;
    QLabel          *mMarkerColorLabel;
    QLabel          *mMarkerSizeLabel;
    NumericComboBox *mPenSizeCombobox;
    NumericComboBox *mMarkerSizeCombobox;
    NumericComboBox *mCaptureDelayCombobox;
    QPushButton     *mBrowseButton;
    QPushButton     *mOkButton;
    QPushButton     *mCancelButton;
    ColorComboBox   *mPenColorCombobox;
    ColorComboBox   *mMarkerColorCombobox;
    void loadSettings();
    void saveSettings();
    void initGui();
};

#endif // SETTINGSDIALOG_H
