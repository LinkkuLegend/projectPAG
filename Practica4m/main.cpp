
#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication aplicacion(argc, argv);

    MainWindow* _mainWindow = new MainWindow();
    _mainWindow->show();

    return aplicacion.exec();
}

