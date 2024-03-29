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

#include "TempFileProvider.h"

#include <QCoreApplication>

TempFileProvider::TempFileProvider(const QSharedPointer<IConfig> &config) :
    mConfig(config)
{
    connect(qApp, &QCoreApplication::aboutToQuit, this, &TempFileProvider::removeTempFiles);
}

QString TempFileProvider::tempFile()
{
	QTemporaryFile file(mConfig->tempDirectory() + QDir::separator() + QLatin1String("ksnip_tmp_XXXXXX.png"));
	file.setAutoRemove(false);
	if (!file.open()) {
		qWarning("Failed to created temporary file %s", qPrintable(file.fileName()));
	}

    mTempFiles.append(file.fileName());

	return file.fileName();
}

void TempFileProvider::removeTempFiles() {
    for(const auto& file : mTempFiles) {
        QFile(file).remove();
    }
}
