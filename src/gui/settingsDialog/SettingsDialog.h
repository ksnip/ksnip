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

#ifndef KSNIP_SETTINGSDIALOG_H
#define KSNIP_SETTINGSDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include <QStackedLayout>
#include <QApplication>

#include "AnnotationSettings.h"
#include "ApplicationSettings.h"
#include "ImageGrabberSettings.h"
#include "HotKeySettings.h"
#include "SaverSettings.h"
#include "StickerSettings.h"
#include "TrayIconSettings.h"
#include "SnippingAreaSettings.h"
#include "WatermarkSettings.h"
#include "src/gui/settingsDialog/uploader/UploaderSettings.h"
#include "src/gui/settingsDialog/uploader/ImgurUploaderSettings.h"
#include "src/gui/settingsDialog/uploader/ScriptUploaderSettings.h"
#include "src/gui/settingsDialog/uploader/FtpUploaderSettings.h"
#include "src/gui/settingsDialog/actions/ActionsSettings.h"
#include "src/gui/settingsDialog/plugins/PluginsSettings.h"
#include "src/backend/config/IConfig.h"
#include "src/common/provider/scaledSizeProvider/IScaledSizeProvider.h"

class SettingsDialog : public QDialog
{
	Q_OBJECT
public:
	explicit SettingsDialog(
			const QList<CaptureModes> &captureModes,
			const QSharedPointer<IConfig> &config,
			const QSharedPointer<IScaledSizeProvider> &scaledSizeProvider,
			const QSharedPointer<IDirectoryPathProvider> &directoryPathProvider,
			const QSharedPointer<IFileDialogService> &fileDialogService,
			const QSharedPointer<IPlatformChecker> &platformChecker,
			const QSharedPointer<IPluginFinder> &pluginFinder,
			QWidget *parent);
	~SettingsDialog() override;

private:
	QSharedPointer<IConfig> mConfig;
	QSharedPointer<IScaledSizeProvider> mScaledSizeProvider;
	QPushButton *mOkButton;
	QPushButton *mCancelButton;
	QWidget *mEmptyWidget;
	ApplicationSettings *mApplicationSettings;
	ImageGrabberSettings *mImageGrabberSettings;
	ImgurUploaderSettings *mImgurUploaderSettings;
	ScriptUploaderSettings *mScriptUploaderSettings;
	HotKeySettings *mHotKeySettings;
	AnnotationSettings *mAnnotationSettings;
	UploaderSettings *mUploaderSettings;
	SaverSettings *mSaverSettings;
	StickerSettings *mStickerSettings;
	TrayIconSettings *mTrayIconSettings;
	SnippingAreaSettings *mSnippingAreaSettings;
	WatermarkSettings *mWatermarkSettings;
	ActionsSettings *mActionsSettings;
	FtpUploaderSettings *mFtpUploaderSettings;
	PluginsSettings *mPluginsSettings;
	QLineEdit *mSearchSettingsLineEdit;
	QTreeWidget *mTreeWidget;
	QStackedLayout *mStackedLayout;
	QList<QTreeWidgetItem*> mNavigatorItems;

	void saveSettings();
	void initGui();

	bool filterNavigatorItem(QTreeWidgetItem *navigatorItem, const QString &filterString);
	bool settingsPageContainsFilterString(QWidget *settingsPage, const QString &filterString);

private slots:
	void switchTab();
	void filterSettings(const QString &filterString);
	void cancelClicked();
	void okClicked();
};

#endif // KSNIP_SETTINGSDIALOG_H
