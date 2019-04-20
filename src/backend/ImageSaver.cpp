/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
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
 */

#include "ImageSaver.h"

ImageSaver::ImageSaver(QWidget *parent)
{
	Q_ASSERT(parent != nullptr);

	mParent = parent;
	mConfig = KsnipConfig::instance();
}

bool ImageSaver::saveAs(const QImage &image)
{
	auto path = savePath();

	auto title = QObject::tr("Save As");
	auto filter = QObject::tr("Images") + QStringLiteral(" (*.png *.gif *.jpg);;") + QObject::tr("All Files") + QStringLiteral("(*)");
	QFileDialog saveDialog(mParent, title, path, filter);
	saveDialog.setAcceptMode(QFileDialog::AcceptSave);

	if (saveDialog.exec() == QDialog::Accepted) {
		path = saveDialog.selectedFiles().first();
	} else {
		return false;
	}

	return saveImageToPath(image, path);
}

bool ImageSaver::save(const QImage &image)
{
	auto path = savePath();
	return saveImageToPath(image, path);
}

bool ImageSaver::saveImageToPath(const QImage &image, const QString &path)
{
	ensurePathExists(path);

	auto isSuccessful = image.save(path);
	if (!isSuccessful) {
		qCritical("Unable to save file '%s'", qPrintable(path));
	}
	return isSuccessful;
}

QString ImageSaver::savePath(const QString& format) const
{
	return PathHelper::makeUniqueFilename(saveDirectory(), getFilename(), getFormat(format));
}

QString ImageSaver::getFilename() const
{
	return PathHelper::replaceWildcards(mConfig->saveFilename());
}

QString ImageSaver::getFormat(const QString &format) const
{
	QString selectedFormat;
	if (format.isNull()) {
		selectedFormat = mConfig->saveFormat();
	} else {
		selectedFormat = format.startsWith(QStringLiteral(".")) ? format : QStringLiteral(".") + format;
	}
	return selectedFormat;
}

QString ImageSaver::saveDirectory() const
{
	return PathHelper::replaceWildcards(mConfig->saveDirectory());
}

void ImageSaver::ensurePathExists(const QString &path)
{
	auto directory = PathHelper::extractPath(path);
	QDir dir(directory);
	if(!dir.exists()) {
		dir.mkpath(QStringLiteral("."));
	}
}
