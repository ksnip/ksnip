/*
 * Copyright (C) 2019 Damir Porobic <https://github.com/damirporobic>
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

#include "TranslationLoader.h"

void TranslationLoader::load(const QApplication &app) const
{
    auto ksnipTranslator = new QTranslator();
    auto kImageAnnotatorTranslator = new QTranslator();

	auto pathToKsnipTranslations = QStringLiteral(KSNIP_LANG_INSTALL_DIR);
	auto pathToKImageAnnotatorTranslations = QStringLiteral(KIMAGEANNOTATOR_LANG_INSTALL_DIR);

	loadTranslations(app, ksnipTranslator, pathToKsnipTranslations, QStringLiteral("ksnip"));
	loadTranslations(app, kImageAnnotatorTranslator, pathToKImageAnnotatorTranslations, QStringLiteral("kImageAnnotator"));
}

void TranslationLoader::loadTranslations(const QApplication &app, QTranslator *translator, QString &path, const QString &applicationName) const
{
	auto translationSuccessfullyLoaded = loadTranslationFromAbsolutePath(translator, path, applicationName);

	if (!translationSuccessfullyLoaded) {
		translationSuccessfullyLoaded = loadTranslationFromRelativePath(translator, path, applicationName);
	}

	// Fix for appimages as they need to use relative paths
	if (!translationSuccessfullyLoaded) {
	    translationSuccessfullyLoaded = loadTranslationForAppImage(translator, path, applicationName);
	}

	if (translationSuccessfullyLoaded) {
	    app.installTranslator(translator);  
	} else {
	    qWarning("Unable to find any translation files for %s.", qPrintable(applicationName));
	}
}

bool TranslationLoader::loadTranslationFromAbsolutePath(QTranslator *translator, const QString &path, const QString &applicationName) const
{
	return loadTranslation(translator, path, applicationName);
}

bool TranslationLoader::loadTranslationFromRelativePath(QTranslator *translator, const QString &path, const QString &applicationName) const
{
	auto relativePathToAppDir = QCoreApplication::applicationDirPath() + QStringLiteral("/");
	return loadTranslation(translator, relativePathToAppDir + path, applicationName);
}

bool TranslationLoader::loadTranslationForAppImage(QTranslator *translator, const QString &path, const QString &applicationName) const
{
    auto relativePathToAppDir = QCoreApplication::applicationDirPath() + QStringLiteral("/../..");
    return loadTranslation(translator, relativePathToAppDir + path, applicationName);
}

bool TranslationLoader::loadTranslation(QTranslator *translator, const QString &path, const QString &applicationName) const
{
	auto separator = QStringLiteral("_");
    return translator->load(QLocale(), applicationName, separator, path);
}
