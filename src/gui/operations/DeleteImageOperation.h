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

#ifndef KSNIP_DELETEIMAGEOPERATION_H
#define KSNIP_DELETEIMAGEOPERATION_H

#include <QObject>

#include <utility>

#include "src/gui/fileService/IFileService.h"
#include "src/gui/messageBoxService/IMessageBoxService.h"

class DeleteImageOperation : public QObject
{
	Q_OBJECT
public:
	explicit DeleteImageOperation(QString path, IFileService *fileService, IMessageBoxService *messageBoxService);
	~DeleteImageOperation() override = default;
	bool execute();

private:
	QString mPath;
	IFileService *mFileService;
	IMessageBoxService *mMessageBoxService;
};

#endif //KSNIP_DELETEIMAGEOPERATION_H
