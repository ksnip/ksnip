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

PluginManager::PluginManager(const QSharedPointer<IConfig> &config, const QSharedPointer<ILogger> &logger) :
	mConfig(config),
	mLogger(logger)
{
	loadPlugins();
}

bool PluginManager::isOcrAvailable() const
{
	return !mPluginOcr.isNull();
}

void PluginManager::loadPlugins()
{
	auto pluginOcrPath = mConfig->pluginOcrPath();
	if(!pluginOcrPath.isNull() && !pluginOcrPath.isEmpty()) {
		mLogger->log(QString("Loading OCR Plugin from %1").arg(pluginOcrPath));

		QPluginLoader pluginLoader(pluginOcrPath);
		auto plugin = pluginLoader.instance();

		if(plugin != nullptr) {
			mPluginOcr = QSharedPointer<IPluginOcr>(qobject_cast<IPluginOcr*>(plugin));
		} else {
			mLogger->log(QString("Unable to load OCR Plugin from %1").arg(pluginOcrPath));
		}
	}
}

QString PluginManager::ocr(const QPixmap &pixmap) const
{
	if(isOcrAvailable()) {
		return mPluginOcr->recognize(pixmap);
	} else {
		return {};
	}
}
