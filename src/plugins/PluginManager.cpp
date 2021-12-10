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

#include "PluginManager.h"

PluginManager::PluginManager(const QSharedPointer<IConfig> &config, const QSharedPointer<IPluginLoader> &loader, const QSharedPointer<ILogger> &logger) :
	mConfig(config),
	mLoader(loader),
	mLogger(logger)
{
	loadPlugins();
}

bool PluginManager::isAvailable(PluginType type)  const
{
	return mPluginMap.contains(type);
}

void PluginManager::loadPlugins()
{
	auto pluginInfos = mConfig->pluginInfos();

	for (const auto& pluginInfo : pluginInfos) {
		auto plugin = mLoader->load(pluginInfo.path());
		if(plugin.isNull()) {
			mLogger->log(QString("Unable to load plugin %1 of type %2").arg(pluginInfo.path(), EnumTranslator::instance()->toString(pluginInfo.type())));
		} else {
			mPluginMap[pluginInfo.type()] = plugin;
		}
	}
}

QSharedPointer<QObject> PluginManager::get(PluginType type) const
{
	if(isAvailable(type)) {
		return mPluginMap[type];
	} else {
		mLogger->log(QString("Unavailable plugin type requested %1").arg(EnumTranslator::instance()->toString(type)));

		return {};
	}
}
