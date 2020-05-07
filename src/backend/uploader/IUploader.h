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

#ifndef KSNIP_IUPLOADER_H
#define KSNIP_IUPLOADER_H

#include "UploadResult.h"
#include "src/common/enum/UploaderType.h"

class IUploader
{
public:
	virtual ~IUploader() = default;
	virtual void upload(const QImage &image) = 0;
	virtual UploaderType type() const = 0;

protected:
	virtual void finished(const UploadResult &result) = 0;
};

#endif //KSNIP_IUPLOADER_H
