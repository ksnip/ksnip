/*
 *  Copyright (C) 2016 Damir Porobic <damir.porobic@gmx.com>
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

SettingsDialog::SettingsDialog(
		const QList<CaptureModes> &captureModes,
		const QSharedPointer<IConfig> &config,
		const QSharedPointer<IScaledSizeProvider> &scaledSizeProvider,
		const QSharedPointer<IDirectoryPathProvider> &directoryPathProvider,
		const QSharedPointer<IFileDialogService> &fileDialogService,
		const QSharedPointer<IPlatformChecker> &platformChecker,
		const QSharedPointer<IPluginFinder> &pluginFinder,
		QWidget *parent) :
	QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
	mOkButton(new QPushButton),
	mCancelButton(new QPushButton),
	mTreeWidget(new QTreeWidget),
	mStackedLayout(new QStackedLayout),
	mConfig(config),
	mScaledSizeProvider(scaledSizeProvider),
	mSettingsFilter(new SettingsFilter()),
	mEmptyWidget(new QWidget()),
	mApplicationSettings(new ApplicationSettings(mConfig, fileDialogService)),
	mImageGrabberSettings(new ImageGrabberSettings(mConfig)),
	mImgurUploaderSettings(new ImgurUploaderSettings(mConfig)),
	mScriptUploaderSettings(new ScriptUploaderSettings(mConfig, fileDialogService)),
	mAnnotationSettings(new AnnotationSettings(mConfig, mScaledSizeProvider)),
	mHotKeySettings(new HotKeySettings(captureModes, platformChecker, mConfig)),
	mUploaderSettings(new UploaderSettings(mConfig)),
	mSaverSettings(new SaverSettings(mConfig, fileDialogService)),
	mStickerSettings(new StickerSettings(mConfig, directoryPathProvider)),
	mTrayIconSettings(new TrayIconSettings(captureModes, mConfig)),
	mSnippingAreaSettings(new SnippingAreaSettings(mConfig, mScaledSizeProvider)),
	mWatermarkSettings(new WatermarkSettings(mConfig, mScaledSizeProvider)),
	mActionsSettings(new ActionsSettings(captureModes, platformChecker, mConfig)),
	mPluginsSettings(new PluginsSettings(mConfig, fileDialogService, pluginFinder)),
	mSearchSettingsLineEdit(new QLineEdit(this)),
	mFtpUploaderSettings(new FtpUploaderSettings(mConfig))
{
	setWindowTitle(QApplication::applicationName() + QLatin1String(" - ") + tr("Settings"));

	initGui();

	connect(mTreeWidget, &QTreeWidget::itemSelectionChanged, this, &SettingsDialog::switchTab);
	connect(mSearchSettingsLineEdit, &QLineEdit::textChanged, this, &SettingsDialog::filterSettings);
}

SettingsDialog::~SettingsDialog()
{
	delete mOkButton;
	delete mCancelButton;
	delete mTreeWidget;
	delete mStackedLayout;
	delete mEmptyWidget;
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
	delete mActionsSettings;
	delete mFtpUploaderSettings;
	delete mPluginsSettings;
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
	mActionsSettings->saveSettings();
	mFtpUploaderSettings->saveSettings();
	mPluginsSettings->saveSettings();
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
	mStackedLayout->addWidget(mFtpUploaderSettings);
	mStackedLayout->addWidget(mScriptUploaderSettings);
	mStackedLayout->addWidget(mAnnotationSettings);
	mStackedLayout->addWidget(mStickerSettings);
	mStackedLayout->addWidget(mWatermarkSettings);
	mStackedLayout->addWidget(mHotKeySettings);
	mStackedLayout->addWidget(mActionsSettings);
	mStackedLayout->addWidget(mPluginsSettings);
	mStackedLayout->addWidget(mEmptyWidget);

	auto application = new QTreeWidgetItem(mTreeWidget, { tr("Application") });
	auto saver = new QTreeWidgetItem(application, { tr("Saver") });
	auto trayIcon = new QTreeWidgetItem(application, { tr("Tray Icon") });
	auto imageGrabber = new QTreeWidgetItem(mTreeWidget, { tr("Image Grabber") });
	auto snippingArea = new QTreeWidgetItem(imageGrabber, { tr("Snipping Area") });
	auto uploader = new QTreeWidgetItem(mTreeWidget, { tr("Uploader") });
	auto imgurUploader = new QTreeWidgetItem(uploader, { tr("Imgur Uploader") });
	auto ftpUploader = new QTreeWidgetItem(uploader, { tr("FTP Uploader") });
	auto scriptUploader = new QTreeWidgetItem(uploader, { tr("Script Uploader") });
	auto annotator = new QTreeWidgetItem(mTreeWidget, { tr("Annotator") });
	auto stickers = new QTreeWidgetItem(annotator, { tr("Stickers") });
	auto watermark = new QTreeWidgetItem(annotator, { tr("Watermark") });
	auto hotkeys = new QTreeWidgetItem(mTreeWidget, { tr("HotKeys") });
	auto actions = new QTreeWidgetItem(mTreeWidget, { tr("Actions") });
	auto plugins = new QTreeWidgetItem(mTreeWidget, { tr("Plugins") });

	mNavigatorItems.append(application);
	mNavigatorItems.append(saver);
	mNavigatorItems.append(trayIcon);
	mNavigatorItems.append(imageGrabber);
	mNavigatorItems.append(snippingArea);
	mNavigatorItems.append(uploader);
	mNavigatorItems.append(imgurUploader);
	mNavigatorItems.append(ftpUploader);
	mNavigatorItems.append(scriptUploader);
	mNavigatorItems.append(annotator);
	mNavigatorItems.append(stickers);
	mNavigatorItems.append(watermark);
	mNavigatorItems.append(hotkeys);
	mNavigatorItems.append(actions);
	mNavigatorItems.append(plugins);

	mTreeWidget->addTopLevelItem(application);
	mTreeWidget->addTopLevelItem(imageGrabber);
	mTreeWidget->addTopLevelItem(uploader);
	mTreeWidget->addTopLevelItem(annotator);
	mTreeWidget->addTopLevelItem(hotkeys);
	mTreeWidget->addTopLevelItem(actions);
	mTreeWidget->addTopLevelItem(plugins);
	mTreeWidget->setHeaderHidden(true);
	mNavigatorItems[0]->setSelected(true);
	mTreeWidget->setFixedWidth(mTreeWidget->minimumSizeHint().width() + mScaledSizeProvider->scaledWidth(100));
	mTreeWidget->expandAll();

	mSearchSettingsLineEdit->setPlaceholderText(tr("Search Settings..."));
	mSearchSettingsLineEdit->setFixedWidth(mTreeWidget->width());
	mSearchSettingsLineEdit->setClearButtonEnabled(true);

	auto settingsNavigationLayout = new QVBoxLayout();
	settingsNavigationLayout->addWidget(mSearchSettingsLineEdit);
	settingsNavigationLayout->addWidget(mTreeWidget);

	auto listAndStackLayout = new QHBoxLayout;
	listAndStackLayout->addLayout(settingsNavigationLayout);
	listAndStackLayout->addLayout(mStackedLayout);

	auto mainLayout = new QVBoxLayout();
	mainLayout->addLayout(listAndStackLayout);
	mainLayout->addLayout(buttonLayout);

	setLayout(mainLayout);
}

void SettingsDialog::switchTab()
{
	if (mTreeWidget->selectedItems().empty()) {
		mStackedLayout->setCurrentIndex(mNavigatorItems.size());
	} else {
		mStackedLayout->setCurrentIndex(mNavigatorItems.indexOf(mTreeWidget->currentItem()));
	}
}

void SettingsDialog::filterSettings(const QString &filterString)
{
	mSettingsFilter->filterSettings(filterString, mTreeWidget, [this](QTreeWidgetItem *treeWidgetItem) {
		return mStackedLayout->itemAt(mNavigatorItems.indexOf(treeWidgetItem))->widget();
	});
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
