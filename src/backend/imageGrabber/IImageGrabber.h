/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_IIMAGEGRABBER_H
#define KSNIP_IIMAGEGRABBER_H

#include "src/common/enum/CaptureModes.h"
#include "src/common/dtos/CaptureDto.h"

class IImageGrabber : public QObject
{
	Q_OBJECT
public:
	explicit IImageGrabber() = default;
	~IImageGrabber() override = default;
	virtual bool isCaptureModeSupported(CaptureModes captureMode) const = 0;
	virtual QList<CaptureModes> supportedCaptureModes() const = 0;
	virtual void grabImage(CaptureModes captureMode, bool captureCursor, int delay) = 0;

signals:
	void finished(const CaptureDto &capture) const;
	void canceled() const;
};

#endif //KSNIP_IIMAGEGRABBER_H
