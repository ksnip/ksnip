/*
 *  Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef KSNIP_IMGURRESPONSELOGGER_H
#define KSNIP_IMGURRESPONSELOGGER_H

#include <QStandardPaths>
#include <QFile>
#include <QTextStream>

#include "UploadResponse.h"

class ImgurResponseLogger
{
public:
    explicit ImgurResponseLogger();
    ~ImgurResponseLogger() = default;

    void log(const UploadResponse &response);
	QStringList getLogs() const;

private:
    QString mLogFilename;
    QString mLogPath;
    QString mLogFilePath;
    void createPathIfRequired() const;
    const QString getLogEntry(const UploadResponse &response) const;
    void writeLogEntry(const QString &logEntry) const;
};

#endif //KSNIP_IMGURRESPONSELOGGER_H
