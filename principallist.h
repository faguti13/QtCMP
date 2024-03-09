#ifndef PRINCIPALLIST_H
#define PRINCIPALLIST_H
#include <string>
#include "Node.h"

class principalLIst
{
public:
    principalLIst();
    Node** getArrayList();
};

//Métodos
void listFilesInFolder(const std::string& folderPath);
void loadAndPrintMetadata(const std::string& filePath);

#endif // PRINCIPALLIST_H

