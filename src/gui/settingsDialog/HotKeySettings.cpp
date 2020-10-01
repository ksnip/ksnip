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

#include "HotKeySettings.h"

HotKeySettings::HotKeySettings(KsnipConfig *ksnipConfig, const QList<CaptureModes> &captureModes) :
	mConfig(ksnipConfig),
	mCaptureModes(captureModes),
	mEnableGlobalHotKeysCheckBox(new QCheckBox(this)),
	mRectAreaLabel(new QLabel(this)),
	mLastRectAreaLabel(new QLabel(this)),
	mFullScreenLabel(new QLabel(this)),
	mCurrentScreenLabel(new QLabel(this)),
	mActiveWindowLabel(new QLabel(this)),
	mWindowUnderCursorLabel(new QLabel(this)),
	mPortalLabel(new QLabel(this)),
	mRectAreaClearPushButton(new QPushButton(this)),
	mLastRectAreaClearPushButton(new QPushButton(this)),
	mFullScreenClearPushButton(new QPushButton(this)),
	mCurrentScreenClearPushButton(new QPushButton(this)),
	mActiveWindowClearPushButton(new QPushButton(this)),
	mWindowUnderCursorClearPushButton(new QPushButton(this)),
	mPortalClearPushButton(new QPushButton(this)),
	mLayout(new QGridLayout(this))
{
	Q_ASSERT(mConfig != nullptr);

	initGui();
	loadConfig();
}

HotKeySettings::~HotKeySettings()
{
	delete mEnableGlobalHotKeysCheckBox;
	delete mRectAreaLabel;
	delete mLastRectAreaLabel;
	delete mFullScreenLabel;
	delete mCurrentScreenLabel;
	delete mActiveWindowLabel;
	delete mWindowUnderCursorLabel;
	delete mPortalLabel;
	delete mRectAreaKeySequenceLineEdit;
	delete mLastRectAreaKeySequenceLineEdit;
	delete mFullScreenKeySequenceLineEdit;
	delete mCurrentScreenKeySequenceLineEdit;
	delete mActiveWindowKeySequenceLineEdit;
	delete mWindowUnderCursorKeySequenceLineEdit;
	delete mPortalKeySequenceLineEdit;
	delete mRectAreaClearPushButton;
	delete mLastRectAreaClearPushButton;
	delete mFullScreenClearPushButton;
	delete mCurrentScreenClearPushButton;
	delete mActiveWindowClearPushButton;
	delete mWindowUnderCursorClearPushButton;
	delete mPortalClearPushButton;
	delete mLayout;
}

void HotKeySettings::saveSettings()
{
	mConfig->setGlobalHotKeysEnabled(mEnableGlobalHotKeysCheckBox->isChecked());
	mConfig->setRectAreaHotKey(mRectAreaKeySequenceLineEdit->value());
	mConfig->setLastRectAreaHotKey(mLastRectAreaKeySequenceLineEdit->value());
	mConfig->setFullScreenHotKey(mFullScreenKeySequenceLineEdit->value());
	mConfig->setCurrentScreenHotKey(mCurrentScreenKeySequenceLineEdit->value());
	mConfig->setActiveWindowHotKey(mActiveWindowKeySequenceLineEdit->value());
	mConfig->setWindowUnderCursorHotKey(mWindowUnderCursorKeySequenceLineEdit->value());
	mConfig->setPortalHotKey(mPortalKeySequenceLineEdit->value());
}

void HotKeySettings::initGui()
{
	auto allowedKeys = HotKeyMap::instance()->getAllKeys();
	mRectAreaKeySequenceLineEdit = new KeySequenceLineEdit(this, allowedKeys);
	mLastRectAreaKeySequenceLineEdit = new KeySequenceLineEdit(this, allowedKeys);
	mFullScreenKeySequenceLineEdit = new KeySequenceLineEdit(this, allowedKeys);
	mCurrentScreenKeySequenceLineEdit = new KeySequenceLineEdit(this, allowedKeys);
	mActiveWindowKeySequenceLineEdit = new KeySequenceLineEdit(this, allowedKeys);
	mWindowUnderCursorKeySequenceLineEdit = new KeySequenceLineEdit(this, allowedKeys);
	mPortalKeySequenceLineEdit = new KeySequenceLineEdit(this, allowedKeys);

	mEnableGlobalHotKeysCheckBox->setText(tr("Enable Global HotKeys"));
	mEnableGlobalHotKeysCheckBox->setToolTip(tr("HotKeys are currently supported only for Windows and X11"));
	connect(mEnableGlobalHotKeysCheckBox, &QCheckBox::stateChanged, this, &HotKeySettings::globalHotKeysStateChanged);

	mRectAreaLabel->setText(tr("Capture Rect Area") + QLatin1Literal(":"));
	mLastRectAreaLabel->setText(tr("Capture Last Rect Area") + QLatin1Literal(":"));
	mFullScreenLabel->setText(tr("Capture Full Screen") + QLatin1Literal(":"));
	mCurrentScreenLabel->setText(tr("Capture current Screen") + QLatin1Literal(":"));
	mActiveWindowLabel->setText(tr("Capture active Window") + QLatin1Literal(":"));
	mWindowUnderCursorLabel->setText(tr("Capture Window under Cursor") + QLatin1Literal(":"));
	mPortalLabel->setText(tr("Capture using Portal") + QLatin1Literal(":"));

	auto clearText = tr("Clear");
	mRectAreaClearPushButton->setText(clearText);
	connect(mRectAreaClearPushButton, &QPushButton::clicked, mRectAreaKeySequenceLineEdit, &KeySequenceLineEdit::clear);

	mLastRectAreaClearPushButton->setText(clearText);
	connect(mLastRectAreaClearPushButton, &QPushButton::clicked, mLastRectAreaKeySequenceLineEdit, &KeySequenceLineEdit::clear);

	mFullScreenClearPushButton->setText(clearText);
	connect(mFullScreenClearPushButton, &QPushButton::clicked, mFullScreenKeySequenceLineEdit, &KeySequenceLineEdit::clear);

	mCurrentScreenClearPushButton->setText(clearText);
	connect(mCurrentScreenClearPushButton, &QPushButton::clicked, mCurrentScreenKeySequenceLineEdit, &KeySequenceLineEdit::clear);

	mActiveWindowClearPushButton->setText(clearText);
	connect(mActiveWindowClearPushButton, &QPushButton::clicked, mActiveWindowKeySequenceLineEdit, &KeySequenceLineEdit::clear);

	mWindowUnderCursorClearPushButton->setText(clearText);
	connect(mWindowUnderCursorClearPushButton, &QPushButton::clicked, mWindowUnderCursorKeySequenceLineEdit, &KeySequenceLineEdit::clear);

    mPortalClearPushButton->setText(clearText);
    connect(mPortalClearPushButton, &QPushButton::clicked, mPortalKeySequenceLineEdit, &KeySequenceLineEdit::clear);

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->setColumnStretch(1, 1);
	mLayout->addWidget(mEnableGlobalHotKeysCheckBox, 0, 0, 1, 3);

	mLayout->addWidget(mRectAreaLabel, 1, 0, 1, 1);
	mLayout->addWidget(mRectAreaKeySequenceLineEdit, 1, 1, 1, 1);
	mLayout->addWidget(mRectAreaClearPushButton, 1, 2, 1, 1);

	mLayout->addWidget(mLastRectAreaLabel, 2, 0,1,1);
	mLayout->addWidget(mLastRectAreaKeySequenceLineEdit, 2, 1, 1, 1);
	mLayout->addWidget(mLastRectAreaClearPushButton, 2, 2, 1, 1);

	mLayout->addWidget(mFullScreenLabel, 3, 0, 1, 1);
	mLayout->addWidget(mFullScreenKeySequenceLineEdit, 3, 1, 1, 1);
	mLayout->addWidget(mFullScreenClearPushButton, 3, 2, 1, 1);

	mLayout->addWidget(mCurrentScreenLabel, 4, 0, 1, 1);
	mLayout->addWidget(mCurrentScreenKeySequenceLineEdit, 4, 1, 1, 1);
	mLayout->addWidget(mCurrentScreenClearPushButton, 4, 2, 1, 1);

	mLayout->addWidget(mActiveWindowLabel, 5, 0, 1, 1);
	mLayout->addWidget(mActiveWindowKeySequenceLineEdit, 5, 1, 1, 1);
	mLayout->addWidget(mActiveWindowClearPushButton, 5, 2, 1, 1);

	mLayout->addWidget(mWindowUnderCursorLabel, 6, 0, 1, 1);
	mLayout->addWidget(mWindowUnderCursorKeySequenceLineEdit, 6, 1, 1, 1);
	mLayout->addWidget(mWindowUnderCursorClearPushButton, 6, 2, 1, 1);

    mLayout->addWidget(mPortalLabel, 7, 0, 1, 1);
    mLayout->addWidget(mPortalKeySequenceLineEdit, 7, 1, 1, 1);
    mLayout->addWidget(mPortalClearPushButton, 7, 2, 1, 1);

	setTitle(tr("Global HotKeys"));
	setLayout(mLayout);
}

void HotKeySettings::loadConfig()
{
	mEnableGlobalHotKeysCheckBox->setChecked(mConfig->globalHotKeysEnabled());
	mEnableGlobalHotKeysCheckBox->setEnabled(!mConfig->isGlobalHotKeysEnabledReadOnly());
	mRectAreaKeySequenceLineEdit->setValue(mConfig->rectAreaHotKey());
	mLastRectAreaKeySequenceLineEdit->setValue(mConfig->lastRectAreaHotKey());
	mFullScreenKeySequenceLineEdit->setValue(mConfig->fullScreenHotKey());
	mCurrentScreenKeySequenceLineEdit->setValue(mConfig->currentScreenHotKey());
	mActiveWindowKeySequenceLineEdit->setValue(mConfig->activeWindowHotKey());
	mWindowUnderCursorKeySequenceLineEdit->setValue(mConfig->windowUnderCursorHotKey());
	mPortalKeySequenceLineEdit->setValue(mConfig->portalHotKey());
	globalHotKeysStateChanged();
}

void HotKeySettings::globalHotKeysStateChanged()
{
	auto hotKeysEnabled = mEnableGlobalHotKeysCheckBox->isChecked() && mEnableGlobalHotKeysCheckBox->isEnabled();
	auto isRectAreaSupported = mCaptureModes.contains(CaptureModes::RectArea);
	auto isLastRectAreaSupported = mCaptureModes.contains(CaptureModes::LastRectArea);
	auto isFullScreenSupported = mCaptureModes.contains(CaptureModes::FullScreen);
	auto isCurrentScreenSupported = mCaptureModes.contains(CaptureModes::CurrentScreen);
	auto isActiveWindowSupported = mCaptureModes.contains(CaptureModes::ActiveWindow);
	auto isWindowUnderCursorSupported = mCaptureModes.contains(CaptureModes::WindowUnderCursor);
	auto isPortalSupported = mCaptureModes.contains(CaptureModes::Portal);

	mRectAreaLabel->setEnabled(hotKeysEnabled && isRectAreaSupported);
	mRectAreaKeySequenceLineEdit->setEnabled(hotKeysEnabled && isRectAreaSupported);
	mRectAreaClearPushButton->setEnabled(hotKeysEnabled && isRectAreaSupported);

	mLastRectAreaLabel->setEnabled(hotKeysEnabled && isLastRectAreaSupported);
	mLastRectAreaKeySequenceLineEdit->setEnabled(hotKeysEnabled && isLastRectAreaSupported);
	mLastRectAreaClearPushButton->setEnabled(hotKeysEnabled && isLastRectAreaSupported);

	mFullScreenLabel->setEnabled(hotKeysEnabled && isFullScreenSupported);
	mFullScreenKeySequenceLineEdit->setEnabled(hotKeysEnabled && isFullScreenSupported);
	mFullScreenClearPushButton->setEnabled(hotKeysEnabled && isFullScreenSupported);

	mCurrentScreenLabel->setEnabled(hotKeysEnabled && isCurrentScreenSupported);
	mCurrentScreenKeySequenceLineEdit->setEnabled(hotKeysEnabled && isCurrentScreenSupported);
	mCurrentScreenClearPushButton->setEnabled(hotKeysEnabled && isCurrentScreenSupported);

	mActiveWindowLabel->setEnabled(hotKeysEnabled && isActiveWindowSupported);
	mActiveWindowKeySequenceLineEdit->setEnabled(hotKeysEnabled && isActiveWindowSupported);
	mActiveWindowClearPushButton->setEnabled(hotKeysEnabled && isActiveWindowSupported);

	mWindowUnderCursorLabel->setEnabled(hotKeysEnabled && isWindowUnderCursorSupported);
	mWindowUnderCursorKeySequenceLineEdit->setEnabled(hotKeysEnabled && isWindowUnderCursorSupported);
	mWindowUnderCursorClearPushButton->setEnabled(hotKeysEnabled && isWindowUnderCursorSupported);

    mPortalLabel->setEnabled(hotKeysEnabled && isPortalSupported);
    mPortalKeySequenceLineEdit->setEnabled(hotKeysEnabled && isPortalSupported);
    mPortalClearPushButton->setEnabled(hotKeysEnabled && isPortalSupported);
}
