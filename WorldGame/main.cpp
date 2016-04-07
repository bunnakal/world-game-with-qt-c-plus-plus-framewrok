#include "worldgame.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WorldGame w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();

    return a.exec();
}
