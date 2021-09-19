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

#ifndef KSNIP_CONSOLELOGGER_H
#define KSNIP_CONSOLELOGGER_H

#include <QNetworkReply>
#include <QMetaEnum>

#include "ILogger.h"

class ConsoleLogger : public ILogger
{
public:
	ConsoleLogger() = default;
	~ConsoleLogger() = default;

	void log(const QString &message) const override;
	void log(const QString &message, bool isSuccess) const override;
	void log(const QString &message, QNetworkReply::NetworkError value) const override;

private:
	static QString boolToString(bool isSuccess) ;
};


#endif //KSNIP_CONSOLELOGGER_H
