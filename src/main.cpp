#include <QtGui/QApplication>

#include "gui/MainWindow.h"
#include "src/backend/CmdParser.h"
#include "src/backend/ImageGrabber.h"

void printHelp();

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    // Setup application properties
    app.setOrganizationName("ksnip");
    app.setOrganizationDomain("ksnip.local");
    app.setApplicationName("ksnip");
    app.setApplicationVersion("v1.3.2");

    CmdParser parser;
    // Add command line options
    parser.addOption("h", "Displays this help", "help");
    parser.addOption("v", "Displays version information", "version");
    parser.addOption("f", "Capture the fullscreen including all monitors", "fullscreen");
    parser.addOption("m", "Capture the screen where the mouse is currently located.", "current");
    parser.addOption("a", "Capture the window that currently has focus", "activewindow");
    parser.addOption("d", "Delay before taking the screenshot, in seconds. "
                     "Only used with capture", "delay");

    MainWindow window;
    QStringList arguments = QCoreApplication::arguments();

    // If there are no options except the the ksnip executable name, just run the application
    if (arguments.count() <= 1) {
        window.show();
        return app.exec();
    }

    // We have some option, check what we have got.
    if (parser.parse(arguments)) {
        if (parser.isSet("h")) {
            parser.showHelp();
        } else if (parser.isSet("v")) {
            parser.showVersion();
        } else if (parser.isSet("f")) {
            window.instantCapture(ImageGrabber::FullScreen,
                                  parser.value("d").toInt());
        } else if (parser.isSet("a")) {
            window.instantCapture(ImageGrabber::ActiveWindow,
                                  parser.value("d").toInt());
        } else if (parser.isSet("m")) {
            window.instantCapture(ImageGrabber::CurrentScreen,
                                  parser.value("d").toInt());
        } else if (parser.isSet("d") &&
                   !parser.isSet("f") &&
                   !parser.isSet("a") &&
                   !parser.isSet("n")) {
            std::cout << "Delay set but no capture mode selected.\n";
            parser.showHelp();
        } else {
            window.show();
            return app.exec();
        }
    } else {
        // There was an error while parsing and the parse function returned false.
        return 0;
    }
}
