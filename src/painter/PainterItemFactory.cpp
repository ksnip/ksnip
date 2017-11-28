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

#include "PainterItemFactory.h"

PainterItemFactory::PainterItemFactory()
{
    mConfig = KsnipConfig::instance();
}

AbstractPainterItem* PainterItemFactory::createItem(Painter::Modes mode, const QPointF& pos) const
{
    auto item = createNewItem(mode, pos);

    if (item && mode != Painter::Marker && mConfig->itemShadowEnabled()) {
        item->addShadowEffect();
    }

    return item;
}

AbstractPainterItem * PainterItemFactory::createCopyOfItem(AbstractPainterItem* other) const
{
    if (auto item = dynamic_cast<PainterMarker*>(other)){
        return new PainterMarker(*item);
    } else if (auto item = dynamic_cast<PainterPen*>(other)) {
        return new PainterPen(*item);
    } else if (auto item = dynamic_cast<PainterArrow*>(other)) {
        return new PainterArrow(*item);
    } else if (auto item = dynamic_cast<PainterLine*>(other)) {
        return new PainterLine(*item);
    } else if (auto item = dynamic_cast<PainterEllipse*>(other)) {
        return new PainterEllipse(*item);
    } else if (auto item = dynamic_cast<PainterRect*>(other)) {
        return new PainterRect(*item);
    } else if (auto item = dynamic_cast<PainterNumber*>(other)) {
        return new PainterNumber(*item);
    } else if (auto item = dynamic_cast<PainterText*>(other)) {
        return new PainterText(*item);
    } else {
        return nullptr;
    }
}

AbstractPainterItem* PainterItemFactory::createNewItem(Painter::Modes mode, const QPointF& pos) const
{
    switch (mode) {
    case Painter::Pen:
        return new PainterPen(pos, mConfig->pen());
    case Painter::Marker:
        return new PainterMarker(pos, mConfig->marker());
    case Painter::Rect:
        return new PainterRect(pos, mConfig->rect(), mConfig->rectFill());
    case Painter::Ellipse:
        return new PainterEllipse(pos, mConfig->ellipse(), mConfig->ellipseFill());
    case Painter::Line:
        return new PainterLine(pos, mConfig->line());
    case Painter::Arrow:
        return new PainterArrow(pos, mConfig->arrow());
    case Painter::Text:
        return new PainterText(pos - QPointF(0, 12), mConfig->text(), mConfig->textFont());
    case Painter::Number:
        return new PainterNumber(pos, mConfig->number(), mConfig->numberFont());
    default:
        return nullptr;
    }
}

