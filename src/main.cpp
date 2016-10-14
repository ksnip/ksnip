#include <QtGui/QApplication>

#include "gui/MainWindow.h"
#include <iostream>

int main( int argc, char **argv )
{
    QApplication app( argc, argv );
    
    // Setup application properties 
    app.setOrganizationName( "ksnip" );
    app.setOrganizationDomain( "ksnip.local" );
    app.setApplicationName( "ksnip" );
    app.setApplicationVersion("v1.1.0");
    
//     std::cout << "Your input: " << QCoreApplication::arguments().at(1).toStdString() << "\n";
    
    MainWindow window;
    window.show();
    return app.exec();
}