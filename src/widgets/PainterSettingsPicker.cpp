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

#include "PainterSettingsPicker.h"
#include <cmath>

PainterSettingsPicker::PainterSettingsPicker(QWidget* parent, int colons) :
                                             QToolButton(parent),
                                             mPopup(nullptr)
{
    setFocusPolicy(Qt::StrongFocus);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    // Create color grid popup and connect to it.
    mPopup = new PainterSettingsPopup(colons, this);

    connect(mPopup, SIGNAL(colorChanged(const QColor&)), SLOT(updateColor(const QColor&)));
    connect(mPopup, SIGNAL(fillChanged(const bool&)), SLOT(updateFill(const bool&)));
    connect(mPopup, SIGNAL(sizeChanged(const int&)), SLOT(updateSize(const int&)));
    connect(mPopup, SIGNAL(hid()), SLOT(popupClosed()));

    // Connect this push button's pressed() signal.
    connect(this, SIGNAL(released()), SLOT(buttonPressed()));

    setPopupMode(QToolButton::InstantPopup);
}

PainterSettingsPicker::~PainterSettingsPicker()
{
}

void PainterSettingsPicker::buttonPressed()
{
    // Don't try to show popup when it's empty
    if (mPopup->isEmpty()) {
        return;
    }

    const QRect desktop = QApplication::desktop()->geometry();

    // Make sure the popup is inside the desktop.
    QPoint pos = mapToGlobal(rect().bottomLeft());
    if (pos.x() < desktop.left()) {
        pos.setX(desktop.left());
    }
    if (pos.y() < desktop.top()) {
        pos.setY(desktop.top());
    }

    if ((pos.x() + mPopup->sizeHint().width()) > desktop.width()) {
        pos.setX(desktop.width() - mPopup->sizeHint().width());
    }
    if ((pos.y() + mPopup->sizeHint().height()) > desktop.bottom()) {
        pos.setY(desktop.bottom() - mPopup->sizeHint().height());
    }
    mPopup->move(pos);

    // Remove focus from this widget, preventing the focus rect
    // from showing when the popup is shown. Order an update to
    // make sure the focus rect is cleared.

    clearFocus();
    update();
    setDown(true);

    // Allow keyboard navigation as soon as the popup shows.
    mPopup->setFocus();

    // Execute the popup. The popup will enter the event loop.
    mPopup->show();
}

void PainterSettingsPicker::popupClosed()
{
    setDown(false);
    setFocus();
}

/*
 * Returns the currently selected color
 */
QColor PainterSettingsPicker::color() const
{
    return mPopup->color();
}

/*
 * Sets the currently selected color
 */
void PainterSettingsPicker::setColor(const QColor& color)
{
    mPopup->setColor(color);
}

/*
 * Returns the true if fill is requested, otherwise false.
 */
bool PainterSettingsPicker::fill() const
{
    return mPopup->fill();
}

void PainterSettingsPicker::setFill(const bool& fill)
{
    mPopup->setFill(fill);
}

/*
 * Returns requested size, if size slider is not used, returns 0
 */
int PainterSettingsPicker::size() const
{
    return mPopup->size();
}

void PainterSettingsPicker::setSize(const int& size)
{
    mPopup->setSize(size);
}

/*
 * Adds a color grid to the popup, additionally, the more button and fill
 * checkbox can be added. The color grid can also be filled with default colors
 */
void PainterSettingsPicker::addPopupColorGrid(const bool& colorDialog,
                                              const bool& fillCheckbox,
                                              const bool& standardColor)
{
    mPopup->addColorGrid(colorDialog, fillCheckbox);
    if (standardColor) {
        insertStandardColor();
    }
}

void PainterSettingsPicker::addPopupSizeSlider(const int min, const int max, const int interval)
{
    mPopup->addSizeSlider(min, max, interval);
}

/*
 * Inserts a set of predefined colors
 */
void PainterSettingsPicker::insertStandardColor()
{
    mPopup->insertColor(QColor("white"), "White", -1);
    mPopup->insertColor(QColor("black"), "Black", -1);
    mPopup->insertColor(QColor("green"), "Green", -1);
    mPopup->insertColor(QColor("darkGreen"), "Dark green", -1);
    mPopup->insertColor(QColor("blue"), "Blue", -1);
    mPopup->insertColor(QColor("darkBlue"), "Dark blue", -1);
    mPopup->insertColor(QColor("cyan"), "Cyan", -1);
    mPopup->insertColor(QColor("darkCyan"), "Dark cyan", -1);
    mPopup->insertColor(QColor("magenta"), "Magenta", -1);
    mPopup->insertColor(QColor("darkMagenta"), "Dark magenta", -1);
    mPopup->insertColor(QColor("red"), "red", -1);
    mPopup->insertColor(QColor("yellow"), "Yellow", -1);
    mPopup->insertColor(QColor("grey"), "Grey", -1);
}

/*
 * Remove all elements from popup
 */
void PainterSettingsPicker::clearPopup()
{
    mPopup->clear();
}

/*
 * Called when a new color was selected on the color grid, further emits a
 * signal to inform other about this change.
 */
void PainterSettingsPicker::updateColor(const QColor& color)
{
    emit colorChanged(color);
}

/*
 * Same as updateColor only for fill.
 */
void PainterSettingsPicker::updateFill(const bool& fill)
{
    emit fillChanged(fill);
}

/*
 * Same as updateColor only for size
 */
void PainterSettingsPicker::updateSize(const int& size)
{
    emit sizeChanged(size);
}

/*
 * Adds a color to the color grid
 */
void PainterSettingsPicker::insertColor(const QColor& color, const QString& text, int index)
{
    mPopup->insertColor(color, text, index);
}

//
// PainterSettingsPopup
//
PainterSettingsPopup::PainterSettingsPopup(int width, QWidget* parent) :
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


PainterSettingsPopup::~PainterSettingsPopup()
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


void PainterSettingsPopup::insertColor(const QColor& color, const QString& text, int index)
{
    if (!mColorGrid) {
        return;
    }

    // Don't add colors that we have already.
    PainterSettingsColorItem* existingItem = findColor(color);
    PainterSettingsColorItem* lastSelectedItem = findColor(mColor);

    if (existingItem) {
        if (lastSelectedItem && existingItem != lastSelectedItem) {
            lastSelectedItem->setSelected(false);
        }
        existingItem->setFocus();
        existingItem->setSelected(true);
        return;
    }

    PainterSettingsColorItem* item = new PainterSettingsColorItem(color, text, this);

    if (lastSelectedItem) {
        lastSelectedItem->setSelected(false);
    } else {
        item->setSelected(true);
        mColor = color;
    }
    item->setFocus();

    connect(item, SIGNAL(selected()), SLOT(updateColor()));

    if (index == -1) {
        index = mColorItems.count();
    }

    mColorItems.insert((unsigned int)index, item);
    regenerateColorGrid();
    update();
}

void PainterSettingsPopup::exec()
{
    show();

    QEventLoop e;
    mEventLoop = &e;
    (void) e.exec();
    mEventLoop = 0;
}

QColor PainterSettingsPopup::color() const
{
    return mColor;
}

/*
 * Sets the color grid to the specified color, if this color is not already in
 * the grid, it adds it to the end.
 */
void PainterSettingsPopup::setColor(const QColor& color)
{
    PainterSettingsColorItem* newSelected = findColor(color);
    if (!newSelected) {
        insertColor(color, tr("Custom"), -1);
        newSelected = findColor(color);
    }

    for (PainterSettingsColorItem* item : mColorItems) {
        if (item->isSelected()) {
            item->setSelected(false);
        }
    }

    newSelected->setSelected(true);
    emit colorChanged(color);
}

bool PainterSettingsPopup::fill() const
{
    if (mFillCheckBox == nullptr) {
        return false;
    }
    return mFillCheckBox->isChecked();
}

void PainterSettingsPopup::setFill(const bool& fill)
{
    if (mFillCheckBox == nullptr || mFillCheckBox->isChecked() == fill) {
        return;
    }
    mFillCheckBox->setChecked(fill);
    emit fillChanged(fill);
}

int PainterSettingsPopup::size() const
{
    if (!mSizeSlider) {
        return 0;
    }
    return mSizeSlider->value();
}

void PainterSettingsPopup::setSize(const int& size)
{
    if (!mSizeSlider) {
        return;
    }
    int s = size;
    if (size < mSizeSlider->minimum() || size < 0) {
        s = mSizeSlider->minimum();
    } else if (size > mSizeSlider->maximum()) {
        s = mSizeSlider->maximum();
    }
    mSizeSlider->setValue(s);
    updateSizeLabel(s);
    emit sizeChanged(s);
}

PainterSettingsColorItem* PainterSettingsPopup::findColor(const QColor& color) const
{
    for (PainterSettingsColorItem* item : mColorItems) {
        if (item->color() == color) {
            return item;
        }
    }

    return nullptr;
}

QColor PainterSettingsPopup::colorAt(int index) const
{
    if (index < 0 || index > (int) mColorItems.count() - 1) {
        return QColor();
    }

    PainterSettingsPopup* that = (PainterSettingsPopup*)this;
    return that->mColorItems.at(index)->color();
}

void PainterSettingsPopup::addColorGrid(const bool& colorDialog, const bool& fillCheckbox)
{
    if (!mColorGrid) {
        mColorGrid = new QGridLayout();
        mColorGrid->setMargin(1);
        mColorGrid->setSpacing(0);
    }

    if (!mMoreButton && colorDialog) {
        mMoreButton = new PainterSettingsButton(this);
        mMoreButton->setFixedWidth(24);
        mMoreButton->setFixedHeight(21);
        mMoreButton->setFrameRect(QRect(2, 2, 20, 17));
        connect(mMoreButton, SIGNAL(clicked()), SLOT(getColorFromDialog()));
    }

    if (!mFillCheckBox && fillCheckbox) {
        mFillCheckBox = new QCheckBox(tr("Solid Fill"));
        mFillCheckBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        connect(mFillCheckBox, SIGNAL(clicked()), this, SLOT(updateFill()));
        mLayout->insertWidget(1, mFillCheckBox);
    }
    regenerateColorGrid();
    update();
}

void PainterSettingsPopup::addSizeSlider(const int min, const int max, const int interval)
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
        mSizeSlider->setTickInterval(interval);
        mSizeSlider->setMinimum(min);
        mSizeSlider->setMaximum(max);
        mSizeSlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        connect(mSizeSlider, SIGNAL(sliderReleased()), SLOT(updateSize()));
        connect(mSizeSlider, SIGNAL(valueChanged(int)), SLOT(updateSizeLabel(int)));
        mLayout->insertWidget(4, mSizeSlider);
    }
}

/*
 * Returns true is no elements have been added to the popup so there is no point
 * in showing the popup.
 */
bool PainterSettingsPopup::isEmpty() const
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
void PainterSettingsPopup::clear()
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

    for (PainterSettingsColorItem* item : mColorItems) {
        mColorItems.removeOne(item);
        delete item;
    }
}

/*
 * Opens a color dialog and lets the user select a color, the new selected color
 * is added to the color grid if not already in there and set to the current
 * color
 */
void PainterSettingsPopup::getColorFromDialog()
{
    QColor color = QColorDialog::getColor(mColor, parentWidget());
    if (!color.isValid()) {
        return;
    }
    setColor(color);
}

/*
 * Called when one of the colors was selected, it emits the colorChange signal
 * to inform everyone of the change.
 */
void PainterSettingsPopup::updateColor()
{
    if (!mColorGrid) {
        return;
    }

    for (PainterSettingsColorItem* item : mColorItems) {
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
void PainterSettingsPopup::updateFill()
{
    emit fillChanged(mFillCheckBox->isChecked());
    hide();
}

void PainterSettingsPopup::updateSize()
{
    emit sizeChanged(mSizeSlider->value());
    hide();
}

void PainterSettingsPopup::updateSizeLabel(int size)
{
    mSizeLabel->setText(tr("Size") + ": " + QString::number(size) + "px");

    // When the users clicks somewhere outside the slider, the value is changed
    // but no release event is triggered so we check here if the value was
    // changed while the selider was not done, if yes, simulate release event.
    if (mSizeSlider && !mSizeSlider->isSliderDown()) {
        updateSize();
    }
}

void PainterSettingsPopup::showEvent(QShowEvent*)
{
    for (PainterSettingsColorItem* item : mColorItems) {
        if (item->isSelected()) {
            item->setFocus();
            break;
        }
    }
}

void PainterSettingsPopup::hideEvent(QHideEvent* e)
{
    if (mEventLoop) {
        mEventLoop->exit();
    }

    setFocus();

    emit hid();
    QFrame::hideEvent(e);
}

void PainterSettingsPopup::mouseReleaseEvent(QMouseEvent* e)
{
    if (!rect().contains(e->pos())) {
        hide();
    }
}

void PainterSettingsPopup::regenerateColorGrid()
{
    if (!mColorGrid) {
        return;
    }

    int columns = mColorColumns;
    if (columns == -1) {
        columns = (int) std::ceil(std::sqrt((float) mColorItems.count()));
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

    int ccol = 0, crow = 0;
    for (int i = 0; i < mColorItems.size(); ++i) {
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

//
// PainterSettingsColorItem
//

PainterSettingsColorItem::PainterSettingsColorItem(const QColor& color, const QString& text, QWidget* parent) :
    QFrame(parent), mColor(color), mText(text), mSelected(false)
{
    setToolTip(mText);
    setFixedWidth(24);
    setFixedHeight(21);
}

PainterSettingsColorItem::~PainterSettingsColorItem()
{
}

QColor PainterSettingsColorItem::color() const
{
    return mColor;
}

QString PainterSettingsColorItem::text() const
{
    return mText;
}

bool PainterSettingsColorItem::isSelected() const
{
    return mSelected;
}

void PainterSettingsColorItem::setSelected(bool selected)
{
    mSelected = selected;
    update();
}

void PainterSettingsColorItem::setColor(const QColor& color, const QString& text)
{
    mColor = color;
    mText = text;
    setToolTip(mText);
    update();
}

void PainterSettingsColorItem::mouseMoveEvent(QMouseEvent* event)
{
    setFocus();
    update();
}

void PainterSettingsColorItem::mouseReleaseEvent(QMouseEvent* event)
{
    mSelected = true;
    emit selected();
}

void PainterSettingsColorItem::mousePressEvent(QMouseEvent* event)
{
    setFocus();
    update();
}

void PainterSettingsColorItem::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    int w = width();            // width of cell in pixels
    int h = height();           // height of cell in pixels

    p.setPen(QPen(Qt::gray, 0, Qt::SolidLine));

    if (mSelected) {
        p.drawRect(1, 1, w - 3, h - 3);
    }

    p.setPen(QPen(Qt::black, 0, Qt::SolidLine));
    p.drawRect(3, 3, w - 7, h - 7);
    p.fillRect(QRect(4, 4, w - 8, h - 8), QBrush(mColor));

    if (hasFocus()) {
        p.drawRect(0, 0, w - 1, h - 1);
    }
}

//
// PainterSettingsButton
//
PainterSettingsButton::PainterSettingsButton(QWidget* parent) : QFrame(parent)
{
    setFrameStyle(StyledPanel);
}

void PainterSettingsButton::mousePressEvent(QMouseEvent* event)
{
    setFrameShadow(Sunken);
    update();
}

void PainterSettingsButton::mouseMoveEvent(QMouseEvent* event)
{
    setFocus();
    update();
}

void PainterSettingsButton::mouseReleaseEvent(QMouseEvent* event)
{
    setFrameShadow(Raised);
    repaint();
    emit clicked();
}

void PainterSettingsButton::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down
            || event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        qApp->sendEvent(parent(), event);
    } else if (event->key() == Qt::Key_Enter
               || event->key() == Qt::Key_Space || event->key() == Qt::Key_Return) {
        setFrameShadow(Sunken);
        update();
    } else {
        QFrame::keyPressEvent(event);
    }
}

void PainterSettingsButton::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down
            || event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        qApp->sendEvent(parent(), event);
    } else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Space
               || event->key() == Qt::Key_Return) {
        setFrameShadow(Raised);
        repaint();
        emit clicked();
    } else {
        QFrame::keyReleaseEvent(event);
    }
}

void PainterSettingsButton::focusInEvent(QFocusEvent* event)
{
    setFrameShadow(Raised);
    update();
    QFrame::focusOutEvent(event);
}

void PainterSettingsButton::focusOutEvent(QFocusEvent* event)
{
    setFrameShadow(Raised);
    update();
    QFrame::focusOutEvent(event);
}

void PainterSettingsButton::paintEvent(QPaintEvent* event)
{
    QFrame::paintEvent(event);

    QPainter p(this);
    p.fillRect(contentsRect(), palette().button());

    QRect r = rect();

    int offset = frameShadow() == Sunken ? 1 : 0;

    QPen pen(palette().buttonText(), 1);
    p.setPen(pen);

    p.drawRect(r.center().x() + offset - 4, r.center().y() + offset, 1, 1);
    p.drawRect(r.center().x() + offset    , r.center().y() + offset, 1, 1);
    p.drawRect(r.center().x() + offset + 4, r.center().y() + offset, 1, 1);
    if (hasFocus()) {
        p.setPen(QPen(Qt::black, 0, Qt::SolidLine));
        p.drawRect(0, 0, width() - 1, height() - 1);
    }

    p.end();

}

// #include "PainterSettingsPicker.moc"
