#include <QApplication>
#include "Node.h"
#include "circularlist.h"
#include "doublylinkedlist.h"
#include "mainwindow.h"
#include "pagedarray.h"
#include "principallist.h"
#include "serverconnection.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
