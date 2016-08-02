#include <QtGui/QApplication>
#include "capturewindow.h"
#include "snippingarea.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    CaptureWindow window;
    
    window.show();
    return app.exec();
}
