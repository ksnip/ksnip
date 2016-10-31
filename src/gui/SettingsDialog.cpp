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

SettingsDialog::SettingsDialog( MainWindow *parent ) :
    QDialog( parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint ),
    mParent( parent ),
    mAlwaysCopyToClipboardCheckbox( new QCheckBox ),
    mPromptToSaveBeforeExitCheckbox( new QCheckBox ),
    mSaveKsnipPositionCheckbox( new QCheckBox ),
    mSaveKsnipToolSelectionCheckbox( new QCheckBox ),
    mSaveLocationLineEdit( new QLineEdit),
    mImgurPinLineEdit( new QLineEdit),
    mCaptureDelayLabel( new QLabel ),
    mSaveLocationLabel( new QLabel),
    mImgurUsernameLabel(new QLabel),
    mImgurUsernameValueLabel (new QLabel),
    mImgurGetPinLabel(new QLabel),
    mPenColorLabel( new QLabel ),
    mPenSizeLabel( new QLabel ),
    mMarkerColorLabel( new QLabel ),
    mMarkerSizeLabel( new QLabel ),
    mPenSizeCombobox( new NumericComboBox( 1, 1, 10, this ) ),
    mMarkerSizeCombobox( new NumericComboBox( 10, 2, 11, this ) ),
    mCaptureDelayCombobox( new NumericComboBox( 0, 1, 11, this ) ),
    mBrowseButton(new QPushButton),
    mImgurGetTokenButton( new QPushButton),
    mOkButton( new QPushButton ),
    mCancelButton( new QPushButton ),
    mImgurUploader(new ImgurUploader),
    mListWidget(new QListWidget),
    mStackedLayout (new QStackedLayout)
{
    setWindowTitle( QApplication::applicationName() + " - " + tr( "Settings" ) );

    initGui();

    // We don't want the window to be resizable
    setFixedSize( sizeHint() );

    loadSettings();
    
    connect(mImgurUploader, SIGNAL(tokenUpdated(QString,QString,QString,ImgurUploader::Result)), this, SLOT(imgurTokenUpdated(QString,QString,QString,ImgurUploader::Result)));
    connect(mListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(listSelectionChanged()));
}

//
// Private Functions
//
void SettingsDialog::loadSettings()
{
    if ( KsnipConfig::instance()->alwaysCopyToClipboard() ) {
        mAlwaysCopyToClipboardCheckbox->setCheckState( Qt::Checked );
    }
    else {
        mAlwaysCopyToClipboardCheckbox->setCheckState( Qt::Unchecked );
    }

    if ( KsnipConfig::instance()->promptSaveBeforeExit() ) {
        mPromptToSaveBeforeExitCheckbox->setCheckState( Qt::Checked );
    }
    else {
        mPromptToSaveBeforeExitCheckbox->setCheckState( Qt::Unchecked );
    }

    if ( KsnipConfig::instance()->saveKsnipPosition() ) {
        mSaveKsnipPositionCheckbox->setCheckState( Qt::Checked );
    }
    else {
        mSaveKsnipPositionCheckbox->setCheckState( Qt::Unchecked );
    }

    if ( KsnipConfig::instance()->saveKsnipToolSelection() ) {
        mSaveKsnipToolSelectionCheckbox->setCheckState( Qt::Checked );
    }
    else {
        mSaveKsnipToolSelectionCheckbox->setCheckState( Qt::Unchecked );
    }
    
    mImgurUsernameValueLabel->setText(KsnipConfig::instance()->imgurUsername());

    mPenColorCombobox->setColor( KsnipConfig::instance()->penColor() );
    mPenSizeCombobox->setValue( KsnipConfig::instance()->penSize() );

    mMarkerColorCombobox->setColor( KsnipConfig::instance()->markerColor() );
    mMarkerSizeCombobox->setValue( KsnipConfig::instance()->markerSize() );

    mCaptureDelayCombobox->setValue( KsnipConfig::instance()->captureDelay() / 1000 );
}

void SettingsDialog::saveSettings()
{
    KsnipConfig::instance()->setAlwaysCopyToClipboard( mAlwaysCopyToClipboardCheckbox->isChecked() );

    KsnipConfig::instance()->setPromptSaveBeforeExit( mPromptToSaveBeforeExitCheckbox->isChecked() );

    KsnipConfig::instance()->setSaveKsnipPosition( mSaveKsnipPositionCheckbox->isChecked() );

    KsnipConfig::instance()->setSaveKsnipToolSelection( mSaveKsnipToolSelectionCheckbox->isChecked() );

    KsnipConfig::instance()->setPenColor( mPenColorCombobox->color() );
    KsnipConfig::instance()->setPenSize( mPenSizeCombobox->value() );

    KsnipConfig::instance()->setMarkerColor( mMarkerColorCombobox->color() );
    KsnipConfig::instance()->setMarkerSize( mMarkerSizeCombobox->value() );

    KsnipConfig::instance()->setCaptureDelay( mCaptureDelayCombobox->value() * 1000 );
    
    KsnipConfig::instance()->setSaveDirectory(StringManip::extractPath(mSaveLocationLineEdit->displayText()));
    
    KsnipConfig::instance()->setSaveFilename(StringManip::extractFilename(mSaveLocationLineEdit->displayText()));
    
    KsnipConfig::instance()->setSaveFormat(StringManip::extractFormat(mSaveLocationLineEdit->displayText()));
}

void SettingsDialog::initGui()
{
    // Create Application Settings 
    mAlwaysCopyToClipboardCheckbox->setText( tr( "Always copy capture to clipboard." ) );
    mPromptToSaveBeforeExitCheckbox->setText( tr( "Prompt to save before exiting ksnip." ) );
    mSaveKsnipPositionCheckbox->setText( tr( "Save ksnip position on move and load on startup." ) );
    mSaveKsnipToolSelectionCheckbox->setText( tr( "Save ksnip tool selection and "
                                                  "load on startup." ) );

    mSaveLocationLineEdit->setText(KsnipConfig::instance()->saveDirectory() +
                                   KsnipConfig::instance()->saveFilename() +
                                   KsnipConfig::instance()->saveFormat()
    );
    mSaveLocationLineEdit->setToolTip(tr ("Filename can contain $Y, $M, $D for date and $T for time."));  
    
    // Create Imgur Uploader Settings
    mImgurPinLineEdit->setPlaceholderText( tr( "PIN" ) );
    mImgurPinLineEdit->setToolTip( tr( "Enter imgur Pin which will be exchanged for a token." ) );
    connect(mImgurPinLineEdit, SIGNAL(textChanged(QString)), this, SLOT(imgurPinEntered(QString)));
    
    // Create Labels
    mSaveLocationLabel->setText( tr("Capture save location and filename") + ":");
    mCaptureDelayLabel->setText( tr( "Delay (sec)" ) + ":" );
    mImgurUsernameLabel->setText( tr( "Username" ) + ":" );
    mImgurGetPinLabel->setText("<a href=\"" + mImgurUploader->pinRequestUrl().toString() + "\">Get PIN</a>");
    mImgurGetPinLabel->setTextFormat(Qt::RichText);
    mImgurGetPinLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    mImgurGetPinLabel->setOpenExternalLinks(true);
    mPenColorLabel->setText( tr( "Pen Color" ) + ":" );
    mPenSizeLabel->setText( tr( "Pen Size" ) + ":" );
    mMarkerColorLabel->setText( tr( "Marker Color" )  + ":" );
    mMarkerSizeLabel->setText( tr( "Marker Size" ) + ":" );

    // Setup combo box, to avoid creating the same variable twice and adding once the pen color set
    // then marker color set, we add it this way, in the second run we just add additional colors
    // at specific position so it's ordered
    QStringList colorNames;
    colorNames.append( "Blue" );
    colorNames.append( "Cyan" );
    colorNames.append( "Orange" );
    colorNames.append( "Red" );
    colorNames.append( "Yellow" );
    mMarkerColorCombobox = new ColorComboBox( colorNames, this );

    colorNames.insert( 0, "Black" );
    colorNames.insert( 2, "Brown" );
    colorNames.insert( 4, "Green" );
    colorNames.insert( 5, "Grey" );
    colorNames.insert( 7, "Pink" );
    colorNames.insert( 8, "Purple" );
    colorNames.insert( 10, "White" );
    mPenColorCombobox = new ColorComboBox( colorNames, this );

    // Create Push
    mBrowseButton->setText(tr("Browse"));
    connect(mBrowseButton, SIGNAL(clicked()), this, SLOT(browseButtonClicked()));
    
    mImgurGetTokenButton->setText( tr("Get Token"));
    connect(mImgurGetTokenButton, SIGNAL(clicked()), this, SLOT(getTokenButtonClicked()));
    mImgurGetTokenButton->setEnabled(false);
    
    mOkButton->setText( tr( "OK" ) );
    connect( mOkButton, SIGNAL( clicked() ), this, SLOT( okButtonClicked() ) );

    mCancelButton->setText( tr( "Cancel" ) );
    connect( mCancelButton, SIGNAL( clicked() ), this, SLOT( cancelButtonClicked() ) );

    // Setup application settings layout
    QGridLayout *applicationGrid = new QGridLayout;
    applicationGrid->setAlignment(Qt::AlignTop);
    applicationGrid->addWidget( mAlwaysCopyToClipboardCheckbox, 1, 1, 1, -1 );
    applicationGrid->addWidget( mPromptToSaveBeforeExitCheckbox, 2, 1, 1, -1 );
    applicationGrid->addWidget( mSaveKsnipPositionCheckbox, 3, 1, 1, -1 );
    applicationGrid->addWidget( mSaveKsnipToolSelectionCheckbox, 4, 1, 1, -1 );
    applicationGrid->addWidget( mSaveLocationLabel, 5, 1);
    applicationGrid->addWidget( mSaveLocationLineEdit, 6, 1, 1, 3);
    applicationGrid->addWidget( mBrowseButton, 6, 4);
    
    QGroupBox *applicationGrpBox = new QGroupBox( tr( "Application Settings" ) );
    applicationGrpBox->setLayout( applicationGrid );

    // Setup image grabber layout
    QGridLayout *imageGrabberGrid = new QGridLayout;
    imageGrabberGrid->setAlignment(Qt::AlignTop);
    imageGrabberGrid->addWidget( mCaptureDelayLabel, 0, 1);
    imageGrabberGrid->addWidget( mCaptureDelayCombobox, 0, 2, 1, 3); 
            
    QGroupBox *imageGrabberGrpBox = new QGroupBox( tr( "Image Grabber" ) );
    imageGrabberGrpBox->setLayout( imageGrabberGrid );
    
    // Setup imgur uploader layout
    QGridLayout *imgurUploaderGrid = new QGridLayout;
    imgurUploaderGrid->setAlignment(Qt::AlignTop);
    imgurUploaderGrid->addWidget(mImgurUsernameLabel, 1, 1);
    imgurUploaderGrid->addWidget(mImgurUsernameValueLabel, 1, 2);
    imgurUploaderGrid->addWidget(mImgurGetPinLabel, 1, 4, Qt::AlignCenter);
    imgurUploaderGrid->addWidget(mImgurPinLineEdit, 2, 1, 1, 3);
    imgurUploaderGrid->addWidget(mImgurGetTokenButton, 2, 4);
    
    QGroupBox *imgurUploaderGrpBox = new QGroupBox(tr("Imgur Uploader"));
    imgurUploaderGrpBox->setLayout(imgurUploaderGrid);
    
    // Setup painter layout
    QGridLayout *painterGrid = new QGridLayout;
    painterGrid->setAlignment(Qt::AlignTop);
    painterGrid->addWidget( mPenColorLabel, 1, 1 );
    painterGrid->addWidget( mPenColorCombobox, 1, 2, 1, 3 );
    painterGrid->addWidget( mPenSizeLabel, 2, 1 );
    painterGrid->addWidget( mPenSizeCombobox, 2, 2, 1, 3 );
    painterGrid->addWidget( mMarkerColorLabel, 3, 1 );
    painterGrid->addWidget( mMarkerColorCombobox, 3, 2, 1, 3 );
    painterGrid->addWidget( mMarkerSizeLabel, 4, 1 );
    painterGrid->addWidget( mMarkerSizeCombobox, 4, 2, 1, 3 );
    
    QGroupBox *painterGrpBox = new QGroupBox( tr( "Painter Settings" ) );
    painterGrpBox->setLayout( painterGrid );

    // Setup push button layout
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget( mOkButton );
    buttonLayout->addWidget( mCancelButton );
    buttonLayout->setAlignment( Qt::AlignRight );
    
    // Populate Stacked layout and listview
    mStackedLayout->addWidget(applicationGrpBox);
    mStackedLayout->addWidget(imageGrabberGrpBox);
    mStackedLayout->addWidget(imgurUploaderGrpBox);
    mStackedLayout->addWidget(painterGrpBox);
    
    mListWidget->addItem(tr ("Application"));
    mListWidget->addItem(tr("Image Grabber"));
    mListWidget->addItem(tr("Imgur Uploader"));
    mListWidget->addItem(tr("Painter"));
    mListWidget->setFixedWidth(mListWidget->sizeHintForColumn(0) + 20);
    
    // Setup main window layout
    QHBoxLayout *listAndStackLayout = new QHBoxLayout;
    listAndStackLayout->addWidget(mListWidget);
    listAndStackLayout->addLayout(mStackedLayout);
    
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout( listAndStackLayout );
    mainLayout->addLayout( buttonLayout );
    
    setLayout( mainLayout );
}

//
// Public Slots
//

void SettingsDialog::browseButtonClicked()
{
    mSaveLocationLineEdit->setText( QFileDialog::getOpenFileName(this,
                                    tr("Capture save location"), 
                                    KsnipConfig::instance()->saveDirectory() +
                                    KsnipConfig::instance()->saveFilename() +
                                    KsnipConfig::instance()->saveFormat(), 
                                    tr("All")));
}

void SettingsDialog::getTokenButtonClicked()
{
    mImgurUploader->getAccessToken(mImgurPinLineEdit->text().toUtf8());
    mImgurPinLineEdit->clear();
}

void SettingsDialog::okButtonClicked()
{
    saveSettings();
    close();
}

/*
 * Called when the list view selection has changed, it will change the selected stacked layout
 * providing the effect of switching between the different settings option
 */
void SettingsDialog::listSelectionChanged()
{
    mStackedLayout->setCurrentIndex(mListWidget->currentRow());
}

void SettingsDialog::cancelButtonClicked()
{
    close();
}

void SettingsDialog::imgurPinEntered( QString text )
{
    if (text.length() > 8){
        mImgurGetTokenButton->setEnabled(true);
    }
    else{
        mImgurGetTokenButton->setEnabled(false);
    }
}

void SettingsDialog::imgurTokenUpdated( const QString accessToken, const QString refreshTocken, 
                                        const QString username, ImgurUploader::Result result )
{
    if (result == ImgurUploader::Successful)
    {
        KsnipConfig::instance()->setImgurAccessToken(accessToken);
        KsnipConfig::instance()->setImgurRefreshToken(refreshTocken);
        KsnipConfig::instance()->setImgurUsername(username);
        
        mImgurUsernameValueLabel->setText(username);
    }
}