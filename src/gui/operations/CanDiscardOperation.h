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

#ifndef KSNIP_CANDISCARDOPERATION_H
#define KSNIP_CANDISCARDOPERATION_H

#include <QApplication>

#include <utility>

#include "SaveOperation.h"
#include "NotifyOperation.h"
#include "src/backend/config/IConfig.h"
#include "src/backend/recentImages/IRecentImageService.h"
#include "src/gui/messageBoxService/MessageBoxService.h"

class CanDiscardOperation : public QObject
{
	Q_OBJECT
public:
	CanDiscardOperation(QImage image,
						bool isUnsaved,
						QString pathToImageSource,
						QString filename,
						const QSharedPointer<INotificationService> &notificationService,
						const QSharedPointer<IRecentImageService> &recentImageService,
						const QSharedPointer<IMessageBoxService> &messageBoxService,
						const QSharedPointer<IImageSaver> &imageSaver,
						const QSharedPointer<ISavePathProvider> &savePathProvider,
						const QSharedPointer<IConfig> &config,
						QWidget *parent);
	~CanDiscardOperation() override = default;
	bool execute();

private:
	QSharedPointer<IConfig> mConfig;
	bool mIsUnsaved;
	QWidget *mParent;
	QImage mImage;
	QString mPathToImageSource;
	QString mFilename;
	QSharedPointer<INotificationService> mNotificationService;
	QSharedPointer<IMessageBoxService> mMessageBoxService;
	QSharedPointer<IRecentImageService> mRecentImageService;
	QSharedPointer<IImageSaver> mImageSaver;
	QSharedPointer<ISavePathProvider> mSavePathProvider;

	MessageBoxResponse getSaveBeforeDiscard() const;
	bool saveImage() const;
};

#endif //KSNIP_CANDISCARDOPERATION_H
