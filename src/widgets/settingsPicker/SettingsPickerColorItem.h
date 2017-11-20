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

#ifndef SETTINGSPICKERCOLORITEM_H
#define SETTINGSPICKERCOLORITEM_H

#include <QFrame>
#include <QMouseEvent>
#include <QPainter>

class SettingsPickerColorItem : public QFrame
{
    Q_OBJECT

public:
    SettingsPickerColorItem(const QColor &color = Qt::white,
                             const QString &text = QString::null,
                             QWidget *parent = 0);
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
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QColor  mColor;
    QString mText;
    bool    mSelected;
};

#endif // SETTINGSPICKERCOLORITEM_H
