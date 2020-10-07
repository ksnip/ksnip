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

#ifndef KSNIP_CAPTURETABSTATEHANDLERMOCK_H
#define KSNIP_CAPTURETABSTATEHANDLERMOCK_H

#include <QMap>

#include "src/gui/captureHandler/ICaptureTabStateHandler.h"
#include "tests/utils/CallCounter.h"

class CaptureTabStateHandlerMock : public ICaptureTabStateHandler
{
Q_OBJECT
public:
	explicit CaptureTabStateHandlerMock() = default;
	~CaptureTabStateHandlerMock() override = default;
	void add(int index, const QString &filename, const QString &path, bool isSaved) override;
	bool isSaved(int index) override;
	bool isPathValid(int index) override;
	QString path(int index) override;
	QString filename(int index) override;
	void setSaveState(int index, const SaveResultDto &saveResult) override;
	int count() const override;
	int currentTabIndex() const override;

	// Mock Methods
	void currentTabIndex_set(int index);
	void path_set(int index, const QString &path);
	int path_callCounter(int index) const;
	void isPathValid_set(int index, bool value);
	void isSaved_set(int index, bool value);

public slots:
	void tabMoved(int fromIndex, int toIndex) override;
	void currentTabChanged(int index) override;
	void tabRemoved(int index) override;
	void currentTabContentChanged() override;

private:
	int mCurrentTabIndex;
	QMap<int,QString> mPathMap;
	CallCounter<int> mPathCallCounter;
	QMap<int,bool> mIsPathValidMap;
	QMap<int,bool> mIsSaveMap;
};


#endif //KSNIP_CAPTURETABSTATEHANDLERMOCK_H
