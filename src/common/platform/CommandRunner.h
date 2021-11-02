/*
 * Copyright (C) 2017 Damir Porobic <damir.porobic@gmx.com>
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

#ifndef COMMANDRUNNER_H
#define COMMANDRUNNER_H

#include <QProcess>
#include <QFile>
#include <QTextStream>

#include "ICommandRunner.h"

class CommandRunner : public ICommandRunner
{
public:
    QString getEnvironmentVariable(const QString &variable) const override;
    bool isEnvironmentVariableSet(const QString &variable) const override;
	QString readFile(const QString &path) const override;
};

#endif // COMMANDRUNNER_H
