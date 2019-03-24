/*
 * Copyright (C) 2019 Damir Porobic <https://github.com/damirporobic>
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

#include "TranslationLoader.h"

TranslationLoader::TranslationLoader()
{
    mPathToTranslation = QStringLiteral(KSNIP_LANG_INSTAL_DIR);
}

void TranslationLoader::load(const QApplication &app) const
{
    auto translator = new QTranslator();
    auto translationSuccessfullyLoaded = loadTranslationFromAbsolutePath(translator);

	if (!translationSuccessfullyLoaded) {
		translationSuccessfullyLoaded = loadTranslationFromRelativePath(translator);
	}

    // Fix for appimages as they need to use relative paths
    if (!translationSuccessfullyLoaded) {
        translationSuccessfullyLoaded = loadTranslationForAppImage(translator);
    }

    if (translationSuccessfullyLoaded) {
        app.installTranslator(translator);
    } else {
        qWarning("Unable to find any translation files.");
    }
}

bool TranslationLoader::loadTranslationFromAbsolutePath(QTranslator *translator) const
{
	return loadTranslation(translator, mPathToTranslation);
}

bool TranslationLoader::loadTranslationFromRelativePath(QTranslator *translator) const
{
	auto relativePathToAppDir = QCoreApplication::applicationDirPath() + QStringLiteral("/");
	return loadTranslation(translator, relativePathToAppDir + mPathToTranslation);
}

bool TranslationLoader::loadTranslationForAppImage(QTranslator *translator) const
{
    auto relativePathToAppDir = QCoreApplication::applicationDirPath() + QStringLiteral("/../..");
    return loadTranslation(translator, relativePathToAppDir + mPathToTranslation);
}

bool TranslationLoader::loadTranslation(QTranslator *translator, const QString &path) const
{
    auto applicationName = QStringLiteral("ksnip");
    auto separator = QStringLiteral("_");
    return translator->load(QLocale(), applicationName, separator, path);
}
