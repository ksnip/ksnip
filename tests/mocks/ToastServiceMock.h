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

#ifndef KSNIP_TOASTSERVICEMOCK_H
#define KSNIP_TOASTSERVICEMOCK_H

#include <QString>

#include "src/gui/IToastService.h"
#include "tests/utils/CallCounter.h"

class ToastServiceMock : public IToastService
{
public:
	void showInfoToast(const QString &title, const QString &message, const QString &contentUrl) override;
	void showWarningToast(const QString &title, const QString &message, const QString &contentUrl) override;
	void showCriticalToast(const QString &title, const QString &message, const QString &contentUrl) override;

	// Mock Methods
	int showInfoToast_callCounter(const QString &message) const;
	int showInfoToast_callCounter() const;
	int showWarningToast_callCounter(const QString &message) const;
	int showWarningToast_callCounter() const;
	int showCriticalToast_callCounter(const QString &message) const;
	int showCriticalToast_callCounter() const;

private:
	CallCounter<QString> mShowInfoToastCallCounter;
	CallCounter<QString> mShowWarningToastCallCounter;
	CallCounter<QString> mShowCriticalToastCallCounter;
};

#endif //KSNIP_TOASTSERVICEMOCK_H
