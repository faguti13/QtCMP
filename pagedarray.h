#ifndef PAGEDARRAY_H
#define PAGEDARRAY_H

#include "Node.h"
#include <fstream>
#include <iostream>

class PagedArray
{
public:
    PagedArray(int pageSize, const std::string& swapFilePath);
    ~PagedArray();

    void add(const Node& newNode);
    void remove(int index);
    Node getByIndex(int index);

private:
    struct ListNode
    {
        Node node;
        ListNode* next;
        ListNode* prev;

        ListNode(const Node& n)
            : node(n)
            , next(nullptr)
            , prev(nullptr)
        {}
    };

    void writeToSwap(const Node& node, std::streampos position);
    void readFromSwap(Node& node, std::streampos position);
    void updatePagedArray();

    int pageSize;
    int bytesPerNode;
    ListNode* head;
    ListNode* tail;
    std::string swapFilePath;
};

#endif // PAGEDARRAY_H
