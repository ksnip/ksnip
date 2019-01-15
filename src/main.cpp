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
#include "src/common/helper/CommandLineParserHelper.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

    // Setup application properties
    app.setOrganizationName(QStringLiteral("ksnip"));
    app.setOrganizationDomain(QStringLiteral("ksnip.org"));
    app.setApplicationName(QStringLiteral("ksnip"));
    app.setApplicationVersion(QStringLiteral(KSNIP_VERSION));

    QTranslator translator;
    auto pathToTranslations = QStringLiteral(KSNIP_LANG_INSTAL_DIR);
    auto translationSuccessfullyLoaded = translator.load(QLocale(), QStringLiteral("ksnip"), QStringLiteral("_"), pathToTranslations);

    // Fix for appimages as they need to use relative paths
    if (!translationSuccessfullyLoaded) {
        auto appDirPath = QCoreApplication::applicationDirPath() + QStringLiteral("/../..");
        translationSuccessfullyLoaded = translator.load(QLocale(), QStringLiteral("ksnip"), QStringLiteral("_"), appDirPath + pathToTranslations);
    }

    if (translationSuccessfullyLoaded) {
        app.installTranslator(&translator);
    }

    auto imageGrabber = ImageGrabberFactory::createImageGrabber();

    // Setup command line parser
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::translate("main", "Ksnip Screenshot Tool"));
    parser.addHelpOption();
    parser.addVersionOption();
    CommandLineParserHelper::addImageGrabberOptions(parser, imageGrabber->supportedCaptureModes());
    CommandLineParserHelper::addDefaultOptions(parser);
    parser.process(app);

    auto arguments = QCoreApplication::arguments();
    MainWindow* window;

    // If there are no options except the the ksnip executable name, just run the application
    if (arguments.count() <= 1) {
        window = new MainWindow(imageGrabber, RunMode::GUI);
        return app.exec();
    }

    if (parser.isSet(QStringLiteral("e"))) {
        auto pathToImage = parser.value(QStringLiteral("e"));
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
    if (parser.isSet(QStringLiteral("d"))) {
        auto delayValid = true;
        delay = parser.value(QStringLiteral("d")).toInt(&delayValid);
        if (!delay) {
            qWarning("Please enter delay in seconds.");
            return 1;
        }
    }

    // Check if the user wants the mouse cursor to be included
    auto captureCursor = parser.isSet("c");

    CaptureModes mode;
    if (CommandLineParserHelper::isSet(parser, QStringLiteral("r"))) {
        mode = CaptureModes::RectArea;
    } else if (CommandLineParserHelper::isSet(parser, QStringLiteral("f"))) {
        mode = CaptureModes::FullScreen;
    } else if (CommandLineParserHelper::isSet(parser, QStringLiteral("m"))) {
        mode = CaptureModes::CurrentScreen;
    } else if (CommandLineParserHelper::isSet(parser, QStringLiteral("a"))) {
        mode = CaptureModes::ActiveWindow;
    } else if (CommandLineParserHelper::isSet(parser, QStringLiteral("u"))) {
        mode = CaptureModes::WindowUnderCursor;
    } else {
        qWarning("Please select capture mode.");
        return 1;
    }

    if (parser.isSet(QStringLiteral("s"))) {
        window = new MainWindow(imageGrabber, RunMode::CLI);
    } else {
        window = new MainWindow(imageGrabber, RunMode::Edit);
    }

    window->captureScreenshot(mode, captureCursor, delay * 1000);
    return app.exec();
}
