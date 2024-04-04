#include "principallist.h"
#include "doublylinkedlist.h"

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


//principalList::principalList() { // Constructor de principalList
principalList::principalList(doublyLinkedList& listInstance){

    //Abre el .ini para obtener la ruta de la carpeta
    try {
        pt::ptree tree;
        pt::ini_parser::read_ini("/home/joaquin/QtCMP/config.ini", tree); // CAMBIAR POR RUTA RELATIVA

        // Accede al path establecido en el archivo .ini
        std::string folderPath = tree.get<std::string>("music.musicFolderPath");
        //std::cout << "Dirección folder de música: " << folderPath << std::endl;

        // Llama al método que detecta la cantidad de archivos en la carpeta
        listFilesInFolder(folderPath, listInstance);

    } catch(const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

void principalList::listFilesInFolder(const std::string& folderPath, doublyLinkedList& listInstance) {
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        std::string filePathArchive = entry.path();

        // Verificar que el archivo tenga la extensión ".mp3" antes de procesarlo
        if (fs::is_regular_file(entry) && filePathArchive.substr(filePathArchive.find_last_of(".") + 1) == "mp3") {
            loadAndPrintMetadata(filePathArchive, listInstance);
        }
    }
}

void principalList::loadAndPrintMetadata(const std::string& filePath, doublyLinkedList& listInstance) { // Método para cargar y mostrar los metadatos de un .mp3
    // Cargar el archivo MP3, con MPEG::File el archivo está preparado para lectura de los metadatos
    MPEG::File file(filePath.c_str());

    // Obtener el puntero a Tag (donde están los metadatos)
    //(ID3 es un contenedor de metadatos)
    Tag *tag = file.ID3v2Tag();

    // Acceder a los tags
    if (tag) {

        // Inserta los metadatos en un nodo de la lista
        listInstance.insertEnd(tag->title().toCString(true), tag->artist().toCString(true), tag->album().toCString(true),
                                       tag->genre().toCString(true), filePath, 0, 0);

    } else {
        cout << "No se encontraron metadatos en el archivo." << endl;
    }}
