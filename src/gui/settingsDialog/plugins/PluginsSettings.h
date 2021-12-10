/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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
 */

#ifndef KSNIP_PLUGINSSETTINGS_H
#define KSNIP_PLUGINSSETTINGS_H

#include <QGroupBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>

#include "src/backend/config/IConfig.h"
#include "src/common/adapter/fileDialog/IFileDialogService.h"
#include "src/common/helper/PathHelper.h"
#include "src/plugins/PluginInfo.h"
#include "src/plugins/IPluginFinder.h"

class PluginsSettings : public QGroupBox
{
	Q_OBJECT
public:
	explicit PluginsSettings(
			const QSharedPointer<IConfig> &config,
			const QSharedPointer<IFileDialogService> &fileDialogService,
			const QSharedPointer<IPluginFinder> &pluginFinder);
	~PluginsSettings() override = default;
	void saveSettings();

private:
	QGridLayout *mLayout;
	QLabel *mPluginPathLabel;
	QLineEdit *mPluginPathLineEdit;
	QPushButton *mBrowseButton;
	QPushButton *mDetectButton;
	QTableWidget *mTableWidget;
	QSharedPointer<IConfig> mConfig;
	QSharedPointer<IFileDialogService> mFileDialogService;
	QSharedPointer<IPluginFinder> mPluginFinder;
	QList<PluginInfo> mDetectedPlugins;

	void initGui();
	void loadConfig();
	void updatePluginTable();
	
private slots:
	void choosePluginDirectory();
	void detectPlugins();
};

#endif //KSNIP_PLUGINSSETTINGS_H
