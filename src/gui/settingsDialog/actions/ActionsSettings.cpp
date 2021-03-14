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

#include "ActionsSettings.h"

ActionsSettings::ActionsSettings(KsnipConfig *config, const QList<CaptureModes> &captureModes) :
	mConfig(config),
	mLayout(new QVBoxLayout(this)),
	mTabWidget(new QTabWidget(this)),
	mCaptureModes(captureModes)
{
	Q_ASSERT(mConfig != nullptr);

	initGui();
	loadConfig();

	mTabWidget->setCurrentIndex(0);
}

ActionsSettings::~ActionsSettings()
{
	delete mTabWidget;
	delete mLayout;
}

void ActionsSettings::saveSettings()
{
	QList<Action> actions;
	auto count = mTabWidget->count();
	for (int index = 0; index < count; ++index) {
		auto tabContent = dynamic_cast<ActionSettingTab *>(mTabWidget->widget(index));
		if(tabContent != nullptr) {
			actions.append(tabContent->action());
		}
	}
	mConfig->setActions(actions);
}

void ActionsSettings::initGui()
{
	auto addButton = new QPushButton();
	addButton->setText(tr("Add"));
	connect(addButton, &QPushButton::clicked, this, &ActionsSettings::addEmptyTab);

	auto addTabIndex = mTabWidget->addTab(new EmptyActionSettingTab, QString());
	mTabWidget->setTabEnabled(addTabIndex, false);
	mTabWidget->tabBar()->setTabButton(addTabIndex, QTabBar::RightSide, addButton);

	mTabWidget->setTabsClosable(true);
	connect(mTabWidget, &QTabWidget::tabCloseRequested, this, &ActionsSettings::closeTab);

	mLayout->addWidget(mTabWidget);

	setTitle(tr("Actions Settings"));
	setLayout(mLayout);
}

void ActionsSettings::loadConfig()
{
	auto actions = mConfig->actions();
	for(const auto& action : actions) {
		auto tabContent = new ActionSettingTab(action, mCaptureModes);
		insertTab(tabContent, action.name());
	}
}

void ActionsSettings::insertTab(ActionSettingTab *tabContent, const QString &name)
{
	auto index = mTabWidget->insertTab(mTabWidget->count() - 1, tabContent, name);
	mTabWidget->setCurrentIndex(index);
}

void ActionsSettings::addEmptyTab()
{
	auto name = tr("Action") + QLatin1String(" ") + QString::number(mTabWidget->count());
	auto tabContent = new ActionSettingTab(name, mCaptureModes);
	insertTab(tabContent, name);
}

void ActionsSettings::closeTab(int index)
{
	mTabWidget->removeTab(index);
}
