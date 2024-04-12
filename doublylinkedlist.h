#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <string>
#include "Node.h"

// Declaración de la clase doublyLinkedList
class doublyLinkedList
{
public:
    doublyLinkedList();

    Node* head;
    Node* tail;

    // Método para insertar al final de la lista
    void insertEnd(const std::string& title, const std::string& artist, const std::string& album, const std::string& genre,
                   const std::string& reference, int upVotes, int downVotes);

    // Método para imprimir toda la información de los nodos
    void printForward();

    // Método para obtener el puntero al primer nodo (head)
    Node* getHead() const;

    // Método para obtener un puntero a la lista doblemente enlazada creada
    doublyLinkedList* getPointerToDoublyLinkedList();

    Node** getArrayList(Node*);

    Node** getRandomArrayList(Node*);

    // Método para obtener los punteros a los nodos de la lista enlazada en las posiciones dadas
    std::vector<Node*> getNodesAtIndices(const std::vector<int>& indices, const doublyLinkedList& principalLinkedList) const;

    void clear();

    int getNodeCount() const;
};

#endif // DOUBLYLINKEDLIST_H
