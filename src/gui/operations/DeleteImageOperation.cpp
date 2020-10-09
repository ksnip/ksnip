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

#include "DeleteImageOperation.h"

DeleteImageOperation::DeleteImageOperation(QString path, IFileService *fileService, IMessageBoxService *messageBoxService) :
	mPath(std::move(path)),
	mFileService(fileService),
	mMessageBoxService(messageBoxService)
{

}

DeleteImageOperation::~DeleteImageOperation()
{
	delete mFileService;
	delete mMessageBoxService;
}

bool DeleteImageOperation::execute()
{
	auto title = tr("Delete Image");
	auto question = tr("The item \'%1\' will be deleted.\nDo you want to continue?").arg(mPath);
	auto response = mMessageBoxService->okCancel(title, question);
	return response && mFileService->remove(mPath);
}