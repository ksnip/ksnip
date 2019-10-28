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

#ifndef KSNIP_TRAYICON_H
#define KSNIP_TRAYICON_H

#include <QSystemTrayIcon>
#include <QMenu>

#include "src/common/enum/CaptureModes.h"

class TrayIcon : public QSystemTrayIcon
{
Q_OBJECT
public:
	explicit TrayIcon(QObject *parent);
	~TrayIcon() override;
	void setNewCaptureAction(QAction *action);
	void setOpenAction(QAction *action);
	void setSaveAction(QAction *action);
	void setCopyAction(QAction *action);
	void setUploadAction(QAction *action);
	void setQuitAction(QAction *action);
	void setEnabled(bool enabled);
	void showInfoToast(const QString &title, const QString &message);
	void showWarningToast(const QString &title, const QString &message);
	void showCriticalToast(const QString &title, const QString &message);

signals:
	void showEditorTriggered() const;

private:
	QMenu mMenu;
	QAction *mNewCaptureAction;
	QAction *mOpenAction;
	QAction *mSaveAction;
	QAction *mCopyAction;
	QAction *mUploadAction;
	QAction *mShowEditorAction;
	QAction *mQuitAction;

	void setupMenu();

private slots:
	void activated(ActivationReason reason) const;
};

#endif //KSNIP_TRAYICON_H
