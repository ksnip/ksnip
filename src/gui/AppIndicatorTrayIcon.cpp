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

#include "AppIndicatorTrayIcon.h"

AppIndicatorTrayIcon::AppIndicatorTrayIcon(const QSharedPointer<IConfig> &config, const QSharedPointer<IIconLoader> &iconLoader, QObject *parent) :
	QObject(parent),
	mConfig(config),
	mIndicator(nullptr),
	mOpenAction(nullptr),
	mSaveAction(nullptr),
	mPasteAction(nullptr),
	mCopyAction(nullptr),
	mUploadAction(nullptr),
	mShowEditorAction(nullptr),
	mQuitAction(nullptr),
	mActionsMenu(nullptr),
	mGtkMenu(nullptr),
	mIsVisible(false)
{
	mShowEditorAction = new QAction(tr("Show Editor"), this);
	connect(mShowEditorAction, &QAction::triggered, this, &AppIndicatorTrayIcon::showEditorTriggered);

	gtk_init(nullptr, nullptr);
	mIndicator = app_indicator_new_with_path("ksnip", "ksnip", APP_INDICATOR_CATEGORY_APPLICATION_STATUS, "/usr/share/icons/hicolor/scalable/apps");
	app_indicator_set_status(mIndicator, APP_INDICATOR_STATUS_PASSIVE);
}

AppIndicatorTrayIcon::~AppIndicatorTrayIcon()
{
	delete mShowEditorAction;
	if (mIndicator) {
		g_object_unref(mIndicator);
	}
}

void AppIndicatorTrayIcon::setCaptureActions(const QList<QAction*> &captureActions)
{
	mCaptureActions = captureActions;
}

void AppIndicatorTrayIcon::setOpenAction(QAction *action)
{
	mOpenAction = action;
}

void AppIndicatorTrayIcon::setSaveAction(QAction *action)
{
	mSaveAction = action;
}

void AppIndicatorTrayIcon::setPasteAction(QAction *action)
{
	mPasteAction = action;
}

void AppIndicatorTrayIcon::setCopyAction(QAction *action)
{
	mCopyAction = action;
}

void AppIndicatorTrayIcon::setUploadAction(QAction *action)
{
	mUploadAction = action;
}

void AppIndicatorTrayIcon::setQuitAction(QAction *action)
{
	mQuitAction = action;
}

void AppIndicatorTrayIcon::setActionsMenu(QMenu *actionsMenu)
{
	mActionsMenu = actionsMenu;
}

GtkWidget* AppIndicatorTrayIcon::createGtkMenuItem(QAction *action)
{
	auto item = gtk_menu_item_new_with_label(action->text().remove(QLatin1Char('&')).toUtf8().constData());
	g_object_set_data(G_OBJECT(item), "qt-action", action);
	g_signal_connect(item, "activate", G_CALLBACK(onMenuItemActivated), this);
	return item;
}

GtkWidget* AppIndicatorTrayIcon::createGtkSeparator()
{
	return gtk_separator_menu_item_new();
}

void AppIndicatorTrayIcon::onMenuItemActivated(GtkMenuItem *menuItem, gpointer userData)
{
	auto action = static_cast<QAction*>(g_object_get_data(G_OBJECT(menuItem), "qt-action"));
	if (action) {
		QTimer::singleShot(0, action, &QAction::trigger);
	}
}

void AppIndicatorTrayIcon::setupMenu()
{
	mGtkMenu = gtk_menu_new();

	gtk_menu_shell_append(GTK_MENU_SHELL(mGtkMenu), createGtkMenuItem(mShowEditorAction));
	gtk_menu_shell_append(GTK_MENU_SHELL(mGtkMenu), createGtkSeparator());

	for (auto captureAction : mCaptureActions) {
		gtk_menu_shell_append(GTK_MENU_SHELL(mGtkMenu), createGtkMenuItem(captureAction));
	}
	gtk_menu_shell_append(GTK_MENU_SHELL(mGtkMenu), createGtkSeparator());

	if (mActionsMenu) {
		auto actionsItem = gtk_menu_item_new_with_label(mActionsMenu->title().remove(QLatin1Char('&')).toUtf8().constData());
		auto actionsSubmenu = gtk_menu_new();
		for (auto action : mActionsMenu->actions()) {
			if (action->isSeparator()) {
				gtk_menu_shell_append(GTK_MENU_SHELL(actionsSubmenu), createGtkSeparator());
			} else {
				gtk_menu_shell_append(GTK_MENU_SHELL(actionsSubmenu), createGtkMenuItem(action));
			}
		}
		gtk_menu_item_set_submenu(GTK_MENU_ITEM(actionsItem), actionsSubmenu);
		gtk_menu_shell_append(GTK_MENU_SHELL(mGtkMenu), actionsItem);
		gtk_menu_shell_append(GTK_MENU_SHELL(mGtkMenu), createGtkSeparator());
	}

	gtk_menu_shell_append(GTK_MENU_SHELL(mGtkMenu), createGtkMenuItem(mOpenAction));
	gtk_menu_shell_append(GTK_MENU_SHELL(mGtkMenu), createGtkMenuItem(mSaveAction));
	gtk_menu_shell_append(GTK_MENU_SHELL(mGtkMenu), createGtkMenuItem(mPasteAction));
	gtk_menu_shell_append(GTK_MENU_SHELL(mGtkMenu), createGtkMenuItem(mCopyAction));
	gtk_menu_shell_append(GTK_MENU_SHELL(mGtkMenu), createGtkMenuItem(mUploadAction));
	gtk_menu_shell_append(GTK_MENU_SHELL(mGtkMenu), createGtkSeparator());
	gtk_menu_shell_append(GTK_MENU_SHELL(mGtkMenu), createGtkMenuItem(mQuitAction));

	gtk_widget_show_all(mGtkMenu);
	app_indicator_set_menu(mIndicator, GTK_MENU(mGtkMenu));
}

void AppIndicatorTrayIcon::setEnabled(bool enabled)
{
	if (enabled) {
		setupMenu();
		app_indicator_set_status(mIndicator, APP_INDICATOR_STATUS_ACTIVE);
		mIsVisible = true;
	} else {
		app_indicator_set_status(mIndicator, APP_INDICATOR_STATUS_PASSIVE);
		mIsVisible = false;
	}
}

void AppIndicatorTrayIcon::hide()
{
	app_indicator_set_status(mIndicator, APP_INDICATOR_STATUS_PASSIVE);
	mIsVisible = false;
}

bool AppIndicatorTrayIcon::isVisible() const
{
	return mIsVisible;
}

void AppIndicatorTrayIcon::showInfo(const QString &title, const QString &message, const QString &contentUrl)
{
	Q_UNUSED(title);
	Q_UNUSED(message);
	Q_UNUSED(contentUrl);
}

void AppIndicatorTrayIcon::showWarning(const QString &title, const QString &message, const QString &contentUrl)
{
	Q_UNUSED(title);
	Q_UNUSED(message);
	Q_UNUSED(contentUrl);
}

void AppIndicatorTrayIcon::showCritical(const QString &title, const QString &message, const QString &contentUrl)
{
	Q_UNUSED(title);
	Q_UNUSED(message);
	Q_UNUSED(contentUrl);
}

void AppIndicatorTrayIcon::triggerDefaultCaptureMode() const
{
	auto captureMode = mConfig->defaultTrayIconCaptureMode();
	for (auto action : mCaptureActions) {
		if (action->data().value<CaptureModes>() == captureMode) {
			action->trigger();
			return;
		}
	}
}
