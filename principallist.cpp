#include "principallist.h"

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

namespace fs = std::filesystem;
namespace pt = boost::property_tree;
using namespace std;
using namespace TagLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node { //Estructura del nodo (def el contenido de cada uno)
    std::string title;
    std::string artist;
    std::string album;
    std::string genre;
    std::string reference;
    int upVotes;
    int downVotes;

    Node* prev;
    Node* next;

    Node(const std::string& t, const std::string& a, const std::string& al, const std::string& g,const std::string& r, int uV, int dV)
        : title(t), artist(a), album(al), genre(g), reference(r), upVotes(uV), downVotes(dV), prev(nullptr), next(nullptr) {}
};

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
};

////////////////////////////////////////////////////////////////////////////////////////////

// Clase para la lista principal (inicio)
class principalList {
public:
    principalList(); // Declaración del constructor
};

principalLIst::principalLIst() { // Constructor de principalLIst
    //Abre el .ini para obtener la ruta de la carpeta
    try {
        pt::ptree tree;
        pt::ini_parser::read_ini("/home/asly/Downloads/QtCMP/config.ini", tree); // CAMBIAR POR RUTA RELATIVA

        // Accede al path establecido en el archivo .ini
        std::string folderPath = tree.get<std::string>("music.musicFolderPath");
        std::cout << "Dirección folder de música: " << folderPath << std::endl;

        // Llama al método que detecta la cantidad de archivos en la carpeta
        listFilesInFolder(folderPath);

    } catch(const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

DoublyLinkedList principalLinkedList;

void listFilesInFolder(const std::string& folderPath) { // Método para saber el path de cada .mp3
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        //std::cout << entry.path() << std::endl; //Comprobar que pase bien el path
        std::string filePathArchive = entry.path();
        loadAndPrintMetadata(filePathArchive); // Llama al método que carga y muestra los metadatos
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
        //cout << "Título: " << tag->title().toCString(true) << endl; // Prubas para verificar que obtenga los metadatos bien
        //cout << "Artista: " << tag->artist().toCString(true) << endl;
        //cout << "Álbum: " << tag->album().toCString(true) << endl;
        //cout << "Género: " << tag->genre().toCString(true) << endl;
        //cout << "Referencia: " << filePath << endl;

        // Inserta los metadatos en un nodo de la lista
        principalLinkedList.insertEnd(tag->title().toCString(true), tag->artist().toCString(true), tag->album().toCString(true),
                                      tag->genre().toCString(true), filePath, 0, 0);

        std::cout << "Nodos actuales en la lista:" << std::endl;
        principalLinkedList.printForward();

    } else {
        cout << "No se encontraron metadatos en el archivo." << endl;
    }}


