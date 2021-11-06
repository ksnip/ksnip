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

#include "PlatformCheckerTests.h"

#include "src/common/platform/PlatformChecker.h"

#include "tests/utils/TestRunner.h"
#include "tests/mocks/common/platform/CommandRunnerMock.h"

void PlatformCheckerTests::isX11_Should_ReturnTrue_When_X11InEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);
	
	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(QString("XDG_SESSION_TYPE")))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-X11-somethingElse");
			});
	
	PlatformChecker platformChecker(commandRunnerMock);
	
	// act
	auto result = platformChecker.isX11();
	
	// assert
	QCOMPARE(result, true);
}

void PlatformCheckerTests::isX11_Should_ReturnFalse_When_X11NotInEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(QString("XDG_SESSION_TYPE")))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Wayland-somethingElse");
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isX11();

	// assert
	QCOMPARE(result, false);
}

void PlatformCheckerTests::isWayland_Should_ReturnTrue_When_WaylandInEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(QString("XDG_SESSION_TYPE")))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Wayland-somethingElse");
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isWayland();

	// assert
	QCOMPARE(result, true);
}

void PlatformCheckerTests::isWayland_Should_ReturnFalse_When_WaylandNotInEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(QString("XDG_SESSION_TYPE")))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-X11-somethingElse");
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isWayland();

	// assert
	QCOMPARE(result, false);
}

void PlatformCheckerTests::isKde_Should_ReturnTrue_When_KdeInEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(QString("XDG_CURRENT_DESKTOP")))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Kde-somethingElse");
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isKde();

	// assert
	QCOMPARE(result, true);
}

void PlatformCheckerTests::isKde_Should_ReturnFalse_When_KdeNotInEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(QString("XDG_CURRENT_DESKTOP")))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Gnome-somethingElse");
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isKde();

	// assert
	QCOMPARE(result, false);
}

void PlatformCheckerTests::isGnome_Should_ReturnTrue_When_GnomeInEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(QString("XDG_CURRENT_DESKTOP")))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Gnome-somethingElse");
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isGnome();

	// assert
	QCOMPARE(result, true);
}

void PlatformCheckerTests::isGnome_Should_ReturnTrue_When_UnityInEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(QString("XDG_CURRENT_DESKTOP")))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Unity-somethingElse");
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isGnome();

	// assert
	QCOMPARE(result, true);
}

void PlatformCheckerTests::isGnome_Should_ReturnFalse_When_GnomeOrUnityNotInEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(QString("XDG_CURRENT_DESKTOP")))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Kde-somethingElse");
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isGnome();

	// assert
	QCOMPARE(result, false);
}

void PlatformCheckerTests::isSnap_Should_ReturnTrue_When_SnapEnvVarSet()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, isEnvironmentVariableSet(QString("SNAP")))
			.WillRepeatedly([=](const QString &variable) {
				return true;
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isSnap();

	// assert
	QCOMPARE(result, true);
}

void PlatformCheckerTests::isSnap_Should_ReturnFalse_When_SnapEnvVarNotSet()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, isEnvironmentVariableSet(QString("SNAP")))
			.WillRepeatedly([=](const QString &variable) {
				return false;
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isSnap();

	// assert
	QCOMPARE(result, false);
}

void PlatformCheckerTests::gnomeVersion_Should_ReturnGnomeVersion_When_GnomeAndVersionFileExists()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(QString("XDG_CURRENT_DESKTOP")))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Gnome-somethingElse");
			});

	EXPECT_CALL(*commandRunnerMock, readFile(QString("/usr/share/gnome/gnome-version.xml")))
			.WillRepeatedly([=](const QString &path) {
				return QString("<version>111</version><platform>42</platform>");
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.gnomeVersion();

	// assert
	QCOMPARE(result, 42);
}

void PlatformCheckerTests::gnomeVersion_Should_ReturnMinusOne_When_NotGnomeButVersionFileExists()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(QString("XDG_CURRENT_DESKTOP")))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Kde-somethingElse");
			});

	EXPECT_CALL(*commandRunnerMock, readFile(QString("/usr/share/gnome/gnome-version.xml")))
			.WillRepeatedly([=](const QString &path) {
				return QString("<version>111</version><platform>42</platform>");
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.gnomeVersion();

	// assert
	QCOMPARE(result, -1);
}

void PlatformCheckerTests::gnomeVersion_Should_ReturnMinusOne_When_GnomeButVersionFileDoesNotExists()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(QString("XDG_CURRENT_DESKTOP")))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Gnome-somethingElse");
			});

	EXPECT_CALL(*commandRunnerMock, readFile(QString("/usr/share/gnome/gnome-version.xml")))
			.WillRepeatedly([=](const QString &path) {
				return QString();
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.gnomeVersion();

	// assert
	QCOMPARE(result, -1);
}

void PlatformCheckerTests::isX11_Should_CallCommandRunnerOnlyOnce_When_CalledMultipleTimes()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(testing::_))
			.Times(testing::Exactly(1))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-X11-somethingElse");
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	platformChecker.isX11();
	platformChecker.isX11();
}

void PlatformCheckerTests::isWayland_Should_CallCommandRunnerOnlyOnce_When_CalledMultipleTimes()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(testing::_))
			.Times(testing::Exactly(1))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-X11-somethingElse");
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	platformChecker.isWayland();
	platformChecker.isWayland();
}

void PlatformCheckerTests::isKde_Should_CallCommandRunnerOnlyOnce_When_CalledMultipleTimes()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(testing::_))
			.Times(testing::Exactly(1))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-kde-somethingElse");
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	platformChecker.isKde();
	platformChecker.isKde();
}

void PlatformCheckerTests::isGnome_Should_CallCommandRunnerOnlyOnce_When_CalledMultipleTimes()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(testing::_))
			.Times(testing::Exactly(1))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Gnome-somethingElse");
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	platformChecker.isGnome();
	platformChecker.isGnome();
}

void PlatformCheckerTests::isSnap_Should_CallCommandRunnerOnlyOnce_When_CalledMultipleTimes()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, isEnvironmentVariableSet(QString("SNAP")))
			.Times(testing::Exactly(1))
			.WillRepeatedly([=](const QString &variable) {
				return true;
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	platformChecker.isSnap();
	platformChecker.isSnap();
}

void PlatformCheckerTests::gnomeVersion_Should_CallCommandRunnerOnlyOnce_When_CalledMultipleTimes()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(QString("XDG_CURRENT_DESKTOP")))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Gnome-somethingElse");
			});

	EXPECT_CALL(*commandRunnerMock, readFile(QString("/usr/share/gnome/gnome-version.xml")))
			.WillRepeatedly([=](const QString &path) {
				return QString();
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	platformChecker.gnomeVersion();
	platformChecker.gnomeVersion();
}

TEST_MAIN(PlatformCheckerTests)
