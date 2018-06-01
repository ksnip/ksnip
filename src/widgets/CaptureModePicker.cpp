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

#include "CaptureModePicker.h"

CaptureModePicker::CaptureModePicker(const QList<CaptureModes> &captureModes)
{
    init(captureModes);

    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    setButtonText(tr("New"));
}

void CaptureModePicker::setCaptureMode(CaptureModes mode)
{
    auto action = mActionToCaptureMode.key(mode, nullptr);
    if (action != nullptr) {
        setDefaultAction(action);
        mSelectedCaptureMode = mode;
    }
}

CaptureModes CaptureModePicker::captureMode() const
{
    return mSelectedCaptureMode;
}

void CaptureModePicker::init(const QList<CaptureModes> &captureModes)
{
    CustomMenu *menu = new CustomMenu();

    if (captureModes.contains(CaptureModes::RectArea)) {
        auto action = new QAction(this);
        action->setIconText(tr("Rectangular Area"));
        action->setToolTip(tr("Draw a rectangular area with your mouse"));
        action->setIcon(IconLoader::loadIcon(QStringLiteral("drawRect")));
        connect(action, &QAction::triggered, [this]()
        {
            selectCaptureMode(CaptureModes::RectArea);
        });
        mActionToCaptureMode[action] = CaptureModes::RectArea;
        menu->addAction(action);
    }

    if (captureModes.contains(CaptureModes::FullScreen)) {
        auto action = new QAction(this);
        action->setIconText(tr("Full Screen (All Monitors)"));
        action->setToolTip(tr("Capture full screen including all monitors"));
        action->setIcon(IconLoader::loadIcon(QStringLiteral("fullScreen")));
        connect(action, &QAction::triggered, [this]()
        {
            selectCaptureMode(CaptureModes::FullScreen);
        });
        mActionToCaptureMode[action] = CaptureModes::FullScreen;
        menu->addAction(action);

    }

    if (captureModes.contains(CaptureModes::CurrentScreen)) {
        auto action = new QAction(this);
        action->setIconText(tr("Current Screen"));
        action->setToolTip(tr("Capture screen where the mouse is located"));
        action->setIcon(IconLoader::loadIcon(QStringLiteral("currentScreen")));
        connect(action, &QAction::triggered, [this]()
        {
            selectCaptureMode(CaptureModes::CurrentScreen);
        });
        mActionToCaptureMode[action] = CaptureModes::CurrentScreen;
        menu->addAction(action);

    }

    if (captureModes.contains(CaptureModes::ActiveWindow)) {
        auto action = new QAction(this);
        action->setIconText(tr("Active Window"));
        action->setToolTip(tr("Capture window that currently has focus"));
        action->setIcon(IconLoader::loadIcon(QStringLiteral("activeWindow")));
        connect(action, &QAction::triggered, [this]()
        {
            selectCaptureMode(CaptureModes::ActiveWindow);
        });
        mActionToCaptureMode[action] = CaptureModes::ActiveWindow;
        menu->addAction(action);
    }

    if (captureModes.contains(CaptureModes::WindowUnderCursor)) {
        auto action = new QAction(this);
        action->setIconText(tr("Window Under Cursor"));
        action->setToolTip(tr("Capture that is currently under the mouse cursor"));
        action->setIcon(IconLoader::loadIcon(QStringLiteral("windowUnderCursor")));
        connect(action, &QAction::triggered, [this]()
        {
            selectCaptureMode(CaptureModes::WindowUnderCursor);
        });
        mActionToCaptureMode[action] = CaptureModes::WindowUnderCursor;
        menu->addAction(action);
    }

    auto allActions = mActionToCaptureMode.keys();
    if (!allActions.isEmpty()) {
        setDefaultAction(allActions[0]);
    }
    setMenu(menu);
}

void CaptureModePicker::selectCaptureMode(CaptureModes mode)
{
    mSelectedCaptureMode = mode;
    emit captureModeSelected(mode);
}
