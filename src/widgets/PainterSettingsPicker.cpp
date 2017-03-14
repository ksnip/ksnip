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

PainterSettingsPicker::PainterSettingsPicker(QWidget *parent, int cols, bool enableColorDialog) : 
                                             QToolButton(parent), popup(0), withColorDialog(enableColorDialog)
{
    setFocusPolicy(Qt::StrongFocus);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
//     setAutoDefault(false);
//     setAutoFillBackground(true);
    setCheckable(true);

    // Set text
    setText(tr("Black"));
    firstInserted = false;

    // Create and set icon
    col = Qt::black;
    dirty = true;

    // Create color grid popup and connect to it.
    popup = new PainterSettingsColorPopup(cols, withColorDialog, this);
    connect(popup, SIGNAL(selected(const QColor &)),
            SLOT(setCurrentColor(const QColor &)));
    connect(popup, SIGNAL(hid()), SLOT(popupClosed()));

    // Connect this push button's pressed() signal.
    connect(this, SIGNAL(toggled(bool)), SLOT(buttonPressed(bool)));

    setIcon(QIcon::fromTheme("preferences-system"));
}

PainterSettingsPicker::~PainterSettingsPicker()
{
}

void PainterSettingsPicker::buttonPressed(bool toggled)
{
    if (!toggled)
        return;

    const QRect desktop = QApplication::desktop()->geometry();
    // Make sure the popup is inside the desktop.
    QPoint pos = mapToGlobal(rect().bottomLeft());
    if (pos.x() < desktop.left())
        pos.setX(desktop.left());
    if (pos.y() < desktop.top())
        pos.setY(desktop.top());

    if ((pos.x() + popup->sizeHint().width()) > desktop.width())
        pos.setX(desktop.width() - popup->sizeHint().width());
    if ((pos.y() + popup->sizeHint().height()) > desktop.bottom())
        pos.setY(desktop.bottom() - popup->sizeHint().height());
    popup->move(pos);

    if (PainterSettingsColorItem *item = popup->find(col))
        item->setSelected(true);

    // Remove focus from this widget, preventing the focus rect
    // from showing when the popup is shown. Order an update to
    // make sure the focus rect is cleared.
    clearFocus();
    update();

    // Allow keyboard navigation as soon as the popup shows.
    popup->setFocus();

    // Execute the popup. The popup will enter the event loop.
    popup->show();
}

void PainterSettingsPicker::paintEvent(QPaintEvent *e)
{
    if (dirty) {
        int iconSize = style()->pixelMetric(QStyle::PM_SmallIconSize);
        QPixmap pix(iconSize, iconSize);
        pix.fill(palette().button().color());

        QPainter p(&pix);

        int w = pix.width();   // width of cell in pixels
        int h = pix.height();  // height of cell in pixels
        p.setPen(QPen(Qt::gray));
        p.setBrush(col);
        p.drawRect(2, 2, w - 5, h - 5);
//         setIcon(QIcon(pix));

        dirty = false;
    }
    QToolButton::paintEvent(e);
}

void PainterSettingsPicker::popupClosed()
{
    setChecked(false);
    setFocus();
}

QColor PainterSettingsPicker::currentColor() const
{
    return col;
}

QColor PainterSettingsPicker::color(int index) const
{
    return popup->color(index);
}

void PainterSettingsPicker::setStandardColors()
{
    insertColor(Qt::black, tr("Black"));
    insertColor(Qt::white, tr("White"));
    insertColor(Qt::red, tr("Red"));
    insertColor(Qt::darkRed, tr("Dark red"));
    insertColor(Qt::green, tr("Green"));
    insertColor(Qt::darkGreen, tr("Dark green"));
    insertColor(Qt::blue, tr("Blue"));
    insertColor(Qt::darkBlue, tr("Dark blue"));
    insertColor(Qt::cyan, tr("Cyan"));
    insertColor(Qt::darkCyan, tr("Dark cyan"));
    insertColor(Qt::magenta, tr("Magenta"));
    insertColor(Qt::darkMagenta, tr("Dark magenta"));
    insertColor(Qt::yellow, tr("Yellow"));
    insertColor(Qt::darkYellow, tr("Dark yellow"));
    insertColor(Qt::gray, tr("Gray"));
    insertColor(Qt::darkGray, tr("Dark gray"));
    insertColor(Qt::lightGray, tr("Light gray"));
}

void PainterSettingsPicker::setCurrentColor(const QColor &color)
{
    if (col == color || !color.isValid())
        return;

    PainterSettingsColorItem *item = popup->find(color);
    if (!item) {
        insertColor(color, tr("Custom"));
        item = popup->find(color);
    }

    col = color;
    setText(item->text());

    dirty = true;

    popup->hide();
    repaint();

    item->setSelected(true);
    emit colorChanged(color);
}

void PainterSettingsPicker::insertColor(const QColor &color, const QString &text, int index)
{
    popup->insertColor(color, text, index);
    if (!firstInserted) {
        col = color;
        setText(text);
        firstInserted = true;
    }
}

void PainterSettingsPicker::setColorDialogEnabled(bool enabled)
{
    withColorDialog = enabled;
}

bool PainterSettingsPicker::colorDialogEnabled() const
{
    return withColorDialog;
}

QColor PainterSettingsPicker::getColor(const QPoint &point, bool allowCustomColors)
{
    PainterSettingsColorPopup popup(-1, allowCustomColors);

    popup.insertColor(Qt::black, tr("Black"), 0);
    popup.insertColor(Qt::white, tr("White"), 1);
    popup.insertColor(Qt::red, tr("Red"), 2);
    popup.insertColor(Qt::darkRed, tr("Dark red"), 3);
    popup.insertColor(Qt::green, tr("Green"), 4);
    popup.insertColor(Qt::darkGreen, tr("Dark green"), 5);
    popup.insertColor(Qt::blue, tr("Blue"), 6);
    popup.insertColor(Qt::darkBlue, tr("Dark blue"), 7);
    popup.insertColor(Qt::cyan, tr("Cyan"), 8);
    popup.insertColor(Qt::darkCyan, tr("Dark cyan"), 9);
    popup.insertColor(Qt::magenta, tr("Magenta"), 10);
    popup.insertColor(Qt::darkMagenta, tr("Dark magenta"), 11);
    popup.insertColor(Qt::yellow, tr("Yellow"), 12);
    popup.insertColor(Qt::darkYellow, tr("Dark yellow"), 13);
    popup.insertColor(Qt::gray, tr("Gray"), 14);
    popup.insertColor(Qt::darkGray, tr("Dark gray"), 15);
    popup.insertColor(Qt::lightGray, tr("Light gray"), 16);

    popup.move(point);
    popup.exec();
    return popup.lastSelected();
}

PainterSettingsColorPopup::PainterSettingsColorPopup(int width, bool withColorDialog, QWidget *parent) : 
                                                     QFrame(parent, Qt::Popup)
{
    setFrameStyle(QFrame::StyledPanel);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    cols = width;

    if (withColorDialog) {
        moreButton = new PainterSettingsButton(this);
        moreButton->setFixedWidth(24);
        moreButton->setFixedHeight(21);
        moreButton->setFrameRect(QRect(2, 2, 20, 17));
        connect(moreButton, SIGNAL(clicked()), SLOT(getColorFromDialog()));
    } else {
        moreButton = 0;
    }

    eventLoop = 0;
    grid = 0;
    regenerateGrid();
}


PainterSettingsColorPopup::~PainterSettingsColorPopup()
{
    if (eventLoop)
        eventLoop->exit();
}

PainterSettingsColorItem *PainterSettingsColorPopup::find(const QColor &col) const
{
    for (int i = 0; i < items.size(); ++i) {
        if (items.at(i) && items.at(i)->color() == col)
            return items.at(i);
    }

    return 0;
}

void PainterSettingsColorPopup::insertColor(const QColor &col, const QString &text, int index)
{
    // Don't add colors that we have already.
    PainterSettingsColorItem *existingItem = find(col);
    PainterSettingsColorItem *lastSelectedItem = find(lastSelected());

    if (existingItem) {
        if (lastSelectedItem && existingItem != lastSelectedItem)
            lastSelectedItem->setSelected(false);
        existingItem->setFocus();
        existingItem->setSelected(true);
        return;
    }

    PainterSettingsColorItem *item = new PainterSettingsColorItem(col, text, this);

    if (lastSelectedItem) {
        lastSelectedItem->setSelected(false);
    }
    else {
        item->setSelected(true);
        lastSel = col;
    }
    item->setFocus();

    connect(item, SIGNAL(selected()), SLOT(updateSelected()));

    if (index == -1)
        index = items.count();

    items.insert((unsigned int)index, item);
    regenerateGrid();

    update();
}

QColor PainterSettingsColorPopup::color(int index) const
{
    if (index < 0 || index > (int) items.count() - 1)
        return QColor();

    PainterSettingsColorPopup *that = (PainterSettingsColorPopup *)this;
    return that->items.at(index)->color();
}

void PainterSettingsColorPopup::exec()
{
    show();

    QEventLoop e;
    eventLoop = &e;
    (void) e.exec();
    eventLoop = 0;
}

void PainterSettingsColorPopup::updateSelected()
{
    QLayoutItem *layoutItem;
    int i = 0;
    while ((layoutItem = grid->itemAt(i)) != 0) {
        QWidget *w = layoutItem->widget();
        if (w && w->inherits("PainterSettingsColorItem")) {
            PainterSettingsColorItem *litem = reinterpret_cast<PainterSettingsColorItem *>(layoutItem->widget());
            if (litem != sender())
                litem->setSelected(false);
        }
        ++i;
    }

    if (sender() && sender()->inherits("PainterSettingsColorItem")) {
        PainterSettingsColorItem *item = (PainterSettingsColorItem *)sender();
        lastSel = item->color();
        emit selected(item->color());
    }

    hide();
}

void PainterSettingsColorPopup::mouseReleaseEvent(QMouseEvent *e)
{
    if (!rect().contains(e->pos()))
        hide();
}

void PainterSettingsColorPopup::keyPressEvent(QKeyEvent *e)
{
    int curRow = 0;
    int curCol = 0;

    bool foundFocus = false;
    for (int j = 0; !foundFocus && j < grid->rowCount(); ++j) {
        for (int i = 0; !foundFocus && i < grid->columnCount(); ++i) {
            if (widgetAt[j][i] && widgetAt[j][i]->hasFocus()) {
                curRow = j;
                curCol = i;
                foundFocus = true;
                break;
            }
        }
    }

    switch (e->key()) {
    case Qt::Key_Left:
        if (curCol > 0) --curCol;
        else if (curRow > 0) {
            --curRow;
            curCol = grid->columnCount() - 1;
        }
        break;
    case Qt::Key_Right:
        if (curCol < grid->columnCount() - 1 && widgetAt[curRow][curCol + 1]) ++curCol;
        else if (curRow < grid->rowCount() - 1) {
            ++curRow;
            curCol = 0;
        }
        break;
    case Qt::Key_Up:
        if (curRow > 0) --curRow;
        else curCol = 0;
        break;
    case Qt::Key_Down:
        if (curRow < grid->rowCount() - 1) {
            QWidget *w = widgetAt[curRow + 1][curCol];
            if (w) {
                ++curRow;
            } else for (int i = 1; i < grid->columnCount(); ++i) {
                    if (!widgetAt[curRow + 1][i]) {
                        curCol = i - 1;
                        ++curRow;
                        break;
                    }
                }
        }
        break;
    case Qt::Key_Space:
    case Qt::Key_Return:
    case Qt::Key_Enter: {
        QWidget *w = widgetAt[curRow][curCol];
        if (w && w->inherits("PainterSettingsColorItem")) {
            PainterSettingsColorItem *wi = reinterpret_cast<PainterSettingsColorItem *>(w);
            wi->setSelected(true);

            QLayoutItem *layoutItem;
            int i = 0;
            while ((layoutItem = grid->itemAt(i)) != 0) {
                QWidget *w = layoutItem->widget();
                if (w && w->inherits("PainterSettingsColorItem")) {
                    PainterSettingsColorItem *litem
                        = reinterpret_cast<PainterSettingsColorItem *>(layoutItem->widget());
                    if (litem != wi)
                        litem->setSelected(false);
                }
                ++i;
            }

            lastSel = wi->color();
            emit selected(wi->color());
            hide();
        } else if (w && w->inherits("QPushButton")) {
            PainterSettingsColorItem *wi = reinterpret_cast<PainterSettingsColorItem *>(w);
            wi->setSelected(true);

            QLayoutItem *layoutItem;
            int i = 0;
            while ((layoutItem = grid->itemAt(i)) != 0) {
                QWidget *w = layoutItem->widget();
                if (w && w->inherits("PainterSettingsColorItem")) {
                    PainterSettingsColorItem *litem
                        = reinterpret_cast<PainterSettingsColorItem *>(layoutItem->widget());
                    if (litem != wi)
                        litem->setSelected(false);
                }
                ++i;
            }

            lastSel = wi->color();
            emit selected(wi->color());
            hide();
        }
    }
    break;
    case Qt::Key_Escape:
        hide();
        break;
    default:
        e->ignore();
        break;
    }

    widgetAt[curRow][curCol]->setFocus();
}

void PainterSettingsColorPopup::hideEvent(QHideEvent *e)
{
    if (eventLoop) {
        eventLoop->exit();
    }

    setFocus();

    emit hid();
    QFrame::hideEvent(e);
}

QColor PainterSettingsColorPopup::lastSelected() const
{
    return lastSel;
}

void PainterSettingsColorPopup::showEvent(QShowEvent *)
{
    bool foundSelected = false;
    for (int i = 0; i < grid->columnCount(); ++i) {
        for (int j = 0; j < grid->rowCount(); ++j) {
            QWidget *w = widgetAt[j][i];
            if (w && w->inherits("PainterSettingsColorItem")) {
                if (((PainterSettingsColorItem *)w)->isSelected()) {
                    w->setFocus();
                    foundSelected = true;
                    break;
                }
            }
        }
    }

    if (!foundSelected) {
        if (items.count() == 0)
            setFocus();
        else
            widgetAt[0][0]->setFocus();
    }
}

void PainterSettingsColorPopup::regenerateGrid()
{
    widgetAt.clear();

    int columns = cols;
    if (columns == -1)
        columns = (int) ceil(sqrt((float) items.count()));

    // When the number of columns grows, the number of rows will
    // fall. There's no way to shrink a grid, so we create a new
    // one.
    if (grid) delete grid;
    grid = new QGridLayout(this);
    grid->setMargin(1);
    grid->setSpacing(0);

    int ccol = 0, crow = 0;
    for (int i = 0; i < items.size(); ++i) {
        if (items.at(i)) {
            widgetAt[crow][ccol] = items.at(i);
            grid->addWidget(items.at(i), crow, ccol++);
            if (ccol == columns) {
                ++crow;
                ccol = 0;
            }
        }
    }

    if (moreButton) {
        grid->addWidget(moreButton, crow, ccol);
        widgetAt[crow][ccol] = moreButton;
    }
    updateGeometry();
}

void PainterSettingsColorPopup::getColorFromDialog()
{
    bool ok;
    QRgb rgb = QColorDialog::getRgba(lastSel.rgba(), &ok, parentWidget());
    if (!ok)
        return;

    QColor col = QColor::fromRgba(rgb);
    insertColor(col, tr("Custom"), -1);
    lastSel = col;
    emit selected(col);
}

PainterSettingsColorItem::PainterSettingsColorItem(const QColor &color, const QString &text, QWidget *parent) : 
                                                   QFrame(parent), c(color), t(text), sel(false)
{
    setToolTip(t);
    setFixedWidth(24);
    setFixedHeight(21);
}

PainterSettingsColorItem::~PainterSettingsColorItem()
{
}

QColor PainterSettingsColorItem::color() const
{
    return c;
}

QString PainterSettingsColorItem::text() const
{
    return t;
}

bool PainterSettingsColorItem::isSelected() const
{
    return sel;
}

void PainterSettingsColorItem::setSelected(bool selected)
{
    sel = selected;
    update();
}

void PainterSettingsColorItem::setColor(const QColor &color, const QString &text)
{
    c = color;
    t = text;
    setToolTip(t);
    update();
}

void PainterSettingsColorItem::mouseMoveEvent(QMouseEvent *)
{
    setFocus();
    update();
}

void PainterSettingsColorItem::mouseReleaseEvent(QMouseEvent *)
{
    sel = true;
    emit selected();
}

void PainterSettingsColorItem::mousePressEvent(QMouseEvent *)
{
    setFocus();
    update();
}

void PainterSettingsColorItem::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    int w = width();			// width of cell in pixels
    int h = height();			// height of cell in pixels

    p.setPen( QPen( Qt::gray, 0, Qt::SolidLine ) );

    if (sel)
        p.drawRect(1, 1, w - 3, h - 3);

    p.setPen( QPen( Qt::black, 0, Qt::SolidLine ) );
    p.drawRect(3, 3, w - 7, h - 7);
    p.fillRect(QRect(4, 4, w - 8, h - 8), QBrush(c));

    if (hasFocus())
        p.drawRect(0, 0, w - 1, h - 1);
}

//
// PainterSettingsButton
//
PainterSettingsButton::PainterSettingsButton(QWidget *parent) : QFrame(parent)
{
    setFrameStyle(StyledPanel);
}

void PainterSettingsButton::mousePressEvent(QMouseEvent *)
{
    setFrameShadow(Sunken);
    update();
}

void PainterSettingsButton::mouseMoveEvent(QMouseEvent *)
{
    setFocus();
    update();
}

void PainterSettingsButton::mouseReleaseEvent(QMouseEvent *)
{
    setFrameShadow(Raised);
    repaint();
    emit clicked();
}

void PainterSettingsButton::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Up
            || e->key() == Qt::Key_Down
            || e->key() == Qt::Key_Left
            || e->key() == Qt::Key_Right) {
        qApp->sendEvent(parent(), e);
    } else if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Space || e->key() == Qt::Key_Return) {
        setFrameShadow(Sunken);
        update();
    } else {
        QFrame::keyPressEvent(e);
    }
}

void PainterSettingsButton::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Up
            || e->key() == Qt::Key_Down
            || e->key() == Qt::Key_Left
            || e->key() == Qt::Key_Right) {
        qApp->sendEvent(parent(), e);
    } else if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Space || e->key() == Qt::Key_Return) {
        setFrameShadow(Raised);
        repaint();
        emit clicked();
    } else {
        QFrame::keyReleaseEvent(e);
    }

}

void PainterSettingsButton::focusInEvent(QFocusEvent *e)
{
    setFrameShadow(Raised);
    update();
    QFrame::focusOutEvent(e);
}

void PainterSettingsButton::focusOutEvent(QFocusEvent *e)
{
    setFrameShadow(Raised);
    update();
    QFrame::focusOutEvent(e);
}

void PainterSettingsButton::paintEvent(QPaintEvent *e)
{
    QFrame::paintEvent(e);

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
        p.setPen( QPen( Qt::black, 0, Qt::SolidLine ) );
        p.drawRect(0, 0, width() - 1, height() - 1);
    }

    p.end();

}

// #include "PainterSettingsPicker.moc"
