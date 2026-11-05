#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T>
class BSNode {
    public:
        // Atributos públicos
        T elem;               // elemento guardado en el nodo
        BSNode<T>* left;      // puntero al sucesor izquierdo
        BSNode<T>* right;     // puntero al sucesor derecho

        // Constructor: por defecto los hijos son nulos
        BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr)
            : elem(elem), left(left), right(right) {}

        // Imprime el nodo (solo el elemento)
        friend std::ostream& operator<<(std::ostream& out, const BSNode<T>& bsn) {
            out << bsn.elem;
            return out;
        }
};

#endif
