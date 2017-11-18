/*
 *  Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#include "StringFormattingHelper.h"

/*
 * Split the path into sections each divided by forward slash and return
 * everything from begin to the last part just before the filename.
 */
QString StringFormattingHelper::extractPath(const QString& path)
{
    return path.section("/", 0, -2);
}

/*
 * Split the path in section divided by forward slash. Check if the last section
 * contains a dot which could be used as demarcation for the file format, we
 * need to remove it. If no file format was provided, just return the last
 * section.
 */
QString StringFormattingHelper::extractFilename(const QString& path)
{
    if (path.section("/", -1).contains(".")) {
        return path.section("/", -1).section(".", 0, -2);
    } else {
        return path.section("/", -1);
    }
}

/*
 * Split the path in section divided by forward slash. If the last section
 * contains a dot, split it again and return the part after the last dot. If no
 * dot was found, return empty string, we have no file format.
 */
QString StringFormattingHelper::extractFormat(const QString& path)
{
    if (path.section("/", -1).contains(".")) {
        return path.section(".", -1);
    } else {
        return QString();
    }
}

QString StringFormattingHelper::updateTimeAndDate(QString filename)
{
    filename.replace("$Y", QDateTime::currentDateTime().toString("yyyy"));
    filename.replace("$M", QDateTime::currentDateTime().toString("MM"));
    filename.replace("$D", QDateTime::currentDateTime().toString("dd"));
    filename.replace("$T", QDateTime::currentDateTime().toString("hhmmss"));
    return filename;
}

QString StringFormattingHelper::makeUniqueFilename(const QString& path,
                                        const QString& filename,
                                        const QString& exension)
{
    if (!QFile::exists(path + filename + exension)) {
        return path + filename + exension;
    }

    auto i = 1;
    while (QFile::exists(path + filename + "(" + QString::number(i) + ")" + exension)) {
        i++;
    }
    return path + filename + "(" + QString::number(i) + ")" + exension;
}
