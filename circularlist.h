#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H
#include "doublylinkedlist.h"

#include <unordered_map>
#include <unordered_set>
#include <string>

// Definición de la clase NodeC
class NodeC {
public:
    int index;
    NodeC* nextC;

    NodeC(int _index): index(_index), nextC(nullptr) {}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Declaración de la clase circularList
class circularList
{

private:
    std::unordered_map<std::string, NodeC*> artistMap; // artistMap se usa como "contenedor" para almacenar las listas circulares de cada artista

public:
    circularList();

    //std::unordered_map<std::string, NodeC*> artistMap;
    //static std::unordered_map<std::string, NodeC*> artistMap; // "Contenedor" para almacenar listas circulares de artistas

    // Método para verificar si un artista ya está en la lista circular
    bool containsArtist(const std::string& artist);

    // Método para crear una nueva lista circular para un artista
    void createArtistList(const std::string& artist);

    // Método para agregar un nombre de nodo a la lista circular de un artista específico
    void addToArtistList(const std::string& artist, int index);

    // Método para recorrer la lista y encontrar los diferentes artistas
    void findArtists(circularList& artistLists, Node* headPtr);

    // Método para imprimir el contenido de todas las listas circulares (para verificar)
    void printCircularLists(const circularList& artistLists);

    // Método para retornar solo los nombres de los artistas encontrados
    std::unordered_set<std::string> getUniqueArtists(Node* headPtr);

    // Método para imprimir el contenido de una lista circular específica
    void printCircularList(const std::string& artistName, const circularList& artistLists) const;

    // Método para retornar los indices guardados en una lista circular específica
    std::vector<int> getSongIndices(const std::string& artistName, const circularList& artistLists) const;

};

#endif // CIRCULARLIST_H
