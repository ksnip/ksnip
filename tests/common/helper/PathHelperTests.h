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

#ifndef KSNIP_PATHHELPERTESTS_H
#define KSNIP_PATHHELPERTESTS_H

#include <QtTest>

#include "src/common/helper/PathHelper.h"

class PathHelperTests : public QObject
{
	Q_OBJECT
private slots:
	void IsPathValid_Should_ReturnFalse_When_StringEmpty();
	void IsPathValid_Should_ReturnFalse_When_StringNull();
	void IsPipePath_Should_ReturnTrue_When_PathIsDash();
	void IsPipePath_Should_ReturnFalse_When_PathIsNull();
	void IsPipePath_Should_ReturnFalse_When_PathIsEmpty();
	void IsPathValid_Should_ReturnTrue_When_StringHasContent();
	void ExtractParentDirectory_Should_ReturnStringWithParentDirectoryPath();
	void ExtractFilename_Should_ReturnStringWithFilenameWithoutFormat_When_FormatExists();
	void ExtractFilename_Should_ReturnStringWithFilenameWithoutFormat_When_NoFormatExists();
	void ExtractFilenameWithFormat_Should_ReturnStringWithFilenameWithFormat_When_FormatExists();
	void ExtractFilenameWithFormat_Should_ReturnStringWithFilenameWithFormat_When_NoFormatExists();
	void ExtractFormat_Should_ReturnWithFormat_When_FormatExists();
	void ExtractFormat_Should_ReturnEmptyString_When_NoFormatExists();
};

#endif //KSNIP_PATHHELPERTESTS_H
