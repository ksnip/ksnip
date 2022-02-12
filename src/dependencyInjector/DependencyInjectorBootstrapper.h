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

#ifndef KSNIP_DEPENDENCYINJECTORBOOTSTRAPPER_H
#define KSNIP_DEPENDENCYINJECTORBOOTSTRAPPER_H

#include "DependencyInjector.h"

class DependencyInjectorBootstrapper
{
public:
	DependencyInjectorBootstrapper() = default;
	~DependencyInjectorBootstrapper() = default;

	static void BootstrapCore(DependencyInjector *dependencyInjector);
	static void BootstrapCommandLine(DependencyInjector *dependencyInjector);
	static void BootstrapGui(DependencyInjector *dependencyInjector);

private:
	static void injectConfig(DependencyInjector *dependencyInjector);
	static void injectLogger(DependencyInjector *dependencyInjector);
	static void injectImageGrabber(DependencyInjector *dependencyInjector);
	static void injectFileDialogService(DependencyInjector *dependencyInjector);
	static void injectDirectoryPathProvider(DependencyInjector *dependencyInjector);
	static void injectDesktopServiceAdapter(DependencyInjector *dependencyInjector);
	static void injectScaledSizeProvider(DependencyInjector *dependencyInjector);
	static void injectPluginLoader(DependencyInjector *dependencyInjector);
	static void injectOcrWindowCreator(DependencyInjector *dependencyInjector);
};

#endif //KSNIP_DEPENDENCYINJECTORBOOTSTRAPPER_H
