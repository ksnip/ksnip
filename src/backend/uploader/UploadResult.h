/*
 * Copyright (C) 2030 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_UPLOADRESULT_H
#define KSNIP_UPLOADRESULT_H

#include <QString>

#include "src/common/enum/UploadStatus.h"
#include "src/common/enum/UploaderType.h"

struct UploadResult
{
	UploadStatus status;
	UploaderType type;
	QString content;

	explicit UploadResult(UploadStatus status, UploaderType type) {
		this->status = status;
		this->type = type;
	}

	explicit UploadResult(UploadStatus status, UploaderType type, const QString &content) {
		this->status = status;
		this->type = type;
		this->content = content;
	}
};

#endif //KSNIP_UPLOADRESULT_H
