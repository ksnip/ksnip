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

StandAloneBootstrapper::StandAloneBootstrapper() :
	mImageGrabber(nullptr),
	mCommandLine(nullptr),
	mMainWindow(nullptr)
{

}

StandAloneBootstrapper::~StandAloneBootstrapper()
{
	delete mCommandLine;
}

int StandAloneBootstrapper::start(const QApplication &app)
{
	app.setQuitOnLastWindowClosed(false);

	createImageGrabber();
	createCommandLineParser(app);
	loadTranslations(app);

	if (isVersionRequested()) {
		return showVersion();
	}

	if (isStartedWithoutArguments()) {
		return startKsnip(app);
	}

	if (isEditRequested()) {
		return startKsnipAndEditImage(app);
	}

	return startKsnipAndTakeCapture(app);
}

bool StandAloneBootstrapper::isEditRequested() const
{
	return mCommandLine->isEditSet();
}

bool StandAloneBootstrapper::isVersionRequested() const
{
	return mCommandLine->isVersionSet();
}

bool StandAloneBootstrapper::isStartedWithoutArguments() const
{
	auto arguments = QCoreApplication::arguments();
	return arguments.count() <= 1;
}

int StandAloneBootstrapper::startKsnipAndTakeCapture(const QApplication &app)
{
	auto captureMode = getCaptureMode();
	auto runMode = getRunMode();
	auto captureCursor = getCaptureCursor();
	auto delay = getDelay();

	createMainWindow(runMode);
	mMainWindow->captureScreenshot(captureMode, captureCursor, delay);
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

RunMode StandAloneBootstrapper::getRunMode() const
{
	return getSave() ? RunMode::CLI : RunMode::Edit;
}

bool StandAloneBootstrapper::getSave() const
{
	return mCommandLine->isSaveSet();
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
		createMainWindow(RunMode::Edit);
		if(PathHelper::isPipePath(pathToImage)) {
			mMainWindow->processImage(CaptureDto(pixmap));
		} else {
			mMainWindow->processImage(CaptureFromFileDto(pixmap, pathToImage));
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
	createMainWindow(RunMode::GUI);
	return app.exec();
}

int StandAloneBootstrapper::showVersion()
{
	qInfo("Version: %s", qPrintable(KSNIP_VERSION));
	qInfo("Build: %s", qPrintable(KSNIP_BUILD_NUMBER));
	return 0;
}

void StandAloneBootstrapper::createMainWindow(RunMode mode)
{
	Q_ASSERT(mMainWindow == nullptr);

	mMainWindow = new MainWindow(mImageGrabber, mode);
}

void StandAloneBootstrapper::createCommandLineParser(const QApplication &app)
{
	mCommandLine = new KsnipCommandLine (app, mImageGrabber->supportedCaptureModes());
}

void StandAloneBootstrapper::createImageGrabber()
{
	mImageGrabber = ImageGrabberFactory::createImageGrabber();
}

void StandAloneBootstrapper::loadTranslations(const QApplication &app)
{
	TranslationLoader::load(app);
}
