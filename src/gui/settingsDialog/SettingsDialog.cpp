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
	mUploaderSettings(new UploaderSettings(mConfig)),
	mSaverSettings(new SaverSettings(mConfig)),
	mStickerSettings(new StickerSettings(mConfig)),
	mTrayIconSettings(new TrayIconSettings(mConfig, captureModes)),
	mSnippingAreaSettings(new SnippingAreaSettings(mConfig)),
	mWatermarkSettings(new WatermarkSettings(mConfig))
{
    setWindowTitle(QApplication::applicationName() + QLatin1String(" - ") + tr("Settings"));

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
    delete mSaverSettings;
    delete mStickerSettings;
    delete mTrayIconSettings;
    delete mSnippingAreaSettings;
    delete mWatermarkSettings;
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
    mSaverSettings->saveSettings();
    mStickerSettings->saveSettings();
    mTrayIconSettings->saveSettings();
    mSnippingAreaSettings->saveSettings();
    mWatermarkSettings->saveSettings();
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
    mStackedLayout->addWidget(mSaverSettings);
    mStackedLayout->addWidget(mTrayIconSettings);
    mStackedLayout->addWidget(mImageGrabberSettings);
    mStackedLayout->addWidget(mSnippingAreaSettings);
    mStackedLayout->addWidget(mUploaderSettings);
    mStackedLayout->addWidget(mImgurUploaderSettings);
    mStackedLayout->addWidget(mScriptUploaderSettings);
	mStackedLayout->addWidget(mAnnotationSettings);
	mStackedLayout->addWidget(mStickerSettings);
	mStackedLayout->addWidget(mWatermarkSettings);
	mStackedLayout->addWidget(mHotKeySettings);

	auto application = new QTreeWidgetItem(mTreeWidget, { tr("Application") });
	auto saver = new QTreeWidgetItem(application, { tr("Saver") });
	auto trayIcon = new QTreeWidgetItem(application, { tr("Tray Icon") });
	auto imageGrabber = new QTreeWidgetItem(mTreeWidget, { tr("Image Grabber") });
	auto snippingArea = new QTreeWidgetItem(imageGrabber, { tr("Snipping Area") });
	auto uploader = new QTreeWidgetItem(mTreeWidget, { tr("Uploader") });
	auto imgurUploader = new QTreeWidgetItem(uploader, { tr("Imgur Uploader") });
	auto scriptUploader = new QTreeWidgetItem(uploader, { tr("Script Uploader") });
	auto annotator = new QTreeWidgetItem(mTreeWidget, { tr("Annotator") });
	auto stickers = new QTreeWidgetItem(annotator, { tr("Stickers") });
	auto watermark = new QTreeWidgetItem(annotator, { tr("Watermark") });
	auto hotkeys = new QTreeWidgetItem(mTreeWidget, { tr("HotKeys") });

	mNavigatorItems.append(application);
	mNavigatorItems.append(saver);
	mNavigatorItems.append(trayIcon);
	mNavigatorItems.append(imageGrabber);
	mNavigatorItems.append(snippingArea);
	mNavigatorItems.append(uploader);
	mNavigatorItems.append(imgurUploader);
	mNavigatorItems.append(scriptUploader);
	mNavigatorItems.append(annotator);
	mNavigatorItems.append(stickers);
	mNavigatorItems.append(watermark);
	mNavigatorItems.append(hotkeys);

	mTreeWidget->addTopLevelItem(application);
	mTreeWidget->addTopLevelItem(imageGrabber);
	mTreeWidget->addTopLevelItem(uploader);
	mTreeWidget->addTopLevelItem(annotator);
    mTreeWidget->addTopLevelItem(hotkeys);
	mTreeWidget->setHeaderHidden(true);
    mTreeWidget->setItemSelected(mNavigatorItems[0], true);
    mTreeWidget->setFixedWidth(mTreeWidget->minimumSizeHint().width() + ScaledSizeProvider::scaledWidth(100));
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
