#include <QApplication>
#include "layerwindow.h"

#include "maiaObject.h"
#include "server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    layerWindow w;
    w.show();
    Server x;

    return a.exec();
}
