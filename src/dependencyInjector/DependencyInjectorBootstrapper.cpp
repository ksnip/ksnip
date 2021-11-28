/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "DependencyInjectorBootstrapper.h"

#include "src/backend/TranslationLoader.h"
#include "src/backend/config/Config.h"
#include "src/backend/uploader/UploadHandler.h"
#include "src/backend/uploader/ftp/FtpUploader.h"
#include "src/backend/uploader/script/ScriptUploader.h"
#include "src/backend/uploader/imgur/ImgurUploader.h"
#include "src/backend/commandLine/CommandLineCaptureHandler.h"
#include "src/backend/recentImages/RecentImagesPathStore.h"
#include "src/backend/recentImages/ImagePathStorage.h"
#include "src/backend/saver/SavePathProvider.h"
#include "src/backend/saver/ImageSaver.h"
#include "src/gui/fileService/FileService.h"
#include "src/gui/clipboard/ClipboardAdapter.h"
#include "src/gui/desktopService/DesktopServiceAdapter.h"
#include "src/gui/messageBoxService/MessageBoxService.h"
#include "src/gui/captureHandler/CaptureTabStateHandler.h"
#include "src/gui/modelessWindows/ocrWindow/OcrWindowCreator.h"
#include "src/gui/modelessWindows/ocrWindow/OcrWindowHandler.h"
#include "src/logging/ConsoleLogger.h"
#include "src/logging/NoneLogger.h"
#include "src/common/loader/IconLoader.h"
#include "src/common/platform/CommandRunner.h"
#include "src/common/platform/PlatformChecker.h"
#include "src/common/provider/directoryPathProvider/DirectoryPathProvider.h"
#include "src/common/provider/scaledSizeProvider/ScaledSizeProvider.h"
#include "src/plugins/PluginManager.h"

#if defined(__APPLE__)
#include "src/backend/config/MacConfig.h"
#include "src/backend/imageGrabber/MacImageGrabber.h"
#include "src/common/adapter/fileDialog/FileDialogAdapter.h"
#endif

#if defined(UNIX_X11)
#include "src/backend/config/WaylandConfig.h"
#include "src/backend/imageGrabber/X11ImageGrabber.h"
#include "src/backend/imageGrabber/GnomeX11ImageGrabber.h"
#include "src/backend/imageGrabber/WaylandImageGrabber.h"
#include "src/backend/imageGrabber/KdeWaylandImageGrabber.h"
#include "src/backend/imageGrabber/GnomeWaylandImageGrabber.h"
#include "src/common/adapter/fileDialog/SnapFileDialogAdapter.h"
#include "src/common/provider/directoryPathProvider/SnapDirectoryPathProvider.h"
#include "src/common/provider/scaledSizeProvider/GnomeScaledSizeProvider.h"
#include "src/gui/desktopService/SnapDesktopServiceAdapter.h"
#endif

#if  defined(_WIN32)
#include "src/backend/config/Config.h"
#include "src/backend/imageGrabber/WinImageGrabber.h"
#include "src/common/adapter/fileDialog/FileDialogAdapter.h"
#endif

void DependencyInjectorBootstrapper::BootstrapCore(DependencyInjector *dependencyInjector)
{
	dependencyInjector->registerInstance<ICommandRunner, CommandRunner>();
	dependencyInjector->registerInstance<IPlatformChecker, PlatformChecker, ICommandRunner>();
	injectDirectoryPathProvider(dependencyInjector);
	injectConfig(dependencyInjector);
	injectLogger(dependencyInjector);
	dependencyInjector->registerInstance<ITranslationLoader, TranslationLoader, ILogger>();
}

void DependencyInjectorBootstrapper::BootstrapCommandLine(DependencyInjector *dependencyInjector)
{
	injectImageGrabber(dependencyInjector);
	dependencyInjector->registerInstance<ISavePathProvider, SavePathProvider, IConfig>();
	dependencyInjector->registerInstance<IImageSaver, ImageSaver, IConfig>();
	dependencyInjector->registerInstance<IFtpUploader, FtpUploader, IConfig, ILogger>();
	dependencyInjector->registerInstance<IScriptUploader, ScriptUploader, IConfig>();
	dependencyInjector->registerInstance<IImgurUploader, ImgurUploader, IConfig>();
	dependencyInjector->registerInstance<IUploadHandler, UploadHandler, IConfig, IFtpUploader, IScriptUploader, IImgurUploader>();
	dependencyInjector->registerInstance<ICommandLineCaptureHandler, CommandLineCaptureHandler, IImageGrabber, IUploadHandler, IImageSaver, ISavePathProvider>();
}

void DependencyInjectorBootstrapper::BootstrapGui(DependencyInjector *dependencyInjector)
{
	dependencyInjector->registerInstance<IFileService, FileService>();
	dependencyInjector->registerInstance<IImagePathStorage, ImagePathStorage>();
	dependencyInjector->registerInstance<IClipboard, ClipboardAdapter>();
	injectDesktopServiceAdapter(dependencyInjector);
	dependencyInjector->registerInstance<IMessageBoxService, MessageBoxService>();
	dependencyInjector->registerInstance<ICaptureTabStateHandler, CaptureTabStateHandler>();
	dependencyInjector->registerInstance<IRecentImageService, RecentImagesPathStore, IImagePathStorage>();
	dependencyInjector->registerInstance<IIconLoader, IconLoader>();
	injectFileDialogService(dependencyInjector);
	injectScaledSizeProvider(dependencyInjector);
	dependencyInjector->registerInstance<IPluginManager, PluginManager, IConfig, ILogger>();
	dependencyInjector->registerInstance<IOcrWindowCreator, OcrWindowCreator, IPluginManager>();
	dependencyInjector->registerInstance<IOcrWindowHandler, OcrWindowHandler, IOcrWindowCreator>();
}

void DependencyInjectorBootstrapper::injectDesktopServiceAdapter(DependencyInjector *dependencyInjector)
{
#if defined(UNIX_X11)
	auto platformChecker = dependencyInjector->get<IPlatformChecker>();
	if(platformChecker->isSnap()) {
		dependencyInjector->registerInstance<IDesktopService, SnapDesktopServiceAdapter>();
	} else {
		dependencyInjector->registerInstance<IDesktopService, DesktopServiceAdapter>();
	}
#else
	dependencyInjector->registerInstance<IDesktopService, DesktopServiceAdapter>();
#endif

}

void DependencyInjectorBootstrapper::injectImageGrabber(DependencyInjector *dependencyInjector)
{
	auto logger = dependencyInjector->get<ILogger>();
	auto config = dependencyInjector->get<IConfig>();

#if defined(__APPLE__)
	logger->log(QLatin1String("MacImageGrabber selected"));
	dependencyInjector->registerFactory<IImageGrabber, MacImageGrabber, IConfig>();
#endif

#if defined(UNIX_X11)
	auto platformChecker = dependencyInjector->get<IPlatformChecker>();
	if (platformChecker->isX11()) {
		if (platformChecker->isGnome()) {
			logger->log(QLatin1String("GnomeX11ImageGrabber selected"));
			dependencyInjector->registerFactory<IImageGrabber, GnomeX11ImageGrabber, IConfig>();
		} else {
			logger->log(QLatin1String("X11ImageGrabber selected"));
			dependencyInjector->registerFactory<IImageGrabber, X11ImageGrabber, IConfig>();
		}
	} else if (platformChecker->isWayland()) {
		if (config->forceGenericWaylandEnabled()) {
			logger->log(QLatin1String("WaylandImageGrabber selected"));
			dependencyInjector->registerFactory<IImageGrabber, WaylandImageGrabber, IConfig>();
		} else if (platformChecker->isKde()) {
			logger->log(QLatin1String("KdeWaylandImageGrabber selected"));
			dependencyInjector->registerFactory<IImageGrabber, KdeWaylandImageGrabber, IConfig>();
		} else if (platformChecker->isGnome()) {
			logger->log(QLatin1String("GnomeWaylandImageGrabber selected"));
			dependencyInjector->registerFactory<IImageGrabber, GnomeWaylandImageGrabber, IConfig>();
		} else {
			qCritical("Unknown wayland platform, using default wayland Image Grabber.");
			logger->log(QLatin1String("WaylandImageGrabber selected"));
			dependencyInjector->registerFactory<IImageGrabber, WaylandImageGrabber, IConfig>();
		}
	} else {
		qCritical("Unknown platform, using default X11 Image Grabber.");
		dependencyInjector->registerFactory<IImageGrabber, X11ImageGrabber, IConfig>();
	}
#endif

#if  defined(_WIN32)
	logger->log(QLatin1String("WinImageGrabber selected"));
	dependencyInjector->registerFactory<IImageGrabber, WinImageGrabber, IConfig>();
#endif
}

void DependencyInjectorBootstrapper::injectLogger(DependencyInjector *dependencyInjector)
{
	auto config = dependencyInjector->get<IConfig>();
	if (config->isDebugEnabled()) {
		dependencyInjector->registerInstance<ILogger, ConsoleLogger>();
	} else {
		dependencyInjector->registerInstance<ILogger, NoneLogger>();
	}
}

void DependencyInjectorBootstrapper::injectConfig(DependencyInjector *dependencyInjector)
{
#if defined(__APPLE__)
	dependencyInjector->registerInstance<IConfig, MacConfig, IDirectoryPathProvider>();
#endif

#if defined(UNIX_X11)
	auto platformChecker = dependencyInjector->get<IPlatformChecker>();
	if (platformChecker->isWayland()) {
		dependencyInjector->registerInstance<IConfig, WaylandConfig, IDirectoryPathProvider, IPlatformChecker>();
	} else {
		dependencyInjector->registerInstance<IConfig, Config, IDirectoryPathProvider>();
	}
#endif

#if  defined(_WIN32)
	dependencyInjector->registerInstance<IConfig, Config, IDirectoryPathProvider>();
#endif
}

void DependencyInjectorBootstrapper::injectFileDialogService(DependencyInjector *dependencyInjector)
{
#if defined(UNIX_X11)
	auto platformChecker = dependencyInjector->get<IPlatformChecker>();
	if (platformChecker->isSnap()) {
		dependencyInjector->registerInstance<IFileDialogService, SnapFileDialogAdapter>();
	} else {
		dependencyInjector->registerInstance<IFileDialogService, FileDialogAdapter>();
	}
#else
	dependencyInjector->registerInstance<IFileDialogService, FileDialogAdapter>();
#endif
}

void DependencyInjectorBootstrapper::injectDirectoryPathProvider(DependencyInjector *dependencyInjector)
{
#if defined(UNIX_X11)
	auto platformChecker = dependencyInjector->get<IPlatformChecker>();
	if (platformChecker->isSnap()) {
		dependencyInjector->registerInstance<IDirectoryPathProvider, SnapDirectoryPathProvider>();
	} else {
		dependencyInjector->registerInstance<IDirectoryPathProvider, DirectoryPathProvider>();
	}
#else
	dependencyInjector->registerInstance<IDirectoryPathProvider, DirectoryPathProvider>();
#endif
}

void DependencyInjectorBootstrapper::injectScaledSizeProvider(DependencyInjector *dependencyInjector)
{
#if defined(UNIX_X11)
	auto platformChecker = dependencyInjector->get<IPlatformChecker>();
	if(platformChecker->isGnome()) {
		dependencyInjector->registerInstance<IScaledSizeProvider, GnomeScaledSizeProvider>();
	} else {
		dependencyInjector->registerInstance<IScaledSizeProvider, ScaledSizeProvider>();
	}
#else
	dependencyInjector->registerInstance<IScaledSizeProvider, ScaledSizeProvider>();
#endif
}
