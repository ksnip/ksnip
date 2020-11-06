/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_APPLICATIONSETTINGS_H
#define KSNIP_APPLICATIONSETTINGS_H

#include <QGroupBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QStyleFactory>
#include <QFileDialog>

#include "src/backend/config/KsnipConfig.h"

class ApplicationSettings : public QGroupBox
{
	Q_OBJECT
public:
	explicit ApplicationSettings(KsnipConfig *ksnipConfig);
	~ApplicationSettings() override;
	void saveSettings();

private:
	QCheckBox *mAutoCopyToClipboardNewCapturesCheckbox;
	QCheckBox *mRememberPositionCheckbox;
	QCheckBox *mCaptureOnStartupCheckbox;
	QCheckBox *mUseTrayIconCheckBox;
	QCheckBox *mMinimizeToTrayCheckBox;
	QCheckBox *mCloseToTrayCheckBox;
	QCheckBox *mStartMinimizedToTrayCheckBox;
	QCheckBox *mUseTabsCheckbox;
	QCheckBox *mAutoHideTabsCheckbox;
	QCheckBox *mUseSingleInstanceCheckBox;
	QLabel *mApplicationStyleLabel;
	QComboBox *mApplicationStyleCombobox;
	QGridLayout *mLayout;
	KsnipConfig *mConfig;

	void initGui();
	void loadConfig();

private slots:
	void useTrayIconChanged();
	void useTabsChanged();
};

#endif //KSNIP_APPLICATIONSETTINGS_H
