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

#include <QDesktopServices>
#include <QMessageBox>
#include <QPushButton>
#include <QTimer>
#include <QUrl>

#include <CoreGraphics/CoreGraphics.h>

bool MacScreenCapturePermission::isGranted()
{
	return CGPreflightScreenCaptureAccess();
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

QString MacScreenCapturePermission::informativeText(const QString &openSettingsLabel)
{
	// Numbers and line breaks are added here so translators only see plain sentences
	QStringList steps;
	steps << tr("Click \"%1\".").arg(openSettingsLabel);
	steps << tr("In Privacy & Security, open \"Screen & System Audio Recording\" (called \"Screen Recording\" on older macOS versions).");
	steps << tr("Turn on the switch next to ksnip. If ksnip is not listed, click + and add it.");
	steps << tr("If macOS asks, choose \"Quit & Reopen\" so ksnip can start using the permission.");

	QStringList paragraphs;
	paragraphs << tr("Without it macOS only gives ksnip your wallpaper and its own windows.");

	QStringList numberedSteps;
	for (auto i = 0; i < steps.count(); ++i) {
		numberedSteps << QStringLiteral("%1. %2").arg(i + 1).arg(steps.at(i));
	}
	paragraphs << numberedSteps.join(QLatin1Char('\n'));

	paragraphs << tr("If ksnip is already switched on but this message keeps appearing, select ksnip in the list, remove it with the minus button, and add it again.");

	return paragraphs.join(QStringLiteral("\n\n"));
}

bool MacScreenCapturePermission::askUserToOpenSettings(QWidget *parent, const QString &intro)
{
	auto openSettingsLabel = tr("Open System Settings");

	QMessageBox messageBox(parent);
	messageBox.setIcon(QMessageBox::Information);
	messageBox.setWindowTitle(tr("Screen Recording permission needed"));
	messageBox.setText(intro);
	messageBox.setInformativeText(informativeText(openSettingsLabel));

	auto openSettingsButton = messageBox.addButton(openSettingsLabel, QMessageBox::AcceptRole);
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
	CGRequestScreenCaptureAccess();
	QDesktopServices::openUrl(QUrl(QStringLiteral("x-apple.systempreferences:com.apple.preference.security?Privacy_ScreenCapture")));
}
