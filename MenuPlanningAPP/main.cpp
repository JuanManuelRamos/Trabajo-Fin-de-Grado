#include "mainwindowmenuplan.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    srand (time(NULL));
    QApplication a(argc, argv);
    MainWindowMenuPlan w;
    w.show();

    return a.exec();
}
