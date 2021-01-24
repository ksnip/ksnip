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

#ifndef KSNIP_WATERMARKSETTINGS_H
#define KSNIP_WATERMARKSETTINGS_H

#include <QGroupBox>
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>

#include "src/backend/config/KsnipConfig.h"
#include "src/gui/operations/UpdateWatermarkOperation.h"
#include "src/common/provider/ScaledSizeProvider.h"

class WatermarkSettings : public QGroupBox
{
Q_OBJECT
public:
	explicit WatermarkSettings(KsnipConfig *config);
	~WatermarkSettings() override;
	void saveSettings();

private:
	QGridLayout *mLayout;
	KsnipConfig *mConfig;
	QCheckBox *mRotateWatermarkCheckbox;
	QLabel *mWatermarkImageLabel;
	QPushButton *mUpdateWatermarkImageButton;
	WatermarkImageLoader mWatermarkImageLoader;

	void initGui();
	void loadConfig();

private slots:
	void updateWatermarkImageClicked();
};


#endif //KSNIP_WATERMARKSETTINGS_H
