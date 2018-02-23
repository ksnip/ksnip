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

#include <QApplication>
#include <QCommandLineParser>

#include "BuildConfig.h"
#include "gui/MainWindow.h"
#include "src/backend/imageGrabber/ImageGrabberFactory.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

    // Setup application properties
    app.setOrganizationName(QStringLiteral("ksnip"));
    app.setOrganizationDomain(QStringLiteral("ksnip.local"));
    app.setApplicationName(QStringLiteral("ksnip"));
    app.setApplicationVersion(QStringLiteral(KSNIP_VERSION));

    QTranslator translator;
    auto translationSuccessfullyLoaded = translator.load(QLocale(), QStringLiteral("ksnip"), QStringLiteral("_"), QStringLiteral(KSNIP_LANG_INSTAL_DIR));
    if (!translationSuccessfullyLoaded) {
        qCritical("found nothing at %s", KSNIP_LANG_INSTAL_DIR);
        qCritical("looking now at ../usr/share/ksnip/translations");
        translationSuccessfullyLoaded = translator.load(QLocale(), QStringLiteral("ksnip"), QStringLiteral("_"), QStringLiteral("../usr/share/ksnip/translations"));
    }

    if (translationSuccessfullyLoaded) {
        qCritical("found translation!");
        app.installTranslator(&translator);
    } else {
        qCritical("found not translation...");
    }


    ImageGrabberFactory imageGrabberFactory;
    auto imageGrabber = imageGrabberFactory.createImageGrabber();

    // Setup command line parser
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::translate("main", "Ksnip Screenshot Tool"));
    parser.addHelpOption();
    parser.addVersionOption();

    // Add image grabber specific options
    if (imageGrabber->isCaptureModeSupported(CaptureModes::RectArea)) {
        parser.addOption({{QStringLiteral("r"), QStringLiteral("rectarea")},
            QCoreApplication::translate("main", "Select a rectangular area from where to take a screenshot.")
        });
    }
    if (imageGrabber->isCaptureModeSupported(CaptureModes::FullScreen)) {
        parser.addOption({{QStringLiteral("f"), QStringLiteral("fullscreen")},
            QCoreApplication::translate("main", "Capture the fullscreen including all monitors.")
        });
    }
    if (imageGrabber->isCaptureModeSupported(CaptureModes::CurrentScreen)) {
        parser.addOption({{QStringLiteral("m"), QStringLiteral("current")},
            QCoreApplication::translate("main", "Capture the screen (monitor) where the mouse cursor is currently located.")
        });
    }
    if (imageGrabber->isCaptureModeSupported(CaptureModes::ActiveWindow)) {
        parser.addOption({{QStringLiteral("a"), QStringLiteral("active")},
            QCoreApplication::translate("main", "Capture the window that currently has input focus.")
        });
    }
    if (imageGrabber->isCaptureModeSupported(CaptureModes::WindowUnderCursor)) {
        parser.addOption({{QStringLiteral("u"), QStringLiteral("windowundercursor")},
            QCoreApplication::translate("main", "Capture the window that is currently under the mouse cursor.")
        });
    }

    // Add default options
    parser.addOptions({
        {{QStringLiteral("d"), QStringLiteral("delay")},
            QCoreApplication::translate("main", "Delay before taking the screenshot."),
            QCoreApplication::translate("main", "seconds")
        },
        {{QStringLiteral("c"), QStringLiteral("cursor")},
            QCoreApplication::translate("main", "Capture mouse cursor on screenshot."),
        },
        {{QStringLiteral("e"), QStringLiteral("edit")},
            QCoreApplication::translate("main", "Edit existing image in ksnip"),
            QCoreApplication::translate("main", "image")
        }
    });
    parser.process(app);

    auto arguments = QCoreApplication::arguments();
    MainWindow* window;

    // If there are no options except the the ksnip executable name, just run
    // the application
    if (arguments.count() <= 1) {
        window = new MainWindow(imageGrabber, MainWindow::GUI);
        return app.exec();
    }

    if (parser.isSet(QStringLiteral("e"))) {
        auto pathToImage = parser.value(QStringLiteral("e"));
        QPixmap pixmap(pathToImage);

        if (pixmap.isNull()) {
            qWarning("Unable to open image file %s.", qPrintable(pathToImage));
            return 1;
        }

        window = new MainWindow(imageGrabber, MainWindow::GUI);
        window->showCapture(pixmap);
        return app.exec();
    }

    // If we have reached this point, we are running CLI mode
    window = new MainWindow(imageGrabber, MainWindow::CLI);

    // Check if delay was selected, if yes, make sure a valid number was provided
    int delay = 0;
    if (parser.isSet(QStringLiteral("d"))) {
        bool delayValid = true;
        delay = parser.value(QStringLiteral("d")).toInt(&delayValid);
        if (!delay) {
            qWarning("Please enter delay in seconds.");
            return 1;
        }
    }

    // Check if the user wants the mouse cursor to be included
    bool cursor = parser.isSet("c");
    CaptureModes mode;

    if (parser.isSet(QStringLiteral("r"))) {
        mode = CaptureModes::RectArea;
    } else if (parser.isSet(QStringLiteral("f"))) {
        mode = CaptureModes::FullScreen;
    } else if (parser.isSet(QStringLiteral("m"))) {
        mode = CaptureModes::CurrentScreen;
    } else if (parser.isSet(QStringLiteral("a"))) {
        mode = CaptureModes::ActiveWindow;
    } else if (parser.isSet(QStringLiteral("u"))) {
        mode = CaptureModes::WindowUnderCursor;
    } else {
        qWarning("Please select capture mode.");
        return 1;
    }

    window->instantCapture(mode, cursor, delay * 1000);
    return app.exec();
}
