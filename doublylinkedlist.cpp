#include "doublylinkedlist.h"
#include <iostream>
#include "Node.h"

// Constructor (head y tail inicializados a nullptr)
doublyLinkedList::doublyLinkedList() : head(nullptr), tail(nullptr) {}


// Método para insertar en la lista
void doublyLinkedList::insertEnd(const std::string& title, const std::string& artist, const std::string& album, const std::string& genre,
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
void doublyLinkedList::printForward() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << "Canción: " << current->title << " , " << current->artist << " , " << current->album
                  << " , " << current->genre<< " , " << current->reference
                   << " , " << current->upVotes << " , " << current->downVotes << std::endl;
        current = current->next;
    }
}

// Método para obtener el nodo inicial
Node* doublyLinkedList::getHead() const {
    return head;
}

// Método para obtener un puntero a la lista doblemente enlazada creada
doublyLinkedList* doublyLinkedList::getPointerToDoublyLinkedList(){
    return this;
}

// Método para acceder a los punteros a los nodos de la lista enlazada original.
Node** doublyLinkedList::getArrayList(Node* headPtr) {
    const int maxSongs = 50;
    Node** nodeArray = new Node*[maxSongs]; // Utiliza new para asignar memoria dinámica

    // Inicializar el array a nullptr para asegurarse de que los elementos no inicializados sean seguros de usar
    std::fill_n(nodeArray, maxSongs, nullptr);

    // Recorre la lista enlazada y agrega los nodos al array
    Node* current = headPtr;
    int index = 0;
    while (current != nullptr && index < maxSongs) {
        nodeArray[index++] = current;
        current = current->next;
    }

    // Devuelve el array
    return nodeArray;
}

// Método para obtener los punteros a los nodos de la lista enlazada en las posiciones dadas
std::vector<Node*> doublyLinkedList::getNodesAtIndices(const std::vector<int>& indices, const doublyLinkedList& principalLinkedList) const {
    std::vector<Node*> nodes;
    int i;
    for (int index : indices) {
        Node* current = head;
        if (index == 1) {
            nodes.push_back(current);
        }
        else{
            for (i = 1; i < index; ++i){
                current = current->next;}
            nodes.push_back(current);
        }
    }
    return nodes;
}

// Método para liberar la lista
void doublyLinkedList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current; // Libera la memoria del nodo actual
        current = nextNode; // Avanza al siguiente nodo
    }
    // Establece los punteros de cabeza y cola a nullptr para indicar que la lista está vacía
    head = nullptr;
    tail = nullptr;
}


// Método para obtener la cantidad de nodos en la lista
int doublyLinkedList::getNodeCount() const {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}



