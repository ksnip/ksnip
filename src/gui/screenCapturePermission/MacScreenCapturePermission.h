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

#ifndef KSNIP_MACSCREENCAPTUREPERMISSION_H
#define KSNIP_MACSCREENCAPTUREPERMISSION_H

#include <QCoreApplication>
#include <QSharedPointer>

#include "src/backend/config/IConfig.h"

class QWidget;

/*
 * macOS only gives an app the contents of other windows once the user has granted the
 * Screen Recording permission in System Settings. Without it a capture silently
 * contains only the wallpaper and the app's own windows. This class checks for the
 * permission and walks the user through granting it.
 */
class MacScreenCapturePermission
{
	Q_DECLARE_TR_FUNCTIONS(MacScreenCapturePermission)
public:
	/*
	 * True when ksnip may capture the screen.
	 */
	static bool isGranted();

	/*
	 * Shown once after the first launch when the permission is missing, so the user
	 * does not have to find out by taking a screenshot that comes out blank.
	 */
	static void showGuideOnFirstLaunch(const QSharedPointer<IConfig> &config);

	/*
	 * Shown when the user tries to capture without the permission.
	 */
	static void showPermissionRequired(QWidget *parent);

private:
	static bool askUserToOpenSettings(QWidget *parent, const QString &intro);
	static QString informativeText(const QString &openSettingsLabel);
	static void requestAccessAndOpenSettings();
};

#endif //KSNIP_MACSCREENCAPTUREPERMISSION_H
