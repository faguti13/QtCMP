#include "principallist.h"
#include "Node.h"

#include <iostream>
#include <taglib/taglib.h> //Para los metadatos
#include <taglib/mpegfile.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>
#include <filesystem> // Para leer los archivos de la carpeta
#include <string>
#include <boost/property_tree/ptree.hpp> // Para leer el .ini
#include <boost/property_tree/ini_parser.hpp>
#include <QCoreApplication>
#include <unordered_set> // Para almacenar los diferentes artistas

namespace fs = std::filesystem;
namespace pt = boost::property_tree;
using namespace std;
using namespace TagLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Definición de la clase NodeC
class NodeC {
public:
    int index;
    NodeC* nextC;

    NodeC(int _index): index(_index), nextC(nullptr) {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Clase para la lista circular
class CircularList {
public:
    std::unordered_map<std::string, NodeC*> artistMap; // artistMap se usa como "contenedor" para almacenar las listas circulares de cada artista

    // Método para verificar si un artista ya está en la lista circular
    bool containsArtist(const std::string& artist) {
        return artistMap.find(artist) != artistMap.end();
    }

    // Método para crear una nueva lista circular para un artista
    void createArtistList(const std::string& artist) {
        artistMap[artist] = nullptr; // Inicializa la lista circular como vacía
    }

    // Método para agregar un nombre de nodo a la lista circular de un artista específico
    void addToArtistList(const std::string& artist, int index) {
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
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Clase lista doblemente enlazada
class DoublyLinkedList {
private:
    Node* head; //Punteros
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Método para insertar en la lista
    void insertEnd(const std::string& title, const std::string& artist, const std::string& album, const std::string& genre,
                         const std::string& reference, int upVotes, int downVotes) {
        Node* newNode = new Node(title, artist, album, genre,  reference, upVotes, downVotes);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Método para imprimir toda la info de los nodos (para verificar)
    void printForward() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << "Canción: " << current->title << " , " << current->artist << " , " << current->album
                      << " , " << current->genre<< " , " << current->reference
                      << " , " << current->upVotes << " , " << current->downVotes << std::endl;
            current = current->next;
        }
    }

    Node* getHead() const {
        return head;
    }

    // Método para recorrer la lista y encontrar los diferentes artistas
    void printArtists(CircularList& artistLists) {
        int index = 1;
        Node* current = head;
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
    void printCircularLists(const CircularList& artistLists) {
        for (const auto& pair : artistLists.artistMap) {
            std::cout << "Artista: " << pair.first << std::endl;
            std::cout << "Posiciones de Canciones:" << std::endl;

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

};

////////////////////////////////////////////////////////////////////////////////////////////

DoublyLinkedList principalLinkedList;
CircularList artistLists;

// Clase para la lista principal (inicio)
class principalList {
public:
    principalList(); // Declaración del constructor

        //void getArrayList(){}
};

principalLIst::principalLIst() { // Constructor de principalLIst
    //Abre el .ini para obtener la ruta de la carpeta
    try {
        pt::ptree tree;
        pt::ini_parser::read_ini("/home/asly/Desktop/QtCMP/config.ini", tree); // CAMBIAR POR RUTA RELATIVA

        // Accede al path establecido en el archivo .ini
        std::string folderPath = tree.get<std::string>("music.musicFolderPath");
        //std::cout << "Dirección folder de música: " << folderPath << std::endl;

        // Llama al método que detecta la cantidad de archivos en la carpeta
        listFilesInFolder(folderPath);

        //principalLinkedList.printForward();

    } catch(const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    //principalLinkedList.printArtists();
    principalLinkedList.printArtists(artistLists);
    principalLinkedList.printCircularLists(artistLists);
}

Node** principalLIst::getArrayList() {
    const int maxSongs = 50;
    Node** nodeArray = new Node*[maxSongs]; // Utiliza new para asignar memoria dinámica

    // Inicializar el array a nullptr para asegurarse de que los elementos no inicializados sean seguros de usar
    std::fill_n(nodeArray, maxSongs, nullptr);

    // Recorre la lista enlazada y agrega los nodos al array
    Node* current = principalLinkedList.getHead();
    int index = 0;
    while (current != nullptr && index < maxSongs) {
        nodeArray[index++] = current;
        current = current->next;
    }

    // Devuelve el array
    return nodeArray;
}


void listFilesInFolder(const std::string& folderPath) {
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        std::string filePathArchive = entry.path();

        // Verificar que el archivo tenga la extensión ".mp3" antes de procesarlo
        if (fs::is_regular_file(entry) && filePathArchive.substr(filePathArchive.find_last_of(".") + 1) == "mp3") {
            loadAndPrintMetadata(filePathArchive);
        }
    }
}

void loadAndPrintMetadata(const std::string& filePath) { // Método para cargar y mostrar los metadatos de un .mp3
    // Cargar el archivo MP3, con MPEG::File el archivo está preparado para lectura de los metadatos
    MPEG::File file(filePath.c_str());

    // Obtener el puntero a Tag (donde están los metadatos)
    //(ID3 es un contenedor de metadatos)
    Tag *tag = file.ID3v2Tag();

    // Acceder a los tags
    if (tag) {

        // Inserta los metadatos en un nodo de la lista
        principalLinkedList.insertEnd(tag->title().toCString(true), tag->artist().toCString(true), tag->album().toCString(true),
                                      tag->genre().toCString(true), filePath, 0, 0);

        //std::cout << "Nodos actuales en la lista:" << std::endl;
        //principalLinkedList.printForward();

    } else {
        cout << "No se encontraron metadatos en el archivo." << endl;
    }}


