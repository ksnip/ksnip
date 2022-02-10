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

#ifndef KSNIP_PLUGINMANAGER_H
#define KSNIP_PLUGINMANAGER_H

#include <QSharedPointer>

#include "IPluginManager.h"
#include "IPluginLoader.h"
#include "PluginInfo.h"
#include "src/backend/config/IConfig.h"
#include "src/logging/ILogger.h"
#include "src/common/helper/EnumTranslator.h"

class PluginManager : public IPluginManager
{
public:
	explicit PluginManager(const QSharedPointer<IConfig> &config, const QSharedPointer<IPluginLoader> &loader, const QSharedPointer<ILogger> &logger);
	~PluginManager() = default;
	bool isAvailable(PluginType type) const override;
	QSharedPointer<QObject> get(PluginType type) const override;
	QString getPath(PluginType type) const override;

private:
	QSharedPointer<IConfig> mConfig;
	QSharedPointer<IPluginLoader> mLoader;
	QSharedPointer<ILogger> mLogger;
	QMap<PluginType, QSharedPointer<QObject>> mPluginMap;
	QMap<PluginType, QString> mPluginPathMap;

	void loadPlugins();
};

#endif //KSNIP_PLUGINMANAGER_H
