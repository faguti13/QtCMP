#include <iostream>

using namespace std;

class NodoC {
public:
    int dato;
    NodoC* nextC;

    // Constructor
    NodoC(int _dato) : dato(_dato), nextC(nullptr) {}
};

class ListaCircular {
private:
    NodoC* headC;

public:
    // Constructor
    ListaCircular() : headC(nullptr) {}

    // Destructor
    ~ListaCircular() {
        if (headC != nullptr) {
            NodoC* current = headC;
            NodoC* next;
            do {
                next = current->nextC;
                delete current;
                current = next;
            } while (current != headC);
        }
    }

    // Método para agregar un elemento al final de la lista
    void agregarAlFinal(int dato) {
        NodoC* newNode = new NodoC(dato);
        if (headC == nullptr) {
            headC = newNode;
            headC->nextC = headC;
        } else {
            NodoC* temp = headC;
            while (temp->nextC != headC) {
                temp = temp->nextC;
            }
            temp->nextC = newNode;
            newNode->nextC = headC;
        }
    }

    // Método para mostrar los elementos de la lista
    void mostrarLista() {
        if (headC != nullptr) {
            NodoC* temp = headC;
            do {
                cout << temp->dato << " ";
                temp = temp->nextC;
            } while (temp != headC);
            cout << endl;
        } else {
            cout << "La lista está vacía." << endl;
        }
    }
};

int main() {
    ListaCircular lista;

    lista.agregarAlFinal(1);
    lista.agregarAlFinal(2);
    lista.agregarAlFinal(3);
    lista.agregarAlFinal(4);

    cout << "Elementos de la lista circular: ";
    lista.mostrarLista();

    return 0;
}
