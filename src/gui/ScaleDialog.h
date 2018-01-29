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

#ifndef SCALEDIALOG_H
#define SCALEDIALOG_H

#include <QDialog>
#include <QApplication>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>

#include "src/widgets/CustomSpinBox.h"

class ScaleDialog : public QDialog
{
    Q_OBJECT
public:
    ScaleDialog(int width, int height, QWidget *parent = nullptr);
    ~ScaleDialog();

signals:
    void finished(float percentWidth, float percentHeight);

private:
    int            mWidth;
    int            mHeight;
    QCheckBox     *mKeepAspectRatioCheckBox;
    QLabel        *mWidthPixelLabel;
    QLabel        *mHeightPixelLabel;
    QLabel        *mWidthPercentLabel;
    QLabel        *mHeightPercentLaberl;
    CustomSpinBox *mWidthPixelSpinBox;
    CustomSpinBox *mHeightPixelSpinBox;
    CustomSpinBox *mWidthPercentSpinBox;
    CustomSpinBox *mHeightPercentSpinBox;
    QPushButton   *mOkButton;
    QPushButton   *mCancelButton;
    QGridLayout   *mPixelGridLayout;
    QGridLayout   *mPercentGridLayout;
    QGroupBox     *mPixelGroupBox;
    QGroupBox     *mPercentGroupBox;
    QHBoxLayout   *mButtonRowLayout;
    QVBoxLayout   *mMainLayout;

    void initGui();
    float calculatePercent(int baseValue, int newValue) const;
    float calculatePercent(int newValue) const;
    void setHeight(float percent);
    void setWidth(float percent);
    void setHeightInSpinBox(float percent);
    void setWidthInSpinBox(float percent);
};

#endif // SCALEDIALOG_H
