/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#include "CaptureModePicker.h"

CaptureModePicker::CaptureModePicker(const QList<CaptureModes> &captureModes)
{
    init(captureModes);

    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    setButtonText(tr("New"));
}

void CaptureModePicker::setCaptureMode(CaptureModes mode)
{
    for(auto action : mCaptureActions) {
	    if (action->data().value<CaptureModes>() == mode) {
		    setDefaultAction(action);
		    mSelectedCaptureMode = mode;
		    return;
	    }
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
	    auto action = createAction(
				tr("Rectangular Area"),
				tr("Draw a rectangular area with your mouse"),
				QStringLiteral("drawRect.svg"),
				CaptureModes::RectArea,
				QKeySequence(Qt::SHIFT + Qt::Key_R));
        menu->addAction(action);
    }

	if (isCaptureModeSupported(captureModes, CaptureModes::LastRectArea)) {
		auto action = createAction(
			tr("Last Rectangular Area"),
			tr("Capture a screenshot of the last selected rectangular area"),
			QStringLiteral("lastRect.svg"),
			CaptureModes::LastRectArea,
			QKeySequence(Qt::SHIFT + Qt::Key_L));
		menu->addAction(action);
	}

    if (isCaptureModeSupported(captureModes, CaptureModes::FullScreen)) {
        auto action = createAction(
				tr("Full Screen (All Monitors)"),
				tr("Capture full screen including all monitors"),
				QStringLiteral("fullScreen.svg"),
				CaptureModes::FullScreen,
				QKeySequence(Qt::SHIFT + Qt::Key_F));
        menu->addAction(action);
    }

    if (isCaptureModeSupported(captureModes, CaptureModes::CurrentScreen)) {
	    auto action = createAction(
	    		tr("Current Screen"),
	    		tr("Capture screen where the mouse is located"),
	    		QStringLiteral("currentScreen.svg"),
	    		CaptureModes::CurrentScreen,
				QKeySequence(Qt::SHIFT + Qt::Key_M));
        menu->addAction(action);
    }

    if (isCaptureModeSupported(captureModes, CaptureModes::ActiveWindow)) {
	    auto action = createAction(
	    		tr("Active Window"),
	    		tr("Capture window that currently has focus"),
	    		QStringLiteral("activeWindow.svg"),
	    		CaptureModes::ActiveWindow,
				QKeySequence(Qt::SHIFT + Qt::Key_A));
        menu->addAction(action);
    }

    if (isCaptureModeSupported(captureModes, CaptureModes::WindowUnderCursor)) {
        auto action = createAction(
        		tr("Window Under Cursor"),
				tr("Capture that is currently under the mouse cursor"),
				QStringLiteral("windowUnderCursor.svg"),
				CaptureModes::WindowUnderCursor,
				QKeySequence(Qt::SHIFT + Qt::Key_U));
        menu->addAction(action);
    }

    if (isCaptureModeSupported(captureModes, CaptureModes::Portal)) {
        auto action = createAction(
                tr("Screenshot Portal"),
                tr("Uses the screenshot Portal for taking screenshot"),
                QStringLiteral("wayland.svg"),
                CaptureModes::Portal,
                QKeySequence(Qt::SHIFT + Qt::Key_T));
        menu->addAction(action);
    }

    if (!mCaptureActions.isEmpty()) {
        setDefaultAction(mCaptureActions.first());
    }
    setMenu(menu);
}

bool CaptureModePicker::isCaptureModeSupported(const QList<CaptureModes> &captureModes, CaptureModes captureMode) const
{
    return captureModes.contains(captureMode);
}

QAction *CaptureModePicker::createAction(const QString &text, const QString &tooltip, const QString &iconName, CaptureModes captureMode, const QKeySequence &shortcut)
{
    auto action = new QAction(this);
    action->setIconText(text);
    action->setToolTip(tooltip);
	action->setIcon(IconLoader::load(iconName));
	action->setShortcut(shortcut);
	action->setData(static_cast<int>(captureMode));
    connect(action, &QAction::triggered, [this, captureMode]() { selectCaptureMode(captureMode); } );
	mCaptureActions.append(action);
    return action;
}

void CaptureModePicker::selectCaptureMode(CaptureModes mode)
{
    mSelectedCaptureMode = mode;
    emit captureModeSelected(mode);
}

QList<QAction*> CaptureModePicker::captureActions() const
{
	return mCaptureActions;
}
