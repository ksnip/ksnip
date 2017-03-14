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
#include <QMap>
#include <QEventLoop>
#include <QMouseEvent>
#include <QGridLayout>
#include <QToolButton>
#include <QStyle>
#include <QColorDialog>
#include <QIcon>

#if defined(Q_WS_WIN)
#  if !defined(PAINTERSETTINGSPICKER_EXPORT) && !defined(PAINTERSETTINGSPICKER_IMPORT)
#    define PAINTERSETTINGSPICKER_EXPORT
#  elif defined(PAINTERSETTINGSPICKER_IMPORT)
#    if defined(PAINTERSETTINGSPICKER_EXPORT)
#      undef PAINTERSETTINGSPICKER_EXPORT
#    endif
#    define PAINTERSETTINGSPICKER_EXPORT __declspec(dllimport)
#  elif defined(PAINTERSETTINGSPICKER_EXPORT)
#    undef PAINTERSETTINGSPICKER_EXPORT
#    define PAINTERSETTINGSPICKER_EXPORT __declspec(dllexport)
#  endif
#else
#  define PAINTERSETTINGSPICKER_EXPORT
#endif

/*
 *   A class  that acts very much  like a QPushButton. It's not styled,
 *   so we  can  expect  the  exact  same    look,  feel and   geometry
 *   everywhere.     Also,  this  button     always emits   clicked  on
 *   mouseRelease, even if the mouse button was  not pressed inside the
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
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void paintEvent(QPaintEvent *e);
    void focusInEvent(QFocusEvent *e);
    void focusOutEvent(QFocusEvent *e);
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

    void setSelected(bool);
    bool isSelected() const;
signals:
    void clicked();
    void selected();

public slots:
    void setColor(const QColor &color, const QString &text = QString());

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

private:
    QColor c;
    QString t;
    bool sel;
};

/*
 * Color Popup
 */
class PainterSettingsColorPopup : public QFrame
{
    Q_OBJECT

public:
    PainterSettingsColorPopup(int width, bool withColorDialog,
                              QWidget *parent = 0);
    ~PainterSettingsColorPopup();

    void insertColor(const QColor &col, const QString &text, int index);
    void exec();

    void setExecFlag();

    QColor lastSelected() const;

    PainterSettingsColorItem *find(const QColor &col) const;
    QColor color(int index) const;

signals:
    void selected(const QColor &);
    void hid();

public slots:
    void getColorFromDialog();

protected slots:
    void updateSelected();

protected:
    void keyPressEvent(QKeyEvent *e);
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void regenerateGrid();

private:
    QMap<int, QMap<int, QWidget *> > widgetAt;
    QList<PainterSettingsColorItem *> items;
    QGridLayout *grid;
    PainterSettingsButton *moreButton;
    QEventLoop *eventLoop;

    int lastPos;
    int cols;
    QColor lastSel;
};

/*
 * Main widget
 */
class PAINTERSETTINGSPICKER_EXPORT PainterSettingsPicker : public QToolButton
{
    Q_OBJECT

    Q_PROPERTY(bool colorDialog READ colorDialogEnabled WRITE setColorDialogEnabled)

public:
    PainterSettingsPicker(QWidget *parent = 0,
                          int columns = -1, bool enableColorDialog = true);
    ~PainterSettingsPicker();
    void insertColor(const QColor &color, const QString &text = QString::null, int index = -1);
    QColor currentColor() const;
    QColor color(int index) const;
    void setColorDialogEnabled(bool enabled);
    bool colorDialogEnabled() const;
    void setStandardColors();
    static QColor getColor(const QPoint &pos, bool allowCustomColors = true);

public Q_SLOTS:
    void setCurrentColor(const QColor &col);

Q_SIGNALS:
    void colorChanged(const QColor &);

protected:
    void paintEvent(QPaintEvent *e);

private Q_SLOTS:
    void buttonPressed(bool toggled);
    void popupClosed();

private:
    PainterSettingsColorPopup *popup;
    QColor col;
    bool withColorDialog;
    bool dirty;
    bool firstInserted;
};

#endif // PAINTERSETTINGSPICKER_H
