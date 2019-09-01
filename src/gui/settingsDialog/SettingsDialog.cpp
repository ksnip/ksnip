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

SettingsDialog::SettingsDialog(QWidget *parent) :
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
	mOkButton(new QPushButton),
	mCancelButton(new QPushButton),
	mListWidget(new QListWidget),
	mStackedLayout(new QStackedLayout),
	mConfig(KsnipConfig::instance())
{
    setWindowTitle(QApplication::applicationName() + QStringLiteral(" - ") + tr("Settings"));

    initGui();

    connect(mListWidget, &QListWidget::itemSelectionChanged, this, &SettingsDialog::switchTab);
}

SettingsDialog::~SettingsDialog()
{
    delete mOkButton;
    delete mCancelButton;
    delete mListWidget;
    delete mStackedLayout;
    delete mApplicationSettings;
    delete mImageGrabberSettings;
    delete mImgurUploaderSettings;
    delete mAnnotationSettings;
}

void SettingsDialog::saveSettings()
{
    mApplicationSettings->saveSettings();
    mImageGrabberSettings->saveSettings();
    mImgurUploaderSettings->saveSettings();
    mAnnotationSettings->saveSettings();
}

void SettingsDialog::initGui()
{
	mApplicationSettings = new ApplicationSettings(mConfig);
	mImageGrabberSettings = new ImageGrabberSettings(mConfig);
	mImgurUploaderSettings = new ImgurUploaderSettings(mConfig);
    mAnnotationSettings = new AnnotationSettings(mConfig);

    mOkButton->setText(tr("OK"));
    connect(mOkButton, &QPushButton::clicked, this, &SettingsDialog::okClicked);

    mCancelButton->setText(tr("Cancel"));
    connect(mCancelButton, &QPushButton::clicked, this, &SettingsDialog::cancelClicked);

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(mOkButton);
    buttonLayout->addWidget(mCancelButton);
    buttonLayout->setAlignment(Qt::AlignRight);

    mStackedLayout->addWidget(mApplicationSettings);
    mStackedLayout->addWidget(mImageGrabberSettings);
    mStackedLayout->addWidget(mImgurUploaderSettings);
	mStackedLayout->addWidget(mAnnotationSettings);

    mListWidget->addItem(tr("Application"));
    mListWidget->addItem(tr("Image Grabber"));
    mListWidget->addItem(tr("Imgur Uploader"));
    mListWidget->addItem(tr("Annotator"));
    mListWidget->setCurrentRow(0);
    mListWidget->setFixedWidth(mListWidget->sizeHintForColumn(0) + 20);

    auto listAndStackLayout = new QHBoxLayout;
    listAndStackLayout->addWidget(mListWidget);
    listAndStackLayout->addLayout(mStackedLayout);

    auto mainLayout = new QVBoxLayout();
    mainLayout->addLayout(listAndStackLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void SettingsDialog::switchTab()
{
    mStackedLayout->setCurrentIndex(mListWidget->currentRow());
}

void SettingsDialog::okClicked()
{
    saveSettings();
    close();
}

void SettingsDialog::cancelClicked()
{
    close();
}
