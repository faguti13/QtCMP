#ifndef PAGEDARRAY_H
#define PAGEDARRAY_H

#include "Node.h"
#include "doublylinkedlist.h"
#include <iostream>

class pagedArray {
public:
    pagedArray();

    static void toBinary(const pagedArray& pagArrayInstance, const char* folderPath, Node* headPtr, int allowedNodesForPage);
    void leerArchivoBinario(const std::string& nombreArchivo, const int numNodes) const;
    void writeFixedString(std::ofstream& file, const std::string& str, size_t size) const;
    void writeFixedInt(std::ofstream& file, int value) const;
    std::string readTitle(const std::string& nombreArchivo, const int numNode) const;
    std::string readArtist(const std::string& nombreArchivo, const int numNode) const;
    std::string readAlbum(const std::string& nombreArchivo, const int numNode) const;
    std::string readGenre(const std::string& nombreArchivo, const int numNode) const;
    std::string readReference(const std::string& nombreArchivo, const int numNode) const;
    int readUpVotes(const std::string& nombreArchivo, const int numNode) const;
    int readDownVotes(const std::string& nombreArchivo, const int numNode) const;

};

#endif
