/*
 * Copyright (C) 2022 Damir Porobic <damir.porobic@gmx.com>
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

#include "WindowsPluginLoader.h"

WindowsPluginLoader::WindowsPluginLoader(const QSharedPointer<ILogger> &logger) : 
	PluginLoader(logger),
	mLogger(logger)
{

}

QObject *WindowsPluginLoader::load(const QString &path) const 
{
	// Under Windows the 3rd Party Dlls are next to the plugin in the same directory
	// in order to find them we set the current directory to the plugin directory
	auto currentDir = QDir::current();
	auto pluginDir = QFileInfo(path).path();
	auto isDirectoryChanged = QDir::setCurrent(pluginDir);

	if(!isDirectoryChanged) {
		mLogger->log(QString("Unable to change to plugin directory %1").arg(pluginDir));
	}

	auto plugin = PluginLoader::load(path);

	// Return previous current directory
	QDir::setCurrent(currentDir.absolutePath());

	return plugin;
}
