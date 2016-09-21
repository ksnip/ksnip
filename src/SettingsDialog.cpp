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

SettingsDialog::SettingsDialog(MainWindow *parent) : 
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint ),
    mMainLayout ( new QVBoxLayout ),
    mApplicationSettingsGroupbox ( new QGroupBox ),
    mPenSettingsGroupbox ( new QGroupBox ),
    mMarkerSettingsGroupbox ( new QGroupBox ),
    mApplicationSettingsLayout ( new QVBoxLayout ),
    mPenSettingsLayout ( new QGridLayout ),
    mMarkerSettingsLayout ( new QGridLayout ),
    mButtonLayout ( new QHBoxLayout ),
    mAlwaysCopyToClipboardCheckbox ( new QCheckBox ),
    mPromptToSaveBeforeExitCheckbox ( new QCheckBox ),
    mSaveKsnipPositionCheckbox ( new QCheckBox ),
    mSaveKsnipToolSelectionCheckbox ( new QCheckBox ),
    mPenColorLabel ( new QLabel ),
    mPenSizeLabel( new QLabel ),
    mMarkerColorLabel ( new QLabel ),
    mMarkerSizeLabel( new QLabel ),
    mPenSizeCombobox( new SizeComboBox ( 1, 1, 10, this ) ),
    mMarkerSizeCombobox ( new SizeComboBox ( 10, 2, 11, this ) ),
    mOkButton ( new QPushButton ),
    mCancelButton ( new QPushButton )
{
    mParent = parent;
    
    setWindowTitle ( "ksnip - " + tr ( "Settings" ) );
    
    createCheckboxes();
    createLabels();
    createCombobox();
    createButtons();
    createLayouts();

    setLayout ( mMainLayout );
    
    setFixedSize(sizeHint());
    
    loadSettings();
}

//
// Public Slots
//

void SettingsDialog::okButtonClicked()
{
    saveSettings();
    close();
}

void SettingsDialog::cancelButtonClicked()
{
    close();
}

//
// Private Functions
//

void SettingsDialog::loadSettings()
{
    QSettings settings;

    if ( mParent->getAlwaysCopyToClipboard() ) {
        mAlwaysCopyToClipboardCheckbox->setCheckState ( Qt::Checked );
    }
    else {
        mAlwaysCopyToClipboardCheckbox->setCheckState ( Qt::Unchecked );
    }

    if ( mParent->getPromptSaveBeforeExit() ) {
        mPromptToSaveBeforeExitCheckbox->setCheckState ( Qt::Checked );
    }
    else {
        mPromptToSaveBeforeExitCheckbox->setCheckState ( Qt::Unchecked );
    }

    if ( mParent->getSaveKsnipPosition() ) {
        mSaveKsnipPositionCheckbox->setCheckState ( Qt::Checked );
    }
    else {
        mSaveKsnipPositionCheckbox->setCheckState ( Qt::Unchecked );
    }

    if ( mParent->getSaveKsnipToolSelection() ) {
        mSaveKsnipToolSelectionCheckbox->setCheckState ( Qt::Checked );
    }
    else {
        mSaveKsnipToolSelectionCheckbox->setCheckState ( Qt::Unchecked );
    }

    mPenColorCombobox->setColor ( mParent->getPenProperties().color() );
    mPenSizeCombobox->setSize ( mParent->getPenProperties().width() );

    mMarkerColorCombobox->setColor ( mParent->getMarkerProperties().color() );
    mMarkerSizeCombobox->setSize ( mParent->getMarkerProperties().width() );   
}

void SettingsDialog::saveSettings()
{
    QSettings settings;

    mParent->setAlwaysCopyToClipboard ( mAlwaysCopyToClipboardCheckbox->isChecked() );

    mParent->setPromptSaveBeforeExit ( mPromptToSaveBeforeExitCheckbox->isChecked() );

    mParent->setSaveKsnipPosition ( mSaveKsnipPositionCheckbox->isChecked() );

    mParent->setSaveKsnipToolSelection ( mSaveKsnipToolSelectionCheckbox->isChecked() );
    
    mParent->setPenProperties(mPenColorCombobox->color(), mPenSizeCombobox->size());
    
    mParent->setMarkerProperties(mMarkerColorCombobox->color(), mMarkerSizeCombobox->size());
}

void SettingsDialog::createCheckboxes()
{
    mAlwaysCopyToClipboardCheckbox->setText ( tr ( "Always copy capture to clipboard." ) );

    mPromptToSaveBeforeExitCheckbox->setText ( tr ( "Prompt to save before exiting ksnip." ) );

    mSaveKsnipPositionCheckbox->setText ( tr( "Save ksnip position on move and load on startup." ));

    mSaveKsnipToolSelectionCheckbox->setText ( tr( "Save ksnip tool selection and load on startup." ));
}

void SettingsDialog::createLabels()
{
    mPenColorLabel->setText ( tr ( "Pen Color" ) );
    mPenSizeLabel->setText( tr ( "Pen Size" ));

    mMarkerColorLabel->setText ( tr ( "Marker Color" ) );
    mMarkerSizeLabel->setText( tr ( "Marker Size" ) );
}

void SettingsDialog::createCombobox()
{
    QStringList colorNames;
    colorNames.append ( "Blue" );  
    colorNames.append ( "Cyan" );
    colorNames.append ( "Orange" );
    colorNames.append ( "Red" );
    colorNames.append ( "Yellow" );
    
    mMarkerColorCombobox = new ColorComboBox(colorNames, this);
    
    colorNames.insert ( 0, "Black" ); 
    colorNames.insert ( 2, "Brown" );
    colorNames.insert ( 4, "Green" );
    colorNames.insert ( 5, "Grey" ); 
    colorNames.insert ( 7, "Pink" ); 
    colorNames.insert ( 8, "Purple" ); 
    colorNames.insert ( 10, "White" ); 
    
    mPenColorCombobox = new ColorComboBox(colorNames, this);
}

void SettingsDialog::createButtons()
{
    mOkButton->setText ( tr ( "OK" ) );
    connect(mOkButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));

    mCancelButton->setText ( tr ( "Cancel" ) );
    connect(mCancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonClicked()));    
}

void SettingsDialog::createLayouts()
{
    mApplicationSettingsLayout->addWidget ( mAlwaysCopyToClipboardCheckbox );
    mApplicationSettingsLayout->addWidget ( mPromptToSaveBeforeExitCheckbox );
    mApplicationSettingsLayout->addWidget ( mSaveKsnipPositionCheckbox );
    mApplicationSettingsLayout->addWidget ( mSaveKsnipToolSelectionCheckbox );
    mApplicationSettingsLayout->addStretch ( 1 );

    mApplicationSettingsGroupbox->setTitle ( tr ( "Application Settings" ) );
    mApplicationSettingsGroupbox->setLayout ( mApplicationSettingsLayout );

    mPenSettingsLayout->addWidget ( mPenColorLabel, 1, 1 );
    mPenSettingsLayout->addWidget ( mPenColorCombobox, 1, 2, 1, 3 );
    mPenSettingsLayout->addWidget( mPenSizeLabel, 2, 1);
    mPenSettingsLayout->addWidget( mPenSizeCombobox, 2, 2, 1, 3);

    mPenSettingsGroupbox->setTitle ( tr ( "Pen Settings" ) );
    mPenSettingsGroupbox->setLayout ( mPenSettingsLayout );

    mMarkerSettingsLayout->addWidget ( mMarkerColorLabel, 1, 1 );
    mMarkerSettingsLayout->addWidget ( mMarkerColorCombobox, 1, 2, 1, 3 );
    mMarkerSettingsLayout->addWidget( mMarkerSizeLabel, 2, 1);
    mMarkerSettingsLayout->addWidget( mMarkerSizeCombobox, 2, 2, 1, 3);

    mMarkerSettingsGroupbox->setTitle ( tr ( "Marker Settings" ) );
    mMarkerSettingsGroupbox->setLayout ( mMarkerSettingsLayout );

    mButtonLayout->addWidget ( mOkButton,  Qt::AlignRight );
    mButtonLayout->addWidget ( mCancelButton, Qt::AlignRight );

    mMainLayout->addWidget ( mApplicationSettingsGroupbox );
    mMainLayout->addWidget ( mPenSettingsGroupbox );
    mMainLayout->addWidget ( mMarkerSettingsGroupbox );
    mMainLayout->addLayout ( mButtonLayout );
    mMainLayout->addStretch ( 1 );
    mMainLayout->addSpacing ( 12 );
}