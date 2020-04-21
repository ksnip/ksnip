/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_CAPTURETABSTATEHANDLER_H
#define KSNIP_CAPTURETABSTATEHANDLER_H

#include <QObject>
#include <QList>
#include <QSharedPointer>

#include "CaptureTabState.h"
#include "src/common/dtos/SaveResultDto.h"
#include "src/common/helper/PathHelper.h"

class CaptureTabStateHandler : public QObject
{
	Q_OBJECT
public:
	explicit CaptureTabStateHandler();
	~CaptureTabStateHandler() override = default;
	void add(int index, const QString &filename, const QString &path, bool isSaved);
	bool currentTabIsSaved();
	QString currentTabPath();
	QString currentTabFilename();
	void setCurrentTabSaveState(const SaveResultDto &saveResult);
	int count() const;
	int currentTabIndex() const;

signals:
	void updateTabInfo(int index, const QString &title, const QString &toolTip);

public slots:
	void tabMoved(int fromIndex, int toIndex);
	void currentTabChanged(int index);
	void tabRemoved(int index);
	void currentTabContentChanged();

private:
	int mCurrentTabIndex;
	QSharedPointer<CaptureTabState> mCachedCurrentTabState;
	QList<QSharedPointer<CaptureTabState>> mCaptureTabStates;

	QSharedPointer<CaptureTabState> getCurrentTabStateFromCache();
	void updateCurrentTabInfo();
};

#endif //KSNIP_CAPTURETABSTATEHANDLER_H
