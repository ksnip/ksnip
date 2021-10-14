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

#ifndef KSNIP_TRAYICON_H
#define KSNIP_TRAYICON_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QDesktopServices>
#include <QUrl>

#include "INotificationService.h"
#include "src/backend/config/IConfig.h"
#include "src/common/enum/CaptureModes.h"
#include "src/common/loader/IconLoader.h"
#include "src/common/helper/PathHelper.h"

class TrayIcon : public QSystemTrayIcon, public INotificationService
{
Q_OBJECT
public:
	explicit TrayIcon(const QSharedPointer<IConfig> &config, QObject *parent);
	~TrayIcon() override;
	void setCaptureActions(const QList<QAction*> &captureActions);
	void setOpenAction(QAction *action);
	void setSaveAction(QAction *action);
	void setPasteAction(QAction *action);
	void setCopyAction(QAction *action);
	void setUploadAction(QAction *action);
	void setQuitAction(QAction *action);
	void setActionsMenu(QMenu *actionsMenu);
	void setEnabled(bool enabled);
	void showInfo(const QString &title, const QString &message, const QString &contentUrl) override;
	void showWarning(const QString &title, const QString &message, const QString &contentUrl) override;
	void showCritical(const QString &title, const QString &message, const QString &contentUrl) override;

signals:
	void showEditorTriggered() const;

private:
	QSharedPointer<IConfig> mConfig;
	QMenu mMenu;
	QList<QAction*> mCaptureActions;
	QAction *mOpenAction;
	QAction *mSaveAction;
	QAction *mPasteAction;
	QAction *mCopyAction;
	QAction *mUploadAction;
	QAction *mShowEditorAction;
	QAction *mQuitAction;
	QMenu *mActionsMenu;
	QString mToastContentUrl;

	void setupMenu();
	void triggerDefaultCaptureMode() const;

private slots:
	void activatedDefaultAction(ActivationReason reason) const;
	void openContentUrl();
	void showMessage(const QString &title, const QString &message, const QString &contentUrl, QSystemTrayIcon::MessageIcon messageIcon);
};

#endif //KSNIP_TRAYICON_H
