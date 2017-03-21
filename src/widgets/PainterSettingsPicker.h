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

/*
 * Most part of this class comes from the Qt Solutions/QtColorPicker example
 */

#ifndef PAINTERSETTINGSPICKER_H
#define PAINTERSETTINGSPICKER_H

#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QFrame>
#include <QEventLoop>
#include <QMouseEvent>
#include <QGridLayout>
#include <QToolButton>
#include <QColorDialog>
#include <QCheckBox>
#include <QSlider>
#include <QLabel>

/*
 *   A class  that acts very much like a QPushButton. It's not styled,
 *   so we  can expect  the  exact same look, feel and geometry
 *   everywhere. Also, this  button always emits clicked on
 *   mouseRelease, even if the mouse button was not pressed inside the
 *   widget.
 */
class PainterSettingsButton : public QFrame
{
    Q_OBJECT

public:
    PainterSettingsButton(QWidget *parent);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
};


/*
 *This class represents each "color" or item in the color grid.
 */
class PainterSettingsColorItem : public QFrame
{
    Q_OBJECT

public:
    PainterSettingsColorItem(const QColor &color = Qt::white, const QString &text = QString::null,
                             QWidget *parent = 0);
    ~PainterSettingsColorItem();
    QColor color() const;
    QString text() const;
    void setSelected(bool selected);
    bool isSelected() const;

signals:
    void clicked();
    void selected();

public slots:
    void setColor(const QColor &color, const QString &text = QString());

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QColor  mColor;
    QString mText;
    bool    mSelected;
};

/*
 * Settings popup that host the color grid and size slider
 */
class PainterSettingsPopup : public QFrame
{
    Q_OBJECT

public:
    PainterSettingsPopup(int width, QWidget *parent = 0);
    ~PainterSettingsPopup();
    void insertColor(const QColor &color, const QString &text, int index);
    void exec();
    QColor color() const;
    void setColor(const QColor &color);
    bool fill() const;
    void setFill(const bool &fill);
    int size() const;
    void setSize(const int &size);
    PainterSettingsColorItem *findColor(const QColor &color) const;
    QColor colorAt(int index) const;
    void addColorGrid(const bool &colorDialog = true, const bool &fillCheckbox = true);
    void addSizeSlider(const int min, const int max, const int interval);
    bool isEmpty() const;
    void clear();

signals:
    void colorChanged(const QColor &);
    void fillChanged(const bool &);
    void sizeChanged(const int &);
    void hid();

public slots:
    void getColorFromDialog();

protected slots:
    void updateColor();
    void updateFill();
    void updateSize();
    void updateSizeLabel(int size);

protected:
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void regenerateColorGrid();

private:
    QList<PainterSettingsColorItem *> mColorItems;
    QVBoxLayout                       *mLayout;
    QGridLayout                       *mColorGrid;
    PainterSettingsButton             *mMoreButton;
    QEventLoop                        *mEventLoop;
    QCheckBox                         *mFillCheckBox;
    QLabel                            *mSizeLabel;
    QSlider                           *mSizeSlider;
    QFrame                            *mSeparator;

    int mLastSelectedColorPos;
    int mColorColumns;
    QColor mColor;
};

/*
 * Tool button that holds all settings
 */
class PainterSettingsPicker : public QToolButton
{
    Q_OBJECT

public:
    PainterSettingsPicker(QWidget *parent = 0, int columns = -1);
    ~PainterSettingsPicker();
    void insertColor(const QColor &color, const QString &text = QString::null, int index = -1);
    QColor color() const;
    void setColor(const QColor &color);
    bool fill() const;
    void setFill(const bool &fill);
    int size() const;
    void setSize(const int &size);
    void addPopupColorGrid(const bool &colorDialog = true,
                           const bool &fillCheckbox = true,
                           const bool &standardColor = true);
    void addPopupSizeSlider(const int min, const int max, const int interval);
    void insertStandardColor();
    void clearPopup();

public slots:
    void updateColor(const QColor &color);
    void updateFill(const bool &fill);
    void updateSize(const int &size);

signals:
    void colorChanged(const QColor &);
    void fillChanged(const bool &);
    void sizeChanged(const int &);

private slots:
    void buttonPressed();
    void popupClosed();

private:
    PainterSettingsPopup *mPopup;
};

#endif // PAINTERSETTINGSPICKER_H
