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

#include "SettingsDialog.h"

SettingsDialog::SettingsDialog() : QDialog(),
                                   mMainLayout( new QVBoxLayout),
                                   mApplicationSettingsGroupbox ( new QGroupBox ),
                                   mApplicationSettingsLayout ( new QVBoxLayout ),
                                   mAlwaysCopyToClipboardCheckbox ( new QCheckBox ),
                                   mPromptToSaveBeforeExitCheckbox ( new QCheckBox ),
                                   mSaveKsnipPositionCheckbox ( new QCheckBox ),
                                   mSaveKsnipSelectionCheckbox ( new QCheckBox )
{
    setWindowTitle("ksnip - " + tr("Settings"));
    
    createCheckboxes();
    createLayouts();
    
    this->setLayout(mMainLayout);
}

void SettingsDialog::createCheckboxes()
{
    mAlwaysCopyToClipboardCheckbox->setText(tr("Always copy capture to clipboard."));
    mAlwaysCopyToClipboardCheckbox->setCheckState(Qt::Unchecked);
    
    mPromptToSaveBeforeExitCheckbox->setText(tr("Prompt to save before exiting ksnip."));
    mPromptToSaveBeforeExitCheckbox->setCheckState(Qt::Unchecked);
    
    mSaveKsnipPositionCheckbox->setText(tr("Save ksnip position on move and load on startup."));
    mSaveKsnipPositionCheckbox->setCheckState(Qt::Checked);
    
    mSaveKsnipSelectionCheckbox->setText(tr("Save ksnip tool selection and load on startup."));
    mSaveKsnipSelectionCheckbox->setCheckState(Qt::Checked);
}

void SettingsDialog::createLayouts()
{
    mApplicationSettingsLayout->addWidget(mAlwaysCopyToClipboardCheckbox);
    mApplicationSettingsLayout->addWidget(mPromptToSaveBeforeExitCheckbox);
    mApplicationSettingsLayout->addWidget(mSaveKsnipPositionCheckbox);
    mApplicationSettingsLayout->addWidget(mSaveKsnipSelectionCheckbox);
    mApplicationSettingsLayout->addStretch(1);
    
    mApplicationSettingsGroupbox->setTitle(tr("Application Settings"));
    mApplicationSettingsGroupbox->setLayout(mApplicationSettingsLayout);
    
    mMainLayout->addWidget(mApplicationSettingsGroupbox);
    mMainLayout->addStretch(1);
    mMainLayout->addSpacing(12);
}