/*
 * Copyright (C) 2026 Xie Zhuoyang
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

#include "PluginManagerTests.h"

#include <QPointer>

#include "src/logging/NoneLogger.h"
#include "src/plugins/PluginManager.h"

#include "tests/mocks/backend/config/ConfigMock.h"
#include "tests/mocks/plugins/PluginLoaderMock.h"
#include "tests/utils/TestRunner.h"

void PluginManagerTests::Destructor_Should_NotDeletePlugin_When_PluginLoaderOwnsInstance()
{
	// arrange
	auto pluginInfo = PluginInfo(PluginType::Ocr, QLatin1String("1.0"), QLatin1String("/plugins/ocr"));
	QObject plugin;
	auto guardedPlugin = QPointer<QObject>(&plugin);
	auto configMock = QSharedPointer<ConfigMock>(new ConfigMock);
	auto pluginLoaderMock = QSharedPointer<PluginLoaderMock>(new PluginLoaderMock);
	auto logger = QSharedPointer<NoneLogger>(new NoneLogger);

	EXPECT_CALL(*configMock, pluginInfos())
			.WillOnce(testing::Return(QList<PluginInfo>{ pluginInfo }));

	EXPECT_CALL(*pluginLoaderMock, load(pluginInfo.path()))
			.WillOnce(testing::Return(&plugin));

	// act
	{
		PluginManager pluginManager(configMock, pluginLoaderMock, logger);

		// assert
		QCOMPARE(pluginManager.get(PluginType::Ocr).data(), &plugin);
	}

	// assert
	QCOMPARE(guardedPlugin.data(), &plugin);
}

void PluginManagerTests::LoadPlugins_Should_NotDeletePlugin_When_LoaderReturnsSameInstanceTwice()
{
	// arrange
	auto firstPluginInfo = PluginInfo(PluginType::Ocr, QLatin1String("1.0"), QLatin1String("/usr/lib/plugin.so"));
	auto secondPluginInfo = PluginInfo(PluginType::Ocr, QLatin1String("1.0"), QLatin1String("/usr/lib64/plugin.so"));
	QObject plugin;
	auto guardedPlugin = QPointer<QObject>(&plugin);
	auto configMock = QSharedPointer<ConfigMock>(new ConfigMock);
	auto pluginLoaderMock = QSharedPointer<PluginLoaderMock>(new PluginLoaderMock);
	auto logger = QSharedPointer<NoneLogger>(new NoneLogger);

	EXPECT_CALL(*configMock, pluginInfos())
			.WillOnce(testing::Return(QList<PluginInfo>{ firstPluginInfo, secondPluginInfo }));

	EXPECT_CALL(*pluginLoaderMock, load(testing::_))
			.Times(2)
			.WillRepeatedly(testing::Return(&plugin));

	// act
	{
		PluginManager pluginManager(configMock, pluginLoaderMock, logger);

		// assert
		QCOMPARE(pluginManager.get(PluginType::Ocr).data(), &plugin);
	}

	// assert
	QCOMPARE(guardedPlugin.data(), &plugin);
}

TEST_MAIN(PluginManagerTests)
