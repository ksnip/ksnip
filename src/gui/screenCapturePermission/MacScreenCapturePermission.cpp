/*
 * Copyright (C) 2026 Damir Porobic <https://github.com/damirporobic>
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "MacScreenCapturePermission.h"

#include <QCoreApplication>
#include <QDesktopServices>
#include <QMessageBox>
#include <QPushButton>
#include <QTimer>
#include <QUrl>

#include <CoreGraphics/CoreGraphics.h>

namespace {

QString tr(const char *text)
{
	return QCoreApplication::translate("MacScreenCapturePermission", text);
}

}

bool MacScreenCapturePermission::isGranted()
{
	if (__builtin_available(macOS 10.15, *)) {
		return CGPreflightScreenCaptureAccess();
	}
	// Older systems have no such permission
	return true;
}

void MacScreenCapturePermission::showGuideOnFirstLaunch(const QSharedPointer<IConfig> &config)
{
	if (config->macScreenCapturePermissionGuideShown() || isGranted()) {
		return;
	}

	// Wait until the event loop runs so the main window is already up when the guide appears
	QTimer::singleShot(0, [config]() {
		config->setMacScreenCapturePermissionGuideShown(true);
		if (!isGranted()) {
			askUserToOpenSettings(nullptr, tr("To take screenshots, ksnip needs permission to record your screen."));
		}
	});
}

void MacScreenCapturePermission::showPermissionRequired(QWidget *parent)
{
	askUserToOpenSettings(parent, tr("ksnip does not have permission to record your screen yet, so it cannot take a screenshot."));
}

bool MacScreenCapturePermission::askUserToOpenSettings(QWidget *parent, const QString &intro)
{
	QMessageBox messageBox(parent);
	messageBox.setIcon(QMessageBox::Information);
	messageBox.setWindowTitle(tr("Screen Recording permission needed"));
	messageBox.setText(intro);
	messageBox.setInformativeText(
		tr("Without it macOS only gives ksnip your wallpaper and its own windows.\n\n"
		   "1. Click \"Open System Settings\".\n"
		   "2. In Privacy & Security, open \"Screen & System Audio Recording\" (called \"Screen Recording\" on older macOS versions).\n"
		   "3. Turn on the switch next to ksnip. If ksnip is not listed, click + and add it.\n"
		   "4. If macOS asks, choose \"Quit & Reopen\" so ksnip can start using the permission.\n\n"
		   "If ksnip is already switched on but this message keeps appearing, select ksnip in the list, "
		   "remove it with the minus button, and add it again."));

	auto openSettingsButton = messageBox.addButton(tr("Open System Settings"), QMessageBox::AcceptRole);
	messageBox.addButton(tr("Not Now"), QMessageBox::RejectRole);
	messageBox.setDefaultButton(openSettingsButton);

	messageBox.exec();

	if (messageBox.clickedButton() == openSettingsButton) {
		requestAccessAndOpenSettings();
		return true;
	}
	return false;
}

void MacScreenCapturePermission::requestAccessAndOpenSettings()
{
	// Asking once makes macOS list ksnip under Screen Recording and shows its own prompt
	// the first time. Later calls do nothing, which is why the settings pane is opened too.
	if (__builtin_available(macOS 10.15, *)) {
		CGRequestScreenCaptureAccess();
	}
	QDesktopServices::openUrl(QUrl(QStringLiteral("x-apple.systempreferences:com.apple.preference.security?Privacy_ScreenCapture")));
}
