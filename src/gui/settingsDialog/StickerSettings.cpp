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

#include "StickerSettings.h"

StickerSettings::StickerSettings(KsnipConfig *config) :
	mConfig(config),
	mListWidget(new QListWidget(this)),
	mAddButton(new QPushButton(this)),
	mRemoveButton(new QPushButton(this)),
	mUpButton(new QPushButton(this)),
	mDownButton(new QPushButton(this)),
	mUseDefaultStickerCheckBox(new QCheckBox(this)),
	mLayout(new QGridLayout),
	mPathDataKey(1001),
	mIsSavedDataKey(1002),
	mIsRemovedDataKey(1003)
{
	initGui();
	loadConfig();
}

StickerSettings::~StickerSettings()
{
	delete mListWidget;
 	delete mAddButton;
	delete mRemoveButton;
	delete mUpButton;
 	delete mDownButton;
 	delete mUseDefaultStickerCheckBox;
 	delete mLayout;
}

void StickerSettings::saveSettings()
{
	auto selectedSticker = processSticker();
	mConfig->setUseDefaultSticker(mUseDefaultStickerCheckBox->isChecked());
	mConfig->setStickerPaths(selectedSticker);
}

QStringList StickerSettings::processSticker() const
{
	QStringList paths;
	for (int i = 0; i < mListWidget->count(); i++) {
		auto path = mListWidget->item(i)->data(mPathDataKey).toString();
		auto isSaved = mListWidget->item(i)->data(mIsSavedDataKey).toBool();
		auto isRemovedSaved = mListWidget->item(i)->data(mIsRemovedDataKey).toBool();

		if(isSaved && isRemovedSaved) {
			QFile::remove(path);
		} else if (isSaved) {
			paths.append(path);
		} else {
			auto directory = stickerDirectory();
			auto filename = PathHelper::extractFilenameWithFormat(path);
			auto newPath = directory + QStringLiteral("/") + filename;
			QFile::copy(path, newPath);
			paths.append(newPath);
		}
	}
	return paths;
}

QString StickerSettings::stickerDirectory() const
{
	auto directory = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
	QDir qdir;
	qdir.mkpath(directory);
	return directory;
}

void StickerSettings::initGui()
{
	connect(mListWidget, &QListWidget::currentRowChanged, this, &StickerSettings::currentRowChanged);

	mAddButton->setText(tr("Add"));
	connect(mAddButton, &QPushButton::clicked, this, &StickerSettings::addTriggered);

	mRemoveButton->setText(tr("Remove"));
	connect(mRemoveButton, &QPushButton::clicked, this, &StickerSettings::removeTriggered);

	mUpButton->setText(tr("Up"));
	connect(mUpButton, &QPushButton::clicked, this, &StickerSettings::upTriggered);

	mDownButton->setText(tr("Down"));
	connect(mDownButton, &QPushButton::clicked, this, &StickerSettings::downTriggered);

	mUseDefaultStickerCheckBox->setText(tr("Use Default Stickers"));

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->addWidget(mListWidget, 0, 0, 5,1);
	mLayout->addWidget(mAddButton, 0, 1, 1,1),
	mLayout->addWidget(mRemoveButton, 1, 1, 1,1),
	mLayout->addWidget(mUpButton, 2, 1, 1,1),
	mLayout->addWidget(mDownButton, 3, 1, 1,1),
	mLayout->addWidget(mUseDefaultStickerCheckBox, 6, 0, 1,1),
	mLayout->setRowStretch(0,1);

	setTitle(tr("Sticker Settings"));
	setLayout(mLayout);
}

void StickerSettings::loadConfig()
{
	auto list = mConfig->stickerPaths();
	for(const auto& path : list) {
		addSticker(path, true);
	}
	currentRowChanged(mListWidget->currentRow());

	mUseDefaultStickerCheckBox->setChecked(mConfig->useDefaultSticker());
}

void StickerSettings::addTriggered()
{
	auto path = QFileDialog::getOpenFileName(this, tr("Add Sticker"), QDir::homePath(), tr("Vector Image Files (*.svg)"));
	addSticker(path, false);
}

void StickerSettings::addSticker(const QString &path, bool isSaved) const
{
	auto filename = PathHelper::extractFilename(path);
	auto item = new QListWidgetItem(QIcon(path), filename);
	item->setData(mPathDataKey, path);
	item->setData(mIsSavedDataKey, isSaved);
	item->setData(mIsRemovedDataKey, false);
	mListWidget->addItem(item);
}

void StickerSettings::removeTriggered()
{
	auto selectedItem = mListWidget->currentItem();
	if(selectedItem != nullptr) {
		selectedItem->setData(mIsRemovedDataKey, true);
		selectedItem->setHidden(true);
	}
}

void StickerSettings::upTriggered()
{
	auto row = mListWidget->currentRow();
	if(row > 0) {
		auto item = mListWidget->takeItem(row);
		auto newRow = row - 1;
		mListWidget->insertItem(newRow, item);
		mListWidget->setCurrentRow(newRow);
		mListWidget->setFocus();
	}
}

void StickerSettings::downTriggered()
{
	auto row = mListWidget->currentRow();
	if(row < mListWidget->count() - 1) {
		auto item = mListWidget->takeItem(row);
		auto newRow = row + 1;
		mListWidget->insertItem(newRow, item);
		mListWidget->setCurrentRow(newRow);
		mListWidget->setFocus();
	}
}

void StickerSettings::currentRowChanged(int row)
{
	mRemoveButton->setEnabled(row != -1);
	mUpButton->setEnabled(row > 0);
	mDownButton->setEnabled(row >= 0 && row < mListWidget->count() - 1);
}
