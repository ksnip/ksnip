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

#include "PainterText.h"

namespace
{

/*
 * Returns the margin that is placed between the textbox and the text inside it.
 */
int textBoxMargin()
{
    return 2;
}

}

//
// Public Functions
//

PainterText::PainterText(QPointF pos, QPen attributes, QFont font) :
    PainterBaseItem(Text, attributes),
    mFont(font),
    mFontMetric(new QFontMetrics(mFont)),
    mCursorBlinkTimer(new QTimer(this)),
    mEditable(true),
    mCursorVisible(true)
{
    mCursorPos = 0;
    setFlags(QGraphicsItem::ItemIsFocusable);
    setOutlineStyle(Qt::DashLine);
    setOutlineWidth(1);
    mRect.moveTo(pos);
    updateRect();

    // Trigger cursor blinking
    connect(mCursorBlinkTimer, SIGNAL(timeout()), this, SLOT(cursorBlink()));
    mCursorBlinkTimer->start(1000);
}

PainterText::~PainterText()
{
    delete mFontMetric;
    delete mCursorBlinkTimer;
}

QRectF PainterText::boundingRect() const
{
    return mRect;
}

void PainterText::moveTo(QPointF newPos)
{
    prepareGeometryChange();
    mRect.translate(newPos - offset() - boundingRect().topLeft());
}

void PainterText::addPoint(QPointF pos, bool modifier)
{
    // Not supported for text
}

bool PainterText::containsRect(QPointF topLeft, QSize size) const
{
    return mRect.intersects(QRectF(topLeft.x() - size.width() / 2,
                                   topLeft.y() - size.height() / 2,
                                   size.width(),
                                   size.height()));
}

bool PainterText::isValid() const
{
    if (mText.length() <= 0) {
        return false;
    } else {
        return true;
    }
}

QFont PainterText::font() const
{
    return mFont;
}

void PainterText::setFont(const QFont& font)
{
    mFont = font;
}

//
// Protected Functions
//

void PainterText::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Backspace:
        removeChar(Previous);
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        insertChar("\n");
        break;
    case Qt::Key_Delete:
        removeChar(Next);
        break;
    case Qt::Key_Escape:
        clearFocus();
        return;
    case Qt::Key_Left:
        moveCursor(Previous);
        break;
    case Qt::Key_Right:
        moveCursor(Next);
        break;
    case Qt::Key_Up:
        moveCursor(Up);
        break;
    case Qt::Key_Down:
        moveCursor(Down);
        break;
    case Qt::Key_Paste:
        pasteClipboard();
        break;
    default:
        if (event->matches(QKeySequence::Paste)) {
            pasteClipboard();
            break;
        }
        if (event->text().isEmpty() || event->modifiers() == Qt::ControlModifier) {
            return;
        }
        insertChar(event->text());
    }
    updateRect();
    prepareGeometryChange();
}

void PainterText::focusOutEvent(QFocusEvent* event)
{
    finishEditing();
}

//
// Private Functions
//

void PainterText::paint(QPainter* painter, const QStyleOptionGraphicsItem* style, QWidget* widget)
{
    painter->setPen(*attributes());

    if (mEditable) {
        painter->drawRect(mRect);
    }

    qreal boxHeight = 0;
    QTextDocument doc(mText);
    for (QTextBlock block = doc.begin(); block != doc.end(); block = block.next()) {
        int blpos = block.position();
        int bllen = block.length();
        QTextLayout textLayout(block);
        textLayout.setFont(mFont);
        int leading = mFontMetric->leading();
        qreal blockHeight = 0;
        textLayout.setCacheEnabled(true);
        textLayout.beginLayout();
        while (1) {
            QTextLine line = textLayout.createLine();
            if (!line.isValid()) {
                break;
            }

            line.setLineWidth(mRect.width());
            blockHeight += leading;
            line.setPosition(mRect.adjusted(textBoxMargin(), textBoxMargin(), 0, 0).topLeft());
            blockHeight += line.height();
        }
        textLayout.endLayout();
        textLayout.draw(painter, QPoint(0, boxHeight));
        if (mCursorVisible && (mCursorPos >= blpos && mCursorPos < blpos + bllen)) {
            textLayout.drawCursor(painter, QPointF(0, boxHeight), mCursorPos - blpos, 1);
        }
        boxHeight += blockHeight;
    }
}

void PainterText::moveCursor(PainterText::CursorPos direction)
{
    switch (direction) {
    case Next:
        mCursorPos++;
        if (mCursorPos > mText.length()) {
            mCursorPos = 0;
        }
        break;
    case Previous:
        mCursorPos--;
        if (mCursorPos < 0) {
            mCursorPos = mText.length();
        }
        break;
    case Up:
    case Down:
        QTextDocument doc(mText);
        QTextBlock block = doc.findBlock(mCursorPos);
        if ((direction == Up && block == doc.firstBlock()) || (direction == Down && block == doc.lastBlock())) {
            break;
        }
        int blpos = block.position();
        if (direction == Up) {
            block = block.previous();
        } else {
            block = block.next();
        }
        if ((mCursorPos - blpos) < block.length()) {
            mCursorPos = block.position() + mCursorPos - blpos;
        } else {
            mCursorPos = block.position() + block.length() - 1;
        }
        break;
    }
    mCursorVisible = true;
}

void PainterText::insertChar(const QString& c)
{
    mText.insert(mCursorPos, c);
    moveCursor(Next);
}

void PainterText::removeChar(PainterText::CursorPos direction)
{
    switch (direction) {
    case Previous:
        if (mCursorPos == 0) {
            return;
        }
        mText.remove(mCursorPos - 1, 1);
        moveCursor(Previous);
        break;
    case Next:
        if (mCursorPos >= mText.length()) {
            return;
        }
        mText.remove(mCursorPos, 1);
    case Up:
    case Down:
        // Do nothing
        break;
    }
}

/*
 * Should be called any time editing was finished, if the text is empty at this
 * point we will add some dummy text as placeholder
 */
void PainterText::finishEditing()
{
    mEditable = false;
    mCursorBlinkTimer->stop();
    mCursorVisible = false;
    updateRect();
    prepareGeometryChange();
}

void PainterText::updateRect()
{
    mRect = mFontMetric->boundingRect(mRect.toRect(), Qt::AlignLeft, mText);
    mRect.adjust(0, 0, textBoxMargin() * 2, textBoxMargin() * 2);
}

void PainterText::pasteClipboard()
{
    QClipboard* clipboard = QApplication::clipboard();
    if (clipboard->text().isEmpty()) {
        return;
    }
    mText.insert(mCursorPos, clipboard->text());
    mCursorPos += clipboard->text().length();
}

//
// Private Slots
//
void PainterText::cursorBlink()
{
    mCursorVisible = !mCursorVisible;
    prepareGeometryChange();
}
