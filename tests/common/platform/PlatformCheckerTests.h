/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_PLATFORMCHECKERTESTS_H
#define KSNIP_PLATFORMCHECKERTESTS_H

#include <QtTest>

class PlatformCheckerTests : public QObject
{
	Q_OBJECT
private slots:
	void isX11_Should_ReturnTrue_WhenX11InEnvVar();
	void isX11_Should_ReturnFalse_WhenX11NotInEnvVar();
	void isWayland_Should_ReturnTrue_WhenWaylandInEnvVar();
	void isWayland_Should_ReturnFalse_WhenWaylandNotInEnvVar();
	void isKde_Should_ReturnTrue_WhenKdeInEnvVar();
	void isKde_Should_ReturnFalse_WhenKdeNotInEnvVar();
	void isGnome_Should_ReturnTrue_WhenGnomeInEnvVar();
	void isGnome_Should_ReturnTrue_WhenUnityInEnvVar();
	void isGnome_Should_ReturnFalse_WhenGnomeOrUnityNotInEnvVar();
	void isSnap_Should_ReturnTrue_WhenSnapEnvVarSet();
	void isSnap_Should_ReturnFalse_WhenSnapEnvVarNotSet();
	void gnomeVersion_Should_ReturnGnomeVersion_WhenGnomeAndVersionFileExists();
	void gnomeVersion_Should_ReturnMinusOne_WhenNotGnomeButVersionFileExists();
	void gnomeVersion_Should_ReturnMinusOne_WhenGnomeButVersionFileDoesNotExists();
};

#endif //KSNIP_PLATFORMCHECKERTESTS_H
