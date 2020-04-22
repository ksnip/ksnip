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

#include "MessageBoxHelper.h"

bool MessageBoxHelper::yesNo(const QString &title, const QString &question)
{
	auto reply = QMessageBox::question(nullptr, title, question, QMessageBox::Yes | QMessageBox::No);
    return reply == QMessageBox::Yes;
}

MessageBoxResponse MessageBoxHelper::yesNoCancel(const QString &title, const QString &question)
{
	auto reply = QMessageBox::question(nullptr, title, question, QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	return mapReplyToMessageBoxResponse(reply);
}

void MessageBoxHelper::ok(const QString &title, const QString &info)
{
	QMessageBox::question(nullptr, title, info, QMessageBox::Ok);
}

MessageBoxResponse MessageBoxHelper::mapReplyToMessageBoxResponse(int reply)
{
	switch (reply) {
		case QMessageBox::Yes:
			return MessageBoxResponse::Yes;
		case QMessageBox::No:
			return MessageBoxResponse::No;
		case QMessageBox::Cancel:
			return MessageBoxResponse::Cancel;
		default:
			return MessageBoxResponse::No;
	}
}
