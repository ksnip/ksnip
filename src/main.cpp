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

#include "gui/MainWindow.h"
#include "src/backend/ImageGrabber.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

    // Setup application properties
    app.setOrganizationName("ksnip");
    app.setOrganizationDomain("ksnip.local");
    app.setApplicationName("ksnip");
    app.setApplicationVersion("v1.4.0");

    // Setup command line parser
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::translate("main", "Ksnip Screenshot Tool"));
    parser.addHelpOption();
    parser.addVersionOption();

    // Add custom options
    parser.addOptions({
        {   {"r", "rectarea"},
            QCoreApplication::translate("main", "Select a rectangular area from where to take a screenshot.")
        },
        {   {"f", "fullscreen"},
            QCoreApplication::translate("main", "Capture the fullscreen including all monitors.")
        },
        {   {"m", "current"},
            QCoreApplication::translate("main", "Capture the screen (monitor) where the mouse cursor is currently located.")
        },
        {   {"a", "active"},
            QCoreApplication::translate("main", "Capture the window that currently has input focus.")
        },
        {   {"d", "delay"},
            QCoreApplication::translate("main", "Delay before taking the screenshot."),
            QCoreApplication::translate("main", "seconds")
        },
        {   {"c", "cursor"},
            QCoreApplication::translate("main", "Capture mouse cursor on screenshot."),
        },
    });
    parser.process(app);

    auto arguments = QCoreApplication::arguments();
    MainWindow* window;

    // If there are no options except the the ksnip executable name, just run
    // the application
    if (arguments.count() <= 1) {
        window = new MainWindow(MainWindow::GUI);
        return app.exec();
    }
    // If we have reached this point, we are running CLI mode
    window = new MainWindow(MainWindow::CLI);

    // Check if delay was selected, if yes, make sure a valid number was provided
    int delay = 0;
    if (parser.isSet("d")) {
        bool delayValid = true;
        delay = parser.value("d").toInt(&delayValid);
        if (!delay) {
            qWarning("Please enter delay in seconds.");
            return 1;
        }
    }

    // Check if the user wants the mouse cursor to be included
    bool cursor = parser.isSet("c");
    ImageGrabber::CaptureMode mode;

    if (parser.isSet("r")) {
        mode = ImageGrabber::RectArea;
    } else if (parser.isSet("f")) {
        mode = ImageGrabber::FullScreen;
    } else if (parser.isSet("m")) {
        mode = ImageGrabber::CurrentScreen;
    } else if (parser.isSet("a")) {
        mode = ImageGrabber::ActiveWindow;
    } else {
        qWarning("Please select capture mode.");
        return 1;
    }

    window->instantCapture(mode, cursor, delay * 1000);
    return app.exec();
}
