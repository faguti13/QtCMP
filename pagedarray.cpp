#include "pagedarray.h"
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
}
