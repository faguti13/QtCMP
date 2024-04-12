#include "circularlist.h"
#include "doublylinkedlist.h"
#include "Node.h"
#include <string>
#include <iostream>
#include <unordered_set>

circularList::circularList() {}

// Método para verificar si un artista ya está en la lista circular
bool circularList::containsArtist(const std::string& artist) {
    return artistMap.find(artist) != artistMap.end();
}

// Método para crear una nueva lista circular para un artista
void circularList::createArtistList(const std::string& artist) {
    artistMap[artist] = nullptr; // Inicializa la lista circular como vacía
}

// Método para agregar un nombre de nodo a la lista circular de un artista específico
void circularList::addToArtistList(const std::string& artist, int index) {
    NodeC* newNode = new NodeC(index); // Crea un nuevo nodo con el nombre del nodo original
    if (artistMap[artist] == nullptr) {
        // Si la lista circular para este artista está vacía, establece el nuevo nodo como el primero
        newNode->nextC = newNode; // El nuevo nodo apunta a sí mismo (circular)
        artistMap[artist] = newNode;
    } else {
        // Si la lista circular ya contiene nodos, insertar el nuevo nodo al final
        NodeC* lastNode = artistMap[artist];
        while (lastNode->nextC != artistMap[artist]) {
            lastNode = lastNode->nextC;
        }
        lastNode->nextC = newNode;
        newNode->nextC = artistMap[artist];
    }
}

// Método para recorrer la lista y encontrar los diferentes artistas
void circularList::findArtists(circularList& artistLists, Node* headPtr) {
    int index = 1;
    Node* current = headPtr;
    while (current != nullptr) {
        // Verificar si el artista ya está en la lista circular
        if (!artistLists.containsArtist(current->artist)) {
            // Si el artista no está en la lista, crear una nueva lista circular para él
            artistLists.createArtistList(current->artist);
        }
        // Agregar el nombre del nodo original a la lista circular correspondiente
        artistLists.addToArtistList(current->artist,index);

        current = current->next;
        index ++;
    }
}

// Método para imprimir el contenido de todas las listas circulares (para verificar)
void circularList::printCircularLists(const circularList& artistLists) {
    for (const auto& pair : artistLists.artistMap) {
        std::cout << "Artista: " << pair.first << std::endl;
        std::cout << "Posiciones de Canciones en la lista:" << std::endl;

        NodeC* current = pair.second;
        if (current) {
            do {
                std::cout << "\t" << " (" << current->index << ") " << std::endl;
                current = current->nextC;

            } while (current != pair.second);
        } else {
            std::cout << "\tNo hay canciones para este artista." << std::endl;
        }

        std::cout << std::endl;
    }
}

// Método para retornar solo los nombres de los artistas encontrados
std::unordered_set<std::string> circularList::getUniqueArtists(Node* headPtr) {
    std::unordered_set<std::string> uniqueArtists; // Conjunto para almacenar artistas únicos

    Node* current = headPtr;
    while (current != nullptr) {
        // Inserta el artista en el conjunto si no está repetido
        uniqueArtists.insert(current->artist); // 'std::unordered_set' garantiza que no se agreguen elementos duplicados
        current = current->next;
    }

    return uniqueArtists;
}

// Método para imprimir el contenido de una lista circular específica
void circularList::printCircularList(const std::string& artistName, const circularList& artistLists) const {
    auto it = artistLists.artistMap.find(artistName);
    if (it != artistLists.artistMap.end()) {
        //std::cout << "Artista: " << artistName << std::endl;
        //std::cout << "Posiciones de Canciones en la lista:" << std::endl;

        NodeC* current = it->second;
        if (current) {
            do {
                std::cout << "\t" << " (" << current->index << ") " << std::endl;
                current = current->nextC;
            } while (current != it->second);
        } else {
            std::cout << "\tNo hay canciones para este artista." << std::endl;
        }

        std::cout << std::endl;
    } else {
        std::cout << "No se encontró ninguna lista circular para el artista: " << artistName << std::endl;
    }
}

// Método para retornar los indices guardados en una lista circular específica
std::vector<int> circularList::getSongIndices(const std::string& artistName, const circularList& artistLists) const {
    std::vector<int> indices;
    auto it = artistLists.artistMap.find(artistName);
    if (it != artistLists.artistMap.end()) {
        NodeC* current = it->second;
        if (current) {
            do {
                indices.push_back(current->index);
                current = current->nextC;
            } while (current != it->second && current->index != it->second->index);
        }
    }
    return indices;
}

