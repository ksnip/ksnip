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

#ifndef KSNIP_UPLOADERSETTINGS_H
#define KSNIP_UPLOADERSETTINGS_H

#include <QGroupBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>

#include "src/backend/config/KsnipConfig.h"
#include "src/common/enum/UploaderType.h"

class UploaderSettings : public QGroupBox
{
	Q_OBJECT
public:
	explicit UploaderSettings(KsnipConfig *ksnipConfig);
	~UploaderSettings() override;
	void saveSettings();

private:
	QGridLayout *mLayout;
	KsnipConfig *mConfig;
	QCheckBox *mConfirmBeforeUploadCheckbox;
	QComboBox *mUploaderTypeComboBox;
	QLabel *mUploaderTypeLabel;

	void initGui();
	void loadConfig();
};

#endif //KSNIP_UPLOADERSETTINGS_H
