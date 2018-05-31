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

#include "ToolPicker.h"

ToolPicker::ToolPicker()
{
    init();

    setToolButtonStyle(Qt::ToolButtonIconOnly);
}

void ToolPicker::setTool(PaintMode tool)
{
    auto action = mActionToTool.key(tool);
    setDefaultAction(action);
    mSelectedTool = tool;
}

PaintMode ToolPicker::tool() const
{
    return mSelectedTool;
}

void ToolPicker::init()
{
    CustomMenu *menu = new CustomMenu();

    auto action = new QAction(tr("Pen"), this);
    action->setIcon(IconLoader::loadIcon(QStringLiteral("pen")));
    action->setShortcut(Qt::Key_P);
    connect(action, &QAction::triggered, [this]()
    {
        selectTool(PaintMode::Pen);
    });
    mActionToTool[action] = PaintMode::Pen;
    menu->addAction(action);

    action = new QAction(tr("Marker"), this);
    action->setIcon(IconLoader::loadIcon(QStringLiteral("marker")));
    action->setShortcut(Qt::Key_B);
    connect(action, &QAction::triggered, [this]()
    {
        selectTool(PaintMode::Marker);
    });
    mActionToTool[action] = PaintMode::Marker;
    menu->addAction(action);

    action = new QAction(tr("Rect"), this);
    action->setIcon(IconLoader::loadIcon(QStringLiteral("rect")));
    action->setShortcut(Qt::Key_R);
    connect(action, &QAction::triggered, [this]()
    {
        selectTool(PaintMode::Rect);
    });
    mActionToTool[action] = PaintMode::Rect;
    menu->addAction(action);

    action = new QAction(tr("Ellipse"), this);
    action->setIcon(IconLoader::loadIcon(QStringLiteral("ellipse")));
    action->setShortcut(Qt::Key_E);
    connect(action, &QAction::triggered, [this]()
    {
        selectTool(PaintMode::Ellipse);
    });
    mActionToTool[action] = PaintMode::Ellipse;
    menu->addAction(action);

    action = new QAction(tr("Line"), this);
    action->setIcon(IconLoader::loadIcon(QStringLiteral("line")));
    action->setShortcut(Qt::Key_L);
    connect(action, &QAction::triggered, [this]()
    {
        selectTool(PaintMode::Line);
    });
    mActionToTool[action] = PaintMode::Line;
    menu->addAction(action);

    action = new QAction(tr("Arrow"), this);
    action->setIcon(IconLoader::loadIcon(QStringLiteral("arrow")));
    action->setShortcut(Qt::Key_A);
    connect(action, &QAction::triggered, [this]()
    {
        selectTool(PaintMode::Arrow);
    });
    mActionToTool[action] = PaintMode::Arrow;
    menu->addAction(action);

    action = new QAction(tr("Text"), this);
    action->setIcon(IconLoader::loadIcon(QStringLiteral("text")));
    action->setShortcut(Qt::Key_T);
    connect(action, &QAction::triggered, [this]()
    {
        selectTool(PaintMode::Text);
    });
    mActionToTool[action] = PaintMode::Text;
    menu->addAction(action);

    action = new QAction(tr("Number"), this);
    action->setIcon(IconLoader::loadIcon(QStringLiteral("number")));
    action->setShortcut(Qt::Key_N);
    connect(action, &QAction::triggered, [this]()
    {
        selectTool(PaintMode::Number);
    });
    mActionToTool[action] = PaintMode::Number;
    menu->addAction(action);

    action = new QAction(tr("Erase"), this);
    action->setIcon(IconLoader::loadIcon(QStringLiteral("eraser")));
    action->setShortcut(Qt::Key_D);
    connect(action, &QAction::triggered, [this]()
    {
        selectTool(PaintMode::Erase);
    });
    mActionToTool[action] = PaintMode::Erase;
    menu->addAction(action);

    action = new QAction(tr("Select"), this);
    action->setIcon(IconLoader::loadIcon(QStringLiteral("select")));
    action->setShortcut(Qt::Key_S);
    connect(action, &QAction::triggered, [this]()
    {
        selectTool(PaintMode::Select);
    });
    mActionToTool[action] = PaintMode::Select;
    menu->addAction(action);

    setMenu(menu);
}

void ToolPicker::selectTool(PaintMode tool)
{
    mSelectedTool = tool;
    emit toolSelected(tool);
}
