/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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

#if  defined(_WIN32) && defined(QT_NO_DEBUG)
// Prevent starting console in background under windows
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <QApplication>

#include "BuildConfig.h"
#include "src/bootstrapper/BootstrapperFactory.h"

int main(int argc, char** argv)
{
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

    app.setOrganizationName(QLatin1String("ksnip"));
    app.setOrganizationDomain(QLatin1String("ksnip.ksnip.org"));
    app.setApplicationName(QLatin1String("ksnip"));
    app.setApplicationVersion(QLatin1String(KSNIP_VERSION));
    app.setDesktopFileName(QLatin1String("org.ksnip.ksnip.desktop"));

    app.setStyle(KsnipConfigProvider::instance()->applicationStyle());

	BootstrapperFactory bootstrapperFactory;
	return bootstrapperFactory.create()->start(app);
}
