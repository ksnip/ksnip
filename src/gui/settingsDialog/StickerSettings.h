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

#ifndef KSNIP_STICKERSETTINGS_H
#define KSNIP_STICKERSETTINGS_H

#include <QGroupBox>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QListWidget>
#include <QStandardPaths>
#include <QDir>
#include <QCheckBox>

#include "src/backend/config/KsnipConfig.h"
#include "src/common/helper/PathHelper.h"

class StickerSettings : public QGroupBox
{
Q_OBJECT
public:
	explicit StickerSettings(KsnipConfig *config);
	~StickerSettings() override;
	void saveSettings();

private:
	QListWidget *mListWidget;
	QPushButton *mAddButton;
	QPushButton *mRemoveButton;
	QPushButton *mUpButton;
	QPushButton *mDownButton;
	QCheckBox *mUseDefaultStickerCheckBox;
	QGridLayout *mLayout;
	KsnipConfig *mConfig;
	int mPathDataKey;
	int mIsSavedDataKey;
	int mIsRemovedDataKey;

	void initGui();
	void loadConfig();

private slots:
	void addTriggered();
	void removeTriggered();
	void upTriggered();
	void downTriggered();
	void currentRowChanged(int row);
	void addSticker(const QString &path, bool isSaved) const;
	QString stickerDirectory() const;
	QStringList processSticker() const;
};


#endif //KSNIP_STICKERSETTINGS_H
