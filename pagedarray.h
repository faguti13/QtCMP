#ifndef PAGEDARRAY_H
#define PAGEDARRAY_H

#include "Node.h"
#include <iostream>
class PagedArray {
public:
    PagedArray(int pageSize, int maxNodes, const std::string& swapFilePath);
    ~PagedArray();

    void add(const Node& newNode);
    void remove(int index);
    void writeToSwap(const Node& node, std::streampos position);
    void readFromSwap(Node& node, std::streampos position);
    int search(const Node& targetNode);
    Node getByIndex(int index);

private:
    void updatePagedArray();

    struct ListNode {
        Node node;
        ListNode* next;

        ListNode(const Node& n) : node(n), next(nullptr) {}
    };

    int pageSize;
    int maxNodes;
    int bytesPerNode;
    Node* array;
    int usedNodesCount;  // Contador de nodos utilizados
    ListNode* accessOrderHead;  // Puntero al inicio de la lista enlazada de orden de acceso
    std::string swapFilePath;

};

#endif // PAGEDARRAY_H
