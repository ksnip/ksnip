/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#include "DelayHandler.h"

DelayHandler::DelayHandler(const QSharedPointer<IConfig> &config) :
		mConfig(config),
		mImplicitDelay(config->implicitCaptureDelay())
{
	connect(mConfig.data(), &IConfig::delayChanged, this, &DelayHandler::delayChanged);
}

int DelayHandler::getDelay(int delay)
{
    return delay < mImplicitDelay ? mImplicitDelay : delay;
}

int DelayHandler::implicitDelay() const
{
    return mImplicitDelay;
}

void DelayHandler::delayChanged()
{
	mImplicitDelay = mConfig->implicitCaptureDelay();
}
