/*
 *  Copyright (C) 2016 Damir Porobic <https://github.com/damirporobic>
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
 *
 */

#ifndef CROPPANEL_H
#define CROPPANEL_H

#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QIntValidator>

#include "src/widgets/CaptureView.h"

class CropPanel : public QWidget
{
    Q_OBJECT
public:
    CropPanel(CaptureView *captureView);
    void show();

signals:
    void closing();

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

private:
    CaptureView *mCaptureView;
    QPushButton *mCropButton;
    QPushButton *mCancelButton;
    QLineEdit   *mPositionXLineEdit;
    QLineEdit   *mPositionYLineEdit;
    QLineEdit   *mWidthLineEdit;
    QLineEdit   *mHeightLineEdit;

    void initGui();

private slots:
    void close();
    void crop();
    void selectedRectChanged(const QRectF &rect);
    void xChanged(const QString &text);
    void yChanged(const QString &text);
    void widthChanged(const QString &text);
    void heightChanged(const QString &text);
};

#endif // CROPPANEL_H
