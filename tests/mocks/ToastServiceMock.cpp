/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "ToastServiceMock.h"

void ToastServiceMock::showInfoToast(const QString &title, const QString &message, const QString &contentUrl)
{
	mShowInfoToastCallCounter.increment(message);
}

void ToastServiceMock::showWarningToast(const QString &title, const QString &message, const QString &contentUrl)
{
	mShowWarningToastCallCounter.increment(message);
}

void ToastServiceMock::showCriticalToast(const QString &title, const QString &message, const QString &contentUrl)
{
	mShowCriticalToastCallCounter.increment(message);
}

int ToastServiceMock::showInfoToast_callCounter(const QString &message) const
{
	return mShowInfoToastCallCounter.count(message);
}

int ToastServiceMock::showInfoToast_callCounter() const
{
	return mShowInfoToastCallCounter.count();
}

int ToastServiceMock::showWarningToast_callCounter(const QString &message) const
{
	return mShowWarningToastCallCounter.count(message);
}

int ToastServiceMock::showWarningToast_callCounter() const
{
	return mShowWarningToastCallCounter.count();
}

int ToastServiceMock::showCriticalToast_callCounter(const QString &message) const
{
	return mShowCriticalToastCallCounter.count(message);
}

int ToastServiceMock::showCriticalToast_callCounter() const
{
	return mShowCriticalToastCallCounter.count();
}




