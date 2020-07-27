/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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

#include "CommandRunner.h"

QString CommandRunner::getEnvironmentVariable(const QString& variable) const
{
    QString value;

    auto command = variable.trimmed();
    command.prepend(QLatin1Literal("echo $"));
    command.append(QLatin1Literal(" 2>&1"));

    auto stream = popen(command.toLatin1(), "r");

    if (stream) {
        char buffer[mMaxBuffer];
        while (!feof(stream)) {
            if (fgets(buffer, mMaxBuffer, stream) != nullptr) {
                value.append(buffer);
            }
        }
        pclose(stream);
    }
    return value;
}

bool CommandRunner::isEnvironmentVariableSet(const QString &variable) const
{
	return QProcessEnvironment::systemEnvironment().contains(variable);
}
