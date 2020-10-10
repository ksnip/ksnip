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

#include "MessageBoxServiceMock.h"

MessageBoxServiceMock::MessageBoxServiceMock() :
	mOkCancelResult(false),
	mYesNoResult(false)
{

}

bool MessageBoxServiceMock::yesNo(const QString &title, const QString &question)
{
	return mYesNoResult;
}

MessageBoxResponse MessageBoxServiceMock::yesNoCancel(const QString &title, const QString &question)
{
	return MessageBoxResponse::Cancel;
}

void MessageBoxServiceMock::ok(const QString &title, const QString &info)
{

}

bool MessageBoxServiceMock::okCancel(const QString &title, const QString &info)
{
	return mOkCancelResult;
}

void MessageBoxServiceMock::yesNo_set(bool response)
{
	mYesNoResult = response;
}

void MessageBoxServiceMock::okCancel_set(bool response)
{
	mOkCancelResult = response;
}
