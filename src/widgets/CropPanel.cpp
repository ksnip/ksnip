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

#include "CropPanel.h"

CropPanel::CropPanel(CaptureView* captureView) : QWidget(),
    mCropButton(new QPushButton()),
    mCancelButton(new QPushButton()),
    mPositionXLineEdit(new QLineEdit()),
    mPositionYLineEdit(new QLineEdit()),
    mWidthLineEdit(new QLineEdit()),
    mHeightLineEdit(new QLineEdit())
{
    mCaptureView = captureView;
    initGui();

    connect(mCaptureView, SIGNAL(selectedRectChanged(const QRectF&)),
            SLOT(selectedRectChanged(const QRectF&)));
}

//
// Public Functions
//
void CropPanel::show()
{
    mCaptureView->setIsCropping(true);
    selectedRectChanged(mCaptureView->getSelectedRect());
    QWidget::show();
}

//
// Protected Functions
//
void CropPanel::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape) {
        closeClicked();
    } else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        cropClicked();
    }
    QWidget::keyPressEvent(event);
}

//
// Private Function
//
void CropPanel::initGui()
{
    mCropButton->setText(tr("Crop"));
    connect(mCropButton, SIGNAL(clicked()), this, SLOT(cropClicked()));

    mCancelButton->setText(tr("Cancel"));
    connect(mCancelButton, SIGNAL(clicked()), this, SLOT(closeClicked()));


    QHBoxLayout* layout = new QHBoxLayout();
    layout->setAlignment(Qt::AlignCenter);

    QLabel* label = new QLabel(tr("X:"));
    layout->addWidget(label, 0, Qt::AlignCenter);

    mPositionXLineEdit->setValidator(new QIntValidator(0, 9999, mPositionXLineEdit));
    mPositionXLineEdit->setFixedSize(40, mPositionXLineEdit->minimumSizeHint().height());
    connect(mPositionXLineEdit, SIGNAL(textEdited(QString)), this, SLOT(xChanged(QString)));
    layout->addWidget(mPositionXLineEdit, 0, Qt::AlignCenter);

    label = new QLabel(tr("Y:"));
    layout->addWidget(label, 0, Qt::AlignCenter);

    mPositionYLineEdit->setValidator(new QIntValidator(0, 9999, mPositionYLineEdit));
    mPositionYLineEdit->setFixedSize(40, mPositionYLineEdit->minimumSizeHint().height());
    connect(mPositionYLineEdit, SIGNAL(textEdited(QString)), this, SLOT(yChanged(QString)));
    layout->addWidget(mPositionYLineEdit, 0, Qt::AlignCenter);

    label = new QLabel(tr("W:"));
    layout->addWidget(label, 0, Qt::AlignCenter);

    mWidthLineEdit->setValidator(new QIntValidator(0, 9999, mWidthLineEdit));
    mWidthLineEdit->setFixedSize(40, mWidthLineEdit->minimumSizeHint().height());
    connect(mWidthLineEdit, SIGNAL(textEdited(QString)), this, SLOT(widthChanged(QString)));
    layout->addWidget(mWidthLineEdit, 0, Qt::AlignCenter);

    label = new QLabel(tr("H:"));
    layout->addWidget(label, 0, Qt::AlignCenter);

    mHeightLineEdit->setValidator(new QIntValidator(0, 9999, mHeightLineEdit));
    mHeightLineEdit->setFixedSize(40, mHeightLineEdit->minimumSizeHint().height());
    connect(mHeightLineEdit, SIGNAL(textEdited(QString)), this, SLOT(heightChanged(QString)));
    layout->addWidget(mHeightLineEdit, 0, Qt::AlignCenter);

    layout->addWidget(mCropButton, 0, Qt::AlignCenter);
    layout->addWidget(mCancelButton, 0, Qt::AlignCenter);

    setLayout(layout);
}

//
// Private Slots
//

void CropPanel::closeClicked()
{
    mCaptureView->setIsCropping(false);
    emit close();
}

void CropPanel::cropClicked()
{
    mCaptureView->crop();
    mCaptureView->setIsCropping(false);
    emit  close();
}

void CropPanel::selectedRectChanged(const QRectF& rect)
{
    mPositionXLineEdit->setText(QString::number(rect.topLeft().x()));
    mPositionYLineEdit->setText(QString::number(rect.topLeft().y()));
    mWidthLineEdit->setText(QString::number(rect.width()));
    mHeightLineEdit->setText(QString::number(rect.height()));
}

void CropPanel::xChanged(const QString& text)
{
    int x = text.toInt();
    QRectF rect = mCaptureView->getSelectedRect();

    // Can't enter negative number
    if ((x + rect.width()) <= mCaptureView->sceneRect().width()) {
        rect.moveTo(x, rect.y());
        mCaptureView->setSelectedRect(rect);
    } else {
        rect.moveTo(mCaptureView->sceneRect().width() - rect.width(), rect.y());
        mCaptureView->setSelectedRect(rect);
        selectedRectChanged(rect);
    }
}

void CropPanel::yChanged(const QString& text)
{
    int y = text.toInt();
    QRectF rect = mCaptureView->getSelectedRect();

    // Can't enter negative number
    if ((y + rect.height()) <= mCaptureView->sceneRect().height()) {
        rect.moveTo(rect.x(), y);
        mCaptureView->setSelectedRect(rect);
    } else {
        rect.moveTo(rect.x(), mCaptureView->sceneRect().height() - rect.height());
        mCaptureView->setSelectedRect(rect);
        selectedRectChanged(rect);
    }
}

void CropPanel::widthChanged(const QString& text)
{
    int width = text.toInt();
    QRectF rect = mCaptureView->getSelectedRect();

    // Can't enter negative number
    if ((rect.x() + width) <= mCaptureView->sceneRect().width()) {
        rect.setWidth(width);
        mCaptureView->setSelectedRect(rect);
    } else {
        rect.setWidth(mCaptureView->sceneRect().width() - rect.x());
        mCaptureView->setSelectedRect(rect);
        selectedRectChanged(rect);
    }
}

void CropPanel::heightChanged(const QString& text)
{
    int height = text.toInt();
    QRectF rect = mCaptureView->getSelectedRect();

    // Can't enter negative number
    if ((rect.y() + height) <= mCaptureView->sceneRect().height()) {
        rect.setHeight(height);
        mCaptureView->setSelectedRect(rect);
    } else {
        rect.setHeight(mCaptureView->sceneRect().height() - rect.y());
        mCaptureView->setSelectedRect(rect);
        selectedRectChanged(rect);
    }
}
