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

#ifndef KSNIP_IMAGEGRABBERSETTINGS_H
#define KSNIP_IMAGEGRABBERSETTINGS_H

#include <QGroupBox>
#include <QCheckBox>
#include <QGridLayout>

#include "src/backend/config/IConfig.h"

class ImageGrabberSettings : public QGroupBox
{
	Q_OBJECT
public:
	explicit ImageGrabberSettings(const QSharedPointer<IConfig> &config);
	~ImageGrabberSettings() override;
	void saveSettings();

private:
	QCheckBox *mCaptureCursorCheckbox;
	QCheckBox *mHideMainWindowDuringScreenshotCheckbox;
	QCheckBox *mShowMainWindowAfterTakingScreenshotCheckbox;
	QCheckBox *mForceGenericWaylandCheckbox;
	QCheckBox *mScaleGenericWaylandScreenshotsCheckbox;
	QGridLayout *mLayout;
	QSharedPointer<IConfig> mConfig;

	void initGui();
	void loadConfig();
};

#endif //KSNIP_IMAGEGRABBERSETTINGS_H
