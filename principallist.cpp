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

void listFilesInFolder(const std::string& folderPath) { // Método para saber el path de cada .mp3
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        std::cout << entry.path() << std::endl;
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

    // Imprimir los metadatos en pantalla
    if (tag) {
        cout << "Título: " << tag->title().toCString(true) << endl;
        cout << "Artista: " << tag->artist().toCString(true) << endl;
        cout << "Álbum: " << tag->album().toCString(true) << endl;
        cout << "Año: " << tag->year() << endl;
        cout << "Género: " << tag->genre().toCString(true) << endl;

    } else {
        cout << "No se encontraron metadatos en el archivo." << endl;
    }
}

