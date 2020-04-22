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

#ifndef KSNIP_GLOBALHOTKEYHANDLER_H
#define KSNIP_GLOBALHOTKEYHANDLER_H

#include <QApplication>
#include <QList>
#include <QSharedPointer>

#include "GlobalHotKey.h"
#include "src/backend/config/KsnipConfigProvider.h"
#include "src/common/enum/CaptureModes.h"

class GlobalHotKeyHandler : public QObject
{
	Q_OBJECT
public:
	explicit GlobalHotKeyHandler(const QList<CaptureModes> &supportedCaptureModes);
	~GlobalHotKeyHandler() override;
	void setEnabled(bool enabled);

signals:
	void newCaptureTriggered(CaptureModes captureMode) const;

private:
	KsnipConfig *mConfig;
	QList<QSharedPointer<GlobalHotKey>> mGlobalHotKeys;
	QList<CaptureModes> mSupportedCaptureModes;

	void removeHotKeys();
	void createHotKey(const QKeySequence &keySequence, CaptureModes captureMode);

private slots:
	void setupHotKeys();
};


#endif //KSNIP_GLOBALHOTKEYHANDLER_H
