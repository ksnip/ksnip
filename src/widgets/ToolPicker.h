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

#ifndef KSNIP_TOOLPICKER_H
#define KSNIP_TOOLPICKER_H

#include <QAction>

#include "src/widgets/CustomToolButton.h"
#include "src/common/loader/IconLoader.h"
#include "src/painter/PaintModes.h"

class ToolPicker : public CustomToolButton
{
Q_OBJECT

public:
    explicit ToolPicker();
    ~ToolPicker() = default;
    void setTool(Painter::Modes tool);
    Painter::Modes tool() const;

signals:
    void toolSelected(Painter::Modes tool) const;

private:
    Painter::Modes mSelectedTool;
    QHash<QAction *, Painter::Modes> mActionToTool;

    void init();
    void selectTool(Painter::Modes tool);
};

#endif //KSNIP_TOOLPICKER_H
