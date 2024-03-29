/*
 * Copyright (C) 2019 Damir Porobic <https://github.com/damirporobic>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KSNIP_MACSNIPPINGAREA_H
#define KSNIP_MACSNIPPINGAREA_H

#include "AbstractSnippingArea.h"
#include "src/common/platform/HdpiScaler.h"

class MacSnippingArea : public AbstractSnippingArea
{
public:
    explicit MacSnippingArea(const QSharedPointer<IConfig> &config);
    ~MacSnippingArea() override = default;
    QRect selectedRectArea() const override;

protected:
    void setFullScreen() override;
    QSizeF getSize() const override;

private:
    HdpiScaler mHdpiScaler;
};

#endif //KSNIP_MACSNIPPINGAREA_H
