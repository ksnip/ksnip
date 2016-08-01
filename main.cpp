#include <QtGui/QApplication>
#include "capturewindow.h"
#include "snippingframe.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    CaptureWindow window;
    
    window.show();
    return app.exec();
}
