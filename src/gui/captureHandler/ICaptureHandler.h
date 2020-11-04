/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_ICAPTUREHANDLER_H
#define KSNIP_ICAPTUREHANDLER_H

#include "src/gui/captureHandler/ICaptureChangeListener.h"
#include "src/common/dtos/CaptureDto.h"

class ICaptureHandler : public QObject
{
public:
	explicit ICaptureHandler() = default;
	~ICaptureHandler() override = default;
	virtual bool canClose() = 0;
	virtual bool canTakeNew() = 0;
	virtual bool isSaved() const = 0;
	virtual QString path() const = 0;
	virtual bool isPathValid() const = 0;
	virtual void saveAs() = 0;
	virtual void save() = 0;
	virtual void rename() = 0;
	virtual void copy() = 0;
	virtual void copyPath() = 0;
	virtual void openDirectory() = 0;
	virtual void removeImage() = 0;
	virtual void load(const CaptureDto &capture) = 0;
	virtual QImage image() const = 0;
	virtual void insertImageItem(const QPointF &pos, const QPixmap &pixmap) = 0;
	virtual void addListener(ICaptureChangeListener *captureChangeListener) = 0;
};

#endif //KSNIP_ICAPTUREHANDLER_H
