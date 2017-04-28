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

    // Setup application properties
    app.setOrganizationName("ksnip");
    app.setOrganizationDomain("ksnip.local");
    app.setApplicationName("ksnip");
    app.setApplicationVersion("v1.4.0-alpha");

    // Setup command line parser
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::translate("main", "Ksnip Screenshot Tool"));
    parser.addHelpOption();
    parser.addVersionOption();

    // Add custom options
    parser.addOptions({
        {   {"f", "fullscreen"},
            QCoreApplication::translate("main", "Capture the fullscreen including all monitors.")
        },
        {   {"m", "current"},
            QCoreApplication::translate("main", "Capture the screen (monitor) where the mouse is currently located. <Default option>")
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

    MainWindow window;
    auto arguments = QCoreApplication::arguments();

    // If there are no options except the the ksnip executable name, just run
    // the application
    if (arguments.count() <= 1) {
        window.show();
        return app.exec();
    }

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

    if (parser.isSet("f")) {
        mode = ImageGrabber::FullScreen;
    } else if (parser.isSet("a")) {
        mode = ImageGrabber::ActiveWindow;
    } else {
        // Default option is current screen
        mode = ImageGrabber::CurrentScreen;
    }

    window.instantCapture(mode, cursor, delay);
    return 0;
}
