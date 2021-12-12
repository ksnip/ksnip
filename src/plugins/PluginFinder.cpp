/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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
 */

#include "PluginFinder.h"

PluginFinder::PluginFinder(const QSharedPointer<IPluginLoader> &loader, const QSharedPointer<IDirectoryService> &directoryService) :
	mLoader(loader),
	mDirectoryService(directoryService)
{

}

QList<PluginInfo> PluginFinder::find(const QString &path) const
{
	auto plugins = QList<PluginInfo>();

	auto pluginsInDirectory = findPluginsInDirectory(path);
	plugins.append(pluginsInDirectory);

	auto childDirectoryInfos = mDirectoryService->childDirectories(path);
	for (const auto& childDirectoryInfo : childDirectoryInfos) {
		auto pluginsInChildDirectory = findPluginsInDirectory(childDirectoryInfo.filePath());
		plugins.append(pluginsInChildDirectory);
	}

	return plugins;
}

QList<PluginInfo> PluginFinder::findPluginsInDirectory(const QString &path) const
{
	auto plugins = QList<PluginInfo>();
	auto childFileInfos = mDirectoryService->childFiles(path);
	for (const auto& childFileInfo : childFileInfos) {
		auto plugin = mLoader->load(childFileInfo.filePath());

		if (plugin != nullptr) {
			auto ocrPlugin = qobject_cast<IPluginOcr*>(plugin);

			if (ocrPlugin != nullptr) {
				PluginInfo pluginInfo(PluginType::Ocr, ocrPlugin->version(), childFileInfo.filePath());
				plugins.append(pluginInfo);
			}
		}
	}
	return plugins;
}
