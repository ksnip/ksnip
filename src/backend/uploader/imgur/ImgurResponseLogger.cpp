/*
 *  Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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
 *
 */

#include <QtGui/QtGui>
#include "ImgurResponseLogger.h"

ImgurResponseLogger::ImgurResponseLogger()
{
    mLogFilename = QStringLiteral("imgur_history.txt");
    mLogPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    mLogFilePath = mLogPath + QStringLiteral("/") + mLogFilename;
}

void ImgurResponseLogger::log(const ImgurResponse &response)
{
    createPathIfRequired();
    auto logEntry = getLogEntry(response);

    writeLogEntry(logEntry);
}

void ImgurResponseLogger::writeLogEntry(const QString &logEntry) const
{
    QFile file(mLogFilePath);
    auto fileOpened = file.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text);
    if(fileOpened) {
        QTextStream stream(&file);
        stream << logEntry << endl;
    }
}

void ImgurResponseLogger::createPathIfRequired() const
{
    QDir qdir;
    qdir.mkpath(mLogPath);
}

QString ImgurResponseLogger::getLogEntry(const ImgurResponse &response) const
{
    auto separator = QStringLiteral(",");
    auto deleteLink = QStringLiteral("https://imgur.com/delete/") + response.deleteHash();
    auto timestamp = response.timeStamp().toString(QStringLiteral("dd.MM.yyyy hh:mm:ss"));
    return timestamp + separator + response.link() + separator + deleteLink;
}

QStringList ImgurResponseLogger::getLogs() const
{
	auto logEntries = QStringList();
	QFile file(mLogFilePath);
	auto fileOpened = file.open(QIODevice::ReadOnly);
	if (fileOpened) {

		QTextStream stream(&file);
		while (!stream.atEnd()) {
			auto entry = stream.readLine();
			logEntries.append(entry);
		}
	}
	return logEntries;
}
