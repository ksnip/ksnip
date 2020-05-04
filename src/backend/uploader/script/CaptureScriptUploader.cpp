/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "CaptureScriptUploader.h"

CaptureScriptUploader::CaptureScriptUploader() : mConfig(KsnipConfigProvider::instance())
{
	connect(&mProcessHandler, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &CaptureScriptUploader::scriptFinished);
	connect(&mProcessHandler, &QProcess::errorOccurred, this, &CaptureScriptUploader::errorOccurred);
}

void CaptureScriptUploader::upload(const QImage &image)
{
	if(saveImageLocally(image)) {
		mProcessHandler.start(mConfig->uploadScriptPath(), { mPathToImage });
	} else {
		auto result = UploadScriptResult(UploadScriptStatus::UnableToSaveTemporaryImage);
		emit finished(result);
	}
}

bool CaptureScriptUploader::saveImageLocally(const QImage &image)
{
	auto timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyyMMddhhmmssz"));
	auto filename = QStringLiteral("ksnip-tmp-") + timestamp + QStringLiteral(".png");
	mPathToImage = mConfig->saveDirectory() + QStringLiteral("/") + filename;
	return image.save(mPathToImage);
}

void CaptureScriptUploader::scriptFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	Q_UNUSED(exitCode);
	Q_UNUSED(exitStatus);

	if(exitStatus != QProcess::ExitStatus::CrashExit) {
		auto output = QString(mProcessHandler.readAllStandardOutput());
		auto result = parseOutput(output);

		writeToConsole(output);
		cleanup();

		emit finished(UploadScriptResult(result));
	}
}

QString CaptureScriptUploader::parseOutput(const QString &output) const
{
	auto startTag = mConfig->uploadScriptCopyOutputAfter();
	auto startTagLength = startTag.length();
	auto endTag = mConfig->uploadScriptCopyOutputBefore();

	auto startIndex = output.indexOf(startTag);
	auto endIndex = output.indexOf(endTag);
	auto indexFrom = startIndex > -1 ? startIndex + startTagLength : 0;
	auto indexTo = endIndex > -1 ? endIndex : output.length() - 1;

	return output.mid(indexFrom, indexTo - indexFrom);
}

void CaptureScriptUploader::errorOccurred(QProcess::ProcessError errorType)
{
	writeToConsole(mProcessHandler.readAllStandardError());
	cleanup();

	auto status = mapErrorTypeToStatus(errorType);
	emit finished(UploadScriptResult(status));
}

UploadScriptStatus CaptureScriptUploader::mapErrorTypeToStatus(QProcess::ProcessError errorType) const
{
	switch (errorType) {
		case QProcess::FailedToStart:
			return UploadScriptStatus::FailedToStart;
		case QProcess::Crashed:
			return UploadScriptStatus::Crashed;
		case QProcess::Timedout:
			return UploadScriptStatus::Timedout;
		case QProcess::ReadError:
			return UploadScriptStatus::ReadError;
		case QProcess::WriteError:
			return UploadScriptStatus::WriteError;
		default:
			return UploadScriptStatus::UnknownError;
	}
}

void CaptureScriptUploader::cleanup()
{
	QFile file(mPathToImage);
	file.remove();
	mPathToImage.clear();
}

void CaptureScriptUploader::writeToConsole(const QString &output) const
{
	qInfo("%s", qPrintable(output));
}
