/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KSNIP_TRAYICONSETTINGS_H
#define KSNIP_TRAYICONSETTINGS_H

#include <QGroupBox>
#include <QLabel>
#include <QGridLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QRadioButton>
#include <QFileDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>

#include "src/backend/config/IConfig.h"
#include "src/common/helper/EnumTranslator.h"

class TrayIconSettings : public QGroupBox
{
Q_OBJECT
public:
	explicit TrayIconSettings(const QList<CaptureModes> &captureModes, const QSharedPointer<IConfig> &config);
	~TrayIconSettings() override = default;
	void saveSettings();

private:
	QCheckBox *mUseTrayIconCheckBox;
	QCheckBox *mMinimizeToTrayCheckBox;
	QCheckBox *mCloseToTrayCheckBox;
	QCheckBox *mTrayIconNotificationsCheckBox;
	QCheckBox *mUsePlatformSpecificNotificationServiceCheckBox;
	QComboBox *mDefaultActionCaptureModeCombobox;
	QCheckBox *mStartMinimizedToTrayCheckBox;
	QRadioButton *mDefaultActionShowEditorRadioButton;
	QRadioButton *mDefaultActionCaptureRadioButton;
	QGridLayout *mLayout;
	QGridLayout *mDefaultActionLayout;
	QGroupBox *mDefaultActionGroupBox;
	QSharedPointer<IConfig> mConfig;

	// settings for customizing the tray icon image
	QRadioButton *mTrayIconDefaultRadioButton;
	QRadioButton *mTrayIconCustomRadioButton;
	QLineEdit *mTrayIconLineEdit;
	QPushButton *mTrayIconCustomFileSelectButton;
	QGroupBox *mTrayIconGroupBox;
	QGridLayout *mTrayIconLayout;


	void initGui();
	void loadConfig();
	void populateDefaultActionCaptureModeCombobox(const QList<CaptureModes> &captureModes);
	TrayIconDefaultActionMode selectedTrayIconDefaultActionMode() const;
	int indexOfSelectedCaptureMode() const;

private slots:
	void selectCustomImage();
	void useTrayIconChanged();
};


#endif //KSNIP_TRAYICONSETTINGS_H
