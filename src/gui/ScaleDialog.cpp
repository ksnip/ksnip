/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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

#include "ScaleDialog.h"

ScaleDialog::ScaleDialog(int width, int height, QWidget* parent) :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    mKeepAspectRatioCheckBox(new QCheckBox),
    mWidthPixelLabel(new QLabel),
    mHeightPixelLabel(new QLabel),
    mWidthPercentLabel(new QLabel),
    mHeightPercentLaberl(new QLabel),
    mWidthPixelSpinBox(new CustomSpinBox),
    mHeightPixelSpinBox(new CustomSpinBox),
    mWidthPercentSpinBox(new CustomSpinBox),
    mHeightPercentSpinBox(new CustomSpinBox),
    mOkButton(new QPushButton),
    mCancelButton(new QPushButton),
    mPixelGridLayout(new QGridLayout),
    mPercentGridLayout(new QGridLayout),
    mPixelGroupBox(new QGroupBox),
    mPercentGroupBox(new QGroupBox),
    mButtonRowLayout(new QHBoxLayout),
    mMainLayout(new QVBoxLayout)
{
    setWindowTitle(QApplication::applicationName() + " - " + tr("Scale Image"));

    mWidth = width;
    mHeight = height;

    initGui();
}

ScaleDialog::~ScaleDialog()
{
    delete mKeepAspectRatioCheckBox;
    delete mWidthPixelLabel;
    delete mHeightPixelLabel;
    delete mWidthPercentLabel;
    delete mHeightPercentLaberl;
    delete mWidthPixelSpinBox;
    delete mHeightPixelSpinBox;
    delete mWidthPercentSpinBox;
    delete mHeightPercentSpinBox;
    delete mOkButton;
    delete mCancelButton;
    delete mPixelGridLayout;
    delete mPercentGridLayout;
    delete mPixelGroupBox;
    delete mPercentGroupBox;
    delete mButtonRowLayout;
    delete mMainLayout;
}

void ScaleDialog::initGui()
{
    mKeepAspectRatioCheckBox->setText(tr("Keep Aspect Ratio"));
    mKeepAspectRatioCheckBox->setChecked(true);

    mWidthPixelLabel->setText(tr("Width:"));
    mHeightPixelLabel->setText(tr("Height:"));

    mWidthPercentLabel->setText(tr("Width:"));
    mHeightPercentLaberl->setText(tr("Height:"));

    mWidthPixelSpinBox->setSuffix(QStringLiteral("px"));
    mWidthPixelSpinBox->setMinimum(1);
    mWidthPixelSpinBox->setMaximum(4000);
    mWidthPixelSpinBox->setValue(mWidth);
    mWidthPixelSpinBox->setWrapping(false);
    connect(mWidthPixelSpinBox, &CustomSpinBox::valueChanged, [this](int newValue) {
        auto valuePercent = calculatePercent(mWidth, newValue);
        mWidthPercentSpinBox->setValue(valuePercent * 100);
        if (mKeepAspectRatioCheckBox->isChecked()) {
            setHeightInSpinBox(valuePercent);
        }
    });

    mHeightPixelSpinBox->setSuffix(QStringLiteral("px"));
    mHeightPixelSpinBox->setMinimum(1);
    mHeightPixelSpinBox->setMaximum(4000);
    mHeightPixelSpinBox->setValue(mHeight);
    mHeightPixelSpinBox->setWrapping(false);
    connect(mHeightPixelSpinBox, &CustomSpinBox::valueChanged, [this](int newValue) {
        auto valuePercent = calculatePercent(mHeight, newValue);
        mHeightPercentSpinBox->setValue(valuePercent * 100);
        if (mKeepAspectRatioCheckBox->isChecked()) {
            setWidthInSpinBox(valuePercent);
        }
    });
    mWidthPercentSpinBox->setSuffix(QStringLiteral("%"));
    mWidthPercentSpinBox->setMinimum(1);
    mWidthPercentSpinBox->setMaximum(400);
    mWidthPercentSpinBox->setValue(100);
    mWidthPercentSpinBox->setWrapping(false);
    connect(mWidthPercentSpinBox, &CustomSpinBox::valueChanged, [this](int newValue) {
        auto valuePercent = calculatePercent(newValue);
        mWidthPixelSpinBox->setValue(valuePercent * mWidth);
        if (mKeepAspectRatioCheckBox->isChecked()) {
            setHeightInSpinBox(valuePercent);
        }
    });
    mHeightPercentSpinBox->setSuffix(QStringLiteral("%"));
    mHeightPercentSpinBox->setMinimum(1);
    mHeightPercentSpinBox->setMaximum(400);
    mHeightPercentSpinBox->setValue(100);
    mHeightPercentSpinBox->setWrapping(false);
    connect(mHeightPercentSpinBox, &CustomSpinBox::valueChanged, [this](int newValue) {
        auto valuePercent = calculatePercent(newValue);
        mHeightPixelSpinBox->setValue(valuePercent * mHeight);
        if (mKeepAspectRatioCheckBox->isChecked()) {
            setWidthInSpinBox(valuePercent);
        }
    });

    mOkButton->setText(tr("OK"));
    connect(mOkButton, &QPushButton::clicked, [this]() {
        emit finished(mWidthPixelSpinBox->value(), mHeightPixelSpinBox->value());
        close();
    });

    mCancelButton->setText(tr("Cancel"));
    connect(mCancelButton, &QPushButton::clicked, [this]() {
        close();
    });

    mPixelGridLayout->addWidget(mWidthPixelLabel, 0, 0);
    mPixelGridLayout->addWidget(mWidthPixelSpinBox, 0, 1);
    mPixelGridLayout->addWidget(mHeightPixelLabel, 1, 0);
    mPixelGridLayout->addWidget(mHeightPixelSpinBox, 1, 1);

    mPercentGridLayout->addWidget(mWidthPercentLabel, 0, 0);
    mPercentGridLayout->addWidget(mWidthPercentSpinBox, 0, 1);
    mPercentGridLayout->addWidget(mHeightPercentLaberl, 1, 0);
    mPercentGridLayout->addWidget(mHeightPercentSpinBox, 1, 1);

    mPixelGroupBox->setTitle(tr("Pixel"));
    mPixelGroupBox->setLayout(mPixelGridLayout);

    mPercentGroupBox->setTitle(tr("Percent"));
    mPercentGroupBox->setLayout(mPercentGridLayout);

    mButtonRowLayout->addWidget(mOkButton);
    mButtonRowLayout->addWidget(mCancelButton);
    mButtonRowLayout->setAlignment(Qt::AlignRight);

    mMainLayout->addWidget(mKeepAspectRatioCheckBox);
    mMainLayout->addWidget(mPixelGroupBox);
    mMainLayout->addWidget(mPercentGroupBox);
    mMainLayout->addLayout(mButtonRowLayout);

    setLayout(mMainLayout);
}

float ScaleDialog::calculatePercent(int baseValue, int newValue) const
{
    return (float)newValue / (float)baseValue;
}

float ScaleDialog::calculatePercent(int newValue) const
{
    return (float)newValue / 100;
}

void ScaleDialog::setHeightInSpinBox(float percent)
{
    mHeightPixelSpinBox->setValue(percent * mHeight);
    mHeightPercentSpinBox->setValue(percent * 100);
}

void ScaleDialog::setWidthInSpinBox(float percent)
{
    mWidthPixelSpinBox->setValue(percent * mWidth);
    mWidthPercentSpinBox->setValue(percent * 100);
}
