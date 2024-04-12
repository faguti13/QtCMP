<<<<<<< HEAD
/*#include "pagedarray.h"
#include "Node.h"
#include <iostream>
#include <fstream>

PagedArray::PagedArray(int pageSize, int maxNodes, const std::string& swapFilePath)
    : pageSize(pageSize), maxNodes(maxNodes), bytesPerNode(sizeof(Node)), swapFilePath(swapFilePath) {
    int nodesPerPage = pageSize / bytesPerNode;
    if (nodesPerPage <= 0) {
        std::cerr << "Tamaño de página insuficiente para un nodo." << std::endl;
    }

    array = new Node[maxNodes];
    usedNodesCount = 0;

    // Reemplaza 'arraySize' con 'maxNodes' y 'mainArray' con 'array'
    for (int i = 0; i < maxNodes; ++i) {
        writeToSwap(array[i], i);
    }
}


PagedArray::~PagedArray() {
    delete[] array;
}

void PagedArray::add(const Node& newNode) {
    int index = search(newNode);

    if (index != -1) {
        std::cout << "El nodo ya está en la lista." << std::endl;
        return;
    }

    if (usedNodesCount >= maxNodes) {
        if (!swapFilePath.empty()) {
            // Realiza el swap con el archivo de swap
            writeToSwap(array[0], 0);  // Guarda el primer nodo en el archivo de swap
            readFromSwap(array[0], usedNodesCount);  // Lee el nuevo nodo desde el archivo de swap
        } else {
            // Implementa tu lógica de reemplazo LRU aquí si no hay archivo de swap
        }
    } else {
        // Resto de la lógica si no se alcanza el límite de nodos
    }

    array[usedNodesCount] = newNode;
    usedNodesCount++;
}

void PagedArray::remove(int index) {
    if (index < 0 || index >= usedNodesCount) {
        std::cerr << "Índice fuera de rango." << std::endl;
        return;
    }

    for (int i = index; i < usedNodesCount - 1; ++i) {
        array[i] = array[i + 1];
    }

    usedNodesCount--;
}

int PagedArray::search(const Node& targetNode) {
    for (int i = 0; i < usedNodesCount; ++i) {
        if (array[i] == targetNode) {
            return i;
        }
    }

    return -1;
}

Node PagedArray::getByIndex(int index) {
    if (index < 0 || index >= usedNodesCount) {
        std::cerr << "Índice fuera de rango." << std::endl;
        return Node{};
    }

    return array[index];
}

void PagedArray::writeToSwap(const Node& node, std::streampos position) {
    std::ofstream swapFile(swapFilePath, std::ios::binary | std::ios::in | std::ios::out);
    if (!swapFile.is_open()) {
        std::cerr << "Error al abrir el archivo de swap." << std::endl;
        return;
    }

    swapFile.seekp(position * bytesPerNode);
    swapFile.write(reinterpret_cast<const char*>(&node), bytesPerNode);
}

void PagedArray::readFromSwap(Node& node, std::streampos position) {
    std::ifstream swapFile(swapFilePath, std::ios::binary);
    if (!swapFile.is_open()) {
        std::cerr << "Error al abrir el archivo de swap." << std::endl;
        return;
    }

    swapFile.seekg(position * bytesPerNode);
    swapFile.read(reinterpret_cast<char*>(&node), bytesPerNode);
}*/


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "pagedarray.h"
#include "doublylinkedlist.h"
#include <vector>
#include <sstream>


using namespace std;


pagedArray::pagedArray() {}

/*
void pagedArray::toBinary(const pagedArray& pagArrayInstance, const char* folderPath, Node* headPtr, int allowedNodesForPage) {
    int i = 0;
    int page = 1;


    Node* temp = headPtr;
    ofstream binaryFile; // Declare binaryFile outside the loop
    string nombreArchivo;

    while (temp != nullptr) {

        if (i == 0) {
            // Close previous file before opening a new one
            if (binaryFile.is_open()) {
                binaryFile.close();
            }

            nombreArchivo = string(folderPath) + "/page" + to_string(page++) + ".bin";
            cout << "Creando archivo: " << nombreArchivo << endl;
            binaryFile.open(nombreArchivo, ios::binary | ios::out);
            if (!binaryFile.is_open()) { // Check if the file is successfully opened
                cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
                return;
            }
        }

        // Write data to the file
        cout << "Escribiendo datos en el archivo..." << endl;
        binaryFile.write(temp->title.c_str(), 110);
        binaryFile.write(temp->artist.c_str(), 50);
        binaryFile.write(temp->album.c_str(), 110);
        binaryFile.write(temp->genre.c_str(), 50);
        binaryFile.write(temp->reference.c_str(), 150);
        binaryFile.write(reinterpret_cast<char*>(&temp->upVotes), sizeof(int));
        binaryFile.write(reinterpret_cast<char*>(&temp->downVotes), sizeof(int));

        temp = temp->next;
        i++;

        // Close the file if either it's the last node for the page or if it's the end of the list
        if (i == allowedNodesForPage || temp == nullptr) {
            i = 0;
            binaryFile.close();
            cout << "apartir de aca lee" << endl;
            pagArrayInstance.leerArchivoBinario(nombreArchivo);
            cout << "Después de leer" << endl;
        }
    }
}


*/


/*void pagedArray::leerArchivoBinario(const std::string& nombreArchivo) const {
    std::ifstream binaryFile(nombreArchivo, std::ios::binary);

    if (!binaryFile) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return;
    }

    // Obtener el tamaño del archivo
    binaryFile.seekg(0, std::ios::end);
    std::streampos fileSize = binaryFile.tellg();
    binaryFile.seekg(0, std::ios::beg);

    if (fileSize == 0) {
        std::cerr << "El archivo está vacío" << std::endl;
        binaryFile.close();
        return;
    }

    std::cout << "Tamaño del archivo: " << fileSize << " bytes" << std::endl;

    // Leer el contenido del archivo en un vector de bytes
    std::vector<char> buffer(fileSize);
    binaryFile.read(buffer.data(), fileSize);

    // Mostrar los datos leídos en la consola
    for (char byte : buffer) {
        std::cout << byte;
    }

    // Verificar si hubo errores durante la lectura
    if (binaryFile.bad()) {
        std::cerr << "Error al leer el archivo" << std::endl;
    }

    binaryFile.close();
}*/

void pagedArray::toBinary(const pagedArray& pagArrayInstance, const char* folderPath, Node* headPtr, int allowedNodesForPage) {
    int i = 0;
    int page = 1;


    Node* temp = headPtr;
    ofstream binaryFile;
    string nombreArchivo;

    while (temp != nullptr) {

        if (i == 0) {
            if (binaryFile.is_open()) { // Cierra el anterior en caso de que estuviera abierto
                binaryFile.close();
            }

            nombreArchivo = string(folderPath) + "/page" + to_string(page++) + ".bin";
            //cout << "Creando archivo: " << nombreArchivo << endl;
            binaryFile.open(nombreArchivo, ios::binary | ios::out);
            if (!binaryFile.is_open()) { // Para verificar que abrió bien
                cerr << "No se pudo abrir el archivo " << nombreArchivo << endl;
                return;
            }
        }

        pagArrayInstance.writeFixedString(binaryFile, temp->title, 110); // Con estas llamadas se escriben los datos los diferentes archivos
        pagArrayInstance.writeFixedString(binaryFile, temp->artist, 50);
        pagArrayInstance.writeFixedString(binaryFile, temp->album, 110);
        pagArrayInstance.writeFixedString(binaryFile, temp->genre, 50);
        pagArrayInstance.writeFixedString(binaryFile, temp->reference, 150);
        pagArrayInstance.writeFixedInt(binaryFile, temp->upVotes);
        pagArrayInstance.writeFixedInt(binaryFile, temp->downVotes);

        temp = temp->next;
        i++;

        // Cierra el archivo si ya se llego al final de la lista doble o si ya se guardaron los nodos especificados
        if (i == allowedNodesForPage || temp == nullptr) {
            i = 0;
            binaryFile.close();
            //cout << "apartir de aca lee" << endl;
            //pagArrayInstance.leerArchivoBinario(nombreArchivo,allowedNodesForPage);
            //cout << "Después de leer" << endl;
        }
    }
}

// Método para imprimir lo que se guardó en un .bin
void pagedArray::leerArchivoBinario(const std::string& nombreArchivo, const int numNodes) const {
    std::ifstream binaryFile(nombreArchivo, std::ios::binary);

    int i ;
    if (!binaryFile) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return;
    }

    // Tamaño de los bloques de datos
    const size_t TITLE_SIZE = 110;
    const size_t ARTIST_SIZE = 50;
    const size_t ALBUM_SIZE = 110;
    const size_t GENRE_SIZE = 50;
    const size_t REFERENCE_SIZE = 150;
    const size_t INT_SIZE = 4;

    char buffer[REFERENCE_SIZE]; // Buffer para las cadenas de texto
    char intBuffer[INT_SIZE]; // Buffer para leer enteros

    std::cout << "archivo .bin en el que se está escribiendo: " << nombreArchivo << std::endl;

    for (i = 0; i < numNodes; ++i) { // Para imprimirlos todos

        // Leer y mostrar el título
        binaryFile.read(buffer, TITLE_SIZE);
        if (binaryFile.gcount() == 0) break;
        std::cout << "Title: ";
        std::cout.write(buffer, strlen(buffer));
        std::cout << std::endl;

        // Leer y mostrar el artista
        binaryFile.read(buffer, ARTIST_SIZE);
        std::cout << "Artist: ";
        std::cout.write(buffer, strlen(buffer));
        std::cout << std::endl;


        // Leer y mostrar el álbum
        binaryFile.read(buffer, ALBUM_SIZE);
        std::cout << "Album: ";
        std::cout.write(buffer, strlen(buffer)); // El "strlen(buffer)" devuelve solo los caracteres no nulos de lo que está en buffer
        std::cout << std::endl;

        // Leer y mostrar el género
        binaryFile.read(buffer, GENRE_SIZE);
        std::cout << "Genre: ";
        std::cout.write(buffer, strlen(buffer));
        std::cout << std::endl;

        // Leer y mostrar la referencia
        binaryFile.read(buffer, REFERENCE_SIZE);
        std::cout << "Reference: ";
        //std::cout.write(buffer.data(), str.size());
        std::cout.write(buffer, strlen(buffer));
        //std::cout.write(buffer, REFERENCE_SIZE);
        std::cout << std::endl;

        // Leer y mostrar los upvotes
        binaryFile.read(intBuffer, INT_SIZE);
        int upVotes = *reinterpret_cast<int*>(intBuffer);
        std::cout << "Up Votes: " << upVotes << std::endl;

        // Leer y mostrar los downvotes
        binaryFile.read(intBuffer, INT_SIZE);
        int downVotes = *reinterpret_cast<int*>(intBuffer);
        std::cout << "Down Votes: " << downVotes << std::endl;
    }

    if (binaryFile.bad()) { // Verificar si hubo errores durante la lectura
        std::cerr << "Error al leer el archivo en el método leerArchivoBinario" << std::endl;
    }

    binaryFile.close();
}


// Método para escribir una cadena con un tamaño fijo en el archivo binario
void pagedArray::writeFixedString(std::ofstream& file, const std::string& str, size_t size) const{
    std::string temp = str;
    temp.resize(size, '\0'); // Acá ellena con caracteres nulos si es necesario
    file.write(temp.c_str(), size); // Escribe la cadena en el archivo
}

// Método para escribir un entero con un tamaño fijo en el archivo binario
void pagedArray::writeFixedInt(std::ofstream& file, int value) const{
    file.write(reinterpret_cast<const char*>(&value), sizeof(int)); // Escribir el entero en el archivo
}


// Método para retornar el titulo de la cancion según el "nodo" requerido
std::string pagedArray::readTitle(const std::string& nombreArchivo, const int numNode) const {
    std::ifstream binaryFile(nombreArchivo, std::ios::binary);

    if (!binaryFile) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return "";
    }

    char buffer[110]; // Buffer para las cadenas de texto
    int startPosition = 478 * numNode;

    binaryFile.seekg(startPosition); // Mueve el puntero de lectura del archivo a la posición adecuada

    binaryFile.read(buffer, 110); // Lee en el .bin

    if (binaryFile.gcount() == 0) {
        std::cerr << "Fin del archivo o error de lectura" << std::endl;
        binaryFile.close(); // Cierra el archivo antes de devolver
        return ""; // Devolver una cadena vacía en caso de error o fin del archivo
    }

    std::string title(buffer, strlen(buffer)); // Obtener el título como una cadena de caracteres

    binaryFile.close();
    return title;
}

// Método para retornar el artista de la cancion según el "nodo" requerido
std::string pagedArray::readArtist(const std::string& nombreArchivo, const int numNode) const {
    std::ifstream binaryFile(nombreArchivo, std::ios::binary);

    if (!binaryFile) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return "";
    }

    char buffer[50]; // Buffer para las cadenas de texto
    int startPosition = 478 * numNode + 110;

    binaryFile.seekg(startPosition); // Mueve el puntero de lectura del archivo a la posición adecuada

    binaryFile.read(buffer, 50); // Lee en el .bin

    if (binaryFile.gcount() == 0) {
        std::cerr << "Fin del archivo o error de lectura" << std::endl;
        binaryFile.close(); // Cierra el archivo antes de devolver
        return ""; // Devolver una cadena vacía en caso de error o fin del archivo
    }

    std::string artist(buffer, strlen(buffer)); // Obtener el título como una cadena de caracteres

    binaryFile.close();
    return artist;
}

// Método para retornar el album de la cancion según el "nodo" requerido
std::string pagedArray::readAlbum(const std::string& nombreArchivo, const int numNode) const {
    std::ifstream binaryFile(nombreArchivo, std::ios::binary);

    if (!binaryFile) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return "";
    }

    char buffer[110]; // Buffer para las cadenas de texto
    int startPosition = 478 * numNode + 160;

    binaryFile.seekg(startPosition); // Mueve el puntero de lectura del archivo a la posición adecuada

    binaryFile.read(buffer, 110); // Lee en el .bin

    if (binaryFile.gcount() == 0) {
        std::cerr << "Fin del archivo o error de lectura" << std::endl;
        binaryFile.close(); // Cierra el archivo antes de devolver
        return ""; // Devolver una cadena vacía en caso de error o fin del archivo
    }

    std::string album(buffer, strlen(buffer)); // Obtener el título como una cadena de caracteres

    binaryFile.close();
    return album;
}

// Método para retornar el género de la cancion según el "nodo" requerido
std::string pagedArray::readGenre(const std::string& nombreArchivo, const int numNode) const {
    std::ifstream binaryFile(nombreArchivo, std::ios::binary);

    if (!binaryFile) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return "";
    }

    char buffer[50]; // Buffer para las cadenas de texto
    int startPosition = 478 * numNode + 270;

    binaryFile.seekg(startPosition); // Mueve el puntero de lectura del archivo a la posición adecuada

    binaryFile.read(buffer, 50); // Lee en el .bin

    if (binaryFile.gcount() == 0) {
        std::cerr << "Fin del archivo o error de lectura" << std::endl;
        binaryFile.close(); // Cierra el archivo antes de devolver
        return ""; // Devolver una cadena vacía en caso de error o fin del archivo
    }

    std::string genre(buffer, strlen(buffer)); // Obtener el título como una cadena de caracteres

    binaryFile.close();
    return genre;
}

// Método para retornar la referencia de la cancion según el "nodo" requerido
std::string pagedArray::readReference(const std::string& nombreArchivo, const int numNode) const {
    std::ifstream binaryFile(nombreArchivo, std::ios::binary);

    if (!binaryFile) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return "";
    }

    char buffer[150]; // Buffer para las cadenas de texto
    int startPosition = 478 * numNode + 320;

    binaryFile.seekg(startPosition); // Mueve el puntero de lectura del archivo a la posición adecuada

    binaryFile.read(buffer, 150); // Lee en el .bin

    if (binaryFile.gcount() == 0) {
        std::cerr << "Fin del archivo o error de lectura" << std::endl;
        binaryFile.close(); // Cierra el archivo antes de devolver
        return ""; // Devolver una cadena vacía en caso de error o fin del archivo
    }

    std::string reference(buffer, strlen(buffer)); // Obtener el título como una cadena de caracteres

    binaryFile.close();
    return reference;
}

// Método para retornar los upvotes de la cancion según el "nodo" requerido
int pagedArray::readUpVotes(const std::string& nombreArchivo, const int numNode) const {
    std::ifstream binaryFile(nombreArchivo, std::ios::binary);

    if (!binaryFile) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return -1; // Devolver un valor indicativo de error, por ejemplo -1
    }

    char buffer[4]; // Buffer para las cadenas de texto
    int startPosition = 478 * numNode + 470;

    binaryFile.seekg(startPosition); // Mueve el puntero de lectura del archivo a la posición adecuada

    binaryFile.read(buffer, 4); // Lee en el .bin

    if (binaryFile.gcount() == 0) {
        std::cerr << "Fin del archivo o error de lectura" << std::endl;
        binaryFile.close(); // Cierra el archivo antes de devolver
        return -1;
    }

    // Obtener el número de upvotes como un entero
    int upVotes;
    std::istringstream(buffer) >> upVotes;

    binaryFile.close();
    return upVotes;
}

// Método para retornar los downvotes de la cancion según el "nodo" requerido
int pagedArray::readDownVotes(const std::string& nombreArchivo, const int numNode) const {
    std::ifstream binaryFile(nombreArchivo, std::ios::binary);

    if (!binaryFile) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return -1; // Devolver un valor indicativo de error, por ejemplo -1
    }

    char buffer[4]; // Buffer para las cadenas de texto
    int startPosition = 478 * numNode + 474;

    binaryFile.seekg(startPosition); // Mueve el puntero de lectura del archivo a la posición adecuada

    binaryFile.read(buffer, 4); // Lee en el .bin

    if (binaryFile.gcount() == 0) {
        std::cerr << "Fin del archivo o error de lectura" << std::endl;
        binaryFile.close(); // Cierra el archivo antes de devolver
        return -1;
    }

    // Obtener el número de upvotes como un entero
    int downVotes;
    std::istringstream(buffer) >> downVotes;

    binaryFile.close();
    return downVotes;
}
=======
>>>>>>> refs/remotes/origin/master
