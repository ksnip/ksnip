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

#ifndef KSNIP_RENAMEOPERATION_H
#define KSNIP_RENAMEOPERATION_H

#include <QCoreApplication>
#include <QFile>
#include <QInputDialog>

#include <utility>

#include "NotifyOperation.h"
#include "src/common/dtos/RenameResultDto.h"
#include "src/common/helper/PathHelper.h"
#include "src/gui/IToastService.h"

class RenameOperation : public QObject
{
	Q_OBJECT
public:
	RenameOperation(QWidget *parent, const QString &pathToImageSource, const QString &imageFilename, IToastService *toastService);
	~RenameOperation() override = default;
	RenameResultDto execute();

private:
	QWidget* mParent;
	QString mPathToImageSource;
	QString mImageFilename;
	IToastService *mToastService;

	QString getNewFilename() const;
	bool rename(const QString &newFilename);
};

#endif //KSNIP_RENAMEOPERATION_H
