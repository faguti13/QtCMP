#include "mainwindow.h"
#include "principallist.h"
#include <QApplication>
#include "pagedarray.h"
#include "Node.h"
#include <iostream>
#include "principallist.h"

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;   
    w.show();
/*

    principalLIst listaPrincipal; // llama al constructor principalLIst

    const int arraySize = 50;  // Tamaño del array principal
    Node** nodeArray = listaPrincipal.getArrayList();  // Obtén el array de nodos

    // Ruta del archivo de swap
    std::string swapFilePath = "/home/fabiangj/QtCMP/swap/swap.bin"; // Ajusta la ruta según tus necesidades

    // Tamaño de página y máximo de nodos en el PagedArray
    int pageSize = 4096;  // Ajusta el tamaño de la página según tus necesidades
    int maxNodes = 50;    // Máximo número de nodos en el PagedArray

    // Crea el PagedArray con la ruta del archivo de swap
    PagedArray pagedArray(pageSize, maxNodes, swapFilePath);

    // Itera sobre el array de nodos y agrégales al PagedArray
    for (int i = 0; i < arraySize; ++i) {
        Node* currentNode = nodeArray[i];
        pagedArray.add(*currentNode);
    }

    // Ahora, el contenido del array se ha paginado al archivo de swap

    // Realiza algunas operaciones sobre el PagedArray (agregar, eliminar, acceder, etc.)
    Node* newNode = new Node(/* ... *);
    pagedArray.add(*newNode);  // Desreferenciar el puntero y pasar el objeto Node por referencia constante

    // Accede a un nodo específico por índice
    int indexToAccess = 10;
    Node accessedNode = pagedArray.getByIndex(indexToAccess);

    // Elimina un nodo específico por índice
    int indexToRemove = 5;
    pagedArray.remove(indexToRemove);
*/
    return a.exec();
}
