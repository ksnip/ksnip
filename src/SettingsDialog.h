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
#include <QGroupBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSettings>

#include "MainWindow.h"
#include "ColorComboBox.h"
#include "SizeComboBox.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    SettingsDialog(MainWindow *parent = 0);
        
public slots:
    void okButtonClicked();
    void cancelButtonClicked();

private:
    MainWindow    *mParent;
    QVBoxLayout   *mMainLayout;
    QGroupBox     *mApplicationSettingsGroupbox;
    QGroupBox     *mPenSettingsGroupbox;
    QGroupBox     *mMarkerSettingsGroupbox;
    QVBoxLayout   *mApplicationSettingsLayout;
    QGridLayout   *mPenSettingsLayout;
    QGridLayout   *mMarkerSettingsLayout;
    QHBoxLayout   *mButtonLayout;
    QCheckBox     *mAlwaysCopyToClipboardCheckbox;
    QCheckBox     *mPromptToSaveBeforeExitCheckbox;
    QCheckBox     *mSaveKsnipPositionCheckbox;
    QCheckBox     *mSaveKsnipToolSelectionCheckbox;
    QLabel        *mPenColorLabel;
    QLabel        *mPenSizeLabel;
    QLabel        *mMarkerColorLabel;
    QLabel        *mMarkerSizeLabel;
    ColorComboBox *mPenColorCombobox;
    SizeComboBox  *mPenSizeCombobox;
    ColorComboBox *mMarkerColorCombobox;
    SizeComboBox  *mMarkerSizeCombobox;
    QPushButton   *mOkButton;
    QPushButton   *mCancelButton;
    void loadSettings();
    void saveSettings();
    void createCheckboxes();
    void createLabels();
    void createCombobox();
    void createButtons();
    void createLayouts();
};

#endif // SETTINGSDIALOG_H
