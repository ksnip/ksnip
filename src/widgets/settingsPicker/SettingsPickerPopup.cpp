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

#include "SettingsPickerPopup.h"

SettingsPickerPopup::SettingsPickerPopup(int width, QWidget* parent) :
    QFrame(parent, Qt::Popup),
    mLayout(new QVBoxLayout(this)),
    mColorGrid(nullptr),
    mMoreButton(nullptr),
    mEventLoop(nullptr),
    mFillCheckBox(nullptr),
    mSizeLabel(nullptr),
    mSizeSlider(nullptr),
    mSeparator(nullptr),
    mColorColumns(width)
{
    setFrameStyle(QFrame::StyledPanel);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    mLayout->setContentsMargins(2, 2, 2, 2);
    mLayout->setSpacing(0);

    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    regenerateColorGrid();
}

SettingsPickerPopup::~SettingsPickerPopup()
{
    if (mEventLoop) {
        mEventLoop->exit();
    }
    delete mSizeLabel;
    delete mFillCheckBox;
    delete mMoreButton;
    delete mColorGrid;
    delete mLayout;

}


void SettingsPickerPopup::insertColor(const QColor& color, const QString& text, int index)
{
    if (!mColorGrid) {
        return;
    }

    // Don't add colors that we have already.
    auto existingItem = findColor(color);
    auto lastSelectedItem = findColor(mColor);

    if (existingItem) {
        if (lastSelectedItem && existingItem != lastSelectedItem) {
            lastSelectedItem->setSelected(false);
        }
        existingItem->setFocus();
        existingItem->setSelected(true);
        return;
    }

    auto item = new SettingsPickerColorItem(color, text, this);

    if (lastSelectedItem) {
        lastSelectedItem->setSelected(false);
    } else {
        item->setSelected(true);
        mColor = color;
    }
    item->setFocus();

    connect(item, &SettingsPickerColorItem::selected,
            this, &SettingsPickerPopup::updateColor);

    if (index == -1) {
        index = mColorItems.count();
    }

    mColorItems.insert((unsigned int)index, item);
    regenerateColorGrid();
    update();
}

void SettingsPickerPopup::exec()
{
    show();

    QEventLoop e;
    mEventLoop = &e;
    (void) e.exec();
    mEventLoop = 0;
}

QColor SettingsPickerPopup::color() const
{
    return mColor;
}

/*
 * Sets the color grid to the specified color, if this color is not already in
 * the grid, it adds it to the end.
 */
void SettingsPickerPopup::setColor(const QColor& color)
{
    auto newSelected = findColor(color);
    if (!newSelected) {
        insertColor(color, tr("Custom"), -1);
        newSelected = findColor(color);
    }

    for (auto item : mColorItems) {
        if (item->isSelected()) {
            item->setSelected(false);
        }
    }

    newSelected->setSelected(true);
    emit colorChanged(color);
}

bool SettingsPickerPopup::fill() const
{
    if (mFillCheckBox == nullptr) {
        return false;
    }
    return mFillCheckBox->isChecked();
}

void SettingsPickerPopup::setFill(bool  fill)
{
    if (mFillCheckBox == nullptr || mFillCheckBox->isChecked() == fill) {
        return;
    }
    mFillCheckBox->setChecked(fill);
    emit fillChanged(fill);
}

int SettingsPickerPopup::size() const
{
    if (!mSizeSlider) {
        return 0;
    }
    return mSizeSlider->value();
}

void SettingsPickerPopup::setSize(int  newSize)
{
    if (!mSizeSlider) {
        return;
    }
    auto size = newSize;
    if (newSize < mSizeSlider->minimum() || newSize < 0) {
        size = mSizeSlider->minimum();
    } else if (newSize > mSizeSlider->maximum()) {
        size = mSizeSlider->maximum();
    }
    mSizeSlider->setValue(size);
    updateSizeLabel(size);
    emit sizeChanged(size);
}

SettingsPickerColorItem* SettingsPickerPopup::findColor(const QColor& color) const
{
    for (auto item : mColorItems) {
        if (item->color() == color) {
            return item;
        }
    }

    return nullptr;
}

QColor SettingsPickerPopup::colorAt(int index) const
{
    if (index < 0 || index > (int) mColorItems.count() - 1) {
        return QColor();
    }

    SettingsPickerPopup* that = (SettingsPickerPopup*)this;
    return that->mColorItems.at(index)->color();
}

void SettingsPickerPopup::addColorGrid(bool colorDialog, bool fillCheckbox)
{
    if (!mColorGrid) {
        mColorGrid = new QGridLayout();
        mColorGrid->setMargin(1);
        mColorGrid->setSpacing(0);
    }

    if (!mMoreButton && colorDialog) {
        mMoreButton = new SettingsPickerButton(this);
        mMoreButton->setFixedWidth(24);
        mMoreButton->setFixedHeight(21);
        mMoreButton->setFrameRect(QRect(2, 2, 20, 17));
        connect(mMoreButton, &SettingsPickerButton::clicked,
                this, &SettingsPickerPopup::getColorFromDialog);
    }

    if (!mFillCheckBox && fillCheckbox) {
        mFillCheckBox = new QCheckBox(tr("Solid Fill"));
        mFillCheckBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        connect(mFillCheckBox, &QCheckBox::clicked,
                this, &SettingsPickerPopup::updateFill);
        mLayout->insertWidget(1, mFillCheckBox);
    }
    regenerateColorGrid();
    update();
}

void SettingsPickerPopup::addSizeSlider(int min, int max, int interval)
{
    if (!mSizeSlider) {
        // Only add a separator when we have a color grid
        if (mColorGrid) {
            mSeparator = new QFrame();
            mSeparator->setFrameShape(QFrame::HLine);
            mSeparator->setMinimumHeight(15);
            mLayout->insertWidget(2, mSeparator);
            mLayout->insertWidget(2, mSeparator);
        }

        mSizeLabel = new QLabel();
        mSizeLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        mLayout->insertWidget(3, mSizeLabel);
        updateSizeLabel(0);

        mSizeSlider = new QSlider(Qt::Orientation::Horizontal);
        mSizeSlider->setMinimum(min);
        mSizeSlider->setMaximum(max);
        mSizeSlider->setTickInterval(interval);
        mSizeSlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        connect(mSizeSlider, &QSlider::sliderReleased,
                this, &SettingsPickerPopup::updateSize);
        connect(mSizeSlider, &QSlider::valueChanged,
                this, &SettingsPickerPopup::updateSizeLabel);
        mLayout->insertWidget(4, mSizeSlider);
    }
}

/*
 * Returns true is no elements have been added to the popup so there is no point
 * in showing the popup.
 */
bool SettingsPickerPopup::isEmpty() const
{
    if (!mColorGrid && !mSizeSlider) {
        return true;
    }
    return false;
}

/*
 * Removes all popup elements, leaves a clean popup that can be filled again.
 * Should be used before initializing the popup again
 */
void SettingsPickerPopup::clear()
{
    delete mMoreButton;
    mMoreButton = nullptr;

    delete mFillCheckBox;
    mFillCheckBox = nullptr;

    delete mSizeSlider;
    mSizeSlider = nullptr;

    delete mSizeLabel;
    mSizeLabel = nullptr;

    delete mColorGrid;
    mColorGrid = nullptr;

    delete mSeparator;
    mSeparator = nullptr;

    for (auto item : mColorItems) {
        mColorItems.removeOne(item);
        delete item;
    }
}

/*
 * Opens a color dialog and lets the user select a color, the new selected color
 * is added to the color grid if not already in there and set to the current
 * color
 */
void SettingsPickerPopup::getColorFromDialog()
{
    auto color = QColorDialog::getColor(mColor, parentWidget());
    if (!color.isValid()) {
        return;
    }
    setColor(color);
}

/*
 * Called when one of the colors was selected, it emits the colorChange signal
 * to inform everyone of the change.
 */
void SettingsPickerPopup::updateColor()
{
    if (!mColorGrid) {
        return;
    }

    for (auto item : mColorItems) {
        if (item != sender()) {
            item->setSelected(false);
        } else {
            mColor = item->color();
            emit colorChanged(item->color());
        }
    }
    hide();
}

/*
 * Called when the checkbox state has changed, emit the fillChanged signal to
 * inform everyone of the changed state.
 */
void SettingsPickerPopup::updateFill()
{
    emit fillChanged(mFillCheckBox->isChecked());
    hide();
}

void SettingsPickerPopup::updateSize()
{
    emit sizeChanged(mSizeSlider->value());
    hide();
}

void SettingsPickerPopup::updateSizeLabel(int size)
{
    mSizeLabel->setText(tr("Size") + ": " + QString::number(size) + "px");

    // When the users clicks somewhere outside the slider, the value is changed
    // but no release event is triggered so we check here if the value was
    // changed while the selider was not done, if yes, simulate release event.
    if (mSizeSlider && !mSizeSlider->isSliderDown()) {
        updateSize();
    }
}

void SettingsPickerPopup::showEvent(QShowEvent*)
{
    for (auto item : mColorItems) {
        if (item->isSelected()) {
            item->setFocus();
            break;
        }
    }
}

void SettingsPickerPopup::hideEvent(QHideEvent* e)
{
    if (mEventLoop) {
        mEventLoop->exit();
    }

    setFocus();

    emit hid();
    QFrame::hideEvent(e);
}

void SettingsPickerPopup::mouseReleaseEvent(QMouseEvent* e)
{
    if (!rect().contains(e->pos())) {
        hide();
    }
}

void SettingsPickerPopup::regenerateColorGrid()
{
    if (!mColorGrid) {
        return;
    }

    auto columns = mColorColumns;
    if (columns == -1) {
        columns = qCeil(qSqrt(mColorItems.count()));
    }

    // When the number of columns grows, the number of rows will
    // fall. There's no way to shrink a grid, so we create a new
    // one.
    if (mColorGrid) {
        delete mColorGrid;
    }
    mColorGrid = new QGridLayout();
    mColorGrid->setMargin(1);
    mColorGrid->setSpacing(0);

    auto ccol = 0, crow = 0;
    for (auto i = 0; i < mColorItems.size(); ++i) {
        if (mColorItems.at(i)) {
            mColorGrid->addWidget(mColorItems.at(i), crow, ccol++);
            if (ccol == columns) {
                ++crow;
                ccol = 0;
            }
        }
    }

    if (mMoreButton) {
        mColorGrid->addWidget(mMoreButton, crow, ccol);
    }
    mLayout->insertLayout(0, mColorGrid);
}
