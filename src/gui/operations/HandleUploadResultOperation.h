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

#ifndef KSNIP_HANDLEUPLOADRESULTOPERATION_H
#define KSNIP_HANDLEUPLOADRESULTOPERATION_H

#include <QUrl>
#include <QApplication>
#include <QDesktopServices>
#include <QClipboard>

#include "src/backend/config/KsnipConfigProvider.h"
#include "src/backend/uploader/UploadResult.h"
#include "src/gui/operations/NotifyOperation.h"

class HandleUploadResultOperation : public QObject
{
	Q_OBJECT
public:
	explicit HandleUploadResultOperation(const UploadResult &result, TrayIcon *trayIcon);
	~HandleUploadResultOperation() override = default;
	bool execute();

private:
	UploadResult mUploadResult;
	TrayIcon *mTrayIcon;
	KsnipConfig *mConfig;
	QClipboard *mClipboard;

	void notifyImgurSuccessfulUpload(const QString &url) const;
	void handleImgurResult();
	void handleScriptResult();
	void copyToClipboard(const QString &url) const;
	void OpenUrl(const QString &url) const;
	void handleUploadError();
	void notifyScriptSuccessfulUpload() const;
	void notifyFailedUpload(const QString &message) const;
};

#endif //KSNIP_HANDLEUPLOADRESULTOPERATION_H
