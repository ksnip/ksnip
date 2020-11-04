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

#include "ICaptureTabStateHandler.h"
#include "CaptureTabState.h"
#include "src/common/dtos/SaveResultDto.h"
#include "src/common/dtos/RenameResultDto.h"
#include "src/common/helper/PathHelper.h"

class CaptureTabStateHandler : public ICaptureTabStateHandler
{
	Q_OBJECT
public:
	explicit CaptureTabStateHandler();
	~CaptureTabStateHandler() override = default;
	void add(int index, const QString &filename, const QString &path, bool isSaved) override;
	bool isSaved(int index) override;
	bool isPathValid(int index) override;
	QString path(int index) override;
	QString filename(int index) override;
	void setSaveState(int index, const SaveResultDto &saveResult) override;
	void renameFile(int index, const RenameResultDto &renameResult) override;
	int count() const override;
	int currentTabIndex() const override;

public slots:
	void tabMoved(int fromIndex, int toIndex) override;
	void currentTabChanged(int index) override;
	void tabRemoved(int index) override;
	void currentTabContentChanged() override;

private:
	int mCurrentTabIndex;
	QList<QSharedPointer<CaptureTabState>> mCaptureTabStates;

	void refreshTabInfo(int index);
	QSharedPointer<CaptureTabState> getTabState(int index);
};

#endif //KSNIP_CAPTURETABSTATEHANDLER_H
