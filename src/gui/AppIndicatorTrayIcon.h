/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
 * Copyright (C) 2026 Aleksandar Pavić
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

#ifndef KSNIP_APPINDICATORTRAYICON_H
#define KSNIP_APPINDICATORTRAYICON_H

#undef signals
#include <libayatana-appindicator/app-indicator.h>
#include <gtk/gtk.h>
#define signals Q_SIGNALS

#include <QObject>
#include <QAction>
#include <QMenu>
#include <QDesktopServices>
#include <QUrl>

#include "INotificationService.h"
#include "src/backend/config/IConfig.h"
#include "src/common/enum/CaptureModes.h"
#include "src/common/loader/IIconLoader.h"
#include "src/common/helper/PathHelper.h"

class AppIndicatorTrayIcon : public QObject, public INotificationService
{
Q_OBJECT
public:
	AppIndicator *mIndicator;

	explicit AppIndicatorTrayIcon(const QSharedPointer<IConfig> &config, const QSharedPointer<IIconLoader> &iconLoader, QObject *parent);
	~AppIndicatorTrayIcon() override;
	void setCaptureActions(const QList<QAction*> &captureActions);
	void setOpenAction(QAction *action);
	void setSaveAction(QAction *action);
	void setPasteAction(QAction *action);
	void setCopyAction(QAction *action);
	void setUploadAction(QAction *action);
	void setQuitAction(QAction *action);
	void setActionsMenu(QMenu *actionsMenu);
	void setEnabled(bool enabled);
	void hide();
	bool isVisible() const;
	void showInfo(const QString &title, const QString &message, const QString &contentUrl) override;
	void showWarning(const QString &title, const QString &message, const QString &contentUrl) override;
	void showCritical(const QString &title, const QString &message, const QString &contentUrl) override;

Q_SIGNALS:
	void showEditorTriggered() const;

private:
	QSharedPointer<IConfig> mConfig;
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
	GtkWidget *mGtkMenu;
	bool mIsVisible;

	void setupMenu();
	void triggerDefaultCaptureMode() const;
	GtkWidget* createGtkMenuItem(QAction *action);
	GtkWidget* createGtkSeparator();
	static void onMenuItemActivated(GtkMenuItem *menuItem, gpointer userData);
};

#endif //KSNIP_APPINDICATORTRAYICON_H
