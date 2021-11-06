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
	void isX11_Should_ReturnTrue_When_X11InEnvVar();
	void isX11_Should_ReturnFalse_When_X11NotInEnvVar();
	void isWayland_Should_ReturnTrue_When_WaylandInEnvVar();
	void isWayland_Should_ReturnFalse_When_WaylandNotInEnvVar();
	void isKde_Should_ReturnTrue_When_KdeInEnvVar();
	void isKde_Should_ReturnFalse_When_KdeNotInEnvVar();
	void isGnome_Should_ReturnTrue_When_GnomeInEnvVar();
	void isGnome_Should_ReturnTrue_When_UnityInEnvVar();
	void isGnome_Should_ReturnFalse_When_GnomeOrUnityNotInEnvVar();
	void isSnap_Should_ReturnTrue_When_SnapEnvVarSet();
	void isSnap_Should_ReturnFalse_When_SnapEnvVarNotSet();
	void gnomeVersion_Should_ReturnGnomeVersion_When_GnomeAndVersionFileExists();
	void gnomeVersion_Should_ReturnMinusOne_When_NotGnomeButVersionFileExists();
	void gnomeVersion_Should_ReturnMinusOne_When_GnomeButVersionFileDoesNotExists();
	void isX11_Should_CallCommandRunnerOnlyOnce_When_CalledMultipleTimes();
	void isWayland_Should_CallCommandRunnerOnlyOnce_When_CalledMultipleTimes();
	void isKde_Should_CallCommandRunnerOnlyOnce_When_CalledMultipleTimes();
	void isGnome_Should_CallCommandRunnerOnlyOnce_When_CalledMultipleTimes();
	void isSnap_Should_CallCommandRunnerOnlyOnce_When_CalledMultipleTimes();
	void gnomeVersion_Should_CallCommandRunnerOnlyOnce_When_CalledMultipleTimes();
};

#endif //KSNIP_PLATFORMCHECKERTESTS_H
