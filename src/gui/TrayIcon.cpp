/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#include "TrayIcon.h"

TrayIcon::TrayIcon(QObject *parent) : QSystemTrayIcon(parent)
{
	setIcon(QPixmap(":/icons/ksnip.svg"));

	mShowEditorAction = new QAction(tr("Show Editor"), this);
	connect(mShowEditorAction, &QAction::triggered, this, &TrayIcon::showEditorTriggered);
	connect(this, &QSystemTrayIcon::activated, this, &TrayIcon::activated);
}

void TrayIcon::setupMenu()
{
	mMenu.addAction(mShowEditorAction);
	mMenu.addSeparator();
	mMenu.addAction(mNewCaptureAction);
	mMenu.addAction(mOpenAction);
	mMenu.addAction(mSaveAction);
	mMenu.addAction(mCopyAction);
	mMenu.addAction(mUploadAction);
	mMenu.addSeparator();
	mMenu.addAction(mQuitAction);
	setContextMenu(&mMenu);
}

TrayIcon::~TrayIcon()
{
	delete mShowEditorAction;
}

void TrayIcon::setNewCaptureAction(QAction *action)
{
	mNewCaptureAction = action;
}

void TrayIcon::setOpenAction(QAction *action)
{
	mOpenAction = action;
}

void TrayIcon::setSaveAction(QAction *action)
{
	mSaveAction = action;
}

void TrayIcon::setCopyAction(QAction *action)
{
	mCopyAction = action;
}

void TrayIcon::setUploadAction(QAction *action)
{
	mUploadAction = action;
}

void TrayIcon::setQuitAction(QAction *action)
{
	mQuitAction = action;
}

void TrayIcon::setEnabled(bool enabled)
{
	if(enabled) {
		setupMenu();
		show();
	} else {
		hide();
	}
}

void TrayIcon::showInfoToast(const QString &title, const QString &message)
{
	showMessage(title, message, QSystemTrayIcon::Information);
}

void TrayIcon::showWarningToast(const QString &title, const QString &message)
{
	showMessage(title, message, QSystemTrayIcon::Warning);
}

void TrayIcon::showCriticalToast(const QString &title, const QString &message)
{
	showMessage(title, message, QSystemTrayIcon::Critical);
}

void TrayIcon::activated(ActivationReason reason) const
{
	if(reason != ActivationReason::Context) {
		emit showEditorTriggered();
	}
}
