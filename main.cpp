#include "mainwindow.h"
#include <QApplication>
#include "pagedarray.h"
#include "Node.h"
#include <iostream>
#include "principallist.h"
#include "doublylinkedlist.h"
#include "circularlist.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
