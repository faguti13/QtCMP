#ifndef PRINCIPALLIST_H
#define PRINCIPALLIST_H
#include "doublylinkedlist.h"
#include <string>


// Declaración de la clase principalList
class principalList {
public:
    //principalList(); // Constructor
    principalList(doublyLinkedList&);

    // Métodos para listar archivos y cargar metadatos
    void listFilesInFolder(const std::string& folderPath, doublyLinkedList&);
    void loadAndPrintMetadata(const std::string& filePath, doublyLinkedList&);
};

//Métodos
void listFilesInFolder(const std::string& folderPath);
void loadAndPrintMetadata(const std::string& filePath);

#endif // PRINCIPALLIST_H

