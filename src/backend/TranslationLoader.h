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

#include "ITranslationLoader.h"
#include "BuildConfig.h"
#include "src/logging/ILogger.h"

class TranslationLoader : public ITranslationLoader
{
public:
    explicit TranslationLoader(const QSharedPointer<ILogger> &logger);
    ~TranslationLoader() = default;
    void load(const QApplication &app) override;

private:
	QSharedPointer<ILogger> mLogger;

	bool loadTranslationFromAbsolutePath(QTranslator *translator, const QString &path, const QString &applicationName);
	bool loadTranslationFromRelativePath(QTranslator *translator, const QString &path, const QString &applicationName);
	bool loadTranslationForAppImage(QTranslator *translator, const QString &path, const QString &applicationName);
	bool loadTranslation(QTranslator *translator, const QString &path, const QString &applicationName);
	bool loadTranslationForSnap(QTranslator *translator, const QString &path, const QString &applicationName);
	void loadTranslations(const QApplication &app, QTranslator *translator, QString &path, const QString &applicationName);
};

#endif //KSNIP_TRANSLATIONLOADER_H
