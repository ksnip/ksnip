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

#ifndef KSNIP_MESSAGEBOXSERVICEMOCK_H
#define KSNIP_MESSAGEBOXSERVICEMOCK_H

#include "src/gui/messageBoxService/IMessageBoxService.h"

class MessageBoxServiceMock : public IMessageBoxService
{
public:
	explicit MessageBoxServiceMock();
	~MessageBoxServiceMock() override = default;
	bool yesNo(const QString &title, const QString &question) override;
	MessageBoxResponse yesNoCancel(const QString &title, const QString &question) override;
	void ok(const QString &title, const QString &info) override;
	bool okCancel(const QString &title, const QString &info) override;

	// Mock Methods
	void yesNo_set(bool response);
	void okCancel_set(bool response);

private:
	bool mYesNoResult;
	bool mOkCancelResult;
};


#endif //KSNIP_MESSAGEBOXSERVICEMOCK_H
