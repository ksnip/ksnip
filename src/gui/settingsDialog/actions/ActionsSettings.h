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

#ifndef KSNIP_ACTIONSSETTINGS_H
#define KSNIP_ACTIONSSETTINGS_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QPushButton>

#include "ActionSettingTab.h"
#include "EmptyActionSettingTab.h"
#include "src/backend/config/KsnipConfig.h"

class ActionsSettings : public QGroupBox
{
Q_OBJECT
public:
	explicit ActionsSettings(KsnipConfig *config, const QList<CaptureModes> &captureModes);
	~ActionsSettings() override;
	void saveSettings();

private:
	QVBoxLayout *mLayout;
	KsnipConfig *mConfig;
	QTabWidget *mTabWidget;
	QList<CaptureModes> mCaptureModes;

	void initGui();
	void loadConfig();
	void insertActionTab(ActionSettingTab *tabContent, const QString &name);

private slots:
	void addEmptyTab();
	void closeTab(int index);
};


#endif //KSNIP_ACTIONSSETTINGS_H
