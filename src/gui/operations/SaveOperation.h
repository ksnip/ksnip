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
#include "src/backend/config/KsnipConfig.h"
#include "src/backend/saver/SavePathProvider.h"
#include "src/backend/saver/ImageSaver.h"
#include "src/gui/IToastService.h"

class SaveOperation : public QObject
{
	Q_OBJECT
public:
    SaveOperation(QWidget *parent, const QImage &image, bool isInstantSave, IToastService *toastService);
	SaveOperation(QWidget *parent, const QImage &image, bool isInstantSave, const QString &pathToImageSource, IToastService *toastService);
    ~SaveOperation() override = default;
	SaveResultDto execute();

private:
    QWidget* mParent;
    QImage mImage;
    SavePathProvider mSavePathProvider;
    ImageSaver mImageSaver;
    QString mPathToImageSource;
    bool mIsInstantSave;
	IToastService *mToastService;
	KsnipConfig *mConfig;

	void notify(const QString &title, const QString &message, const QString &path, NotificationTypes notificationType) const;
	SaveResultDto save(const QString &path);
	QString getSavePath() const;
	void updateSaveDirectoryIfRequired(const QString &path, const SaveResultDto &saveResult) const;
};

#endif //KSNIP_SAVEOPERATION_H
