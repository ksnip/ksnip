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

#ifndef KSNIP_ICAPTURETABSTATEHANDLER_H
#define KSNIP_ICAPTURETABSTATEHANDLER_H

#include <QObject>

class SaveResultDto;

class ICaptureTabStateHandler : public QObject
{
	Q_OBJECT
public:
	explicit ICaptureTabStateHandler() = default;
	~ICaptureTabStateHandler() override = default;
	virtual void add(int index, const QString &filename, const QString &path, bool isSaved) = 0;
	virtual bool isSaved(int index) = 0;
	virtual bool isPathValid(int index) = 0;
	virtual QString path(int index) = 0;
	virtual QString filename(int index) = 0;
	virtual void setSaveState(int index, const SaveResultDto &saveResult) = 0;
	virtual int count() const = 0;
	virtual int currentTabIndex() const = 0;

signals:
	void updateTabInfo(int index, const QString &title, const QString &toolTip);

public slots:
	virtual void tabMoved(int fromIndex, int toIndex) = 0;
	virtual void currentTabChanged(int index) = 0;
	virtual void tabRemoved(int index) = 0;
	virtual void currentTabContentChanged() = 0;
};

#endif //KSNIP_ICAPTURETABSTATEHANDLER_H
