#include <QApplication>

#include "glframe.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    MainWindow window;
    window.show();

    return application.exec();
}
