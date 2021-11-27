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

#include <QPluginLoader>
#include <QSharedPointer>

#include "IPluginManager.h"
#include "src/backend/config/IConfig.h"
#include "src/logging/ILogger.h"
#include "src/plugins/interfaces/IPluginOcr.h"

class PluginManager : public IPluginManager
{
public:
	explicit PluginManager(const QSharedPointer<IConfig> &config, const QSharedPointer<ILogger> &logger);
	~PluginManager() = default;
	bool isOcrAvailable() const override;
	QString ocr(const QPixmap &pixmap) const override;

private:
	QSharedPointer<IConfig> mConfig;
	QSharedPointer<ILogger> mLogger;
	QSharedPointer<IPluginOcr> mPluginOcr;

	void loadPlugins();
};

#endif //KSNIP_PLUGINMANAGER_H
