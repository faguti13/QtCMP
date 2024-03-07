#include "mainwindow.h"
#include "principallist.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    principalLIst listaPrincipal; // llama al constructor principalLIst
    w.show();
    return a.exec();
}
