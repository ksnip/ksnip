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

#ifndef KSNIP_SAVERSETTINGS_H
#define KSNIP_SAVERSETTINGS_H

#include <QGroupBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QRadioButton>

#include "src/backend/config/IConfig.h"
#include "src/common/adapter/fileDialog/IFileDialogService.h"
#include "src/common/helper/PathHelper.h"
#include "src/widgets/CustomSpinBox.h"

class SaverSettings : public QGroupBox
{
	Q_OBJECT
public:
	explicit SaverSettings(const QSharedPointer<IConfig> &config, const QSharedPointer<IFileDialogService> &fileDialogService);
	~SaverSettings() override = default;
	void saveSettings();

private:
	QCheckBox *mAutoSaveNewCapturesCheckbox;
	QCheckBox *mPromptToSaveBeforeExitCheckbox;
	QCheckBox *mRememberSaveDirectoryCheckbox;
	QRadioButton *mSaveQualityDefaultRadioButton;
	QRadioButton *mSaveQualityFactorRadioButton;
	QLabel *mSaveLocationLabel;
	QLineEdit *mSaveLocationLineEdit;
	QPushButton *mBrowseButton;
	CustomSpinBox *mSaveQualityFactorSpinBox;
	QGridLayout *mLayout;
	QGridLayout *mSaveQualityLayout;
	QGroupBox *mSaveQualityGroupBox;
	QSharedPointer<IConfig> mConfig;
	QSharedPointer<IFileDialogService> mFileDialogService;

	void initGui();
	void loadConfig();

private slots:
	void chooseSaveDirectory();
	SaveQualityMode getSaveQualityMode();
};

#endif //KSNIP_SAVERSETTINGS_H
