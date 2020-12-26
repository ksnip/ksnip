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
	filenameWithoutWildcards.replace(QLatin1String("$Y"), QDateTime::currentDateTime().toString(QLatin1String("yyyy")));
	filenameWithoutWildcards.replace(QLatin1String("$M"), QDateTime::currentDateTime().toString(QLatin1String("MM")));
	filenameWithoutWildcards.replace(QLatin1String("$D"), QDateTime::currentDateTime().toString(QLatin1String("dd")));
	filenameWithoutWildcards.replace(QLatin1String("$T"), QDateTime::currentDateTime().toString(QLatin1String("hhmmss")));
	filenameWithoutWildcards.replace(QLatin1String("$h"), QDateTime::currentDateTime().toString(QLatin1String("hh")));
	filenameWithoutWildcards.replace(QLatin1String("$m"), QDateTime::currentDateTime().toString(QLatin1String("mm")));
	filenameWithoutWildcards.replace(QLatin1String("$s"), QDateTime::currentDateTime().toString(QLatin1String("ss")));
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
	auto allFiles = parentDirectory.entryList({ QLatin1String("*") + format }, QDir::Files);
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