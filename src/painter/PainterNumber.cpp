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

#include "PainterNumber.h"

int PainterNumber::mCounter = 1;

PainterNumber::PainterNumber(const QPointF& pos, const QPen& attributes, const QFont &font) :
    AbstractPainterItem(attributes),
    mFont(new QFont(font)),
    mFontMetric(new QFontMetrics(*mFont)),
    mTextColor(new QColor("white"))
{
    mNumber = mCounter++;
    mRect = calculateBoundingRect();
    mRect.moveCenter(pos);
}

PainterNumber::PainterNumber(const PainterNumber& other) : AbstractPainterItem(other)
{
    this->mNumber = mCounter++;  // Should we copy here the number?
    this->mRect = other.mRect;
    this->mFont = new QFont(*other.mFont);
    this->mFontMetric = new QFontMetrics(*other.mFontMetric);
    this->mTextColor = new QColor(*other.mTextColor);
}

PainterNumber::~PainterNumber()
{
    delete mFont;
    delete mFontMetric;
    delete mTextColor;
    mCounter--;
}

QRectF PainterNumber::boundingRect() const
{
    return mRect;
}

void PainterNumber::moveTo(const QPointF& newPos)
{
    prepareGeometryChange();
    mRect.translate(newPos - offset() - boundingRect().topLeft());
}

bool PainterNumber::containsRect(const QPointF& topLeft, const QSize& size) const
{
    return mRect.contains(QRectF(topLeft, size));
}

QRectF PainterNumber::calculateBoundingRect()
{
    auto rect = getTextBoundingRect();
    auto size = rect.width() > rect.height() ? rect.width() : rect.height();
    rect.setSize(QSize(size, size));
    return rect;
}

QString PainterNumber::getText() const
{
    return QString::number(mNumber);
}

QRectF PainterNumber::getTextBoundingRect() const
{
    return mFontMetric->boundingRect(getText()).adjusted(-5, -5, 5, 5);
}

void PainterNumber::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(attributes().color());
    painter->setBrush(attributes().color());
    painter->drawEllipse(mRect);
    painter->setFont(*mFont);
    painter->setPen(*mTextColor);

    auto rect = getTextBoundingRect();
    rect.moveCenter(mRect.center());
    painter->drawText(rect, Qt::AlignCenter, getText());

    paintDecoration(painter);
}
