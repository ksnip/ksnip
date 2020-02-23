/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KSNIP_HANDLEUPLOADRESPONSEOPERATION_H
#define KSNIP_HANDLEUPLOADRESPONSEOPERATION_H

#include <QUrl>
#include <QApplication>
#include <QDesktopServices>
#include <QClipboard>

#include "src/backend/config/KsnipConfigProvider.h"
#include "src/gui/operations/NotifyOperation.h"

class HandleUploadResponseOperation : public QObject
{
	Q_OBJECT
public:
	explicit HandleUploadResponseOperation(const QString &response, TrayIcon *trayIcon);
	~HandleUploadResponseOperation() override = default;
	bool execute();

private:
	QString mResponse;
	TrayIcon *mTrayIcon;
	KsnipConfig *mConfig;
	QClipboard *mClipboard;

	QUrl formatUrl(QString &response) const;
	void copyToClipboard(const QUrl &url) const;

	void openInBrowser(const QUrl &url) const;
	void notifyAboutUpload(const QUrl &url) const;
};

#endif //KSNIP_HANDLEUPLOADRESPONSEOPERATION_H
