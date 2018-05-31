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

QCursor *CursorFactory::createPainterCursor(PaintMode mode, AbstractPainterItem *painterItem)
{
    auto cursorSize = getCursorSize(mode);

    switch(mode) {
        case PaintMode::Pen:
            return new CustomCursor(CustomCursor::Circle, mConfig->penColor(), cursorSize);
        case PaintMode::Marker:
            return new CustomCursor(CustomCursor::Circle, mConfig->markerColor(), cursorSize);
        case PaintMode::Rect:
            return new CustomCursor(CustomCursor::Circle, mConfig->rectColor(), cursorSize);
        case PaintMode::Ellipse:
            return new CustomCursor(CustomCursor::Circle, mConfig->ellipseColor(), cursorSize);
        case PaintMode::Line:
            return new CustomCursor(CustomCursor::Circle, mConfig->lineColor(), cursorSize);
        case PaintMode::Arrow:
            return new CustomCursor(CustomCursor::Circle, mConfig->arrowColor(), cursorSize);
        case PaintMode::Text:
            return new QCursor(Qt::IBeamCursor);
        case PaintMode::Number:
            return new QCursor(Qt::PointingHandCursor);
        case PaintMode::Erase:
            return new CustomCursor(CustomCursor::Rect, QColor(QStringLiteral("white")), cursorSize);
        case PaintMode::Select:
            if(painterItem == nullptr) {
                return new QCursor(Qt::OpenHandCursor);
            } else {
                return new QCursor(Qt::ClosedHandCursor);
            }
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

int CursorFactory::getCursorSize(PaintMode mode) const
{
    if(!mConfig->dynamicCursorSizeEnabled()) {
        return mDefaultCursorSize;
    }

    switch(mode) {
        case PaintMode::Pen:
            return mConfig->penSize();
        case PaintMode::Marker:
            return mConfig->markerSize();
        case PaintMode::Rect:
            return mConfig->rectSize();
        case PaintMode::Ellipse:
            return mConfig->ellipseSize();
        case PaintMode::Line:
            return mConfig->lineSize();
        case PaintMode::Arrow:
            return mConfig->arrowSize();
        case PaintMode::Erase:
            return mConfig->eraseSize();
        default:
            return mDefaultCursorSize;
    }
}
