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

#include "ScriptUploader.h"

ScriptUploader::ScriptUploader() : mConfig(KsnipConfigProvider::instance())
{
	connect(&mProcessHandler, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &ScriptUploader::scriptFinished);
	connect(&mProcessHandler, &QProcess::errorOccurred, this, &ScriptUploader::errorOccurred);
}

void ScriptUploader::upload(const QImage &image)
{
	if(saveImageLocally(image)) {
		mProcessHandler.start(mConfig->uploadScriptPath(), { mPathToImage });
	} else {
		auto result = UploadResult(UploadStatus::UnableToSaveTemporaryImage);
		emit finished(result);
	}
}

UploaderType ScriptUploader::type() const
{
	return UploaderType::Script;
}

bool ScriptUploader::saveImageLocally(const QImage &image)
{
	auto timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyyMMddhhmmssz"));
	auto filename = QStringLiteral("ksnip-tmp-") + timestamp + QStringLiteral(".png");
	mPathToImage = mConfig->saveDirectory() + QStringLiteral("/") + filename;
	return image.save(mPathToImage);
}

void ScriptUploader::scriptFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	Q_UNUSED(exitCode);
	Q_UNUSED(exitStatus);

	if(exitStatus != QProcess::ExitStatus::CrashExit) {
		auto output = QString(mProcessHandler.readAllStandardOutput());
		auto result = parseOutput(output);

		writeToConsole(output);
		cleanup();

		emit finished(UploadResult(UploadStatus::NoError, result));
	}
}

QString ScriptUploader::parseOutput(const QString &output) const
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

void ScriptUploader::errorOccurred(QProcess::ProcessError errorType)
{
	writeToConsole(mProcessHandler.readAllStandardError());
	cleanup();

	auto status = mapErrorTypeToStatus(errorType);
	emit finished(UploadResult(status));
}

UploadStatus ScriptUploader::mapErrorTypeToStatus(QProcess::ProcessError errorType) const
{
	switch (errorType) {
		case QProcess::FailedToStart:
			return UploadStatus::FailedToStart;
		case QProcess::Crashed:
			return UploadStatus::Crashed;
		case QProcess::Timedout:
			return UploadStatus::Timedout;
		case QProcess::ReadError:
			return UploadStatus::ReadError;
		case QProcess::WriteError:
			return UploadStatus::WriteError;
		default:
			return UploadStatus::UnknownError;
	}
}

void ScriptUploader::cleanup()
{
	QFile file(mPathToImage);
	file.remove();
	mPathToImage.clear();
}

void ScriptUploader::writeToConsole(const QString &output) const
{
	qInfo("%s", qPrintable(output));
}

