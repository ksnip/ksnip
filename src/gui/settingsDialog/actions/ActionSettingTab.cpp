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

#include "ActionSettingTab.h"

ActionSettingTab::ActionSettingTab(const QString &name, const QList<CaptureModes> &captureModes) : ActionSettingTab(captureModes)
{
	mNameLineEdit->setTextAndPlaceholderText(name);
}

ActionSettingTab::ActionSettingTab(const Action &action, const QList<CaptureModes> &captureModes) : ActionSettingTab(captureModes)
{
	setAction(action);
}

ActionSettingTab::~ActionSettingTab()
{
	delete mCaptureModeComboBox;
	delete mCaptureEnabledCheckBox;
	delete mIncludeCursorCheckBox;
	delete mShowPinWindowCheckBox;
	delete mCopyToClipboardCheckBox;
	delete mUploadCheckBox;
	delete mOpenDirectoryCheckBox;
	delete mSaveCheckBox;
	delete mCaptureModeLabel;
	delete mDelayLabel;
	delete mNameLabel;
	delete mShortcutLabel;
	delete mDelaySpinBox;
	delete mNameLineEdit;
	delete mShortcutLineEdit;
	delete mLayout;
}

void ActionSettingTab::initGui(const QList<CaptureModes> &captureModes)
{
	mNameLabel->setText(tr("Name") + QLatin1String(":"));
	mNameLineEdit->setMaxLength(50);
	connect(mNameLineEdit, &QLineEdit::editingFinished, this, &ActionSettingTab::nameEditingFinished);

	mShortcutLabel->setText(tr("Shortcut") + QLatin1String(":"));
	mShortcutLabel->setToolTip("When global hotkeys are enabled and supported then\n"
							   "this shortcut will also work as a global hotkey.");

	mShortcutLineEdit->setToolTip(mShortcutLabel->toolTip());

	mShortcutClearButton->setText(tr("Clear"));
	connect(mShortcutClearButton, &QPushButton::clicked, mShortcutLineEdit, &KeySequenceLineEdit::clear);

	mCaptureEnabledCheckBox->setText(tr("Take Capture"));
	connect(mCaptureEnabledCheckBox, &QCheckBox::toggled, this, &ActionSettingTab::captureEnabledChanged);

	mIncludeCursorCheckBox->setText(tr("Include Cursor"));

	mDelayLabel->setText(tr("Delay") + QLatin1String(":"));
	mDelaySpinBox->setSuffix(tr("s"));

	mCaptureModeLabel->setText(tr("Capture Mode") + QLatin1String(":"));
	populateCaptureModeCombobox(captureModes);

	mShowPinWindowCheckBox->setText(tr("Show image in Pin Window"));

	mCopyToClipboardCheckBox->setText(tr("Copy image to Clipboard"));

	mUploadCheckBox->setText(tr("Upload image"));

	mOpenDirectoryCheckBox->setText(tr("Open image parent directory"));

	mSaveCheckBox->setText(tr("Save image"));

	mLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	mLayout->setColumnMinimumWidth(0, 10);
	mLayout->addWidget(mNameLabel, 0, 0, 1, 2);
	mLayout->addWidget(mNameLineEdit, 0, 2, 1, 3);
	mLayout->addWidget(mShortcutLabel, 1, 0, 1, 2);
	mLayout->addWidget(mShortcutLineEdit, 1, 2, 1, 3);
	mLayout->addWidget(mShortcutClearButton, 1, 6, 1, 1);
	mLayout->setRowMinimumHeight(2, 10);
	mLayout->addWidget(mCaptureEnabledCheckBox, 3, 0, 1, 5);
	mLayout->addWidget(mIncludeCursorCheckBox, 4, 1, 1, 4);
	mLayout->addWidget(mDelayLabel, 5, 1, 1, 2);
	mLayout->addWidget(mDelaySpinBox, 5, 3, 1, 2);
	mLayout->addWidget(mCaptureModeLabel, 6, 1, 1, 2);
	mLayout->addWidget(mCaptureModeComboBox, 6, 3, 1, 2);
	mLayout->setRowMinimumHeight(7, 10);
	mLayout->addWidget(mShowPinWindowCheckBox, 8, 0, 1, 5);
	mLayout->addWidget(mCopyToClipboardCheckBox, 9, 0, 1, 5);
	mLayout->addWidget(mUploadCheckBox, 10, 0, 1, 5);
	mLayout->addWidget(mSaveCheckBox, 11, 0, 1, 5);
	mLayout->addWidget(mOpenDirectoryCheckBox, 12, 0, 1, 5);

	setLayout(mLayout);
}

void ActionSettingTab::populateCaptureModeCombobox(const QList<CaptureModes> &captureModes)
{
	for (auto captureMode: captureModes) {
		const auto label = EnumTranslator::instance()->toString(captureMode);
		mCaptureModeComboBox->addItem(label, static_cast<int>(captureMode));
	}
}

void ActionSettingTab::captureEnabledChanged()
{
	auto isEnabled = mCaptureEnabledCheckBox->isChecked();
	mIncludeCursorCheckBox->setEnabled(isEnabled);
	mDelayLabel->setEnabled(isEnabled);
	mDelaySpinBox->setEnabled(isEnabled);
	mCaptureModeLabel->setEnabled(isEnabled);
	mCaptureModeComboBox->setEnabled(isEnabled);
}

Action ActionSettingTab::action() const
{
	Action action;
	action.setName(getTextWithEscapedAmpersand(mNameLineEdit->textOrPlaceholderText()));
	action.setShortcut(mShortcutLineEdit->value());
	action.setIsCaptureEnabled(mCaptureEnabledCheckBox->isChecked());
	action.setCaptureDelay(mDelaySpinBox->value() * 1000);
	action.setIncludeCursor(mIncludeCursorCheckBox->isChecked());
	action.setCaptureMode(mCaptureModeComboBox->currentData().value<CaptureModes>());
	action.setIsPinScreenshotEnabled(mShowPinWindowCheckBox->isChecked());
	action.setIsSaveEnabled(mSaveCheckBox->isChecked());
	action.setIsCopyToClipboardEnabled(mCopyToClipboardCheckBox->isChecked());
	action.setIsOpenDirectoryEnabled(mOpenDirectoryCheckBox->isChecked());
	action.setIsUploadEnabled(mUploadCheckBox->isChecked());
	return action;
}

ActionSettingTab::ActionSettingTab(const QList<CaptureModes> &captureModes) :
	mCaptureModeComboBox(new QComboBox(nullptr)),
	mCaptureEnabledCheckBox(new QCheckBox(this)),
	mIncludeCursorCheckBox(new QCheckBox(this)),
	mShowPinWindowCheckBox(new QCheckBox(this)),
	mCopyToClipboardCheckBox(new QCheckBox(this)),
	mUploadCheckBox(new QCheckBox(this)),
	mOpenDirectoryCheckBox(new QCheckBox(this)),
	mSaveCheckBox(new QCheckBox(this)),
	mCaptureModeLabel(new QLabel(this)),
	mDelayLabel(new QLabel(this)),
	mNameLabel(new QLabel(this)),
	mShortcutLabel(new QLabel(this)),
	mDelaySpinBox(new CustomSpinBox(0, 100)),
	mNameLineEdit(new CustomLineEdit(this)),
	mShortcutLineEdit(new KeySequenceLineEdit(this, HotKeyMap::instance()->getAllKeys())),
	mShortcutClearButton(new QPushButton(this)),
	mLayout(new QGridLayout(this))
{
	initGui(captureModes);
	captureEnabledChanged();
}

void ActionSettingTab::setAction(const Action &action) const
{
	mNameLineEdit->setTextAndPlaceholderText(getTextWithoutEscapedAmpersand(action.name()));
	mShortcutLineEdit->setValue(action.shortcut());
	mCaptureEnabledCheckBox->setChecked(action.isCaptureEnabled());
	mDelaySpinBox->setValue(action.captureDelay() / 1000);
	mIncludeCursorCheckBox->setChecked(action.includeCursor());
	mCaptureModeComboBox->setCurrentIndex(indexOfSelectedCaptureMode(action.captureMode()));
	mShowPinWindowCheckBox->setChecked(action.isPinImageEnabled());
	mSaveCheckBox->setChecked(action.isSaveEnabled());
	mCopyToClipboardCheckBox->setChecked(action.isCopyToClipboardEnabled());
	mOpenDirectoryCheckBox->setChecked(action.isOpenDirectoryEnabled());
	mUploadCheckBox->setChecked(action.isUploadEnabled());
}

int ActionSettingTab::indexOfSelectedCaptureMode(CaptureModes modes) const
{
	return mCaptureModeComboBox->findData(QVariant::fromValue(modes));
}

QString ActionSettingTab::getTextWithEscapedAmpersand(const QString &text)
{
	auto copiedText = text;
	return copiedText.replace(QLatin1String("&"), QLatin1String("&&"));
}

QString ActionSettingTab::getTextWithoutEscapedAmpersand(const QString &text)
{
	auto copiedText = text;
	return copiedText.replace(QLatin1String("&&"), QLatin1String("&"));
}

void ActionSettingTab::nameEditingFinished()
{
	emit nameChanged(getTextWithEscapedAmpersand(mNameLineEdit->textOrPlaceholderText()));
}
