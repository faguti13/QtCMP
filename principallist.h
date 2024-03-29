#ifndef PRINCIPALLIST_H
#define PRINCIPALLIST_H
#include <string>
#include "Node.h"
#include <unordered_set>

class principalLIst
{
public:
    principalLIst();
    Node** getArrayList();
    std::unordered_set<std::string> getUniqueArtists();
};

//Métodos
void listFilesInFolder(const std::string& folderPath);
void loadAndPrintMetadata(const std::string& filePath);
void Prueba();

#endif // PRINCIPALLIST_H

