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

#ifndef SETTINGSPICKERPOPUP_H
#define SETTINGSPICKERPOPUP_H

#include <QFrame>
#include <QtMath>

#include "SettingsPickerColorItem.h"
#include "SettingsPickerButton.h"

class SettingsPickerPopup : public QFrame
{
    Q_OBJECT

public:
    SettingsPickerPopup(int width, QWidget *parent = 0);
    ~SettingsPickerPopup();
    void insertColor(const QColor &color, const QString &text, int index);
    void exec();
    QColor color() const;
    void setColor(const QColor &color);
    bool fill() const;
    void setFill(bool fill);
    int size() const;
    void setSize(int size);
    SettingsPickerColorItem *findColor(const QColor &color) const;
    QColor colorAt(int index) const;
    void addColorGrid(bool colorDialog = true, bool fillCheckbox = true);
    void addSizeSlider(int  min, int  max, int  interval);
    bool isEmpty() const;
    void clear();

signals:
    void colorChanged(const QColor &);
    void fillChanged(bool);
    void sizeChanged(int);
    void hid();

public slots:
    void getColorFromDialog();

protected slots:
    void updateColor();
    void updateFill();
    void updateSize();
    void updateSizeLabel(int size);

protected:
    virtual void showEvent(QShowEvent *eevent) override;
    virtual void hideEvent(QHideEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *e) override;
    void regenerateColorGrid();

private:
    QList<SettingsPickerColorItem *>   mColorItems;
    QVBoxLayout                       *mLayout;
    QGridLayout                       *mColorGrid;
    SettingsPickerButton              *mMoreButton;
    QEventLoop                        *mEventLoop;
    QCheckBox                         *mFillCheckBox;
    QLabel                            *mSizeLabel;
    QSlider                           *mSizeSlider;
    QFrame                            *mSeparator;

    int mLastSelectedColorPos;
    int mColorColumns;
    QColor mColor;
};

#endif // SETTINGSPICKERPOPUP_H
