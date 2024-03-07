#ifndef PRINCIPALLIST_H
#define PRINCIPALLIST_H
#include <string>

class principalLIst
{
public:
    principalLIst();
};

//Métodos
void listFilesInFolder(const std::string& folderPath);
void loadAndPrintMetadata(const std::string& filePath);

#endif // PRINCIPALLIST_H

