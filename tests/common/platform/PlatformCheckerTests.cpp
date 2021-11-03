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

void PlatformCheckerTests::isX11_Should_ReturnTrue_WhenX11InEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);
	
	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-X11-somethingElse");
			});

	EXPECT_CALL(*commandRunnerMock, isEnvironmentVariableSet(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return false;
			});
	
	PlatformChecker platformChecker(commandRunnerMock);
	
	// act
	auto result = platformChecker.isX11();
	
	// assert
	QCOMPARE(result, true);
}

void PlatformCheckerTests::isX11_Should_ReturnFalse_WhenX11NotInEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Wayland-somethingElse");
			});

	EXPECT_CALL(*commandRunnerMock, isEnvironmentVariableSet(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return false;
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isX11();

	// assert
	QCOMPARE(result, false);
}

void PlatformCheckerTests::isWayland_Should_ReturnTrue_WhenWaylandInEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Wayland-somethingElse");
			});

	EXPECT_CALL(*commandRunnerMock, isEnvironmentVariableSet(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return false;
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isWayland();

	// assert
	QCOMPARE(result, true);
}

void PlatformCheckerTests::isWayland_Should_ReturnFalse_WhenWaylandNotInEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-X11-somethingElse");
			});

	EXPECT_CALL(*commandRunnerMock, isEnvironmentVariableSet(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return false;
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isWayland();

	// assert
	QCOMPARE(result, false);
}

void PlatformCheckerTests::isKde_Should_ReturnTrue_WhenKdeInEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Kde-somethingElse");
			});

	EXPECT_CALL(*commandRunnerMock, isEnvironmentVariableSet(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return false;
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isKde();

	// assert
	QCOMPARE(result, true);
}

void PlatformCheckerTests::isKde_Should_ReturnFalse_WhenKdeNotInEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Gnome-somethingElse");
			});

	EXPECT_CALL(*commandRunnerMock, isEnvironmentVariableSet(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return false;
			});

	EXPECT_CALL(*commandRunnerMock, readFile(testing::_))
			.WillRepeatedly([=](const QString &path) {
				return QString();
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isKde();

	// assert
	QCOMPARE(result, false);
}

void PlatformCheckerTests::isGnome_Should_ReturnTrue_WhenGnomeInEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Gnome-somethingElse");
			});

	EXPECT_CALL(*commandRunnerMock, isEnvironmentVariableSet(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return false;
			});

	EXPECT_CALL(*commandRunnerMock, readFile(testing::_))
			.WillRepeatedly([=](const QString &path) {
				return QString();
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isGnome();

	// assert
	QCOMPARE(result, true);
}

void PlatformCheckerTests::isGnome_Should_ReturnTrue_WhenUnityInEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Unity-somethingElse");
			});

	EXPECT_CALL(*commandRunnerMock, isEnvironmentVariableSet(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return false;
			});

	EXPECT_CALL(*commandRunnerMock, readFile(testing::_))
			.WillRepeatedly([=](const QString &path) {
				return QString();
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isGnome();

	// assert
	QCOMPARE(result, true);
}

void PlatformCheckerTests::isGnome_Should_ReturnFalse_WhenGnomeOrUnityNotInEnvVar()
{
	// arrange
	auto commandRunnerMock = QSharedPointer<CommandRunnerMock>(new CommandRunnerMock);

	EXPECT_CALL(*commandRunnerMock, getEnvironmentVariable(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return QLatin1String("Test123-Kde-somethingElse");
			});

	EXPECT_CALL(*commandRunnerMock, isEnvironmentVariableSet(testing::_))
			.WillRepeatedly([=](const QString &variable) {
				return false;
			});

	PlatformChecker platformChecker(commandRunnerMock);

	// act
	auto result = platformChecker.isGnome();

	// assert
	QCOMPARE(result, false);
}

TEST_MAIN(PlatformCheckerTests)
