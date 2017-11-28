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

#ifndef PAINTERITEMFACTORY_H
#define PAINTERITEMFACTORY_H

#include "PainterPen.h"
#include "PainterMarker.h"
#include "PainterRect.h"
#include "PainterEllipse.h"
#include "PainterLine.h"
#include "PainterArrow.h"
#include "PainterText.h"
#include "PainterNumber.h"
#include "PaintModes.h"
#include "src/backend/KsnipConfig.h"

class PainterItemFactory
{
public:
    PainterItemFactory();
    AbstractPainterItem *createItem(Painter::Modes mode, const QPointF &pos) const;
    AbstractPainterItem *createCopyOfItem(AbstractPainterItem *other) const;

private:
    KsnipConfig *mConfig;

    AbstractPainterItem *createNewItem(Painter::Modes mode, const QPointF &pos) const;
};

#endif // PAINTERITEMFACTORY_H
