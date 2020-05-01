/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "X11ErrorLogger.h"

X11ErrorLogger::X11ErrorLogger()
{
	XSetErrorHandler(errorHandler);
}

int X11ErrorLogger::errorHandler(Display *d, XErrorEvent *e)
{
	Q_UNUSED(d);
	switch (e->error_code) {
		case BadAccess:
			qCritical("Unable to assign Global Hotkey, key sequence already in use by other Application");
			break;
		default:
			qCritical("Unknown Global Hotkey Error Code: %s", qPrintable(QString::number(e->error_code)));
			break;
	}
	return 1;
}

