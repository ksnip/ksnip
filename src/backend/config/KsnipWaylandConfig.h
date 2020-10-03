/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_KSNIPWAYLANDCONFIG_H
#define KSNIP_KSNIPWAYLANDCONFIG_H

#include "KsnipConfig.h"

class KsnipWaylandConfig : public KsnipConfig
{
public:
	bool isFreezeImageWhileSnippingEnabledReadOnly() const override;
	bool freezeImageWhileSnippingEnabled() const override;

	bool isGlobalHotKeysEnabledReadOnly() const override;
	bool globalHotKeysEnabled() const override;

	bool isSnippingAreaMagnifyingGlassEnabledReadOnly() const override;
	bool snippingAreaMagnifyingGlassEnabled() const override;

    bool isForceGenericWaylandEnabledReadOnly() const override;

    bool isScaleGenericWaylandScreenshotEnabledReadOnly() const override;
};

#endif //KSNIP_KSNIPWAYLANDCONFIG_H
