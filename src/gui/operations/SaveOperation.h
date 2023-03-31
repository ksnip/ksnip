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

#ifndef KSNIP_SAVEOPERATION_H
#define KSNIP_SAVEOPERATION_H

#include <QCoreApplication>

#include "NotifyOperation.h"
#include "src/common/dtos/SaveResultDto.h"
#include "src/common/adapter/fileDialog/IFileDialogService.h"
#include "src/common/helper/FileDialogFilterHelper.h"
#include "src/backend/recentImages/IRecentImageService.h"
#include "src/backend/config/IConfig.h"
#include "src/backend/saver/ISavePathProvider.h"
#include "src/backend/saver/IImageSaver.h"
#include "src/gui/INotificationService.h"

class SaveOperation : public QObject
{
	Q_OBJECT
public:
    SaveOperation(
			QImage image,
			bool isInstantSave,
			const QSharedPointer<INotificationService> &notificationService,
			const QSharedPointer<IRecentImageService> &recentImageService,
			const QSharedPointer<IImageSaver> &imageSaver,
			const QSharedPointer<ISavePathProvider> &savePathProvider,
			const QSharedPointer<IFileDialogService> &fileDialogService,
			const QSharedPointer<IConfig> &config,
			QWidget *parent);
	SaveOperation(
			const QImage &image,
			bool isInstantSave,
			const QString &pathToImageSource,
			const QSharedPointer<INotificationService> &notificationService,
			const QSharedPointer<IRecentImageService> &recentImageService,
			const QSharedPointer<IImageSaver> &imageSaver,
			const QSharedPointer<ISavePathProvider> &savePathProvider,
			const QSharedPointer<IFileDialogService> &fileDialogService,
			const QSharedPointer<IConfig> &config,
			QWidget *parent);
    ~SaveOperation() override = default;
	SaveResultDto execute();

private:
    QWidget* mParent;
    QImage mImage;
	QString mPathToImageSource;
	bool mIsInstantSave;
	QSharedPointer<IImageSaver> mImageSaver;
	QSharedPointer<ISavePathProvider> mSavePathProvider;
	QSharedPointer<INotificationService> mNotificationService;
	QSharedPointer<IRecentImageService> mRecentImageService;
	QSharedPointer<IFileDialogService> mFileDialogService;
	QSharedPointer<IConfig> mConfig;

	void notify(const QString &title, const QString &message, const QString &path, NotificationTypes notificationType) const;
	SaveResultDto save(const QString &path);
	QString getSavePath() const;
	void updateSaveDirectoryIfRequired(const QString &path, const SaveResultDto &saveResult) const;
};

#endif //KSNIP_SAVEOPERATION_H
