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

#include "PluginsSettings.h"

#include <QDebug>

PluginsSettings::PluginsSettings(
		const QSharedPointer<IConfig> &config,
		const QSharedPointer<IFileDialogService> &fileDialogService,
		const QSharedPointer<IPluginFinder> &pluginFinder) :
	mConfig(config),
	mFileDialogService(fileDialogService),
	mPluginFinder(pluginFinder),
	mLayout(new QGridLayout),
	mPluginPathLabel(new QLabel(this)),
	mPluginPathLineEdit(new QLineEdit(this)),
	mBrowseButton(new QPushButton(this)),
	mDetectButton(new QPushButton(this)),
	mTableWidget(new QTableWidget(5, 2, this))
{
	initGui();
	loadConfig();
}

void PluginsSettings::saveSettings()
{
	mConfig->setPluginInfos(mDetectedPlugins);
	mConfig->setPluginPath(mPluginPathLineEdit->text());
}

void PluginsSettings::initGui()
{
	mPluginPathLabel->setText(tr("Plugin directory") + QLatin1String(":"));

	mPluginPathLineEdit->setToolTip(tr("The directory where the plugins are located."));

	mBrowseButton->setText(tr("Browse"));
	connect(mBrowseButton, &QPushButton::clicked, this, &PluginsSettings::choosePluginDirectory);

	mTableWidget->setHorizontalHeaderLabels(QStringList{ tr("Name"), tr("Version") });
	mTableWidget->horizontalHeader()->setStretchLastSection(true);
	mTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	mTableWidget->verticalHeader()->setVisible(false);

	mDetectButton->setText(tr("Detect"));
	connect(mDetectButton, &QPushButton::clicked, this, &PluginsSettings::detectPlugins);

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->addWidget(mPluginPathLabel, 0, 0, 1, 4);
	mLayout->addWidget(mPluginPathLineEdit, 1, 0, 1, 3);
	mLayout->addWidget(mBrowseButton, 1, 3);
	mLayout->addWidget(mTableWidget, 2, 0, 2, 3);
	mLayout->addWidget(mDetectButton, 2, 3);

	setTitle(tr("Plugin Settings"));
	setLayout(mLayout);
}

void PluginsSettings::loadConfig()
{
	mPluginPathLineEdit->setText(mConfig->pluginPath());
	mDetectedPlugins = mConfig->pluginInfos();

	updatePluginTable();
}

void PluginsSettings::choosePluginDirectory()
{
	auto path = mFileDialogService->getExistingDirectory(this, tr("Plugin location"), mConfig->saveDirectory());

	if(!path.isEmpty()) {
		mPluginPathLineEdit->setText(path);
	}
}

void PluginsSettings::detectPlugins()
{
	auto pluginPath = mPluginPathLineEdit->text();
	if (!pluginPath.isEmpty()) {
		mDetectedPlugins = mPluginFinder->find(pluginPath);

		updatePluginTable();
	}
}

void PluginsSettings::updatePluginTable()
{
	auto pluginCount = mDetectedPlugins.count();
	for (auto i = 0; i < pluginCount; i++) {
		auto pluginInfo = mDetectedPlugins[i];
		auto name = new QTableWidgetItem(PathHelper::extractFilename(pluginInfo.path()));
		auto version = new QTableWidgetItem("1.0.1");
		mTableWidget->setItem(i, 0, name);
		mTableWidget->setItem(i, 1, version);
	}
}
