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

#ifndef KSNIP_STANDALONEBOOTSTRAPPER_H
#define KSNIP_STANDALONEBOOTSTRAPPER_H

#include <QApplication>

#include <iostream>

#include "BuildConfig.h"
#include "src/bootstrapper/IBootstrapper.h"
#include "src/gui/MainWindow.h"
#include "src/backend/imageGrabber/ImageGrabberFactory.h"
#include "src/backend/TranslationLoader.h"
#include "src/backend/commandLine/CommandLine.h"
#include "src/backend/commandLine/CommandLineCaptureHandler.h"

class StandAloneBootstrapper : public QObject, public IBootstrapper
{
	Q_OBJECT
public:
	StandAloneBootstrapper();
	~StandAloneBootstrapper() override;

	int start(const QApplication &app) override;

protected:
	MainWindow *mMainWindow;

	void createCommandLineParser(const QApplication &app);
	static int showVersion();
	bool isStartedWithoutArguments() const;
	bool isVersionRequested() const;
	bool isEditRequested() const;
	CaptureModes getCaptureMode() const;
	int getDelay() const;
	QString getImagePath() const;
	bool getCaptureCursor() const;
	bool getSave() const;
	QString getSavePath() const;

private:
	CommandLine *mCommandLine;
	CommandLineCaptureHandler *mCommandLineCaptureHandler;

	static void loadTranslations(const QApplication &app) ;
	virtual void createMainWindow();
	int startKsnip(const QApplication &app);
	int startKsnipAndEditImage(const QApplication &app);
	int takeCaptureAndStartKsnip(const QApplication &app);
	static QPixmap getPixmapFromCorrectSource(const QString &pathToImage);
	static QPixmap getPixmapFromStdin();
	bool isCommandLineCaptureRequested() const;
	int takeCaptureAndSave(const QApplication &app);

private slots:
	void openMainWindow(const CaptureDto &captureDto);
	void close();

};


#endif //KSNIP_STANDALONEBOOTSTRAPPER_H
