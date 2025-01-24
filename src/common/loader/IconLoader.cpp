/*
 * Copyright (C) 2017 Damir Porobic <damir.porobic@gmx.com>
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

#include "IconLoader.h"

QIcon IconLoader::load(const QString &name)
{
	return QIcon(QLatin1String(":/icons/") + name);
}

QIcon IconLoader::loadForTheme(const QString& name)
{
    auto type = getThemePrefix();
    return QIcon(QLatin1String(":/icons/") + type + name);
}

QString IconLoader::getThemePrefix()
{
    return isDarkTheme() ? QLatin1String("dark/") : QLatin1String("light/");
}

double IconLoader::getThemeLuma()
{
    auto color = QApplication::palette().window().color();
    return 0.2126 * color.redF() + 0.7152 * color.greenF() + 0.0722 * color.blueF();
}

bool IconLoader::isDarkTheme()
{
    return getThemeLuma() > 0.4;
}
