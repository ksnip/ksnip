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
    auto menu = new CustomMenu();

    if (isCaptureModeSupported(captureModes, CaptureModes::RectArea)) {
	    auto action = createAction(tr("Rectangular Area"), tr("Draw a rectangular area with your mouse"), QStringLiteral("drawRect.svg"), CaptureModes::RectArea);
        menu->addAction(action);
    }

    if (isCaptureModeSupported(captureModes, CaptureModes::FullScreen)) {
        auto
	        action = createAction(tr("Full Screen (All Monitors)"), tr("Capture full screen including all monitors"), QStringLiteral("fullScreen.svg"), CaptureModes::FullScreen);
        menu->addAction(action);
    }

    if (isCaptureModeSupported(captureModes, CaptureModes::CurrentScreen)) {
	    auto action = createAction(tr("Current Screen"), tr("Capture screen where the mouse is located"), QStringLiteral("currentScreen.svg"), CaptureModes::CurrentScreen);
        menu->addAction(action);
    }

    if (isCaptureModeSupported(captureModes, CaptureModes::ActiveWindow)) {
	    auto action = createAction(tr("Active Window"), tr("Capture window that currently has focus"), QStringLiteral("activeWindow.svg"), CaptureModes::ActiveWindow);
        menu->addAction(action);
    }

    if (isCaptureModeSupported(captureModes, CaptureModes::WindowUnderCursor)) {
        auto action = createAction(tr("Window Under Cursor"),
                                   tr("Capture that is currently under the mouse cursor"),
                                   QStringLiteral("windowUnderCursor.svg"),
                                   CaptureModes::WindowUnderCursor);
        menu->addAction(action);
    }

    auto allActions = mActionToCaptureMode.keys();
    if (!allActions.isEmpty()) {
        setDefaultAction(allActions[0]);
    }
    setMenu(menu);
}

bool CaptureModePicker::isCaptureModeSupported(const QList<CaptureModes> &captureModes, CaptureModes captureMode) const
{
    return captureModes.contains(captureMode);
}

QAction *CaptureModePicker::createAction(const QString &text, const QString &tooltip, const QString &iconName, CaptureModes captureMode)
{
    auto action = new QAction(this);
    action->setIconText(text);
    action->setToolTip(tooltip);
	action->setIcon(IconLoader::load(iconName));
    connect(action, &QAction::triggered, [this, captureMode]()
    {
        selectCaptureMode(captureMode);
    });
    mActionToCaptureMode[action] = captureMode;
    return action;
}

void CaptureModePicker::selectCaptureMode(CaptureModes mode)
{
    mSelectedCaptureMode = mode;
    emit captureModeSelected(mode);
}
