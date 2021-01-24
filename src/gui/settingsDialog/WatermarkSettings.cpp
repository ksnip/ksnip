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

#include "WatermarkSettings.h"

WatermarkSettings::WatermarkSettings(KsnipConfig *config) :
	mConfig(config),
	mLayout(new QGridLayout(this)),
	mRotateWatermarkCheckbox(new QCheckBox(this)),
	mWatermarkImageLabel(new QLabel(this)),
	mUpdateWatermarkImageButton(new QPushButton(this))
{
	Q_ASSERT(mConfig != nullptr);

	mConfig = config;

	initGui();
	loadConfig();
}

WatermarkSettings::~WatermarkSettings()
{
	delete mRotateWatermarkCheckbox;
	delete mWatermarkImageLabel;
	delete mUpdateWatermarkImageButton;
}

void WatermarkSettings::saveSettings()
{
	mConfig->setRotateWatermarkEnabled(mRotateWatermarkCheckbox->isChecked());
}

void WatermarkSettings::initGui()
{
	mWatermarkImageLabel->setPixmap(mWatermarkImageLoader.load());
	mWatermarkImageLabel->setToolTip(tr("Watermark Image"));
	mWatermarkImageLabel->setAutoFillBackground(true);
	mWatermarkImageLabel->setFixedSize(ScaledSizeProvider::scaledSize(QSize(100, 100)));
	mWatermarkImageLabel->setScaledContents(true);
	mWatermarkImageLabel->setStyleSheet(QLatin1String("QLabel { background-color : white; }"));
	mUpdateWatermarkImageButton->setText(tr("Update"));
	connect(mUpdateWatermarkImageButton, &QPushButton::clicked, this, &WatermarkSettings::updateWatermarkImageClicked);

	mRotateWatermarkCheckbox->setText(tr("Rotate Watermark"));
	mRotateWatermarkCheckbox->setToolTip(tr("When enabled, Watermark will be added with a rotation of 45°"));

	mLayout->setAlignment(Qt::AlignTop);
	mLayout->addWidget(mWatermarkImageLabel, 0, 0);
	mLayout->addWidget(mUpdateWatermarkImageButton, 0, 1, Qt::AlignLeft);
	mLayout->setRowMinimumHeight(1, 15);
	mLayout->addWidget(mRotateWatermarkCheckbox, 2, 0);

	setTitle(tr("Watermark Settings"));
	setLayout(mLayout);
}

void WatermarkSettings::loadConfig()
{
	mRotateWatermarkCheckbox->setChecked(mConfig->rotateWatermarkEnabled());
}

void WatermarkSettings::updateWatermarkImageClicked()
{
	UpdateWatermarkOperation operation(this);
	auto successful = operation.execute();

	if(successful) {
		mWatermarkImageLabel->setPixmap(mWatermarkImageLoader.load());
	}
}
