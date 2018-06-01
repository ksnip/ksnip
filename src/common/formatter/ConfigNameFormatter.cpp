/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#include "ConfigNameFormatter.h"

QString ConfigNameFormatter::paintTool(const PaintMode tool)
{
    return QStringLiteral("PaintTool_") + QString::number(static_cast<int>(tool));
}

QString ConfigNameFormatter::toolSize(const PaintMode tool)
{
    return QStringLiteral("Painter/") + paintTool(tool) + QStringLiteral("_Size");
}

QString ConfigNameFormatter::toolColor(const PaintMode tool)
{
    return QStringLiteral("Painter/") + paintTool(tool) + QStringLiteral("_Color");
}

QString ConfigNameFormatter::toolFill(PaintMode tool)
{
    return QStringLiteral("Painter/") + paintTool(tool) + QStringLiteral("_Fill");
}
