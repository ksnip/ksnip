/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef KSNIP_MESSAGEBOXHELPER_H
#define KSNIP_MESSAGEBOXHELPER_H

#include <QMessageBox>

#include "src/common/enum/MessageBoxResponse.h"

class MessageBoxHelper
{
public:
    static bool yesNo(const QString &title, const QString &question);
    static MessageBoxResponse yesNoCancel(const QString &title, const QString &question);
    static void ok(const QString &title, const QString &info);

private:
	static MessageBoxResponse mapReplyToMessageBoxResponse(int reply);
};

#endif //KSNIP_MESSAGEBOXHELPER_H
