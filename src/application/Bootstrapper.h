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

#ifndef KSNIP_BOOTSTRAPPER_H
#define KSNIP_BOOTSTRAPPER_H

#include <QApplication>

#include "BuildConfig.h"
#include "src/gui/MainWindow.h"
#include "src/application/InstanceLock.h"
#include "src/backend/imageGrabber/ImageGrabberFactory.h"
#include "src/backend/TranslationLoader.h"
#include "src/backend/KsnipCommandLine.h"
#include "src/backend/ipc/IpcServer.h"
#include "src/backend/ipc/IpcClient.h"
#include "src/common/dtos/CaptureFromFileDto.h"

class Bootstrapper
{
public:
	Bootstrapper();
	~Bootstrapper();

	int start(const QApplication &app);

private:
	AbstractImageGrabber *mImageGrabber;
	KsnipCommandLine *mCommandLine;
	MainWindow *mMainWindow;
	IpcServer *mIpcServer;

	void loadTranslations(const QApplication &app) const;
	void createImageGrabber();
	void createCommandLineParser(const QApplication &app);
	void createMainWindow(RunMode mode);
	void createIpcServer();
	int showVersion() const;
	int startKsnip(const QApplication &app);
	int startKsnipAndEditImage(const QApplication &app);
	CaptureModes getCaptureMode() const;
	RunMode getRunMode() const;
	int getDelay() const;
	int startKsnipAndTakeCapture(const QApplication &app);
	bool startedWithoutArguments() const;
};


#endif //KSNIP_BOOTSTRAPPER_H
