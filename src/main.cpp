/*
 * Copyright (C) 2017 Damir Porobic <https://github.com/damirporobic>
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

#if  defined(_WIN32)
// Prevent starting console in background under windows
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <QApplication>

#include "BuildConfig.h"
#include "src/gui/MainWindow.h"
#include "src/backend/imageGrabber/ImageGrabberFactory.h"
#include "src/backend/TranslationLoader.h"
#include "src/backend/KsnipCommandLine.h"
#include "src/gui/keyboardShortcuts/GlobalKeyboardShortcut.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

    app.setOrganizationName(QStringLiteral("ksnip"));
    app.setOrganizationDomain(QStringLiteral("ksnip.org"));
    app.setApplicationName(QStringLiteral("ksnip"));
    app.setApplicationVersion(QStringLiteral(KSNIP_VERSION));

    app.setStyle(KsnipConfig::instance()->applicationStyle());

    TranslationLoader translationLoader;
    translationLoader.load(app);

    auto imageGrabber = ImageGrabberFactory::createImageGrabber();

    KsnipCommandLine commandLine(app, imageGrabber->supportedCaptureModes());

    auto arguments = QCoreApplication::arguments();
    MainWindow* window;

    // If there are no options except the the ksnip executable name, just run the application
    if (arguments.count() <= 1) {
        window = new MainWindow(imageGrabber, RunMode::GUI);
        auto shortcut = new GlobalKeyboardShortcut(app);
        window->connect(shortcut, &GlobalKeyboardShortcut::pressed, window, &MainWindow::triggerNewDefaultCapture);
        return app.exec();
    }

	if (commandLine.isVersionSet()) {
		qInfo("Version: %s", qPrintable(KSNIP_VERSION));
		qInfo("Build: %s", qPrintable(KSNIP_BUILD_NUMBER));
		return 0;
	}

    if (commandLine.isEditSet()) {
        auto pathToImage = commandLine.image();
        QPixmap pixmap(pathToImage);

        if (pixmap.isNull()) {
            qWarning("Unable to open image file %s.", qPrintable(pathToImage));
            return 1;
        }

        window = new MainWindow(imageGrabber, RunMode::Edit);
        window->showCapture(pixmap);
        return app.exec();
    }

    // Check if delay was selected, if yes, make sure a valid number was provided
    auto delay = 0;
    if (commandLine.isDelaySet()) {
        delay = commandLine.delay();
        if (delay < 0) {
            qWarning("Please enter delay in seconds.");
            return 1;
        }
    }

    // Check if the user wants the mouse cursor to be included
    auto captureCursor = commandLine.isCursorSet();

    CaptureModes mode;
    if (commandLine.isCaptureModeSet()) {
        mode = commandLine.captureMode();
    } else {
        qWarning("Please select capture mode.");
        return 1;
    }

    if (commandLine.isSaveSet()) {
        window = new MainWindow(imageGrabber, RunMode::CLI);
    } else {
        window = new MainWindow(imageGrabber, RunMode::Edit);
    }

    window->captureScreenshot(mode, captureCursor, delay * 1000);
    return app.exec();
}
