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

#ifndef KSNIP_HOTKEYSETTINGS_H
#define KSNIP_HOTKEYSETTINGS_H

#include <QGroupBox>
#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>

#include "src/backend/config/KsnipConfig.h"
#include "src/widgets/KeySequenceLineEdit.h"
#include "src/gui/globalHotKeys/HotKeyMap.h"

class HotKeySettings : public QGroupBox
{
	Q_OBJECT
public:
	explicit HotKeySettings(KsnipConfig *ksnipConfig, const QList<CaptureModes> &captureModes);
	~HotKeySettings() override;
	void saveSettings();

private:
	QCheckBox *mEnableGlobalHotKeysCheckBox;
	QLabel *mRectAreaLabel;
	QLabel *mLastRectAreaLabel;
	QLabel *mFullScreenLabel;
	QLabel *mCurrentScreenLabel;
	QLabel *mActiveWindowLabel;
	QLabel *mWindowUnderCursorLabel;
	QLabel *mPortalLabel;
	KeySequenceLineEdit *mRectAreaKeySequenceLineEdit;
	KeySequenceLineEdit *mLastRectAreaKeySequenceLineEdit;
	KeySequenceLineEdit *mFullScreenKeySequenceLineEdit;
	KeySequenceLineEdit *mCurrentScreenKeySequenceLineEdit;
	KeySequenceLineEdit *mActiveWindowKeySequenceLineEdit;
	KeySequenceLineEdit *mWindowUnderCursorKeySequenceLineEdit;
	KeySequenceLineEdit *mPortalKeySequenceLineEdit;
	QPushButton *mRectAreaClearPushButton;
	QPushButton *mLastRectAreaClearPushButton;
	QPushButton *mFullScreenClearPushButton;
	QPushButton *mCurrentScreenClearPushButton;
	QPushButton *mActiveWindowClearPushButton;
	QPushButton *mWindowUnderCursorClearPushButton;
	QPushButton *mPortalClearPushButton;
	QGridLayout *mLayout;
	QList<CaptureModes> mCaptureModes;
	KsnipConfig *mConfig;

	void initGui();
	void loadConfig();

private slots:
	void globalHotKeysStateChanged();
};


#endif //KSNIP_HOTKEYSETTINGS_H
