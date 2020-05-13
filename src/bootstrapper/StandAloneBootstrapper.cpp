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
	createImageGrabber();
	createCommandLineParser(app);
	loadTranslations(app);

	if (mCommandLine->isVersionSet()) {
		return showVersion();
	}

	if (startedWithoutArguments()) {
		return startKsnip(app);
	}

	if (mCommandLine->isEditSet()) {
		return startKsnipAndEditImage(app);
	}

	return startKsnipAndTakeCapture(app);
}

bool StandAloneBootstrapper::startedWithoutArguments() const
{
	auto arguments = QCoreApplication::arguments();
	return arguments.count() <= 1;
}

int StandAloneBootstrapper::startKsnipAndTakeCapture(const QApplication &app)
{
	auto captureMode = getCaptureMode();
	auto runMode = getRunMode();
	auto captureCursor = mCommandLine->isCursorSet();
	auto delay = getDelay();

	createMainWindow(runMode);
	mMainWindow->captureScreenshot(captureMode, captureCursor, delay);
	return app.exec();
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
	return mCommandLine->isSaveSet() ? RunMode::CLI : RunMode::Edit;
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
	auto pathToImage = mCommandLine->imagePath();
	QPixmap pixmap(pathToImage);

	if (pixmap.isNull()) {
		qWarning("Unable to open image file %s.", qPrintable(pathToImage));
		return 1;
	}

	auto captureDto = CaptureFromFileDto(pixmap, pathToImage);

	createMainWindow(RunMode::Edit);
	mMainWindow->processImage(captureDto);
	return app.exec();
}

int StandAloneBootstrapper::startKsnip(const QApplication &app)
{
	createMainWindow(RunMode::GUI);
	return app.exec();
}

int StandAloneBootstrapper::showVersion() const
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

void StandAloneBootstrapper::loadTranslations(const QApplication &app) const
{
	TranslationLoader translationLoader;
	translationLoader.load(app);
}
