#ifndef NODE_H
#define NODE_H

#include <string>
#include <QMetaType>


struct Node { //Estructura del nodo (def el contenido de cada uno)
    std::string title;
    std::string artist;
    std::string album;
    std::string genre;
    std::string reference;
    int upVotes;
    int downVotes;
    int value;
    int accessTime;  // Nuevo campo para el tiempo de acceso


    Node* prev;
    Node* next;

    Node(const std::string& t, const std::string& a, const std::string& al, const std::string& g,const std::string& r, int uV, int dV)
        : title(t), artist(a), album(al), genre(g), reference(r), upVotes(uV), downVotes(dV), prev(nullptr), next(nullptr) {}
    Node() = default;

    bool operator==(const Node& other) const {
        return value == other.value;
    }
};

Q_DECLARE_METATYPE(Node*)  // Registrar el tipo Node*

#endif // NODE_H
