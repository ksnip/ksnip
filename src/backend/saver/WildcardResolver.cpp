/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "WildcardResolver.h"

QString WildcardResolver::replaceDateTimeWildcards(const QString &filename)
{
	auto filenameWithoutWildcards = filename;
	filenameWithoutWildcards.replace(QStringLiteral("$Y"), QDateTime::currentDateTime().toString(QStringLiteral("yyyy")));
	filenameWithoutWildcards.replace(QStringLiteral("$M"), QDateTime::currentDateTime().toString(QStringLiteral("MM")));
	filenameWithoutWildcards.replace(QStringLiteral("$D"), QDateTime::currentDateTime().toString(QStringLiteral("dd")));
	filenameWithoutWildcards.replace(QStringLiteral("$T"), QDateTime::currentDateTime().toString(QStringLiteral("hhmmss")));
	filenameWithoutWildcards.replace(QStringLiteral("$h"), QDateTime::currentDateTime().toString(QStringLiteral("hh")));
	filenameWithoutWildcards.replace(QStringLiteral("$m"), QDateTime::currentDateTime().toString(QStringLiteral("mm")));
	filenameWithoutWildcards.replace(QStringLiteral("$s"), QDateTime::currentDateTime().toString(QStringLiteral("ss")));
	return filenameWithoutWildcards;
}

QString WildcardResolver::replaceNumberWildcards(const QString &filename, const QString &directory, const QString &format)
{
	auto filenameWithoutWildcards = filename;
	auto wildcard = QLatin1Char('#');
	if(filenameWithoutWildcards.contains(wildcard)) {
		auto firstWildcardIndex = filename.indexOf(wildcard);
		auto lastWildcardIndex = filename.lastIndexOf(wildcard);
		auto leftPart = filename.left(firstWildcardIndex);
		auto rightPart = filename.mid(lastWildcardIndex + 1);
		auto digitCount = filename.count(wildcard);
		auto highestNumber = getHighestWildcardNumber(directory, leftPart, rightPart, format);

		filenameWithoutWildcards = leftPart + QString("%1").arg(highestNumber + 1, digitCount, 10, QChar('0')) + rightPart;
	}

	return filenameWithoutWildcards;
}

int WildcardResolver::getHighestWildcardNumber(const QString &directory, const QString &leftPart, const QString &rightPart, const QString &format)
{
	auto rightPartWithFormat = rightPart + format;
	QDir parentDirectory(directory);
	auto number = 0;
	auto allFiles = parentDirectory.entryList({ QStringLiteral("*") + format }, QDir::Files);
	for(auto file : allFiles) {
		if(file.startsWith(leftPart) && file.endsWith(rightPartWithFormat)) {
			file.remove(leftPart);
			file.remove(rightPartWithFormat);
			auto currentNumber = file.toInt();
			number = qMax(number, currentNumber);
		}
	}
	return number;
}