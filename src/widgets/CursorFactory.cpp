/*
*  Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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

#include "CursorFactory.h"

CursorFactory::CursorFactory()
{
    mConfig = KsnipConfig::instance();
    mDefaultCursorSize = 8;
}

QCursor* CursorFactory::createPainterCursor(Painter::Modes mode, AbstractPainterItem* painterItem)
{
    auto cursorSize = getCursorSize(mode);

    switch(mode) {
        case Painter::Pen:
            return new CustomCursor(CustomCursor::Circle, mConfig->penColor(), cursorSize);
        case Painter::Marker:
            return new CustomCursor(CustomCursor::Circle, mConfig->markerColor(), cursorSize);
        case Painter::Rect:
            return new CustomCursor(CustomCursor::Circle, mConfig->rectColor(), cursorSize);
        case Painter::Ellipse:
            return new CustomCursor(CustomCursor::Circle, mConfig->ellipseColor(), cursorSize);
        case Painter::Line:
            return new CustomCursor(CustomCursor::Circle, mConfig->lineColor(), cursorSize);
        case Painter::Arrow:
            return new CustomCursor(CustomCursor::Circle, mConfig->arrowColor(), cursorSize);
        case Painter::Text:
            return new QCursor(Qt::IBeamCursor);
        case Painter::Number:
            return new QCursor(Qt::PointingHandCursor);
        case Painter::Erase:
            return new CustomCursor(CustomCursor::Rect, QColor(QStringLiteral("white")), cursorSize);
        case Painter::Select:
            if(painterItem == nullptr) {
                return new QCursor(Qt::OpenHandCursor);
            } else {
                return new QCursor(Qt::ClosedHandCursor);
            }
        default:
            return createDefaultCursor();
    }
}

QCursor* CursorFactory::createDefaultCursor()
{
    return new CustomCursor;
}

QCursor* CursorFactory::createSnippingCursor()
{
    return new CustomCursor(CustomCursor::Cross, mConfig->snippingCursorColor(), mConfig->snippingCursorSize());
}

int CursorFactory::getCursorSize(Painter::Modes mode) const
{
    if(!mConfig->dynamicCursorSizeEnabled()) {
        return mDefaultCursorSize;
    }

    switch(mode) {
        case Painter::Pen:
            return mConfig->penSize();
        case Painter::Marker:
            return mConfig->markerSize();
        case Painter::Rect:
            return mConfig->rectSize();
        case Painter::Ellipse:
            return mConfig->ellipseSize();
        case Painter::Line:
            return mConfig->lineSize();
        case Painter::Arrow:
            return mConfig->arrowSize();
        case Painter::Erase:
            return mConfig->eraseSize();
        default:
            return mDefaultCursorSize;
    }
}
