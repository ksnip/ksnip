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

#ifndef PAINTERTEXT_H
#define PAINTERTEXT_H

#include <QTimer>
#include <QTextLayout>
#include <QTextDocument>
#include <QTextBlock>
#include <QApplication>
#include <QClipboard>

#include "PainterBaseItem.h"

class PainterText : public QObject, public PainterBaseItem
{
    Q_OBJECT
private:
    enum CursorPos {
        Next,
        Previous,
        Up,
        Down
    };

public:
    PainterText(QPointF pos, QPen attributes, QFont font);
    ~PainterText();
    virtual QRectF boundingRect() const;
    virtual void moveTo(QPointF newPos);
    virtual void addPoint(QPointF pos, bool modifier = 0);
    virtual bool containsRect(QPointF topLeft, QSize size) const;
    virtual bool isValid() const;
    QFont font() const;
    void setFont(const QFont &font);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);

private:
    QRectF        mRect;
    QString       mText;
    QFont         mFont;
    QFontMetrics *mFontMetric;
    QTimer       *mCursorBlinkTimer;
    bool          mEditable;
    int           mCursorPos;
    bool          mCursorVisible;

    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *widget = 0);
    void moveCursor(CursorPos direction);
    void insertChar(const QString &c);
    void removeChar(CursorPos direction);
    void finishEditing();
    void updateRect();
    void pasteClipboard();

private slots:
    void cursorBlink();
};

#endif // PAINTERTEXT_H
