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

#ifndef KSNIP_TRANSLATIONLOADER_H
#define KSNIP_TRANSLATIONLOADER_H

#include <QApplication>
#include <QTranslator>

#include "BuildConfig.h"

class TranslationLoader
{
public:
    TranslationLoader() = default;
    ~TranslationLoader() = default;
    static void load(const QApplication &app);

private:

	static bool loadTranslationFromAbsolutePath(QTranslator *translator, const QString &path, const QString &applicationName);
	static bool loadTranslationFromRelativePath(QTranslator *translator, const QString &path, const QString &applicationName);
	static bool loadTranslationForAppImage(QTranslator *translator, const QString &path, const QString &applicationName);
    static bool loadTranslation(QTranslator *translator, const QString &path, const QString &applicationName);
	static void loadTranslations(const QApplication &app, QTranslator *translator, QString &path, const QString &applicationName);
};

#endif //KSNIP_TRANSLATIONLOADER_H
