/*
 *  Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#ifndef KSNIP_PATHHELPER_H
#define KSNIP_PATHHELPER_H

#include <QString>
#include <QDateTime>
#include <QFile>
#include <QDir>

class PathHelper
{
public:
    static bool isPathValid(const QString &path);
    static QString extractParentDirectory(const QString &path);
    static QString extractFilename(const QString &path);
    static QString extractFilenameWithFormat(const QString &path);
    static QString extractFormat(const QString &path);
};

#endif // KSNIP_PATHHELPER_H
