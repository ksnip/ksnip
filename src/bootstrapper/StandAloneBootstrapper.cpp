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

#include "StandAloneBootstrapper.h"

StandAloneBootstrapper::StandAloneBootstrapper(DependencyInjector *dependencyInjector) :
	mCommandLine(nullptr),
	mMainWindow(nullptr),
	mCommandLineCaptureHandler(nullptr),
	mLogger(dependencyInjector->getObject<ILogger>()),
	mDependencyInjector(dependencyInjector)
{

}

StandAloneBootstrapper::~StandAloneBootstrapper()
{
	delete mCommandLine;
	delete mCommandLineCaptureHandler;
}

int StandAloneBootstrapper::start(const QApplication &app)
{
	app.setQuitOnLastWindowClosed(false);

	createCommandLineParser(app);

	if (isVersionRequested()) {
		return showVersion();
	}

	if (isStartedWithoutArguments()) {
		return startKsnip(app);
	}

	if (isEditRequested()) {
		return startKsnipAndEditImage(app);
	}

	if (isCommandLineCaptureRequested()) {
		return takeCaptureAndProcess(app);
	}

	return takeCaptureAndStartKsnip(app);
}

int StandAloneBootstrapper::takeCaptureAndProcess(const QApplication &app)
{
	connect(mCommandLineCaptureHandler, &CommandLineCaptureHandler::finished, this, &StandAloneBootstrapper::close);
	connect(mCommandLineCaptureHandler, &CommandLineCaptureHandler::canceled, this, &StandAloneBootstrapper::close);

	CommandLineCaptureParameter parameter(getCaptureMode(), getDelay(), getCaptureCursor());
	parameter.isWithSave = getIsSave();
	parameter.isWithUpload = getIsUpload();
	parameter.savePath = getSavePath();

	mCommandLineCaptureHandler->captureAndProcessScreenshot(parameter);

	return app.exec();
}

bool StandAloneBootstrapper::getIsUpload() const
{
	return mCommandLine->isUploadSet();
}

bool StandAloneBootstrapper::getIsSave() const
{
	return mCommandLine->isSaveSet();
}

bool StandAloneBootstrapper::isCommandLineCaptureRequested() const
{
	return getIsSave() || getIsUpload();
}

bool StandAloneBootstrapper::isEditRequested() const
{
	return mCommandLine->isEditSet();
}

bool StandAloneBootstrapper::isVersionRequested() const
{
	return mCommandLine->isVersionSet();
}

bool StandAloneBootstrapper::isStartedWithoutArguments()
{
	auto arguments = QCoreApplication::arguments();
	return arguments.count() <= 1;
}

int StandAloneBootstrapper::takeCaptureAndStartKsnip(const QApplication &app)
{
	loadTranslations(app);

	connect(mCommandLineCaptureHandler, &CommandLineCaptureHandler::finished, this, &StandAloneBootstrapper::openMainWindow);
	connect(mCommandLineCaptureHandler, &CommandLineCaptureHandler::canceled, this, &StandAloneBootstrapper::close);

	CommandLineCaptureParameter parameter(getCaptureMode(), getDelay(), getCaptureCursor());

	mCommandLineCaptureHandler->captureAndProcessScreenshot(parameter);

	return app.exec();
}

bool StandAloneBootstrapper::getCaptureCursor() const
{
	return mCommandLine->isCursorSet();
}

int StandAloneBootstrapper::getDelay() const
{
	auto delay = 0;
	if (mCommandLine->isDelaySet()) {
		delay = mCommandLine->delay();
		if (delay < 0) {
			qWarning("Delay flag set without value, ignoring delay.");
			delay = 0;
		}
	}
	return delay * 1000;
}

bool StandAloneBootstrapper::getSave() const
{
	return mCommandLine->isSaveSet();
}

QString StandAloneBootstrapper::getSavePath() const
{
	return mCommandLine->saveToPath();
}

CaptureModes StandAloneBootstrapper::getCaptureMode() const
{
	if (mCommandLine->isCaptureModeSet()) {
		return mCommandLine->captureMode();
	} else {
		qWarning("No capture mode selected, using default.");
		return CaptureModes::RectArea;
	}
}

int StandAloneBootstrapper::startKsnipAndEditImage(const QApplication &app)
{
	auto pathToImage = getImagePath();
	auto pixmap = getPixmapFromCorrectSource(pathToImage);

	if (pixmap.isNull()) {
		qWarning("Unable to open image file %s.", qPrintable(pathToImage));
		return 1;
	} else {
		loadTranslations(app);
		if(PathHelper::isPipePath(pathToImage)) {
			openMainWindow(CaptureDto(pixmap));
		} else {
			openMainWindow(CaptureFromFileDto(pixmap, pathToImage));
		}
		return app.exec();
	}
}

QPixmap StandAloneBootstrapper::getPixmapFromCorrectSource(const QString &pathToImage)
{
	if (PathHelper::isPipePath(pathToImage)) {
		qInfo("Reading image from stdin.");
		return getPixmapFromStdin();
	} else {
		return QPixmap(pathToImage);
	}
}

QPixmap StandAloneBootstrapper::getPixmapFromStdin()
{
	QByteArray stdinImage;
	while (!std::cin.eof()) {
		char string[1024];
		std::cin.read(string, sizeof(string));
		auto length = std::cin.gcount();
		stdinImage.append(string, length);
	}
	QPixmap pixmap;
	pixmap.loadFromData(stdinImage);
	return pixmap;
}

QString StandAloneBootstrapper::getImagePath() const
{
	return mCommandLine->imagePath();
}

int StandAloneBootstrapper::startKsnip(const QApplication &app)
{
	loadTranslations(app);
	createMainWindow();
	return app.exec();
}

int StandAloneBootstrapper::showVersion()
{
	QTextStream stream(stdout);
	stream << QLatin1String("Version: ") + qPrintable(KSNIP_VERSION) + QLatin1String("\n");
	stream << QLatin1String("Build: ") + qPrintable(KSNIP_BUILD_NUMBER) + QLatin1String("\n");
	return 0;
}

void StandAloneBootstrapper::createMainWindow()
{
	Q_ASSERT(mMainWindow == nullptr);

	mMainWindow = new MainWindow(mDependencyInjector);
}

void StandAloneBootstrapper::createCommandLineParser(const QApplication &app)
{
	Q_ASSERT(mCommandLine == nullptr);
	Q_ASSERT(mCommandLineCaptureHandler == nullptr);

	DependencyInjectorBootstrapper::BootstrapCommandLine(mDependencyInjector);

	mCommandLineCaptureHandler = new CommandLineCaptureHandler(mDependencyInjector);
	mCommandLine = new CommandLine (app, mCommandLineCaptureHandler->supportedCaptureModes());
}

void StandAloneBootstrapper::loadTranslations(const QApplication &app)
{
	TranslationLoader::load(app);
}

void StandAloneBootstrapper::openMainWindow(const CaptureDto &captureDto)
{
	createMainWindow();
	mMainWindow->processImage(captureDto);
}

void StandAloneBootstrapper::close()
{
	QCoreApplication::quit();
}
