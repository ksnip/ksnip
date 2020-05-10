/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent, const QList<CaptureModes> &captureModes) :
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
	mOkButton(new QPushButton),
	mCancelButton(new QPushButton),
	mTreeWidget(new QTreeWidget),
	mStackedLayout(new QStackedLayout),
	mConfig(KsnipConfigProvider::instance()),
	mApplicationSettings(new ApplicationSettings(mConfig)),
	mImageGrabberSettings(new ImageGrabberSettings(mConfig)),
	mImgurUploaderSettings(new ImgurUploaderSettings(mConfig)),
	mScriptUploaderSettings(new ScriptUploaderSettings(mConfig)),
	mAnnotationSettings(new AnnotationSettings(mConfig)),
	mHotKeySettings(new HotKeySettings(mConfig, captureModes)),
	mUploaderSettings(new UploaderSettings(mConfig))
{
    setWindowTitle(QApplication::applicationName() + QStringLiteral(" - ") + tr("Settings"));

    initGui();

    connect(mTreeWidget, &QTreeWidget::itemSelectionChanged, this, &SettingsDialog::switchTab);
}

SettingsDialog::~SettingsDialog()
{
    delete mOkButton;
    delete mCancelButton;
    delete mTreeWidget;
    delete mStackedLayout;
    delete mApplicationSettings;
    delete mImageGrabberSettings;
    delete mImgurUploaderSettings;
    delete mAnnotationSettings;
    delete mHotKeySettings;
    delete mUploaderSettings;
}

void SettingsDialog::saveSettings()
{
    mApplicationSettings->saveSettings();
    mImageGrabberSettings->saveSettings();
    mUploaderSettings->saveSettings();
    mImgurUploaderSettings->saveSettings();
    mScriptUploaderSettings->saveSettings();
    mAnnotationSettings->saveSettings();
    mHotKeySettings->saveSettings();
}

void SettingsDialog::initGui()
{
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
    mStackedLayout->addWidget(mUploaderSettings);
    mStackedLayout->addWidget(mImgurUploaderSettings);
    mStackedLayout->addWidget(mScriptUploaderSettings);
	mStackedLayout->addWidget(mAnnotationSettings);
	mStackedLayout->addWidget(mHotKeySettings);

	auto application = new QTreeWidgetItem(mTreeWidget, { tr("Application") });
	auto imageGrabber = new QTreeWidgetItem(mTreeWidget, { tr("Image Grabber") });
	auto uploader = new QTreeWidgetItem(mTreeWidget, { tr("Uploader") });
	auto imgurUploader = new QTreeWidgetItem(uploader, { tr("Imgur Uploader") });
	auto scriptUploader = new QTreeWidgetItem(uploader, { tr("Script Uploader") });
	auto annotator = new QTreeWidgetItem(mTreeWidget, { tr("Annotator") });
	auto hotkeys = new QTreeWidgetItem(mTreeWidget, { tr("HotKeys") });

	mNavigatorItems.append(application);
	mNavigatorItems.append(imageGrabber);
	mNavigatorItems.append(uploader);
	mNavigatorItems.append(imgurUploader);
	mNavigatorItems.append(scriptUploader);
	mNavigatorItems.append(annotator);
	mNavigatorItems.append(hotkeys);

	mTreeWidget->addTopLevelItem(application);
	mTreeWidget->addTopLevelItem(imageGrabber);
	mTreeWidget->addTopLevelItem(uploader);
	mTreeWidget->addTopLevelItem(annotator);
    mTreeWidget->addTopLevelItem(hotkeys);
	mTreeWidget->setHeaderHidden(true);
    mTreeWidget->setItemSelected(mNavigatorItems[0], true);
    mTreeWidget->setFixedWidth(mTreeWidget->minimumSizeHint().width() + ScaledSizeProvider::getScaledWidth(100));
    mTreeWidget->expandAll();

    auto listAndStackLayout = new QHBoxLayout;
    listAndStackLayout->addWidget(mTreeWidget);
    listAndStackLayout->addLayout(mStackedLayout);

    auto mainLayout = new QVBoxLayout();
    mainLayout->addLayout(listAndStackLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void SettingsDialog::switchTab()
{
    mStackedLayout->setCurrentIndex(mNavigatorItems.indexOf(mTreeWidget->currentItem()));
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
